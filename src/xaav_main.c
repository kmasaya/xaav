#include "xaav.h"


/****************************************************/
// 関数名: ChangeFile
// 型　　: void
// 返り値:
// 説明　: ファイルを切替える
/****************************************************/
void
ChangeFile(argc, argv, _aares, a_num)
     int		argc;
     char**		argv;
     t_aares*		_aares;
     short int		a_num;
{
  static short int	 ls_filename = 1;

  ls_filename += a_num;
  if(0 < ls_filename && ls_filename < argc){
    _aares->file_name = argv[ls_filename];
  } else{
    ls_filename -= a_num;
  }

  return;
}


/****************************************************/
// 関数名: LoadFile
// 型　　: void
// 返り値:
// 説明　: ファイルの読み込み
/****************************************************/
void
LoadFile(_aares)
     t_aares*		_aares;
{
  struct stat		file_status;
  FILE*			aa_file;

  if(stat(_aares->file_name, &file_status) != 0){
    fprintf(stderr, "%s NOT FOUND\n", _aares->file_name);
    exit(0);
  }

  _aares->file_data = malloc(file_status.st_size + 2);

  aa_file = fopen(_aares->file_name, "r");
  fread(_aares->file_data, file_status.st_size, 1, aa_file); 
  fclose(aa_file);

  if('\n' != _aares->file_data[file_status.st_size - 1]){
    _aares->file_data[file_status.st_size] = '\n';
  } else{
    _aares->file_data[file_status.st_size] = '\0';
  }
  _aares->file_data[file_status.st_size + 1] = '\0';

  return;
}


/****************************************************/
// 関数名: EventExpose
// 型　　: void
// 返り値:
// 説明　: Exposeが起きたときの処理
/****************************************************/
void
EventExpose(argc, argv, _xres, _aares, _lineres)
     int		argc;
     char**		argv;
     t_xres*		_xres;
     t_aares*		_aares;
     t_lineres*		_lineres;
{
  LoadFile(_aares);
  WinSizeGet2File(_xres, _aares, _lineres);
  WinResizeHints(_xres);
  XClearWindow(_xres->dsp, _xres->win);
  WriteAA(_xres, _aares, _lineres);
  free(_aares->file_data);

  return;
}


/****************************************************/
// 関数名: main
// 型　　: void
// 返り値:
// 説明　: メイン
/****************************************************/
int
main(argc, argv)
     int		argc;
     char**		argv;
{
  t_xres		_xres;
  t_aares		_aares;
  t_lineres		_lineres;
  XEvent		l_event;
  KeySym		l_keysym;

  setlocale(LC_CTYPE, "");

  _aares.file_name = argv[1];

  XResReset(&_xres);
  LineResReset(&_lineres);

  XWinOpen(argc, argv, &_xres);
  FontSet(&_xres, &_aares, &_lineres);

  short int		done = 0;
  while(0 == done){
    XNextEvent(_xres.dsp, &l_event);
    switch(l_event.type){
    case Expose:
      EventExpose(argc, argv, &_xres, &_aares, &_lineres);
      break;
    case KeyPress:
      l_keysym = XKeycodeToKeysym(_xres.dsp, l_event.xkey.keycode, 0 );
      if(QUIT == l_keysym){
	done = 1;
      } else if(NEXT == l_keysym){
	ChangeFile(argc, argv, &_aares, 1);
      } else if(PREV == l_keysym){
	ChangeFile(argc, argv, &_aares, -1);
      }
      EventExpose(argc, argv, &_xres, &_aares, &_lineres);
      break;
    }
  }

  XResFree(&_xres);

  return 0;
}
 
