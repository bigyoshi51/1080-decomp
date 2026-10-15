/* IDO 7.1 NCC (C++) donor for game_uso_func_00006A30 (0x2C0 / 176 words).
 *
 * Per-frame steer update: va = w->pos; va += w->vel * k; 7ACC(self, &n, &va)
 * (return without 7538 on null); rv = 7C1C(...) (Vec3 by value); pt = the
 * XZ projection of w->0x3C8; yaw = 3ED4(&pt, &rv, 0); self->0x3C =
 * -yaw * (1 + speed / 0xB0) * 0xAC / w->0x6F8.max; flag 16 / 8; then the
 * shared 0x938 / 0xA54 / 0x70 timer tail and 7538(self, flag).
 *
 * C++ / edg facts this body depends on (the cfe wrap capped at 93.2%):
 *  - Vec3 is a value class. operator* returns by value (r -> return temp ->
 *    += binding temp word copies); += takes const Vec3 & (float adds).
 *  - pt is a DERIVED class whose constructor forwards to the base
 *    Vec3(a, b, c). edg's cfront-style constructor protocol emits
 *    `if (this == 0 && (this = operator new(12)) == 0) skip`; that is the
 *    "bnez on a stack address + 055750(0xC)" block. The stores go through
 *    `this` only with a base-initialiser (a body-assigned derived ctor
 *    folds them onto &pt). The class operator new (inline, in Vec3) forwards
 *    to the import, so the jal reloc is game_uso_func_055750 and not
 *    __nw__FUi.
 *  - No named `w` pointer: every access is s0->w->..., and uopt's PRE puts
 *    the tail's load in each branch (the target's per-branch `lw v1,48(s0)`).
 *    A function-scope named w adds an `or v0,v1` copy. The 0x6F8 accessor
 *    on the load expression s0->w->lim keeps the `addiu v0,v1,0x6F8` base.
 *  - Declaration order va, r1, v94, rv, pt, yaw fixes the homes (r1 before
 *    v94 although v94 is written first).
 *  - Frame 184: the tail declares `W *w = s0->w;` in BOTH timer arms (two
 *    slots, no code change). With one or none the frame is 176.
 * Spliced into game_uso.c.o via REPLACE_FUNC_BODY
 * (docs/MATCHING_WORKFLOW.md#game-uso-ncc-cplusplus-donor-recipe). Every
 * symbol is extern "C". */
extern "C" void *game_uso_func_055750(unsigned);
struct Vec3 {
    void *operator new(unsigned n) { return game_uso_func_055750(n); }
    float x, y, z;
    Vec3() {}
    void set(float a, float b, float c) { x = a; y = b; z = c; }
    Vec3(float a, float b, float c) { set(a, b, c); }
    Vec3 &operator=(Vec3 v) { x = v.x; y = v.y; z = v.z; return *this; }
    Vec3 &operator+=(const Vec3 &v) { x = x + v.x; y = y + v.y; z = z + v.z; return *this; }
    Vec3 operator*(float s) const { return Vec3(x * s, y * s, z * s); }
};
struct XZ : Vec3 {
    XZ(const Vec3 &v) : Vec3(v.x, 0.0f, v.z) {}
};
struct Lim { char pad[0x10]; float max; float getMax() const { return max; } };
struct W {
    char pad0[0xB4]; Vec3 pos;           /* 0xB4 */
    char padC0[0x318 - 0xC0]; Vec3 vel;  /* 0x318 */
    char pad324[0x348 - 0x324]; float speed; /* 0x348 */
    char pad34C[0x3C8 - 0x34C]; Vec3 at; /* 0x3C8 */
    char pad3D4[0x6F8 - 0x3D4]; Lim lim; /* 0x6F8 */
    char pad70C[0x840 - 0x70C]; int snd; /* 0x840 */
    char pad844[0x938 - 0x844]; int f938;
    char pad93C[0xA54 - 0x93C]; int fA54;
};
struct Self;
extern "C" {
int game_uso_func_00007ACC(Self *, int *, Vec3 *, int);
Vec3 game_uso_func_00007C1C(Self *, int, int, Vec3 *, int);
float game_uso_func_00003ED4(Vec3 *, Vec3 *, int);
void game_uso_func_000110A4(int);
void game_uso_func_00007538(Self *, int);
}
struct Self {
    char pad0[0x30]; W *w;   /* 0x30 */
    char pad34[0x3C - 0x34]; float f3C;
    char pad40[0x6C - 0x40]; int f6C; int f70;
    char pad74[0x80 - 0x74]; int f80;
    char pad84[0xA8 - 0x84]; float fA8; float fAC; float fB0;
};
extern "C" void game_uso_func_00006A30(Self *s0) {
    int flag = 0;
    if (s0->f80 != 0) {
        Vec3 va = s0->w->pos;
        int r1;
        int v94;
        va += s0->w->vel * s0->fA8;
        r1 = game_uso_func_00007ACC(s0, &v94, &va, 0);
        if (r1 == 0) return;
        Vec3 rv = game_uso_func_00007C1C(s0, r1, v94, &va, 0);
        XZ pt(s0->w->at);
        float yaw = game_uso_func_00003ED4(&pt, &rv, 0);
        s0->f3C = -yaw * (1.0f + s0->w->speed / s0->fB0) * s0->fAC / s0->w->lim.getMax();
        if (s0->f6C == 0) {
            if (v94 == 0) flag = 16;
            else if (80.0f <= s0->w->speed) flag = 8;
        }
    } else {
        if (s0->f6C == 0) flag = 16;
    }
    if (s0->w->f938 != 0 && s0->w->fA54 != 0) {
        int c = s0->f70;
        if (c < 60) {
            W *w = s0->w;
            if (w->speed <= 30.0f) {
                game_uso_func_000110A4(w->snd);
                s0->f70 = 61;
            } else {
                s0->f70 = c + 1;
            }
        } else if (c == 60) {
            W *w = s0->w;
            game_uso_func_000110A4(w->snd);
            s0->f70 = 61;
        }
    }
    game_uso_func_00007538(s0, flag);
}
