#include <stdio.h>
#include <stdlib.h>

int main()
{
    if(!system("dir"))
    {
        for(int i =0; i < 2; i++)
        {
            printf("Szeretek futni!\n");
        }
    }
    system("Ilyen parancs nem letezik..");
    return 0;
}
