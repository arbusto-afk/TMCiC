//
// Created by Ignacio on 14/10/2024.
//

#include "internal_std_getClientChunk.h"


TPoint2d internal_std_getClientChunk(client * c){
 return (TPoint2d){ floor((double)c->x/16), floor((double)c->z/16)};
}