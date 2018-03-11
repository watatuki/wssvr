# autoconf sample

# このファイルがターゲットしている最古のautoconfツールバージョン。おまじないなので触らない。
AC_PREREQ([2.69])

# exsampleがプロジェクト名、1.0がバージョン名なので、適切に設定する
AC_INIT([wssvr], [1.0])

# foreign: GNU標準のファイルがなくてもautoconfを実行できるようにするおまじないなので変更しない
# subdir-objects: ビルドしたオブジェクトファイルをサブディレクトリに配置する指定
AM_INIT_AUTOMAKE([foreign subdir-objects])

# ソースファイル名を指定。ここに書いてあるファイルを消すとconfigureができなくなる。main関数を持つソースファイルを書く。ライブラリのみの場合は、メイン処理を持つファイルを書く。
AC_CONFIG_SRCDIR([src/wssvr.cpp])

# configureの設定を格納するファイルの名前
AC_CONFIG_HEADERS([include/config.h])

# m4マクロの出力ディレクトリの指定、デフォルトのまま変えない
AC_CONFIG_MACRO_DIR([m4])


#自分用のconfigureオプションの作成
#デバッグ用の設定だけは作っておいたほうが良い
AC_ARG_ENABLE([userdebug],
  [AS_HELP_STRING([--enable-userdebug], [Enable user debuging function (default is no)])],
  [:],
  [enable_userdebug=no])
AM_CONDITIONAL([ENABLE_USERDEBUG], [test "$enable_userdebug" = "yes"])

#これはPRINTFDEBUGのコンフィグを作成する例なので不要なら消すこと
AC_ARG_ENABLE([printfdebug],
  [AS_HELP_STRING([--enable-printfdebug], [Enable user printf debug (default is no)])],
  [:],
  [enable_printfdebug=no])
AM_CONDITIONAL([ENABLE_PRINTFDEBUG], [test "$enable_printfdebug" = "yes"])
#PRINTFDEBUGここまで

# Checks for programs.
#C言語を使用する。ソースをCで書く場合は必須
AC_PROG_CC

#C++を使用する。ソースをC++で書く場合は必須
AC_PROG_CXX

#make installを使う。必須設定。
AC_PROG_INSTALL


# 静的ライブラリのデフォルト設定を無効(ビルドしない)にする
AC_DISABLE_STATIC

# Checks for libraries.
#libtoolを使う。シェアードライブラリを生成する場合に必要
LT_INIT
AM_PROG_LIBTOOL 

#Package Configの設定。依存しているライブラリをすべて記述する。
#ここを記載しないと、includeパスの設定やライブラリのリンク設定が行われなくなる。
PKG_PROG_PKG_CONFIG
PKG_CHECK_MODULES([LIBWEBSOCKETS], [libwebsockets])


# Checks for header files.

# Checks for typedefs, structures, and compiler characteristics.

# Checks for library functions.

AC_CONFIG_FILES([Makefile 
				src/Makefile ])
AC_OUTPUT

