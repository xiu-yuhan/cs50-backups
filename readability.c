#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

//find amount of letters in text
int count_letters(string text){
    // string abc[] = {"a","b","c","d","e","f","g","h","i","j","k","l","m","n","o","p","q","r","s","t","u","v","w","x","y","z"};
    char abc[26] = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};
    int letters = 0;
    for (int i = 0; i < strlen(text); i++){
        for(int j = 0; j < 26; j++){
            if (tolower(text[i]) == abc[j]){
                letters += 1;
            }
        }
    }
    return letters;
}

//find amount of words in text
int count_words(string text){
    int words = 1;
    for (int i = 0; i < strlen(text); i++){
        if (text[i] == ' '){
            words += 1;
        }
    }
    return words;
}

//find amount of sentences in text
int count_sentences(string text){
    int sentences = 0;
    for (int i = 0; i < strlen(text); i++){
        if (text[i] == '.' | text[i] == '?' | text[i] == '!'){
            sentences += 1;
        }
    }
    return sentences;
}

int main(void)
{
    //get input from user
    string input = get_string("Text: ");

    //test prints to check correct numbers
    // printf("letters: %i\n",count_letters(input));
    // printf("words: %i\n",count_words(input));
    // printf("sentences: %i\n",count_sentences(input));

    //calculate index using given formula
    float index = ((.0588 * ((count_letters(input)*100)/(float)count_words(input))) - (.296 * ((count_sentences(input)*100)/(float)count_words(input)))) - 15.8;

    //test prtins to check correct numbers
    // printf("index: %f\n",index);
    // printf("L: %f\n",(.0588 * ((count_letters(input)*100)/count_words(input))));
    // printf("S: %f\n",(.296 * ((count_sentences(input)*100)/count_words(input))));

    //output correct index even if index is lower than 1 or greater than 16
    index = round(index);
    if (index < 1){
        printf("Before Grade 1\n");
    }
    else if(index > 16){
        printf("Grade 16+\n");
    }
    else{
        printf("Grade %i\n", (int)index);
    }
}