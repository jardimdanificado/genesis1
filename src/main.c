#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAP_WIDTH 16
#define MAP_HEIGHT 16

#define ROOMS (MAP_WIDTH*MAP_HEIGHT)

#define ROOM_WIDTH 16
#define ROOM_HEIGHT 16

#define MAX_ITEMS 16
#define MAX_EQUIPS 8
#define MAX_CREATURES 16

typedef unsigned int byte;

typedef struct 
{
    int x;
    int y;
} Vector2;
#define Vector2(x, y) ((Vector2) {x, y})
const Vector2 Vector2Null;

typedef struct 
{
    int x;
    int y;
    int z;
} Vector3;
#define Vector3(x, y, z) ((Vector3) {x, y, z})
const Vector3 Vector3Null;

typedef struct
{
    int str;//strength
    int agi;//agility
    int con;//constitution
    int intel;//intelligence
    int wis;//wisdom
    int cha;//charisma
    int luck;//luck
} Stats;
#define Stats(str, agi, con, intel, wis, cha, luck) ((Stats) {str, agi, con, intel, wis, cha, luck})
const Stats StatsNull;

typedef struct 
{
    Vector2 positionLocal;
    int currentRoom;
    float quality;
    float weight;
} Item;
#define Item(positionLocal, currentRoom, quality, weight) ((Item) {positionLocal, currentRoom, quality, weight})
const Item ItemNull;

typedef struct 
{
    Vector2 positionLocal;
    int currentRoom;
    float quality;
    float weight;
    Stats stats;
} Equip;
#define Equip(positionLocal, currentRoom, quality, weight, stats) ((Equip) {positionLocal, currentRoom, quality, weight, stats})
const Equip EquipNull;

typedef struct
{
    byte items[16];
    byte locked_items[16];
    byte equips[8];
    byte locked_equips[8];
} Inventory;
#define Inventory(items, locked_items, equips, locked_equips) ((Inventory) {items, locked_items, equips, locked_equips})
#define EmptyInventory (Inventory){{0}, {0}, {1}, {1}}
const Inventory InventoryNull;

typedef struct 
{
    char name[32];
    Vector2 positionLocal;
    int currentRoom;
    float weight;
    Stats stats;
    Inventory inventory;
} Creature;
#define Creature(name,positionLocal, currentRoom, weight, stats) ((Creature) {name,positionLocal, currentRoom, weight, stats, EmptyInventory})
const Creature CreatureNull;

typedef struct
{
    Vector2 globalPosition;
    byte map[ROOM_WIDTH][ROOM_HEIGHT];
} Room;
#define Room(globalPosition, map) ((Room) {globalPosition, map})
const Room RoomNull;

#define isStructNull(struct, type, empty) (memcmp(&struct, &empty, sizeof(type)) == 0)

int main()
{
    Room rooms[ROOMS];
    Creature creatures[MAX_CREATURES];
    creatures[0] = Creature("player",Vector2(0, 0), 0, 0, Stats(10, 10, 10, 10, 10, 10, 10));
    //printf("Player: %s\n", creatures[0].name);
    //printf("Player: %d\n", isStructNull(creatures[2], Creature, CreatureNull));
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