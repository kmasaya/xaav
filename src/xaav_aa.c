#include "xaav.h"


/****************************************************/
// 関数名: WinSizeGet2File
// 型　　: void
// 返り値:
// 説明　: ファイルの最大幅を取得
/****************************************************/
void
WinSizeGet2File(_xres, _aares, _lineres)
     t_xres*		_xres;
     t_aares*		_aares;
     t_lineres*	_lineres;
{
  XRectangle		ink, logical;
  short int		temp_width = 0, temp_height = 0;

  /* ファイル先頭アドレスを設定 */
  _lineres->start = _aares->file_data;

  /* ファイルの最大幅を取得 */
  while(NULL != (_lineres->end = strchr(_lineres->start, '\n'))){
    _lineres->size = (size_t)(_lineres->end - _lineres->start);
    _lineres->buff = (char *)malloc((int)_lineres->size + 1);
    memcpy(_lineres->buff, _lineres->start, (int)_lineres->size);
    _lineres->buff[_lineres->size] = '\0';
    XmbTextExtents(_xres->fontset, _lineres->buff, (int)_lineres->size, &ink, &logical);
    if(temp_width < logical.width){ temp_width = logical.width;}
    free(_lineres->buff);
    _lineres->start = ++_lineres->end;
    temp_height += _lineres->font_height;
  }
  _xres->hints.width = temp_width + (INDENT_X * 2);
  _xres->hints.height = temp_height + (INDENT_Y * 2);

  return;
}


/****************************************************/
// 関数名: LineResReset
// 型　　: void
// 返り値:
// 説明　: ラインリソースの初期化
/****************************************************/
void
LineResReset(_lineres)
     t_lineres*	_lineres;
{
  _lineres->font_height = 0;
  _lineres->max_width = 0;

  _lineres->size = 0;

  _lineres->y = INDENT_Y;
  _lineres->x = INDENT_X;

  _lineres->buff = NULL;

  return;
}


/****************************************************/
// 関数名: WriteAA
// 型　　: void
// 返り値:
// 説明　: ウィンドウに文字列を書き込む
/****************************************************/
void
WriteAA(_xres, _aares, _lineres)
     t_xres*		_xres;
     t_aares*		_aares;
     t_lineres*	_lineres;
{
  _lineres->start = _aares->file_data;

  while(NULL != (_lineres->end = strchr(_lineres->start, '\n'))){
    _lineres->size = (size_t)(_lineres->end - _lineres->start);
    _lineres->buff = (char *)malloc((int)_lineres->size + 1);
    memcpy(_lineres->buff, _lineres->start, (int)_lineres->size);
    _lineres->buff[_lineres->size] = '\0';
    _lineres->y += _lineres->font_height;
    XmbDrawImageString(_xres->dsp, _xres->win, _xres->fontset, _xres->gc, _lineres->x, _lineres->y, _lineres->buff, (int)_lineres->size);
    free(_lineres->buff);
    _lineres->start = _lineres->end + 1;
  }
  _lineres->y = INDENT_Y;

  return;
}
