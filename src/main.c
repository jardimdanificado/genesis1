#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAP_WIDTH 16
#define MAP_HEIGHT 16

#define ROOMS (MAP_WIDTH*MAP_HEIGHT)

#define ROOM_WIDTH 16
#define ROOM_HEIGHT 16

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
    int currentRoom;
    float quality;
    float weight;    
} Item;

typedef struct 
{
    Vector2 globalPosition;
    byte map[ROOM_WIDTH][ROOM_HEIGHT];
} Room;

int main()
{
    Room rooms[ROOMS];
    for(int i = 0; i < ROOMS; i++)
    {
        rooms[i].globalPosition = Vector2(i % MAP_WIDTH, i / MAP_HEIGHT);
        for (int j = 0; j < ROOM_WIDTH; j++)
        {
            for (int k = 0; k < ROOM_HEIGHT; k++)
            {
                rooms[i].map[j][k] = 0;
            }
        }
    }
    return 0;
}