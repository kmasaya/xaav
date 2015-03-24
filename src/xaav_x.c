#include "xaav.h"


/****************************************************/
// 関数名: XResReset
// 型　　: void
// 返り値:
// 説明　: Xリソースの初期設定
/****************************************************/
void
XResReset(_xres)
     t_xres*		_xres;
{
  _xres->dsp 	 = XOpenDisplay("");
  _xres->screen  = XDefaultScreen(_xres->dsp);
  _xres->rootwin = XDefaultRootWindow(_xres->dsp);
  _xres->depth   = XDefaultDepth(_xres->dsp, _xres->screen);
  _xres->visual  = XDefaultVisual(_xres->dsp, _xres->screen);

  _xres->cl_black = XBlackPixel(_xres->dsp, _xres->screen);
  _xres->cl_white = XWhitePixel(_xres->dsp, _xres->screen);
 
  _xres->hints.x = WIN_X; _xres->hints.y = WIN_Y;
  _xres->hints.width = WIN_WIDTH; _xres->hints.height = WIN_HEIGHT;
  _xres->hints.flags = PPosition | PSize;
  _xres->border = 1;
  _xres->name = WIN_NAME;

  _xres->font_name = FONT_NAME;

  return;
}


/****************************************************/
// 関数名: XWinOpen
// 型　　: void
// 返り値:
// 説明　: ウィンドウの作成、ウィンドウにプロパティをセット、GCを作成、入力イベントを設定、最前面にマップ
/****************************************************/
void
XWinOpen(argc, argv, _xres)
     int		argc;
     char**		argv;
     t_xres*		_xres;
{
  _xres->win = XCreateSimpleWindow(_xres->dsp, _xres->rootwin, _xres->hints.x, _xres->hints.y, _xres->hints.width, _xres->hints.height, _xres->border,  _xres->cl_white, _xres->cl_black);
  XSetStandardProperties(_xres->dsp, _xres->win, _xres->name, _xres->name, None, argv, argc, &_xres->hints);

  _xres->gc = XCreateGC(_xres->dsp, _xres->win, 0, 0);
  XSetBackground(_xres->dsp, _xres->gc, _xres->cl_black);
  XSetForeground(_xres->dsp, _xres->gc, _xres->cl_white);

  XSelectInput(_xres->dsp,  _xres->win, ButtonPressMask | KeyPressMask | ExposureMask);

  XMapRaised(_xres->dsp, _xres->win);

  return;
}


/****************************************************/
// 関数名: XResFree
// 型　　: void
// 返り値:
// 説明　: プログラム終了時のウィンドウリソースの後始末
/****************************************************/
void
XResFree(_xres)
     t_xres*		_xres;
{
  XFreeGC(_xres->dsp,  _xres->gc);
  XDestroyWindow(_xres->dsp, _xres->win);
  XCloseDisplay(_xres->dsp);

  return;
}


/****************************************************/
// 関数名: XFontSet
// 型　　: void
// 返り値:
// 説明　: 使用するフォントをセット
/****************************************************/
void
FontSet(_xres, _aares, _lineres)
     t_xres*		_xres;
     t_aares*		_aares;
     t_lineres*	_lineres;
{
  XFontSetExtents*	font_extents;
  char**		miss_char;
  int			miss_count;
  char*			def;

  _xres->fontset = XCreateFontSet(_xres->dsp, _xres->font_name, &miss_char, &miss_count, &def);
  font_extents = XExtentsOfFontSet(_xres->fontset);
  _lineres->font_height = font_extents->max_ink_extent.height;
  
  return;
}


/****************************************************/
// 関数名: WinResizeHints
// 型　　: void
// 返り値:
// 説明　: ウィンドウをウィンドウヒントに合わせてリサイズ
/****************************************************/
void
WinResizeHints(_xres)
     t_xres*		_xres;
{
  XResizeWindow(_xres->dsp, _xres->win, _xres->hints.width, _xres->hints.height);

  return;
}
