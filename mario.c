#include <cs50.h>
#include <stdio.h>

int main(void)
{
    //get height
    int height = 0;
    while (height < 1 | height > 8){
        height = get_int("Height: ");
    }
    //loop to make every layer of pyramid
    for (int i = 1; i < height+1; i++){
        //creates spaces before pyramid
        for (int s = height-i; s >0 ; s--){
            printf(" ");
        }
        //creates left side of pyramid
        for (int b = i; b > 0; b--){
            printf("#");
        }
        //creates hole in middle
        printf("  ");
        //creates right side of pyramid
        for (int c = i; c > 0; c--){
            printf("#");
        }
        printf("\n");
    }
}