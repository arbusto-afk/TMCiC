//
// Created by Ignacio on 15/10/2024.
//

#include "ColliderDefs.h"

const collider_t collider_BlockCollider = {
        {{1, 1, 1, 0, 0, 0}},
        1,
        DIRECTION_NONE,
        true,
        false,
        false
};
const collider_t collider_EmptyCollider = {
        {{0, 0, 0, 0, 0, 0
         }},
         0,
         DIRECTION_NONE,
         false,
         false,
         false
};

//according to: https://www.mcpk.wiki/wiki/Blocks

    const collider_t collider_Wall4Sided = {
            {{1,1,1.5}},
            1,
            DIRECTION_NONE,
            false,
            false,
            false
    };
const collider_t collider_SoulSand = {
        {{1,1,0.875}},
        1,
        DIRECTION_NONE,
        false,
        false,
        false
};
const collider_t collider_EndPortalFrame = {
        {{1,1, 0.8125}},
        1,
        DIRECTION_NONE,
        false,
        false,
        false
};
const collider_t collider_EnchantmentTable = {
        {{1,1, 0.75}},
        1,
        DIRECTION_NONE,
        false,
        false,
        false
};
const collider_t collider_Bed = {
        {{1,1,0.5625}},
        1,
        DIRECTION_NONE,
        false,
        false,
        false
};
const collider_t collider_slabTop = {
        {{1,1,0.5}},
        1,
        DIRECTION_NONE,
        false,
        true,
        false
};
const collider_t collider_slabBot = {
        {{1,1,0.5, 0,0,0.5}},
        1,
        DIRECTION_NONE,
        false,
        false,
        true
};
const collider_t collider_dayLightSensor = {
        {{1,1,0.375}},
        1,
        DIRECTION_NONE,
        false,
        false,
        false
};

const collider_t collider_floorTrapDoor = {
        {1,1,0.1875},
        1,
        DIRECTION_NONE,
        false,
        false,
        false
};

const collider_t collider_topTrapDoor = {
        {1,1,0.1875, 0 ,0, 1 - 0.1875},
        1,
        DIRECTION_NONE,
        false,
        false,
        false
};
const collider_t collider_Repeater = {
        {{1,1,0.125}},
        1,
        DIRECTION_NONE,
        false,
        false,
        false
};
const collider_t collider_Carpet = {
        {{1,1,0.0625}},
        1,
        DIRECTION_NONE,
        false,
        false,
        false
};

const collider_t collider_LilyPad = {
        {{1,1,0.015625}},
        1,
        DIRECTION_NONE,
        false,
        false,
        false
};
//TODO
const collider_t collider_snow;

/*
 * orientables todos mirando al este
 */


/* east
 *  |
 * -*    south
 *  |
 *  west
 */
const collider_t collider_Wall3Side_Orientable = {
        {{1, 0.75, 1.5}},
        1,
        DIRECTION_EAST,
        false,
        false,
        false

};

const collider_t collider_Anvil_Orientable = {
        {{1,0.75, 1,0,0.125,0}},
        1,
        DIRECTION_EAST,
        false,
        false,
        false
};

const collider_t collider_PistonBase_Orientable = {
        {{1, 0.75, 1}},
        1,
        DIRECTION_EAST,
        false,
        false,
        false
};
const collider_t collider_Wall2SideOpposite = {
        {{1,0.375, 1}},
        1,
        DIRECTION_EAST,
        false,
        false,
        false
};
const collider_t collider_Fence2Side = {
        {{1,0.25,1.5}},
        1,
        DIRECTION_EAST,
        false,
        false,
        false
};

const collider_t collider_Fencegate = {
        {{1,0.25,1.5}},
        1,
        DIRECTION_EAST,
        false,
        false,
        false
};
const collider_t collider_VerticalTrapdoor = {
        {{1,0.1875,1,}},
        1,
        DIRECTION_EAST,
        false,
        false,
        false,
};
const collider_t collider_Door = {
        {{1,0.1875,1}},
        1,
        DIRECTION_EAST,
        false,
        false,
        false
};
const collider_t collider_Ladder = {
        {{1,0.125,1}},
        1,
        DIRECTION_EAST,
        false,
        false,
        false
};
const collider_t collider_GlassPane2Side = {
        {{1, 0.125, 1}},
        1,
        DIRECTION_EAST,
        false,
        false,
        false
};

const collider_t collider_LongChest = {
        {{0.9375, 0.875, 0.875, 0.0625, 0.0625, 0.0625}},
        1,
        DIRECTION_EAST,
        false,
        false,
        false
};

const collider_t collider_DragonEgg = {
        {{0.875, 0.875, 1, 0.125, 0.125, 0}},
        1,
        DIRECTION_NONE,
        false,
        false,
        false
};
const collider_t collider_Cactus = {
        {{0.875, 0.875, 1, 0.125, 0.125, 0}},
        1,
        DIRECTION_NONE,
        false,
        false,
        false
};

const collider_t collider_Chest = {
        {{0.875, 0.875, 0.875, 0.125, 0.125, 0}},
        1,
        DIRECTION_NONE,
        false,
        false,
        false
};
//TODO
const collider_t cake;

const collider_t collider_Wall2Side = {
        {{0.75,0.75,1.5, }},
        1,
        DIRECTION_EAST,
        false,
        false,
        false
};

const collider_t collider_Wall1Side = {
        {{0.75,0.5,1.5, 0, 0.25 }},
        1,
        DIRECTION_EAST,
        false,
        false,
        false,
};
const collider_t collider_Fence1Side = {
        {{0.625, 0.25, 1.5, 0, 0.375}},
        1,
        DIRECTION_EAST,
        false,
        false,
        false
};
const collider_t collider_WallDefault = {
        {{0.5,0.5,1.5, 0.25,0.25,0}},
        1,
        DIRECTION_EAST,
        false,
        false,
        false
};
const collider_t collider_HeadWalled = {
        {{0.5,0.5,0.5,0,0.25,0.25}},
        1,
        DIRECTION_EAST,
        false,
        false,
        false
};
const collider_t collider_HeadDefault = {
        {{0.5,0.5,0.5,0.25,0.25}},
        1,
        DIRECTION_NONE,
        false,
        false,
        false
};
const collider_t collider_Pane1Side = {
        {{0.5, 0.125, 1, 0, (1 - 0.125) / 2}},
        1,
        DIRECTION_EAST,
        false,
        false,
        false
};
const collider_t collider_FenceDefault = {

};

//Faltan cocoas y maceta