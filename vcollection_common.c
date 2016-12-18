/**********************************************************\
|                                                          |
|                       vcollec                            |
|                                                          |
| Official WebSite: http://www.vikin.cc                    |
|                                                          |
\**********************************************************/

/**********************************************************\
 *                                                        *
 * vcollection_common.c                                   *
 *                                                        *
 *                                                        *
 * LastModified: Dec 18, 2016                             *
 * Author: Wang Jiexin <vikindev@outlook.com>             *
 *                                                        *
\**********************************************************/


#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "vcollection_common.h"

void __get_array_max (HashTable *htbl, double *retval) {
  zval *value;

  ZEND_HASH_FOREACH_VAL(htbl, value) {
    if(Z_TYPE_P(value) == IS_ARRAY || Z_TYPE_P(value) == IS_OBJECT || Z_TYPE_P(value) == IS_STRING) {
      continue;
    }
    if (Z_TYPE_P(value) == IS_LONG) {
      if ((double)(Z_LVAL_P(value)) > *retval) {
          *retval = (double)(Z_LVAL_P(value));
      }
    }
    if (Z_TYPE_P(value) == IS_DOUBLE) {
      if ((Z_DVAL_P(value)) > *retval) {
        *retval = Z_DVAL_P(value);
      }
    }
  } ZEND_HASH_FOREACH_END();
}

void __get_array_min (HashTable *htbl, double *retval) {
  zval *value;
  int num = 0;

  ZEND_HASH_FOREACH_VAL(htbl, value) {
    if(Z_TYPE_P(value) == IS_ARRAY || Z_TYPE_P(value) == IS_OBJECT || Z_TYPE_P(value) == IS_STRING) {
      continue;
    }
    if(num == 0) {
      *retval = (double)(Z_LVAL_P(value));
    }
    if (Z_TYPE_P(value) == IS_LONG) {
      if ((double)(Z_LVAL_P(value)) < *retval) {
          *retval = (double)(Z_LVAL_P(value));
      }
    }
    if (Z_TYPE_P(value) == IS_DOUBLE) {
      if ((Z_DVAL_P(value)) < *retval) {
        *retval = Z_DVAL_P(value);
      }
    }
    num++;
  } ZEND_HASH_FOREACH_END();
}

void __get_collect_pluck(zval *array, zend_string *args, zval *retval) {
  zval column;
  zval explode;
  zval cut;
  zval ex_args[2];
  zval mn_args[2];
  zval explode_ret_val;
  zval column_ret_val;
  zval *value;
  int num = 0;

  ARRAY_COLUMN(&column);
  EXPLODE(&explode);
  ZVAL_STRING(&cut, ".");
  ZVAL_COPY(&ex_args[0], &cut);
  ZVAL_STR_COPY(&ex_args[1], args);

  if (call_user_function(EG(function_table), NULL, &explode, &explode_ret_val, 2, ex_args) == FAILURE) {
		zval_ptr_dtor(&ex_args[1]);
		zval_ptr_dtor(&ex_args[0]);
		zval_ptr_dtor(&explode_ret_val);
		ZVAL_UNDEF(&explode_ret_val);
	} else if (Z_ISUNDEF(explode_ret_val)) {
		zval_ptr_dtor(&ex_args[1]);
		zval_ptr_dtor(&ex_args[0]);
		ZVAL_NULL(&explode_ret_val);
	}

	if(Z_TYPE(explode_ret_val) != IS_ARRAY) {
		zval_dtor(&explode_ret_val);
		ZVAL_NULL(retval);
	}else if (Z_TYPE(explode_ret_val) == IS_ARRAY) {
    ZEND_HASH_FOREACH_VAL(Z_ARRVAL(explode_ret_val), value)
  	{
      ZVAL_COPY(&mn_args[1], value);

  		if(num == 0) {
  			ZVAL_COPY(&mn_args[0], array);
  			if (call_user_function(EG(function_table), NULL, &column, &column_ret_val, 2, mn_args) == FAILURE) {
  				zval_ptr_dtor(&mn_args[1]);
  				zval_ptr_dtor(&mn_args[0]);
  				zval_ptr_dtor(&column_ret_val);
  				ZVAL_UNDEF(&column_ret_val);
  			} else if (Z_ISUNDEF(column_ret_val)) {
          zval_ptr_dtor(&mn_args[1]);
  				zval_ptr_dtor(&mn_args[0]);
  				ZVAL_NULL(&column_ret_val);
  			}
  			num++;
  			continue;
  		}
  		ZVAL_COPY(&mn_args[0], &column_ret_val);
  		if (call_user_function(EG(function_table), NULL, &column, &column_ret_val, 2, mn_args) == FAILURE) {
  				zval_ptr_dtor(&mn_args[1]);
  				zval_ptr_dtor(&mn_args[0]);
  				zval_ptr_dtor(&column_ret_val);
  				ZVAL_UNDEF(&column_ret_val);
  			} else if (Z_ISUNDEF(column_ret_val)) {
  				zval_ptr_dtor(&mn_args[1]);
  				zval_ptr_dtor(&mn_args[0]);
  				ZVAL_NULL(&column_ret_val);
  			}
  	} ZEND_HASH_FOREACH_END();

    ZVAL_COPY(retval, &column_ret_val);
  }
}
