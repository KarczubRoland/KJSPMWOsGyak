#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int main()
{
    char input[50];

    do
    {
        printf("Add meg a beirni kivant parancsot! ");
        scanf("%s", &input);
        system(input);

    }
    while(true);
    return 0;
}
