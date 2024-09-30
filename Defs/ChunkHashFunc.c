//
// Created by Ignacio on 9/22/2024.
//

#include "ChunkHashFunc.h"


size_t hash2d(int x, int z) {
    // Use a prime number to reduce collisions for close-together coordinates
    const size_t prime = 31;

    // Mix x and z values by shifting and combining them
    size_t hash = x;
    hash = prime * hash + z;

    // Further mix the result using XOR and shifts to improve hash distribution
    hash ^= (hash >> 16);

    return hash;
}
