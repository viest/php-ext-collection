PHP_ARG_WITH(collection, for collection support,
[  --with-collection             Include collection support])

if test "$PHP_COLLECTION" != "no"; then
  PHP_ADD_EXTENSION_DEP(collection, ds)

  PHP_NEW_EXTENSION(collection, collection.c src/kernel.c src/method.c src/exception.c, $ext_shared,, -DZEND_ENABLE_STATIC_TSRMLS_CACHE=1)

  PHP_ADD_BUILD_DIR([$ext_builddir/src])
fi