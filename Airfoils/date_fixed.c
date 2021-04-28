/******************************************************************************
PROGRAM NAME : date_fixed.c
AUTHER : Masatsugu Kitadai
DATE : 18/4/2021
******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <math.h>

const char *input_file = "original/airfoil.dat";
const char *output_file = "result/Airfoil_fixed.dat";
FILE *input;
FILE *output;

double plot[3];

/*********************************   MAIN   *********************************/
double
main()
{
    int i, j;
    input = fopen(output_file, "r");

    return (0);
}