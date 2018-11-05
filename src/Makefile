# ====================================================================== #
#  [ROVND Makefile]
#  製作者       : clown
#  最終修正日   : 2003/11/25
# ====================================================================== #

## 実行ファイル情報
ROOT    = ../..
INSTALL = $(ROOT)/ROVND
PACKAGE = rovnd

## ソース情報
BINDIR  = $(INSTALL)
LIBDIR  = $(ROOT)/CMN

INCS    = $(BINDIR)/inc/ROVND_Common.h \
          $(BINDIR)/inc/ROVND_Proto.h \
          $(LIBDIR)/inc/FileTreat.h \
          $(LIBDIR)/inc/StrTreat.h
OBJS    = ROVND_Define.o \
          ROVND_ItemManager.o \
          ROVND_PInfManager.o \
          ROVND_GetKind.o \
          ROVND_Main.o
LIBS    = $(LIBDIR)/libCMN.a

## 各種フラグ
CC      = gcc
RM      = rm -f

IFLAGS  = -I$(LIBDIR)/inc -I$(BINDIR)/inc
DFLAGS  =
CFLAGS  = $(IFLAGS) $(DFLAGS)

## Make Rule
all         : $(PACKAGE)

$(PACKAGE)  : $(OBJS) $(LIBS) $(INCS) Makefile
	$(CC) $(CFLAGS) -o $(INSTALL)/$(PACKAGE) $(OBJS) $(LIBS)

clean       :
	$(RM) $(INSTALL)/$(PACKAGE)
	$(RM) $(OBJS) *~ #*#

