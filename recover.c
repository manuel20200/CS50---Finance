#include <stdio.h>
#include <stdlib.h>

char buffer[512];
char open = 0;
int count = 0;
int retorno = 512;
char filename[8];
unsigned char bytes[512];

FILE *img;

int main(int argc, char *argv[])
{
    // Check for invalid usage
    if (argc != 2)
    {
        printf("Parameter not valide\n");
        return 1;
    }

    // Open card.raw file
    FILE *file = fopen(argv[1], "r");
    if (file == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", argv[1]);
        return 4;
    }
    //printf("%p \n", file);

    //check for all card.raw every 512bytes for jpgs
    while (retorno != 0)
    {
        //int retorno = fread(arr, sizeof(char), 512, file);
        int dir = ftell(file);
        retorno = fread(bytes, sizeof(char), 512, file);
        dir = ftell(file);
        //printf("%i -------------------------------------------- \n", retorno);

        for (int i = 0; i < 1; i++)
        {
            //check the first 4 bytes for 0xff // 0xd8 // 0xff // 0xe, if equals posible jpg
            if (bytes[i] == 0xff && bytes[i + 1] == 0xd8 && bytes[i + 2] == 0xff && (bytes[i + 3] & 0xf0) == 0xe0)
            {
                //check if there is a jpeg file actually open
                if (open == 1)
                {
                    fclose(img);
                    open = 0;
                }

                //every start of jpg file increase count by 1
                count++;
                int result = sprintf(filename, "%03i.jpg", (count - 1));

                //FILE *img = fopen(filename, "w");
                img = fopen(filename, "w");
                if (img == NULL)
                {
                    fprintf(stderr, "Could not open img %s.\n", filename);
                    return 4;
                }

                open = 1;
                fwrite(bytes, sizeof(char), 512, img);
            }
            else if (open == 1)
            {

                fwrite(bytes, sizeof(char), 512, img);

            }
        }
    }

    fclose(file);


}
