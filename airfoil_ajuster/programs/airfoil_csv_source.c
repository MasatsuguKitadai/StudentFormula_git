/******************************************************************************
PROGRAM NAME : airfoil_csv.c
AUTHER : Masatsugu Kitadai
DATE : 18/4/2021
******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <math.h>
#define num 10000

double coordinate[num][3];
char airfoil_name[1000];
char buf[128];
char read_file[1000];
char output_file[1000];
char space[1000];

FILE* read;
FILE* output;
/*********************************   MAIN   *********************************/
int main()
{
    int i, chord;
    double x, y;

    i = 0;

    // 読み込むファイルを指定する

    printf("ファイル名：");
    scanf("%s", airfoil_name);

    // 入力・出力ファイル名の指定

    sprintf(read_file, "original//%s.txt", airfoil_name);

    // 読み込むファイルを開く

    read = fopen(read_file, "r");
    if (read == NULL)
    {
        printf("\nファイルが開けません\n");
        printf("最初からやり直してください\n\n");
        printf("何か文字を入力してEnterを押すとプログラムが終了します\n");
        scanf("%s", space);
        exit(0);
    }

    // 最初の1行を読み飛ばす

    fgets(buf, sizeof(buf), read);

    // 最後の行以外を読み込み，配列に格納する

    while (fscanf(read, "%lf %lf", &x, &y) != EOF)
    {
        i = i + 1;
        coordinate[i][1] = x;
        coordinate[i][2] = 0;
        coordinate[i][3] = y;
    }

    // EOFで判別できない最後の行を読み込む

    fscanf(read, "%lf %lf", &x, &y);
    i = i + 1;
    coordinate[i][1] = x;
    coordinate[i][2] = 0;
    coordinate[i][3] = y;

    fclose(read);

    // 配列の大きさを決定

    int data_long;
    data_long = i;

    // 翼弦長を指定する
    printf("翼弦長(mm)：");
    scanf("%d", &chord);

    // 指定された翼弦長に修正する

    for (i = 1; i < data_long; i++)
    {
        coordinate[i][1] = chord * coordinate[i][1];
        coordinate[i][3] = chord * coordinate[i][3];
    }

    // 書き込むファイルの名前を指定する

    sprintf(output_file, "result//%s_%d.csv", airfoil_name, chord);

    // 書き込むファイルを開く

    output = fopen(output_file, "w");

    fprintf(output, "x,y,z\n");

    for (i = 1; i < data_long; i++)
    {
        fprintf(output, "%lf,%lf,%lf\n", coordinate[i][1], coordinate[i][2], coordinate[i][3]);
    }

    fclose(output);

    // アプリケーションに出力

    printf("\n【Result】-------------------------------------------------\n\n");

    printf("\t【 x 】\t\t【 y 】\t\t【 z 】\n");

    for (i = 1; i < data_long; i++)
    {
        printf("%d\t%lf\t%lf\t%lf\n", i, coordinate[i][1], coordinate[i][2], coordinate[i][3]);
    }

    printf("\n-----------------------------------------------------------\n\n");

    printf("何か文字を入力してEnterを押すとプログラムが終了します\n");
    scanf("%s", space);

    return (0);
}