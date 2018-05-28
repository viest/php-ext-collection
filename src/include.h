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

#ifndef PHP_EXT_COLLECTION_INCLUDE_H
#define PHP_EXT_COLLECTION_INCLUDE_H

#include <php.h>

#include "zend_exceptions.h"
#include "zend.h"
#include "zend_API.h"
#include "php.h"

#include "../php_collection.h"

// Class
extern zend_class_entry *vtiful_collection_ce;
extern zend_class_entry *vtiful_collection_exception_ce;

// Startup Module
COLLECTION_STARTUP_FUNCTION(exception);
COLLECTION_STARTUP_FUNCTION(kernel);

// Kernel Class Method
PHP_METHOD(vtiful_collection, __construct);
PHP_METHOD(vtiful_collection, __clone);
PHP_METHOD(vtiful_collection, init);
PHP_METHOD(vtiful_collection, map);
PHP_METHOD(vtiful_collection, count);
PHP_METHOD(vtiful_collection, toArray);

// Define
#define CURRENT_COLLECTION Z_OBJ_P(getThis())->properties

#define INIT_FCALL(arg_num)          \
        zval args[arg_num], ret_val; \
        fci.param_count = arg_num;   \
        fci.retval      = &ret_val;  \
        fci.params      = args;

#define FCALL_TWO_ARGS(bucket)                   \
        ZVAL_COPY_VALUE(&args[0], &bucket->val); \
        if (bucket->key) {                       \
            ZVAL_STR(&args[1], bucket->key);     \
        } else {                                 \
            ZVAL_LONG(&args[1], bucket->h);      \
        }                                        \
        zend_call_function(&fci, &fci_cache);    \

#endif
