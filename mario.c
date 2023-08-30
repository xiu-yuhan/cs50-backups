#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int height = 0;
    while (height < 1 | height > 8){
        height = get_int("Height: ");
    }
    for (int i = 1; i < height+1; i++){
        for (int s = height-i; s >0 ; s--){
            printf(" ");
        }
        for (int b = i; b > 0; b--){
            printf("#");
        }
        printf("  ");
        for (int c = i; c > 0; c--){
            printf("#");
        }
        printf("\n");
    }
}