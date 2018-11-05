/* ====================================================================== *
 *  ファイル名  : ROVND_Common.h
 *  概要        : ROVND共通ヘッダファイル
 *  作成者      : clown
 *  修正日      : 2003/11/25
 * ====================================================================== */
#ifndef ROVND_COMMON_H
#define ROVND_COMMON_H

#define ROVND_MAX_BUFSIZE       1024        // 最大バッファサイズ
#define ROVND_MAX_FNAMESIZE     32          // ファイル名の最大文字列長
#define ROVND_MAX_INAMESIZE     64          // アイテム名の最大文字列長
#define ROVND_MAX_COMMSIZE      256         // コメントの最大文字列長
#define ROVND_MAX_PDIGIT        16          // 価格の最大桁数
#define ROVND_MAX_DATESIZE      16          // 日付の文字列長

#define ROVND_SYM_DELIM         ":"
#define ROVND_SYM_COMM          '#'

typedef enum {
    DAGGER,
    SWORD,
    WSWORD,
    SPEAR,
    AXE,
    MACE,
    ROD,
    BOW,
    KATAL,
    BOOK,
    CLOW,
    MUSICAL,
    WHIP
} T_KIND;

typedef struct {                                // 価格情報を格納する構造体
    char    item_name[ROVND_MAX_INAMESIZE];     // アイテム名
    char    min_price[ROVND_MAX_PDIGIT];        // 最安値
    char    max_price[ROVND_MAX_PDIGIT];        // 最高値
    char    update[ROVND_MAX_DATESIZE];         // 更新日付
} T_PINF;

typedef struct {                                // アイテム情報
    int         id;                             // ID番号(データ上ではkind_id)
    char        itemname[ROVND_MAX_INAMESIZE+1];// アイテム名
    char        comment[ROVND_MAX_COMMSIZE+1];  // コメント
    int         value;                          // ATK/DEF
    int         weight;                         // 重さ
    int         slot;                           // スロット
    int         eq_lv;                          // 武器/防具Lv
    int         need_lv;                        // 要求Lv
} T_ITEMINF;

typedef struct {                                // アイテムテーブル
    int         kind;                           // 種別
    char        comment[ROVND_MAX_COMMSIZE+1];  // コメント
    T_ITEMINF   *data;                          // アイテム情報
    int         item;                           // データ数
    int         size;                           // 確保されている領域サイズ
} T_ITEMTABLE;

extern int  g_kindnum;
extern char g_itemkind[][4];
extern char g_j_itemkind[][256];

#endif  // ROVND_COMMON_H
