#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ROWS 64
#define COLS 64

typedef struct 
{
    char map[ROWS][COLS];
} World;
#define World() {}

int main(int argc, char *argv[]) 
{
    World world = World();
    if (argc != 2) {
        printf("Usage: %s <string>\n", argv[0]);
        return 1;
    }

    char *str = argv[1];
    int len = strlen(str);
    char *rev = malloc(len + 1);
    for (int i = 0; i < len; i++) {
        rev[i] = str[len - i - 1];
    }
    rev[len] = '\0';
    printf("%s\n", rev);
    free(rev);
    return 0;
}