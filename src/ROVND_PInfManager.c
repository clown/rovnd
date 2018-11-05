/* ====================================================================== *
 *  ファイル名  : ROVND_PInfManager.c
 *  概要        : 価格情報の管理
 *  作成者      : clown
 *  修正日      : 2003/11/03
 * ====================================================================== */
#include <stdio.h>
#include <stdlib.h>
#include "ROVND_Proto.h"

static int      m_item;         // 価格情報数
static int      m_size;         // 確保されている領域サイズ
static T_PINF   *m_pinf;

static int PInfConvert(char *src, T_PINF *dest);
static int PInfRealloc(void);

/* ====================================================================== *
 *  関数名      : PInfInit
 *  機能        : 初期処理
 *  戻り値
 *    0         : 正常
 *    -1        : エラー
 *  修正日      : 2003/11/03
 * ====================================================================== */
int PInfInit(char *filename)
{
    m_item = 0;
    m_size = 0;
    m_pinf = NULL;

    return PInfRead(filename);
}

/* ====================================================================== *
 *  関数名      : PInfGet
 *  機能        : インデックスで指定された情報を取得する
 *  戻り値
 *    0         : 正常
 *    -1        : エラー
 *  修正日      : 2003/11/03
 * ====================================================================== */
int PInfGet(int index, T_PINF *dest)
{
    if (index > m_item) {
        return -1;
    }

    *dest = m_pinf[index];
    return 0;
}

/* ====================================================================== *
 *  関数名      : PInfGetRegistNum
 *  機能        : 登録数を取得する
 *  戻り値
 *    0         : 正常
 *    -1        : エラー
 *  修正日      : 2003/11/03
 * ====================================================================== */
int PInfGetRegistNum(void)
{
    return m_item;
}

/* ====================================================================== *
 *  関数名      : PInfRead
 *  機能        : 価格情報ファイルを開いて読み込む
 *  戻り値
 *    0         : 正常
 *    -1        : エラー
 *  修正日      : 2003/11/03
 * ====================================================================== */
int PInfRead(char *filename)
{
    FILE    *fin;
    char    work[ROVND_MAX_BUFSIZE];

    if ((fin = fopen(filename, "r")) == NULL) {
        return -1;
    }

    FileMap(fin, PInfAdd, ROVND_SYM_COMM);
    return 0;
}

/* ====================================================================== *
 *  関数名      : PInfAdd
 *  機能        : 価格情報を追加する
 *  戻り値
 *    0         : 正常
 *    -1        : エラー
 *  修正日      : 2003/11/03
 * ====================================================================== */
int PInfAdd(char *src)
{
    T_PINF  work;

    if (PInfConvert(src, &work) != 0) {
        return -1;
    }

    if (m_item >= m_size) {     // 領域を伸張
        PInfRealloc();
    }

    m_pinf[m_item++] = work;
    return 0;
}

/* ====================================================================== *
 *  関数名      : PInfTerm
 *  機能        : 終了処理
 *  戻り値
 *    0         : 正常
 *  修正日      : 2003/11/03
 * ====================================================================== */
int PInfTerm(void)
{
    free(m_pinf);
    m_pinf = NULL;
    m_size = 0;
    m_item = 0;

    return 0;
}

/* ====================================================================== *
 *  関数名      : PInfConvert
 *  機能        : T_PINF型に変換する
 *  戻り値
 *    0         : 正常
 *    -1        : エラー
 *  修正日      : 2003/11/03
 * ====================================================================== */
static int PInfConvert(char *src, T_PINF *dest)
{
    char    work[32];
    char    *token[32];
    int     item, i;

    item = StrToken(src, token, sizeof(token) / sizeof(char *), ROVND_SYM_DELIM);
    if (item < 4) {     // フォーマット不正
        return -1;
    }

    for (i = 0; i < item; i++) {    // 文頭・文末の空白及び改行文字の除去
        StrTrim(token[i], " \t");
        StrTrimR(token[i], " \t\r\n");
    }
    strcpy(dest->item_name, token[0]);
    strcpy(dest->min_price, token[1]);
    strcpy(dest->max_price, token[2]);
    strcpy(dest->update,    token[3]);

    return 0;
}

/* ====================================================================== *
 *  関数名      : PInfRealloc
 *  機能        : 領域を伸張する
 *  戻り値
 *    0         : 正常
 *    -1        : エラー
 *  修正日      : 2003/11/03
 * ====================================================================== */
static int PInfRealloc(void)
{
    m_size = m_size * 2 + 10;
    m_pinf = (T_PINF *)realloc(m_pinf, sizeof(T_PINF) * m_size);
    if (m_pinf == NULL) {
        return -1;
    }

    return 0;
}
