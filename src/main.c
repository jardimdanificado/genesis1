#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define ROOMS 256

#define ROWSGLOBAL (int)ceil(sqrt(ROOMS))
#define COLSGLOBAL (int)ceil(sqrt(ROOMS))

#define ROWSLOCAL 64
#define COLSLOCAL 64

typedef unsigned int byte;

typedef struct 
{
    int x;
    int y;
} Vector2;
#define Vector2(x, y) ((Vector2) {x, y})

typedef struct 
{
    int x;
    int y;
    int z;
} Vector3;
#define Vector3(x, y, z) ((Vector3) {x, y, z})

typedef struct 
{
    Vector2 positionLocal;
    Vector2 positionGlobal;
    float quality;
    float weight;    
} Item;

typedef struct 
{
    Vector2 globalPosition;
    byte map[ROWSLOCAL][COLSLOCAL];
} Room;

int main(int argc, char *argv[]) 
{
    Room rooms[ROOMS]; 
    for(int i = 0; i < ROOMS; i++)
    {
        rooms[i].globalPosition = Vector2(i % ROWSGLOBAL, i / ROWSGLOBAL);
        for (int j = 0; j < ROWSLOCAL; j++)
        {
            for (int k = 0; k < COLSLOCAL; k++)
            {
                rooms[i].map[j][k] = 0;
            }
        }
    }
    return 0;
}