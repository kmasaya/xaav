CC = gcc
CFLAGS = -Wall
INCLUDES = -I/usr/X11R6/include -I/usr/pkg/include -Iinclude
LIBS = -lX11 -L/usr/X11R6/lib -L/usr/pkg/lib -R/usr/X11R6/lib -R/usr/pkg/lib -std=c99 

vpath %.c src
vpath %.h include

all: xaav

xaav: xaav_main.c xaav_x.c xaav_aa.c xaav.h xaav_user.h xaav_prototype.h
	${CC} ${CFLAGS} ${LIBS} ${INCLUDES}  src/xaav*.c -o $@
