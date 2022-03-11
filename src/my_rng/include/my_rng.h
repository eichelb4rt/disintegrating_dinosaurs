#ifndef RNG_H_
#define RNG_H_

#include <math.h>
#include <time.h>
#include <cstdint>

#define TPI 6.283185307179586231996

// we only use this for seeding
inline uint64_t randvax(uint64_t& seed) {
    return (uint64_t) ((69069 * (uint64_t) seed + 1) % 4294967296);
}

// xoroshiro
inline uint64_t rotl(const uint64_t x, int k) {
    return (x << k) | (x >> (64 - k)); // rotate
}

inline uint64_t xoroshiro128plus(uint64_t& s0, uint64_t& s1) {
    s1 ^= s0; // modify s1
    s0 = rotl(s0, 24) ^ s1 ^ (s1 << 16); // modify s0
    s1 = rotl(s1, 37); // modify s1
    return s0 + s1;
}

// generates random doubles in [0,1)
inline double dxorshift128plus(uint64_t& s0, uint64_t& s1) {
    uint64_t n = (xoroshiro128plus(s0, s1) >> 12) | 0x3FF0000000000000;
    return *(double*) &n - 1.0;
}

// normal distribution -> z1, z2 (just instantly get 2 numbers)
inline void norm_polar(uint64_t& s0, uint64_t& s1, double& z0, double& z1) {
    double m, u1, u2;
    u1 = dxorshift128plus(s0, s1);
    u2 = dxorshift128plus(s0, s1);
    m = sqrt(-2.0 * log(u1));
    z0 = m * cos(TPI * u2);
    z1 = m * sin(TPI * u2);
}

// convenient way to pass seeds to functions
typedef struct {
    uint64_t s0;
    uint64_t s1;
} random_seeds;

// random number following standard gaussian
inline double random_normal(random_seeds& seeds) {
    static bool number_ready = false;
    double z0;
    static double z1;

    if (number_ready) {
        number_ready = false;
        return z1;
    }

    norm_polar(seeds.s0, seeds.s1, z0, z1);
    number_ready = true;
    return z0;
}

// random index
inline int random_index(random_seeds& seeds, int& length) {
    return (int) length * dxorshift128plus(seeds.s0, seeds.s1);
}

// seed our rng thingy
inline void seed(random_seeds& seeds) {
    time_t t = time(NULL);
    seeds.s0 = *(uint64_t*) &t;
    seeds.s1 = randvax(seeds.s0);
}

#endif // RNG_H_