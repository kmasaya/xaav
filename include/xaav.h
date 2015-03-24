#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/keysym.h>


/* 基本リソース */
typedef struct {
    Display *dsp;
    Window rootwin, win;
    GC gc;
    Visual *visual;
    XSizeHints hints;
    unsigned int screen;
    unsigned int depth;
    unsigned int border;
    unsigned long int cl_black, cl_white;
    char *name;
    char *font_name;
    XFontSet fontset;
} t_xres;

/* アスキーアート ファイルリソース */
typedef struct {
    char *file_name;
    char *file_data;
} t_aares;

/* ファイル 行リソース */
typedef struct {
    short int font_height;
    size_t size;
    short int y, x;
    short int max_width;
    char *buff;
    char *start, *end;
} t_lineres;


#include "xaav_user.h" // ユーザ設定
#include "xaav_prototype.h"  // プロトタイプ
