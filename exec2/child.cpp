#include <stdio.h>
#include <cstdlib>
#include <time.h>


int main(void) 
{
    char date[64];
    time_t t = time(NULL);
    strftime(
        date, sizeof(date),
        "%Y/%m/%d %a %H:%M:%S",
        localtime(&t)
    );

    printf("%s ... from child \n", date);

    exit(4);
}