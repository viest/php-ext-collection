dnl $Id$
dnl config.m4 for extension vcollect

dnl Comments in this file start with the string 'dnl'.
dnl Remove where necessary. This file will not work
dnl without editing.

dnl If your extension references something external, use with:

dnl PHP_ARG_WITH(vcollect, for vcollect support,
dnl Make sure that the comment is aligned:
dnl [  --with-vcollect             Include vcollect support])

dnl Otherwise use enable:

dnl PHP_ARG_ENABLE(vcollect, whether to enable vcollect support,
dnl Make sure that the comment is aligned:
dnl [  --enable-vcollect           Enable vcollect support])

if test "$PHP_VCOLLECT" != "no"; then
  dnl Write more examples of tests here...

  dnl # --with-vcollect -> check with-path
  dnl SEARCH_PATH="/usr/local /usr"     # you might want to change this
  dnl SEARCH_FOR="/include/vcollect.h"  # you most likely want to change this
  dnl if test -r $PHP_VCOLLECT/$SEARCH_FOR; then # path given as parameter
  dnl   VCOLLECT_DIR=$PHP_VCOLLECT
  dnl else # search default path list
  dnl   AC_MSG_CHECKING([for vcollect files in default path])
  dnl   for i in $SEARCH_PATH ; do
  dnl     if test -r $i/$SEARCH_FOR; then
  dnl       VCOLLECT_DIR=$i
  dnl       AC_MSG_RESULT(found in $i)
  dnl     fi
  dnl   done
  dnl fi
  dnl
  dnl if test -z "$VCOLLECT_DIR"; then
  dnl   AC_MSG_RESULT([not found])
  dnl   AC_MSG_ERROR([Please reinstall the vcollect distribution])
  dnl fi

  dnl # --with-vcollect -> add include path
  dnl PHP_ADD_INCLUDE($VCOLLECT_DIR/include)

  dnl # --with-vcollect -> check for lib and symbol presence
  dnl LIBNAME=vcollect # you may want to change this
  dnl LIBSYMBOL=vcollect # you most likely want to change this 

  dnl PHP_CHECK_LIBRARY($LIBNAME,$LIBSYMBOL,
  dnl [
  dnl   PHP_ADD_LIBRARY_WITH_PATH($LIBNAME, $VCOLLECT_DIR/$PHP_LIBDIR, VCOLLECT_SHARED_LIBADD)
  dnl   AC_DEFINE(HAVE_VCOLLECTLIB,1,[ ])
  dnl ],[
  dnl   AC_MSG_ERROR([wrong vcollect lib version or lib not found])
  dnl ],[
  dnl   -L$VCOLLECT_DIR/$PHP_LIBDIR -lm
  dnl ])
  dnl
  dnl PHP_SUBST(VCOLLECT_SHARED_LIBADD)

  PHP_NEW_EXTENSION(vcollect, vcollect.c, $ext_shared,, -DZEND_ENABLE_STATIC_TSRMLS_CACHE=1)
fi
