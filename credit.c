#include <cs50.h>
#include <stdio.h>

int main(void)
{
    long cardNum = -1;
    while (cardNum < 0){
        cardNum = get_long("Number: ");
    }
    if (cardNum >10000000000000000 | cardNum < 1000000000000){
        printf("INVALID\n");
    }
    else{
        int sum = 0;
        //gets the num of every other digit then multiply by 2
        //adds the digits to the variable sum
        for (long i = cardNum/10; i > 0; i = i/100){
            if (i%10*2 > 9){
                sum = sum + (((i%10)*2)/10) + (((i%10)*2)%10);
            }
            else{
            sum = sum + (i%10)*2;
            }
        }
        //adds the digits not multiplied by 2 to sum
        for (long n = cardNum; n>0; n = n/100){
            sum = sum + n%10;
        }
        //checks if card is valid
        while (cardNum > 100){
            cardNum = cardNum/10;
        }
        if (sum%10==0 && cardNum/10 == 4){
            printf("VISA\n");
        }
        else if(sum%10==0 && cardNum == 37 | cardNum == 34){
            printf("AMEX\n");
        }
        else if(sum%10==0 && cardNum >50 & cardNum < 56){
            printf("MASTERCARD\n");
        }
        else{
            printf("INVALID\n");
        }
    }
}