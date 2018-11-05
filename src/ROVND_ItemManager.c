/* ====================================================================== *
 *  ファイル名  : ROVND_ItemManager.c
 *  概要        : アイテム情報の管理
 *  作成者      : clown
 *  修正日      : 2003/11/25
 * ====================================================================== */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "StrTreat.h"
#include "FileTreat.h"
#include "ROVND_Proto.h"

static char         m_filename[ROVND_MAX_FNAMESIZE+1];  // 出力ファイル名
static char         m_dispname[ROVND_MAX_BUFSIZE+1];    // 日本語名称
static int          m_item;                             // アイテム情報数
static T_ITEMTABLE  *m_itemtable;

static int ItemRead(char *filename);
static int ItemAdd(char *src);
static int ItemAddTable(char *token[]);
static int ItemAddData(char *token[]);

/* ====================================================================== *
 *  関数名      : ItemInit
 *  機能        : 初期処理
 *  戻り値
 *    0         : 正常
 *    -1        : エラー
 *  修正日      : 2003/11/04
 * ====================================================================== */
int ItemInit(char *filename)
{
    memset(m_filename, '\0', sizeof(m_filename));
    memset(m_dispname, '\0', sizeof(m_dispname));
    m_item      = 0;
    m_itemtable = NULL;

    return ItemRead(filename);
}

/* ====================================================================== *
 *  関数名      : ItemGetTable
 *  機能        : インデックスで指定されたテーブルを取得する
 *  戻り値
 *    0         : 正常
 *    -1        : エラー
 *  修正日      : 2003/11/04
 * ====================================================================== */
int ItemGetTable(int index, T_ITEMTABLE *dest)
{
    if (index > m_item) {
        return -1;
    }

    *dest = m_itemtable[index];
    return 0;
}

/* ====================================================================== *
 *  関数名      : ItemGetRegistNum
 *  機能        : 登録数を取得する
 *  戻り値
 *    0         : 正常
 *    -1        : エラー
 *  修正日      : 2003/11/04
 * ====================================================================== */
int ItemGetRegistNum(void)
{
    return m_item;
}

/* ====================================================================== *
 *  関数名      : ItemTerm
 *  機能        : 終了処理
 *  戻り値
 *    0         : 正常
 *  修正日      : 2003/11/04
 * ====================================================================== */
int ItemTerm(void)
{
    int i;

    memset(m_filename, '\0', sizeof(m_filename));
    memset(m_dispname, '\0', sizeof(m_dispname));
    for (i = 0; i < m_item; i++) {
        free(m_itemtable[i].data);
    }
    free(m_itemtable);
    m_itemtable = NULL;
    m_item      = 0;

    return 0;
}

/* ====================================================================== *
 *  関数名      : ItemRead
 *  機能        : アイテム情報ファイルを開いて読み込む
 *  戻り値
 *    0         : 正常
 *    -1        : エラー
 *  修正日      : 2003/11/04
 * ====================================================================== */
static int ItemRead(char *filename)
{
    FILE    *fin;

    if ((fin = fopen(filename, "r")) == NULL) {
        return -1;
    }

    FileMap(fin, ItemAdd, ROVND_SYM_COMM);
    fclose(fin);

    return 0;
}

/* ====================================================================== *
 *  関数名      : ItemAdd
 *  機能        : アイテム情報を追加する
 *  戻り値
 *    0         : 正常
 *    -1        : エラー
 *  修正日      : 2003/11/04
 * ====================================================================== */
static int ItemAdd(char *src)
{
    char    *token[32];
    int     item, i;

    item = StrTokenEx(src, token, sizeof(token) / sizeof(char *), ROVND_SYM_DELIM, '"');
    if (item == -1) {
        return -1;
    }

    for (i = 0; i < item; i++) {
        // 文頭・文末の空白及び改行文字を除去
        StrTrim(token[i], " \t");
        StrTrimR(token[i], " \t\r\n");
    }

    switch (*token[0]) {
        case 'F':
            strcpy(m_filename, token[1]);
            strcpy(m_dispname, token[2]);
            break;
        case 'H':
            ItemAddTable(token);
            break;
        case 'D':
            ItemAddData(token);
            break;
        default:
            return -1;
            break;
    }

    return 0;
}

/* ====================================================================== *
 *  関数名      : ItemAddTable
 *  機能        : アイテムテーブルを追加する
 *  戻り値
 *    0         : 正常
 *    -1        : エラー
 *  修正日      : 2003/11/25
 * ====================================================================== */
static int ItemAddTable(char *token[])
{
    m_item++;
    m_itemtable = (T_ITEMTABLE *)realloc(m_itemtable, sizeof(T_ITEMTABLE) * m_item);

    m_itemtable[m_item-1].data = NULL;
    m_itemtable[m_item-1].item = 0;
    m_itemtable[m_item-1].size = 0;
    m_itemtable[m_item-1].kind = GetKind(token[1]);
    strcpy(m_itemtable[m_item-1].comment, token[2]);

    return 0;
}

/* ====================================================================== *
 *  関数名      : ItemAddData
 *  機能        : アイテム情報を追加する
 *  戻り値
 *    0         : 正常
 *    -1        : エラー
 *  修正日      : 2003/11/25
 * ====================================================================== */
static int ItemAddData(char *token[])
{
    char    *id;
    int     item;

    if (m_itemtable[m_item-1].item >= m_itemtable[m_item-1].size) {
        m_itemtable[m_item-1].size = m_itemtable[m_item-1].size * 2 + 10;
        m_itemtable[m_item-1].data = (T_ITEMINF *)realloc(m_itemtable[m_item-1].data,
                                        sizeof(T_ITEMINF) * m_itemtable[m_item-1].size);
    }

    item = m_itemtable[m_item-1].item;
    if ((id = strchr(token[1], '_')) == NULL) {
        return -1;
    }
    id++;
    m_itemtable[m_item-1].data[item].id = atoi(id);
    strcpy(m_itemtable[m_item-1].data[item].itemname, token[2]);
    strcpy(m_itemtable[m_item-1].data[item].comment,  token[8]);

    switch (m_itemtable[m_item-1].kind) {
        case DAGGER:    case SWORD:     case WSWORD:
        case SPEAR:     case AXE:       case MACE:
        case ROD:       case BOW:       case KATAL:
        case BOOK:      case CLOW:      case MUSICAL:
        case WHIP:
            m_itemtable[m_item-1].data[item].value   = atoi(token[3]);
            m_itemtable[m_item-1].data[item].weight  = atoi(token[4]);
            m_itemtable[m_item-1].data[item].slot    = atoi(token[5]);
            m_itemtable[m_item-1].data[item].eq_lv   = atoi(token[6]);
            m_itemtable[m_item-1].data[item].need_lv = atoi(token[7]);
            break;
        default:
            return -1;
    }

    item++;
    m_itemtable[item-1].item = item;

    return 0;
}
