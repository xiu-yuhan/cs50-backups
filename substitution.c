#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int check_let(char arg);
void do_sub(string base, string key);

int main(int argc, string argv[])
{
    if(argc == 2)                                                                                 //checking num of arguments
    {
        if(strlen(argv[1]) != 26)                                                                 //checking if key has 26 characters
        {
            printf("Usage: ./substitution key\n");                                                //output if key doesnt have 26 characters
            return 1;
        }
        else
        {
            for (int i = 0; i < strlen(argv[1]); i++)
            {
                if (check_let(argv[1][i]) < 27)                                                   //check to make sure there are only characters in the alphabet
                {
                    for (int k = i+1; k < strlen(argv[1]); k++)
                    {
                        if (tolower(argv[1][i] == argv[1][k]))                                    //check for repeated letters in key
                        {
                            printf("Must not include any repeated letters in the key\n");         //output if key contains repeated letters
                            return 1;
                        }
                    }
                }
                else
                {
                    printf("Key must contain 26 non-letter characters\n");                        //output if key contains numbers
                    return 1;
                }
            }
        }
    }
    else
    {
            printf("Usage: ./substitution key\n");                                                //output if no key given
            return 1;
    }
    string plain = get_string("plaintext: ");                                                     //asks for user input for plaintext
    printf("ciphertext: ");
    do_sub(plain,argv[1]);
    return 0;
}


int check_let(char arg)                                                                           //checks if char argument is a letter
{
    string abc = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

    for (int j = 0; j < strlen(abc); j++)
    {
        if (toupper(arg) == abc[j])                                                              //compares given char with letters in the alphabet using the string abc
        {
            return j;                                                                            //returns the position in the alphabet where the element matched
        }
    }
    return 100;
}

void do_sub(string base, string key)
{
    for (int i = 0; i < strlen(base); i++)
    {
        if (isupper(base[i]))                                                                    //checks if original char is uppercase
        {
            printf("%c",toupper(key[check_let(base[i])]));                                       //prints encoded char in uppercase
        }
        else if(islower(base[i]))                                                                //checks if original char is lowercase
        {
            printf("%c",tolower(key[check_let(base[i])]));                                       //prints encode char in lowercase
        }
        else
        {
            printf("%c",base[i]);                                                                //prints nochar elements
        }
    }
    printf("\n");

}