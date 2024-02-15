#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAP_WIDTH 64
#define MAP_HEIGHT 64

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
} Skills;
#define MAX_STAT 77
#define BASE_STAT 7

typedef struct
{
    int health[7];
    int mind;
    int pee;
    int poo;

    int stamina;
} Stats;


#define Skills(str, agi, con, intel, wis, cha, luck) ((Skills) {str, agi, con, intel, wis, cha, luck})
#define SkillsEmpty (Skills) {0, 0, 0, 0, 0, 0, 0}
#define SkillsFull (Skills) {MAX_STAT, MAX_STAT, MAX_STAT, MAX_STAT, MAX_STAT, MAX_STAT, MAX_STAT}
#define SkillsDefault (Skills) {BASE_STAT, BASE_STAT, BASE_STAT, BASE_STAT, BASE_STAT, BASE_STAT, BASE_STAT}
const Skills SkillsNull;

typedef struct 
{
    Vector2 positionLocal;
    int currentRoom;
    float quality;
    float weight;
    Skills skills;
    Stats stats;
} Item;
#define Item(positionLocal, currentRoom, quality, weight) ((Item) {positionLocal, currentRoom, quality, weight})
const Item ItemNull;

typedef struct
{
    byte items[16];
    byte equips[7];
} Inventory;
#define Inventory(items, equips) ((Inventory) {items, equips})
#define EmptyInventory (Inventory){{0}, {0}}
const Inventory InventoryNull;

typedef struct 
{
    char name[32];
    int age;
    Vector2 positionLocal;
    int currentRoom;
    float weight;
    Skills skills;
    Inventory inventory;
    byte diseases[24];
} Creature;
#define Creature(name,positionLocal, currentRoom, weight, skills) ((Creature) {name, 0, positionLocal, currentRoom, weight, skills, EmptyInventory, {0}})
const Creature CreatureNull;

typedef struct
{
    Vector2 globalPosition;
    byte map[ROOM_WIDTH][ROOM_HEIGHT];
} Room;
#define Room(globalPosition, map) ((Room) {globalPosition, map})
const Room RoomNull;

#define isNull(struct, type, empty) (memcmp(&struct, &empty, sizeof(type)) == 0)

enum Tiles
{
    TILE_DOOR,
    TILE_WALL,
    TILE_FLOOR,
    TILE_WATER
};

enum Furniture
{
    FURNITURE_EMPTY,
    FURNITURE_MANUAL_LATRINE,
    FURNITURE_CHAIR
};

enum Items
{
    ITEM_EMPTY,
    ITEM_BUCKET,
    ITEM_XYLOSPONGE
};

//diseases
typedef struct
{
    char name[32];
    byte duration;
    byte stink;
    byte wetness;
    byte viscosity;
    byte amount;
} Disease;

#define DISEASE_E_COLI (Disease) {DISEASE_NAME_E_COLI, duration: 10, stink: 30, wetness: 30, viscosity: 30, amount: 30}
#define DISEASE_SALMONELLA (Disease) {DISEASE_NAME_SALMONELLA, duration: 40, severity: 4, stink: 46, wetness: 35, viscosity: 12, amount: 10}
#define DISEASE_HEPATITIS (Disease) {DISEASE_NAME_HEPATITIS, duration: 100, stink: 50, wetness: 50, viscosity: 50, amount: 50}
#define DISEASE_PLAGUE (Disease) {DISEASE_NAME_PLAGUE, duration: 255, stink: 60, wetness: 60, viscosity: 60, amount: 60}
#define DISEASE_TUBERCULOSIS (Disease) {DISEASE_NAME_TUBERCULOSIS, duration: 500, stink: 22, wetness: 22, viscosity: 22, amount: 22}
#define DISEASE_POLIO (Disease) {DISEASE_NAME_POLIO, duration: 255, stink: 25, wetness: 25, viscosity: 25, amount: 25}
#define DISEASE_LEPROSY (Disease) {DISEASE_NAME_LEPROSY, duration: 50, stink: 11, wetness: 11, viscosity: 11, amount: 11}
#define DISEASE_GONORRHEA (Disease) {DISEASE_NAME_GONORRHEA, duration: 20, stink: 13, wetness: 13, viscosity: 13, amount: 13}
#define DISEASE_SYPHILIS (Disease) {DISEASE_NAME_SYPHILIS, duration: 140, stink: 15, wetness: 15, viscosity: 15, amount: 15}
#define DISEASE_BUBONIC_PLAGUE (Disease) {DISEASE_NAME_BUBONIC_PLAGUE, duration: 40, severity: 70, stink: 25, wetness: 48, viscosity: 17, amount: 17}
#define DISEASE_SMALLPOX (Disease) {DISEASE_NAME_SMALLPOX, duration: 200, stink: 20, wetness: 20, viscosity: 20, amount: 20}
#define DISEASE_MEASLES (Disease) {DISEASE_NAME_MEASLES, duration: 200, stink: 110, wetness: 110, viscosity: 110, amount: 110}
#define DISEASE_MUMPS (Disease) {DISEASE_NAME_MUMPS, duration: 120, stink: 75, wetness: 75, viscosity: 75, amount: 75}
#define DISEASE_RUBELLA (Disease) {DISEASE_NAME_RUBELLA, duration: 255, stink: 90, wetness: 90, viscosity: 90, amount: 90}
#define DISEASE_CHICKENPOX (Disease) {DISEASE_NAME_CHICKENPOX, duration: 199, stink: 130, wetness: 130, viscosity: 130, amount: 130}
#define DISEASE_COLD (Disease) {DISEASE_NAME_COLD, duration: 10, stink: 90, wetness: 90, viscosity: 90, amount: 90}
#define DISEASE_FLU (Disease) {DISEASE_NAME_FLU, duration: 20, stink: 120, wetness: 120, viscosity: 120, amount: 120}
#define DISEASE_PNEUMONIA (Disease) {DISEASE_NAME_PNEUMONIA, duration: 120, stink: 150, wetness: 150, viscosity: 150, amount: 150}
#define DISEASE_TETANUS (Disease) {DISEASE_NAME_TETANUS, duration: 10, stink: 40, wetness: 40, viscosity: 40, amount: 40}
#define DISEASE_DYPHTERIA (Disease) {DISEASE_NAME_DYPHTERIA, duration: 20, stink: 60, wetness: 60, viscosity: 60, amount: 60}
#define DISEASE_WHOOPING_COUGH (Disease) {DISEASE_NAME_WHOOPING_COUGH, duration: 30, stink: 80, wetness: 80, viscosity: 80, amount: 80}
#define DISEASE_MALARIA (Disease) {DISEASE_NAME_MALARIA, duration: 40, stink: 100, wetness: 100, viscosity: 100, amount: 100}
#define DISEASE_DENGUE (Disease) {DISEASE_NAME_DENGUE, duration: 60, stink: 160, wetness: 160, viscosity: 160, amount: 160}
#define DISEASE_ZIKA (Disease) {DISEASE_NAME_ZIKA, duration: 80, stink: 200, wetness: 200, viscosity: 200, amount: 200}
#define DISEASE_YELLOW_FEVER (Disease) {DISEASE_NAME_YELLOW_FEVER, duration: 100, stink: 250, wetness: 250, viscosity: 250, amount: 250}

typedef struct
{
    byte age;
    byte type;
    byte wetness;
    byte viscosity;
    byte stink;
    byte quality;
    byte amount;
    byte disease;
    int room;
    byte position;
} Faeces;
/*
int main()
{
    Room rooms[ROOMS];
    Creature creatures[MAX_CREATURES];
    creatures[0] = Creature("player",Vector2(0, 0), 0, 0, SkillsDefault);
    printf("Player: %d\n", isNull(creatures[2], Creature, CreatureNull));
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
    for(int i = 0; i < ROOMS; i++)
    {
        printf("Room: %d, %d\n", rooms[i].globalPosition.x, rooms[i].globalPosition.y);
        for (int j = 0; j < ROOM_WIDTH; j++)
        {
            for (int k = 0; k < ROOM_HEIGHT; k++)
            {
                printf("%d", rooms[i].map[j][k]);
            }
            printf("\n");
        }
    }
    return 0;
}*/