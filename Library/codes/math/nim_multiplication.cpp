#include <bits/stdc++.h>

typedef unsigned short u16;
typedef unsigned int u32;
typedef unsigned long long u64;

namespace nimbers {
    constexpr u32 n2f[16] = {0x0001u, 0x071cu, 0x6bd1u, 0x1224u, 0x6ba8u, 0x1333u, 0x1553u, 0x0007u, 0x071eu, 0x0925u, 0xc586u, 0x5dbdu, 0xc463u, 0x5efdu, 0x2aa1u, 0x155au},
                  f2n[16] = {0x0001u, 0x0102u, 0x0183u, 0x8041u, 0x015cu, 0x5f24u, 0xde2cu, 0x957eu, 0x01f4u, 0xf7d8u, 0x76b0u, 0x5d52u, 0xa977u, 0x20d1u, 0xc1a4u, 0x271fu};
    inline u32 nimber2field(u32 x) {u32 y = 0; for (; x; x &= x - 1) y ^= n2f[__builtin_ctz(x)]; return y;}
    inline u32 field2nimber(u32 x) {u32 y = 0; for (; x; x &= x - 1) y ^= f2n[__builtin_ctz(x)]; return y;}
    inline u32 __builtin_double(u32 x) {return x << 1 ^ (x < 32768 ? 0 : 0x16babu);}

    u16 ln[65536], exp[196605], *Hexp = exp + 62133, *H2exp = exp + 58731;

    inline void init() {
        int i;
        for (*exp = i = 1; i < 65535; ++i) exp[i] = __builtin_double(exp[i - 1]);
        for (i = 1; i < 65535; ++i) exp[i] = field2nimber(exp[i]), ln[exp[i]] = i;
        memcpy(exp + 65535, exp, 131070);
        memcpy(exp + 131070, exp, 131070);
    }

    inline u16 product(u16 A, u16 B) {return A && B ? exp[ln[A] + ln[B]] : 0;}
    inline u16 H(u16 A) {return A ? Hexp[ln[A]] : 0;}
    inline u16 H2(u16 A) {return A ? H2exp[ln[A]] : 0;}
    inline u16 Hproduct(u16 A, u16 B) {return A && B ? Hexp[ln[A] + ln[B]] : 0;}

    inline u32 product(u32 A, u32 B) {
        u16 a = A & 65535, b = B & 65535, c = A >> 16, d = B >> 16, e = product(a, b);
        return u32(product(u16(a ^ c), u16(b ^ d)) ^ e) << 16 | (Hproduct(c, d) ^ e);
    }

    inline u32 H(u32 A) {
        u16 a = A & 65535, b = A >> 16;
        return H(u16(a ^ b)) << 16 | H2(b);
    }

    inline u64 product(u64 A, u64 B) {
        u32 a = A & UINT_MAX, b = B & UINT_MAX, c = A >> 32, d = B >> 32, e = product(a, b);
        return u64(product(a ^ c, b ^ d) ^ e) << 32 | (H(product(c, d)) ^ e);
    }
}
