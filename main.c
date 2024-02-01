#include "stdio.h"
#include "stdlib.h"
#include "string.h"

//vectors   
typedef struct Vector2
{
    int x;
    int y;
};
#define Vector2(x, y) (Vector2){ x, y }

typedef struct Vector3
{
    int x;
    int y;
    int z;
} Vector3;
#define Vector3(x, y, z) (Vector3){ x, y, z }

//lists using define
#define List(type) struct { int count; type *items; }
#define list_push(list, item) list.items = (typeof(list.items))realloc(list.items, sizeof(list.items) + sizeof(item)); list.items[list.count++] = item
#define list_remove(list, index) list.items[index] = list.items[--list.count]

/*  example usage:
    List(char*) list = { 0 };
    list_push(list, "hello");
    list_push(list, "world");
    list_push(list, "!");
    for (int i = 0; i < list.count; i++)
    {
        printf("%s\n", list.items[i]);
    }
*/

//string
char* string_concat(char* a, char* b)
{
    char* result = (char*)malloc(strlen(a) + strlen(b) + 1);
    strcpy(result, a);
    strcat(result, b);
    return(result);
}