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

//#define NEW_NULL_PROPERTIES_COLLECTION(class_name)            \
//    do {                                                      \
//        zend_object *intern = ecalloc(1, sizeof(zend_object) + zend_object_properties_size(class_name)); \
//        zend_object_std_init(intern, class_name); \
//        object_properties_init(intern, class_name); \
//        intern->handlers = &collection_handlers; \
//    } while(0)
//
//#define NEW_COLLECTION_OBJECT(class_name, properties_array)   \
//    do {                                                      \
//        zend_object *intern = ecalloc(1, sizeof(zend_object) + zend_object_properties_size(class_name)); \
//        zend_object_std_init(intern, class_name); \
//        object_properties_init(intern, class_name); \
//        intern->handlers = &collection_handlers; \
//        zo->properties  = properties_array;\
//    } while(0)


// Startup Module
COLLECTION_STARTUP_FUNCTION(exception);
COLLECTION_STARTUP_FUNCTION(kernel);

// Kernel Class Method
PHP_METHOD(collection, __construct);
PHP_METHOD(collection, init);
PHP_METHOD(collection, clear);
PHP_METHOD(collection, copy);
PHP_METHOD(collection, count);
PHP_METHOD(collection, isEmpty);
PHP_METHOD(collection, jsonSerialize);
PHP_METHOD(collection, toArray);

#endif
