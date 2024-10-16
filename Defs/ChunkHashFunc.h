//
// Created by Ignacio on 9/22/2024.
//

#ifndef MCBC6_CHUNKHASHFUNC_H
#define MCBC6_CHUNKHASHFUNC_H

#include <stdint.h>
#include <stdlib.h>
#include "TPoint2d.h"

size_t hash2d(int x, int y);

size_t hash2d_pt(TPoint2d p);

#endif //MCBC6_CHUNKHASHFUNC_H
