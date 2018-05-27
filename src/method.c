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
PHP_METHOD(collection, __construct)
{

}
/* }}} */

/** {{{ \Vtiful\Kernel\Collection::init([array $collection])
 */
PHP_METHOD(collection, init)
{
    zval *collection = NULL;

    ZEND_PARSE_PARAMETERS_START(0, 1)
        Z_PARAM_OPTIONAL
        Z_PARAM_ARRAY(collection)
    ZEND_PARSE_PARAMETERS_END();

//    if (collection == NULL) {
//        NEW_NULL_PROPERTIES_COLLECTION(collection_ce);
//    }
//
//    NEW_COLLECTION_OBJECT(collection_ce, collection);
}
/* }}} */

/** {{{ \Vtiful\Kernel\Collection::clear()
 */
PHP_METHOD(collection, clear)
{

}
/* }}} */

/** {{{ \Vtiful\Kernel\Collection::copy()
 */
PHP_METHOD(collection, copy)
{

}
/* }}} */

/** {{{ \Vtiful\Kernel\Collection::count()
 */
PHP_METHOD(collection, count)
{

}
/* }}} */

/** {{{ \Vtiful\Kernel\Collection::isEmpty()
 */
PHP_METHOD(collection, isEmpty)
{

}
/* }}} */

/** {{{ \Vtiful\Kernel\Collection::jsonSerialize()
 */
PHP_METHOD(collection, jsonSerialize)
{

}
/* }}} */

/** {{{ \Vtiful\Kernel\Collection::toArray()
 */
PHP_METHOD(collection, toArray)
{

}
/* }}} */