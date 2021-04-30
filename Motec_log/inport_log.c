/******************************************************************************
PROGRAM NAME : inport_log.c
AUTHER : Masatsugu Kitadai
DATE : 18/4/2021
******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <math.h>
#define num 10000
#define omit 18

double coordinate[num][3];
char file_name[1000];
char buf[128];
char read_file[1000];
char output_file[1000];

FILE *read;
FILE *output;

/*********************************   MAIN   *********************************/
double main()
{
    int i, j, k;
    double x, z;

    i = 0;

    // 読み込むファイルを指定する

    printf("ファイル名：");
    scanf("%s", file_name);

    // 入力・出力ファイル名の指定

    sprintf(read_file, "%s", file_name);

    // 読み込むファイルを開く

    read = fopen(read_file, "r");
    if (read == NULL)
    {
        printf("I can't open the file\n");
        exit(0);
    }

    // 不要な行を読み飛ばす

    for (k = 0; k < omit; k++)
    {
        fgets(buf, sizeof(buf), read);
    }

    // 最後の行以外を読み込み，配列の大きさを確認

    while (fscanf(read, "%lf %lf", &x, &z) != EOF)
    {
        i = i + 1;
    }

    // EOFで判別できない最後の行を読み込む

    fscanf(read, "%lf %lf", &x, &z);
    i = i + 1;

    fclose(read);

    // 配列の大きさを決定

    int data_long;
    data_long = i;

    printf("%d", data_long);

    // 書き込むファイルを開く

    /* output = fopen(output_file, "w");

    printf("\nResult-----------------------------------------------------\n\n");

    for (i = 1; i < data_long; i++)
    {
        printf("%d\t%lf\t%lf\t%lf\n", i, coordinate[i][1], coordinate[i][2], coordinate[i][3]);
        fprintf(output, "%d\t%lf\t%lf\t%lf\n", i, coordinate[i][1], coordinate[i][2], coordinate[i][3]);
    }
    printf("\n-----------------------------------------------------------\n");

    fclose(output);
*/

    return (0);
}