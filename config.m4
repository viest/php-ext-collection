PHP_ARG_WITH(vcollect, for vcollect support,
[  --with-vcollect             Include vcollect support])

if test "$PHP_VCOLLECT" != "no"; then
  PHP_NEW_EXTENSION(vcollect, vcollection.c vcollection_common.c vcollect.c, $ext_shared,, -DZEND_ENABLE_STATIC_TSRMLS_CACHE=1)
fi