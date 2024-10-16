//
// Created by Ignacio on 30/9/2024.
//

#include "internal_std_getChunk.h"

TChunk * internal_std_getChunk(int x, int z, client *c) {
    // Calculate the hash key for the given chunk coordinates
    int hashKey = hash2d(x, z);

    // Traverse the hash list for the given hash key
    TChunkHashNode *current = c->chunkHashVec[hashKey];

    // Loop through the linked list to find the correct chunk
    while (current != NULL) {
        // Assuming the chunk structure has chunkX and chunkZ as the coordinates
        if (current->chunk->x == x && current->chunk->x == z) {
            return current->chunk;  // Found the chunk, return it
        }
        current = current->tail;  // Move to the next node in the list
    }

    // If no chunk was found, return NULL
    return NULL;
}