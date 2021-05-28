/******************************************************************************
PROGRAM NAME : theory.c
AUTHER : Masatsugu Kitadai
DATE : 17/5/2021
******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <math.h>

#define num 10000

const char *xxlabel = "{/Times-New-Roman:Italic=20 velocity} [km/h]";
const char *yylabel = "{/Times-New-Roman:Italic=20 pressure} [Pa]";

const int x_min = 0;    ///x range min
const int x_max = 100;  ///x range max
const int y_min = -500; ///y range min
const int y_max = 0;    ///y range max

char output_file[1000];

//Graph parameters for GNU
char read_file[100];
void graph_GNU(); //png & eps
FILE *gp;         //gnuplot
FILE *output;

/*********************************   MAIN   *********************************/
int main()
{
    int i;
    double pressure_air, pressure_cal, density_air, velocity_kmh;
    double pressure_dif[num];
    double velocity[num];

    // calculate pressure_dif

    density_air = 1.205; // [kg/m^3]
    velocity_kmh = 0;

    for (i = 0; i < num; i++)
    {
        velocity_kmh = velocity_kmh + 0.01;
        velocity[i] = velocity_kmh;
        pressure_dif[i] = -1.0 / 2.0 * density_air * velocity_kmh * velocity_kmh * 1000 / 3600 * 1000 / 3600;
    }

    // create a result file

    sprintf(output_file, "output//result.dat");

    output = fopen(output_file, "w");

    for (i = 1; i < num; i++)
    {
        fprintf(output, "%lf\t%lf\n", velocity[i], pressure_dif[i]);
    }

    fclose(output);

    if ((gp = popen("gnuplot", "w")) == NULL)
    {
        printf("gnuplot is not here!\n");
        exit(0);
    }

    //PNG image
    fprintf(gp, "set terminal pngcairo enhanced font 'Times New Roman,15' \n");
    fprintf(gp, "set output 'output//graph.png'\n");
    fprintf(gp, "set multiplot\n");      // <steps in scan>,<steps between scans>
    fprintf(gp, "unset key\n");          // <steps in scan>,<steps between scans>
    fprintf(gp, "set size ratio 0.8\n"); // <steps in scan>,<steps between scans>

    fprintf(gp, "set lmargin screen 0.15\n"); // <steps in scan>,<steps between scans>
    fprintf(gp, "set rmargin screen 0.85\n"); // <steps in scan>,<steps between scans>
    fprintf(gp, "set tmargin screen 0.85\n"); // <steps in scan>,<steps between scans>
    fprintf(gp, "set bmargin screen 0.15\n"); // <steps in scan>,<steps between scans>

    fprintf(gp, "set xrange [%d:%d]\n", x_min, x_max);       // <steps in scan>,<steps between scans>
    fprintf(gp, "set xlabel '%s'offset 0.0,0.5\n", xxlabel); // <steps in scan>,<steps between scans>
    fprintf(gp, "set yrange [%d:%d]\n", y_min, y_max);       // <steps in scan>,<steps between scans>
    fprintf(gp, "set ylabel '%s'offset 0.5,0.0\n", yylabel); // <steps in scan>,<steps between scans>

    fprintf(gp, "set pm3d map\n"); // <steps in scan>,<steps between scans>
    fprintf(gp, "plot 'output//result.dat' using 1:2 with lines lc 'black'\n");

    fflush(gp);            //Clean up Data
    fprintf(gp, "exit\n"); // Quit gnuplot

    pclose(gp);

    return (0);
}