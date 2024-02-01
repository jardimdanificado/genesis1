#include "stdio.h"
#include "stdlib.h"
#include "string.h"

typedef unsigned char byte;

//vectors   
typedef struct
{
    int x;
    int y;
} Vector2;
#define Vector2(x, y) (Vector2){ x, y }

typedef struct
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
byte* string_concat(char* a, char* b)
{
    char* result = (char*)malloc(strlen(a) + strlen(b) + 1);
    strcpy(result, a);
    strcat(result, b);
    return(result);
}

byte*** byteMap3d(int dim1, int dim2, int dim3, char defaultValue) 
{
    byte*** matriz3D = (byte ***)malloc(dim1 * sizeof(byte**));
    // Verificação se a alocação foi bem-sucedida
    if (matriz3D == NULL) 
    {
        perror("Erro ao alocar a primeira dimensão");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < dim1; ++i) 
    {
        matriz3D[i] = (byte**)malloc(dim2*sizeof(byte*));

        // Verificação se a alocação foi bem-sucedida
        if (matriz3D[i] == NULL) 
        {
            perror("Erro ao alocar a segunda dimensão");
            exit(EXIT_FAILURE);
        }

        for (int j = 0; j < dim2; ++j) 
        {
            matriz3D[i][j] = (byte)malloc(dim3);

            // Verificação se a alocação foi bem-sucedida
            if (matriz3D[i][j] == NULL)
            {
                perror("Erro ao alocar a terceira dimensão");
                exit(EXIT_FAILURE);
            }
            for(int k = 0; k < dim3; ++k)
            {
                matriz3D[i][j][k] = defaultValue;
                printf("%d\n", matriz3D[i][j][k]);
            }
        }
    }

    return matriz3D;
}

void freeByteMap3d(byte*** matriz3D, int dim1, int dim2, int dim3) 
{
    for (int x = 0; x < dim1; ++x) 
    {
        for (int y = 0; y < dim2; ++y) 
        {
            for (int z = 0; z < dim3; ++z) 
            {
                free(matriz3D[x][y][z]);
            }
            free(matriz3D[x][y]);
        }
        free(matriz3D[x]);
    }
    free(matriz3D);
}


int main()
{
    Vector3 mapSize = Vector3(10, 20, 30);
    byte*** map = byteMap3d(mapSize.x, mapSize.y, mapSize.z, 0);
    
    //string
    char* result = string_concat("hello", "world");
    printf("%s\n", result);
    free(result);
    freeByteMap3d(map, mapSize.x, mapSize.y, mapSize.z);
    return 0;
}