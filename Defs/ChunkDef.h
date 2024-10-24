    //
    // Created by Ignacio on 9/22/2024.
    //

    #ifndef MCBC6_CHUNKDEF_H
    #define MCBC6_CHUNKDEF_H

    #define CHUNKSECTION_DIM 16
    #define CHUNKSECTION_BLOCKCOUNT (CHUNKSECTION_DIM * CHUNKSECTION_DIM * CHUNKSECTION_DIM)

    typedef struct {
        unsigned int globalId;
        int longIndex;
        int bitIndex;
    } TBlock;

    typedef struct {
        TBlock blockMatrix[CHUNKSECTION_DIM][CHUNKSECTION_DIM][CHUNKSECTION_DIM];
    //    TBlock *palette; //unused
    //    int paletteDim; //unsued
    } TChunkSection;

    typedef struct {
        int x;
        int z;

        TChunkSection * sectionArr;
        int sectionArrDim; //chunk height in sections
    //    TBlock *palette; //unused
     //   int paletteDim; //unused
    } TChunk;


    #endif //MCBC6_CHUNKDEF_H
