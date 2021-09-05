#include <cstdio>
#include <cstdlib>
#include <unistd.h>

int main(int argc, char * argv[]) 
{
    printf("child!\n");
    for (int i = 0; i < argc; i++) {
        printf("%3d : %s\n", i, argv[i]);
    }
    exit(0);

    return 0;
}