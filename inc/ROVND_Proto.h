/* ====================================================================== *
 *  ファイル名  : ROVND_Proto.h
 *  概要        : 関数プロトタイプ宣言
 *  作成者      : clown
 *  修正日      : 2003/11/04
 * ====================================================================== */
#include "ROVND_Common.h"

/*
 * 価格情報の管理の為の関数
 */
int PInfInit(char *filename);
int PInfGet(int index, T_PINF *dest);
int PInfGetRegistNum(void);
int PInfRead(char *filename);
int PInfAdd(char *src);
int PInfTerm(void);

/*
 * アイテム情報の管理の為の関数
 */
int ItemInit(char *filename);
int ItemGetTable(int index, T_ITEMTABLE *dest);
int ItemGetRegistNum(void);
int ItemTerm(void);

/*
 * その他各種関数
 */
int GetKind(char *element);
