//
// Created by Ignacio on 15/10/2024.
//

#ifndef MCBC6_COLLIDERDEFS_H
#define MCBC6_COLLIDERDEFS_H

#include <stdbool.h>

#define MAXCOLLIDERCOUNT 5
//Directions: 0, x+, z-, x-, z+
enum ORIENTABLE_DIRECTIONS {DIRECTION_NONE, DIRECTION_EAST, DIRECTION_NORTH, DIRECTION_WEST, DIRECTION_SOUTH};

typedef struct simpleCollider {
    double xDim;
    double zDim;
    double yDim;
    double xOffset;
    double zOffset;
    double yOffset;
} simpleCollider_t;

typedef struct collider {
    simpleCollider_t simpleColliderArr[MAXCOLLIDERCOUNT];
    int simpleColliderArrDim;
    int direction;
    int isBlock;
    int isTopSlab;
    int isBotSlab;
} collider_t;

static collider_t blockColliderArr[] = {};
#define blockDefArrDim 1

#endif //MCBC6_COLLIDERDEFS_H
