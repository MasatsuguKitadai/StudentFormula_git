/******************************************************************************
PROGRAM NAME : Oven_temp.c
AUTHER : Masatsugu Kitadai
DATE : 6/5/2021
******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <math.h>
#define num 10000

double data[num];
char file_name[100];
char buf[128];
char read_file[100];
char output_file[100];
char output_file_gnu[100];

FILE *read;
FILE *output;

// Gnuplot

const char *xxlabel = "Time [min]";
const char *yylabel = "Temperature [c]";

const int x_min = 0;   ///x range min
const int x_max = 400; ///x range max
const int y_min = 0;   ///y range min
const int y_max = 150; ///y range max

void graph_GNU();
FILE *gp;
FILE *infile;

/*********************************   MAIN   *********************************/
double main()
{
    int i;
    double temp;
    char date[100], c[100];

    i = 0;

    // 読み込むファイルを指定する

    printf("ファイル名：");
    scanf("%s", file_name);

    // 入力・出力ファイル名の指定

    sprintf(read_file, "data_files//%s.txt", file_name);
    sprintf(output_file, "data_fixed//%s.dat", file_name);
    sprintf(output_file_gnu, "data_fixed//%s.dat", file_name);

    // 読み込むファイルを開く

    read = fopen(read_file, "r");
    if (read == NULL)
    {
        printf("I can't open the file\n");
        exit(0);
    }

    // 最初の1行を読み飛ばす

    fgets(buf, sizeof(buf), read);

    // 最後の行以外を読み込み，配列に格納する

    while (fscanf(read, "%s %lf %s", date, &temp, c) != EOF)
    {
        i = i + 1;
        data[i] = temp;
    }

    // EOFで判別できない最後の行を読み込む

    fscanf(read, "%s %lf %s", date, &temp, c);
    i = i + 1;
    data[i] = temp;
    fclose(read);

    // 配列の大きさを決定

    int data_long;
    data_long = i;

    // datファイルを作成

    output = fopen(output_file, "w");
    for (i = 1; i < data_long; i++)
    {
        fprintf(output, "%d\t\t%lf\n", i, data[i]);
    }
    fclose(output);

    // Gnuplot で作図

    infile = fopen(output_file_gnu, "rb");

    if (infile == NULL)
    {
        printf("ファイルが開けません\n");
    }

    if ((gp = popen("gnuplot", "w")) == NULL)
    {
        printf("gnuplot is not here!\n");
        exit(0);
    }

    //PNG image
    fprintf(gp, "set terminal pngcairo enhanced font 'Times New Roman,15' \n");
    fprintf(gp, "set output 'graph//%s.png'\n", file_name);
    fprintf(gp, "unset key\n"); // <steps in scan>,<steps between scans>

    fprintf(gp, "set lmargin screen 0.15\n"); // <steps in scan>,<steps between scans>
    fprintf(gp, "set rmargin screen 0.85\n"); // <steps in scan>,<steps between scans>
    fprintf(gp, "set tmargin screen 0.85\n"); // <steps in scan>,<steps between scans>
    fprintf(gp, "set bmargin screen 0.15\n"); // <steps in scan>,<steps between scans>

    fprintf(gp, "set xrange [%d:%d]\n", x_min, x_max);       // <steps in scan>,<steps between scans>
    fprintf(gp, "set xlabel '%s'offset 0.0,0.5\n", xxlabel); // <steps in scan>,<steps between scans>
    fprintf(gp, "set yrange [%d:%d]\n", y_min, y_max);       // <steps in scan>,<steps between scans>
    fprintf(gp, "set ylabel '%s'offset 0.5,0.0\n", yylabel); // <steps in scan>,<steps between scans>
    fprintf(gp, "plot 'data_fixed//%s.dat' using 1:2 with lines lc 'black'\n", file_name);

    fflush(gp);            //Clean up Data
    fprintf(gp, "exit\n"); // Quit gnuplot

    pclose(gp);

    fclose(infile);
    return (0);
}