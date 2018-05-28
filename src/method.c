/*
  +----------------------------------------------------------------------+
  | Collection Extension                                                 |
  +----------------------------------------------------------------------+
  | Copyright (c) 2016-2018 The Viest                                    |
  +----------------------------------------------------------------------+
  | http://www.viest.me                                                  |
  +----------------------------------------------------------------------+
  | Author: viest <dev@service.viest.me>                                 |
  +----------------------------------------------------------------------+
*/

#include "include.h"

/** {{{ \Vtiful\Kernel\Collection::__construct()
 */
PHP_METHOD(vtiful_collection, __construct)
{

}
/* }}} */

/** {{{ \Vtiful\Kernel\Collection::__clone()
 */
PHP_METHOD(vtiful_collection, __clone)
{

}
/* }}} */

/** {{{ \Vtiful\Kernel\Collection::init([array $collection])
 */
PHP_METHOD(vtiful_collection, init)
{
    zval *collection = NULL;

    ZEND_PARSE_PARAMETERS_START(0, 1)
            Z_PARAM_OPTIONAL
            Z_PARAM_ARRAY(collection)
    ZEND_PARSE_PARAMETERS_END();

    object_init_ex(return_value, vtiful_collection_ce);

    if (collection != NULL) {
        zend_object *obj = Z_OBJ_P(return_value);
        obj->properties  = Z_ARRVAL_P(collection);
    }
}
/* }}} */

/** {{{ \Vtiful\Kernel\Collection::map(closures $callback)
 */
PHP_METHOD(vtiful_collection, map)
{
    zend_fcall_info       fci       = empty_fcall_info;
    zend_fcall_info_cache fci_cache = empty_fcall_info_cache;

    ZEND_PARSE_PARAMETERS_START(1, 1)
            Z_PARAM_FUNC(fci, fci_cache)
    ZEND_PARSE_PARAMETERS_END();

    INIT_FCALL(2)

    ZEND_HASH_FOREACH_BUCKET(CURRENT_COLLECTION, Bucket* bucket)
            FCALL_TWO_ARGS(bucket)
    ZEND_HASH_FOREACH_END();
}
/* }}} */

/** {{{ \Vtiful\Kernel\Collection::count()
 */
PHP_METHOD(vtiful_collection, count)
{

}
/* }}} */

/** {{{ \Vtiful\Kernel\Collection::toArray()
 */
PHP_METHOD(vtiful_collection, toArray)
{
    zval *empty;

    array_init(empty);

    ZVAL_COPY(return_value, empty);
}
/* }}} */