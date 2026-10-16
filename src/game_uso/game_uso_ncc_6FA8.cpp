/* IDO 7.1 NCC (C++) donor for game_uso_func_00006FA8 (0x1FC / 127 words).
 *
 * Picks the closer of two 0xA374 lookups (handles from D_807FEB60+0x570 /
 * D_807FEB64+0x574) to s0->w->pos: returns 10 if the first is closer,
 * 11 otherwise, 0 if 0x7A98 >= 0 or either lookup failed.
 *
 * edg / frame facts this body depends on (cfe and the earlier NCC drafts
 * capped at 123/127 words):
 *  - `d` / `e` are named Vec3 locals assigned inside the one compare
 *    expression through the implicit operator= (r -> ret -> d hops).
 *  - `w` is a named reference used by the first subtraction only: it is
 *    the 4-byte named slot above d.
 *  - set() returns void. The first subtraction goes through an inline
 *    member with a named `const Vec3 &u = *this;` local: that nested-block
 *    slot sits between the two stages and lifts stage 1 by 8 bytes while
 *    the second stage keeps its gap above r2 (a `Vec3 &set()` return temp
 *    lands below r2 instead).
 * Spliced into game_uso.c.o via REPLACE_FUNC_BODY
 * (docs/MATCHING_WORKFLOW.md#game-uso-ncc-cplusplus-donor-recipe). Every
 * symbol is extern "C". */
struct Vec3 {
    float x, y, z;
    Vec3() {}
    void set(float a, float b, float c) { x = a; y = b; z = c; }
    Vec3(float a, float b, float c) { set(a, b, c); }
    Vec3 operator-(const Vec3 &v) const { return Vec3(x - v.x, y - v.y, z - v.z); }
    Vec3 to(const Vec3 &v) const { const Vec3 &u = *this; return Vec3(u.x - v.x, u.y - v.y, u.z - v.z); }
    float lenSq() const { return x * x + y * y + z * z; }
};
struct Handle { int id; };
struct Obj { char pad[0x30]; Vec3 pos; };
struct W { char pad0[0xB4]; Vec3 pos; };
struct Self { char pad0[0x30]; W *w; };
extern "C" {
extern char game_uso_D_807FEB60;
extern char game_uso_D_807FEB64;
float game_uso_func_00007A98(Self *);
Obj *game_uso_func_0000A374(Self *, Handle, Vec3 *);
}
extern "C" int game_uso_func_00006FA8(Self *s0) {
    int result = 0;
    if (game_uso_func_00007A98(s0) < 0.0f) {
        Handle h1;
        Handle h2;
        Obj *a;
        Obj *b;
        h1.id = (*(Handle **)(&game_uso_D_807FEB60 + 0x570))->id;
        a = game_uso_func_0000A374(s0, h1, &s0->w->pos);
        h2.id = (*(Handle **)(&game_uso_D_807FEB64 + 0x574))->id;
        b = game_uso_func_0000A374(s0, h2, &s0->w->pos);
        if (a != 0 && b != 0) {
            Vec3 &w = s0->w->pos;
            Vec3 d, e;
            if ((d = a->pos.to(w)).lenSq() < (e = b->pos - s0->w->pos).lenSq()) {
                result = 10;
            } else {
                result = 11;
            }
        }
    }
    return result;
}
