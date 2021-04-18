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
    double ch0, ch1, ch2, ch3, ch4, ch5, ch6, ch7, ch8, ch9, ch10, ch11, ch12, ch13, ch14, ch15, ch16, ch17, ch18, ch19;

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
        fscanf(input_file, "%lf, %lf, %lf, %lf, %lf, %lf, %lf, %lf, %lf, %lf, %lf ,%lf ,%lf ,%lf ,%lf ,%lf ,%lf ,%lf ,%lf ,%lf", &ch0, &ch1, &ch2, &ch3, &ch4, &ch5, &ch6, &ch7, &ch8, &ch9, &ch10, &ch11, &ch12, &ch13, &ch14, &ch15, &ch16, &ch17, &ch18, &ch19);

        value[i][0] = ch0;
        value[i][1] = ch1;
        value[i][2] = ch2;
        value[i][3] = ch3;
        value[i][4] = ch4;
        value[i][5] = ch5;
        value[i][6] = ch6;
        value[i][7] = ch7;
        value[i][8] = ch8;
        value[i][9] = ch9;
        value[i][10] = ch10;
        value[i][11] = ch11;
        value[i][12] = ch12;
        value[i][13] = ch13;
        value[i][14] = ch14;
        value[i][15] = ch15;
        value[i][16] = ch16;
        value[i][17] = ch17;
        value[i][18] = ch18;
        value[i][19] = ch19;

        printf("value[%d][1]=%lf", i, value[i][0]);
    }
    fclose(input_file);

    return (0);
}