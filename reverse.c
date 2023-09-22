#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "wav.h"

int check_format(WAVHEADER header);
int get_block_size(WAVHEADER header);

int main(int argc, char *argv[])
{

    // Ensure proper usage
    // TODO #1
    if(argc != 3)
    {
        printf("usage: ./reverse input.wav output.wav\n");
        return 1;
    }

    // Open input file for reading
    // TODO #2
    FILE *input = fopen(argv[1],"r");
    if (input == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    // Read header
    // TODO #3
    WAVHEADER h;
    fread(&h,sizeof(WAVHEADER),1,input);

    // Use check_format to ensure WAV format
    // TODO #4
    if (check_format(h) == 0)
    {
        printf("Invalid WAV Format\n");
        return 1;
    }

    // Open output file for writing
    // TODO #5
    FILE *output = fopen(argv[2],"w");
    if(output == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }
    // Write header to file
    // TODO #6
    fwrite(&h,sizeof(WAVHEADER),1,output);

    // Use get_block_size to calculate size of block
    // TODO #7
    int size = get_block_size(h);

    // Write reversed audio to file
    // TODO #8
    BYTE buffer[size];
    fseek(input,0,SEEK_END);
    int fileSize = ftell(input) - sizeof(WAVHEADER);
    int blockSize = (int) fileSize/size;

    for (int i = blockSize-1; i >=0;i--)
    {
        fseek(input,sizeof(WAVHEADER) + i * size,SEEK_SET);
        fread(buffer,size,1,input);
        fwrite(buffer,size,1,output);
    }

    //close files
    fclose(input);
    fclose(output);
    return 0;
}

int check_format(WAVHEADER header)
{
    // TODO #4
    BYTE form[] = {'W','A','V','E'};
    for (int i = 0; i < 4; i++)
    {
        if(header.format[i] != form[i])
        {
            return 0;
        }
    }
    return 1;
}

int get_block_size(WAVHEADER header)
{
    // TODO #7
    return (header.numChannels * (header.bitsPerSample/8));
}