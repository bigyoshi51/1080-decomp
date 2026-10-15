/* IDO 7.1 NCC (C++) donor for game_uso_func_000071E0 (0x244 / 145 words).
 *
 * Sibling of game_uso_func_00006A30 (same Vec3 / derived-class XZ shapes; see
 * game_uso_ncc_6A30.cpp). Flag-4 early call to A7F8; speed >= 30 counter
 * (reset state 0x64 and the counter at 30); state 3 runs the stage:
 * va = w->pos + w->vel * k, 7ACC / 7C1C, XZ pt(w->0x3C8), yaw = 3ED4,
 * self->0x3C = -yaw * 6, flag 256 when !0x6C && w->0x938, then 7538.
 *
 * C++ / edg facts this body depends on (the cfe wrap capped at 83.6%):
 *  - The counter is an inline member taking the incremented value
 *    (`tick(f54 + 1)`): the parameter colours a1 (a named local gets v0)
 *    and its function-level argument temps take the two top frame slots.
 *    The XZ constructor's reference parameter then reuses the top pointer
 *    slot as its spill home (sp+168).
 *  - The stage is a nested block, so its binding temp / flag / va / ...
 *    homes sit below those two function-level slots.
 *  - The scaled yaw store is its own block with named `k` / `fr`: nested
 *    block locals are placed after every temp of the parent, giving the
 *    target's 176-byte frame with no code change.
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
void game_uso_func_0000A7F8(Self *);
}
struct Self {
    char pad0[0x30]; W *w;   /* 0x30 */
    char pad34[0x3C - 0x34]; float f3C;
    char pad40[0x54 - 0x40]; int f54; char pad58[0x64 - 0x58]; int f64; int f68; int f6C; int f70;
    char pad74[0x80 - 0x74]; int f80;
    char pad84[0xA8 - 0x84]; float fA8; float fAC; float fB0;
    void tick(int c) {
        f54 = c;
        if (c >= 30) {
            f64 = 0;
            f54 = 0;
        }
    }
};
extern "C" void game_uso_func_000071E0(Self *s0) {
    if (s0->f68 & 4) {
        game_uso_func_0000A7F8(s0);
        return;
    }
    if (30.0f <= s0->w->speed) {
        s0->tick(s0->f54 + 1);
    } else {
        s0->f54 = 0;
    }
    if (s0->f64 != 3) return;
    {
        int flag = 0;
        Vec3 va = s0->w->pos;
        int r1;
        int v94;
        va += s0->w->vel * s0->fA8;
        r1 = game_uso_func_00007ACC(s0, &v94, &va, 0);
        if (r1 == 0) return;
        Vec3 rv = game_uso_func_00007C1C(s0, r1, v94, &va, 0);
        XZ pt(s0->w->at);
        float yaw = game_uso_func_00003ED4(&pt, &rv, 0);
        {
            float k = 6.0f;
            float fr = -yaw * k;
            s0->f3C = fr;
        }
        if (s0->f6C == 0) {
            if (s0->w->f938 != 0) flag = 256;
        }
        game_uso_func_00007538(s0, flag);
    }
}
