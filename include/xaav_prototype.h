/* main.c */
void LoadFile(t_aares *);  // ファイル読み込み
void ChangeFile(int, char **, t_aares *, short int);  // ファイル切り替え
void EventExpose(int, char **, t_xres *, t_aares *, t_lineres *);  // Expose

/* xaav_aa.c */
void WinSizeGet2File(t_xres *, t_aares *, t_lineres *);  // ファイル最大幅の取得
void LineResReset(t_lineres *);  // 行リソースの初期化
void WriteAA(t_xres *, t_aares *, t_lineres *);  // ウインドウに文字列を書き込む

/* xaav_x.c */
void XResReset(t_xres *);  // Xリソースの初期設定
void XWinOpen(int, char **, t_xres *);  // ウインドウの作成
void XResFree(t_xres *);  // リソースの解放
void FontSet(t_xres *, t_aares *, t_lineres *);  // フォントセット
void WinResizeHints(t_xres *);  // ウインドウをリサイズ
