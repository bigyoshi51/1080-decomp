import re, sys

def lift_fields(body):
    """Convert expr->unkN to FW(expr,0xN) with balanced-paren backward walk."""
    # fn-ptr calls first: IDENT->unkN(  ->  (*(void(**)())((char*)IDENT+0xN))(
    body=re.sub(r'([a-zA-Z_]\w*)->unk([0-9A-Fa-f]+)\(',
                r'(*(void (**)())((char *)\1 + 0x\2))(', body)
    while True:
        m=re.search(r'->unk([0-9A-Fa-f]+)', body)
        if not m: break
        off=m.group(1); i=m.start()
        # walk back to find the primary ending at i
        j=i-1
        if body[j]==')':
            depth=1; j-=1
            while j>=0 and depth:
                if body[j]==')':depth+=1
                elif body[j]=='(':depth-=1
                j-=1
            # include preceding identifier (e.g. FW)
            while j>=0 and (body[j].isalnum() or body[j]=='_'): j-=1
            prim_start=j+1
        else:
            while j>=0 and (body[j].isalnum() or body[j]=='_'): j-=1
            prim_start=j+1
        prim=body[prim_start:i]
        body=body[:prim_start]+f'FW({prim}, 0x{off})'+body[m.end():]
    return body

if __name__=='__main__':
    print(lift_fields(open(sys.argv[1]).read()))

# Big-swing decode workflow (see project_1080_big_swing_strategy memo):
#  1. python3 scripts/disasm-func.py <fn> --m2c > /tmp/f.c
#  2. lift body via lift_fields() (chained X->a->b->c -> nested FW(); fn-ptr
#     calls cast); wrap #ifdef NON_MATCHING ... #else INCLUDE_ASM ... #endif
#  3. #define FW(p,o) (*(int*)((char*)(p)+(o)))  for word field access
#  4. add  extern int <callee>();  (K&R) for each placeholder/varying-arg callee;
#     make a varying-arg fn-ptr param K&R too:  T (*arg0)()
#  5. declare any m2c-referenced-but-undeclared spXX (buffer scalars) as int;
#     fix m2c-mistyped temps (deref'd -> pointer; subscripted -> array)
#  Best when the fn has NO get-or-alloc iterators (m2c renders those messily).
