/******************************************************************************
 *	ソフトウェアライブラリ
 *
 *	Copyright (c) 1994 SEGA
 *
 * Library:ファイルシステム
 * Module :SIMMファイルアクセスモジュールヘッダ
 * File	  :gfs_mmf.h
 * Date   :1994-11-11
 * Version:1.16
 * Auther :M.S.
 *
 *************************************************************************** */

#if !defined(GFS_MMF_H)
#define     GFS_MMF_H

/*****************************************************************************
 *	インクルードファイル
 *****************************************************************************/

/*****************************************************************************
 *	定数マクロ
 *****************************************************************************/

/*****************************************************************************
 *	列挙定数
 *****************************************************************************/

/*****************************************************************************
 *	処理マクロ
 *****************************************************************************/

/*****************************************************************************
 *	データ型の定義
 *****************************************************************************/

/*****************************************************************************
 *	変数の宣言
 *****************************************************************************/

/*****************************************************************************
 *	関数の宣言
 *****************************************************************************/

/*  MMFの初期化	*/
Bool GFMF_Init(void);

/*  flow-in管理構造体の初期化 */
void GFMF_Setup(GfsFlow *flow, GfsDirId *dirrec, Sint32 fid);

/*  メモリバッファへのデータ読み込み */
Sint32 GFMF_FlowInBuf(GfsFlow *flow);

void GFMF_StopInBuf(GfsFlow *flow, Bool stop_flag);

/*  アクセスポインタ設定 */
Sint32 GFMF_Seek(GfsFlow *flow, Sint32 off);

/*  アクセスポインタ取得 */
Sint32 GFMF_Tell(GfsFlow *flow);

#endif      /* GFS_MMF_H */

/* end of file */
