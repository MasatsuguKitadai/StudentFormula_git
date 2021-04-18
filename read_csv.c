/* defineConstant.h */
#ifndef __DEFINECONSTANT_H__
#define __DEFINECONSTANT_H__

typedef enum
{
    RETURN_OK = 0,
    ARGUMENT_ERROR,
    FILE_OPEN_ERROR,
    MALLOC_ERROR
} RETURN_TYPE;

#endif

#include "defineConstant.h"
/*
   iCountRowCol: 行数と列数をカウントする

   char *pszFileName:   読み込むファイル名
   unsigned int *piRow: 行数
   unsigned int *piCol: 列数

   return: 正常終了 -> 0
           異常終了 -> 0 以外
 */
int iCountRowCol(char *pszFileName, unsigned int *puiRow, unsigned int *puiCol)
{
    FILE *prFile;
    int iRet;
    unsigned int uiRow, uiCol;
    char chData;
    iRet = RETURN_OK;

    /* 引数のチェック */
    if ((NULL == pszFileName) || (NULL == puiRow) || (NULL == puiCol))
    {
        fprintf(stderr, "argument error\n");
        iRet = ARGUMENT_ERROR;
        goto EXIT_COUNT_ROWCOL;
    }
    else
    {
        *puiRow = *puiCol = 0;
    }
    if (NULL == (prFile = fopen(pszFileName, "r")))
    {
        fprintf(stderr, "Error: %s cannot open\n", pszFileName);
        iRet = FILE_OPEN_ERROR;
        goto EXIT_COUNT_ROWCOL;
    }
    uiRow = uiCol = 0;

    while (EOF != fscanf(prFile, "%c", &chData))
    {
        /* カンマの場合 */
        if (',' == chData)
        {
            uiCol++;
        }
        /* 改行コードの場合 */
        if ('\n' == chData)
        {
            uiCol++;
            uiRow++;
        }
    }
    uiCol /= uiRow;

    *puiRow = uiRow;
    *puiCol = uiCol;
    fclose(prFile);

EXIT_COUNT_ROWCOL:
    return iRet;
}