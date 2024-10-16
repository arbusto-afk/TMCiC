//
// Created by Ignacio on 14/10/2024.
//

#include "isInSortedArr.h"


int isInSortedArr(const int * v, int dim, int n)
{
    for(int i = 0; i < dim; i++)
    {
        if(v[i] > n)
            return -1;
        if(v[i] == n)
            return i;
    }
    return -1;
}