/******************************************************************************
PROGRAM NAME : tracking.c
AUTHER : Masatsugu Kitadai
DATE : 18/4/2021
******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define column 20
#define data_long 20

const char *read_file = "log_20210306.CSV";
char date[20];

int omit = 18; // Number of lines to skip
char buf[128]; //

double value[data_long][column];

FILE *input_file;
/*********************************   MAIN   *********************************/
double main()
{
    int i, j;
    double ch[column];

    input_file = fopen(read_file, "r");
    if (read_file == NULL)
    {
        printf("I can't open the file!\n");
        exit(0);
    }

    // Transrate the point of pointer
    for (i = 0; i < omit; i++)
    {
        fgets(buf, sizeof(buf), input_file);
    }

    for (i = 0; i < data_long; i++)
    {
        fscanf(input_file, "%lf, %lf, %lf, %lf, %lf, %lf, %lf, %lf, %lf, %lf, %lf ,%lf ,%lf ,%lf ,%lf ,%lf ,%lf ,%lf ,%lf ,%lf", &ch[0], &ch[1], &ch[2], &ch[3], &ch[4], &ch[5], &ch[6], &ch[7], &ch[8], &ch[9], &ch[10], &ch[11], &ch[12], &ch[13], &ch[14], &ch[15], &ch[16], &ch[17], &ch[18], &ch[19]);

        for (j = 0; j < column; j++)
        {
            value[i][j] = ch[j];
        }

        printf("value[%d][1]=%lf", i, value[i][1]);
    }
    fclose(input_file);

    return (0);
}