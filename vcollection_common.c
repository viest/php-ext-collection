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
#include "ext/standard/php_var.h"
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

void __key_exists (zval *key, zval *array, zval *retval) {
  zval key_exists;
  zval arg[2];

  ZVAL_COPY(&arg[1], array);
  ZVAL_COPY(&arg[0], key);

  ZVAL_STRING(&key_exists, "array_key_exists");
  if (call_user_function(EG(function_table), NULL, &key_exists, retval, 2, arg) == FAILURE) {
    zval_ptr_dtor(&arg[1]);
    zval_ptr_dtor(&arg[0]);
    zval_ptr_dtor(retval);
    ZVAL_UNDEF(retval);
  } else if (Z_ISUNDEF_P(retval)) {
    zval_ptr_dtor(&arg[1]);
    zval_ptr_dtor(&arg[0]);
    ZVAL_NULL(retval);
  }
  zval_ptr_dtor(&arg[1]);
  zval_ptr_dtor(&arg[0]);
}

void __explode (zend_string *str_arg, zval *explode_retval) {
    zval explode;
    zval args[2];
    zval cut;
    EXPLODE(&explode);
    ZVAL_STRING(&cut, ".");

    ZVAL_COPY(&args[0], &cut);
    ZVAL_STR_COPY(&args[1], str_arg);

    if (call_user_function(EG(function_table), NULL, &explode, explode_retval, 2, args) == FAILURE) {
      zval_ptr_dtor(&args[1]);
      zval_ptr_dtor(&args[0]);
      zval_ptr_dtor(explode_retval);
      ZVAL_UNDEF(explode_retval);
    } else if (Z_ISUNDEF_P(explode_retval)) {
      zval_ptr_dtor(&args[1]);
      zval_ptr_dtor(&args[0]);
      ZVAL_NULL(explode_retval);
    }
    zval_ptr_dtor(&args[1]);
    zval_ptr_dtor(&args[0]);
}

void __column (zval *array, zval *str_arg, zval *column_retval) {
  zval column;
  zval args[2];
  ARRAY_COLUMN(&column);

  ZVAL_COPY(&args[0], array);
  ZVAL_COPY(&args[1], str_arg);

  if (call_user_function(EG(function_table), NULL, &column, column_retval, 2, args) == FAILURE) {
    zval_ptr_dtor(&args[1]);
    zval_ptr_dtor(&args[0]);        
    zval_ptr_dtor(column_retval);
    ZVAL_UNDEF(column_retval);
  } else if (Z_ISUNDEF_P(column_retval)) {
    zval_ptr_dtor(&args[1]);
    zval_ptr_dtor(&args[0]);
    ZVAL_NULL(column_retval);
  }
  zval_ptr_dtor(&args[1]);
  zval_ptr_dtor(&args[0]);
}

void __strcmp (zend_string *op1, zend_string *op2, zval *retval) {
  zval strcmp;
  zval arg[2];

  ZVAL_STR_COPY(&arg[1], op1);
  ZVAL_STR_COPY(&arg[0], op2);

  STRCMP(&strcmp);

  if (call_user_function(EG(function_table), NULL, &strcmp, retval, 2, arg) == FAILURE) {
    zval_ptr_dtor(&arg[1]);
    zval_ptr_dtor(&arg[0]);        
    zval_ptr_dtor(retval);
    ZVAL_UNDEF(retval);
  } else if (Z_ISUNDEF_P(retval)) {
    zval_ptr_dtor(&arg[1]);
    zval_ptr_dtor(&arg[0]);
    ZVAL_NULL(retval);
  }
  zval_ptr_dtor(&arg[1]);
  zval_ptr_dtor(&arg[0]);
}

void __intval (zend_string *op1, zval *retval) {
  zval intval;
  zval arg[1];
  INTVAL(&intval);

  ZVAL_STR_COPY(&arg[0], op1);

  if (call_user_function(EG(function_table), NULL, &intval, retval, 1, arg) == FAILURE) {
    zval_ptr_dtor(&arg[0]);        
    zval_ptr_dtor(retval);
    ZVAL_UNDEF(retval);
  } else if (Z_ISUNDEF_P(retval)) {
    zval_ptr_dtor(&arg[0]);
    ZVAL_NULL(retval);
  }
  zval_ptr_dtor(&arg[0]);
}

void __floatval (zend_string *op1, zval *retval) {
  zval floatval;
  zval arg[1];
  FLOATVAL(&floatval);

  ZVAL_STR_COPY(&arg[0], op1);

  if (call_user_function(EG(function_table), NULL, &floatval, retval, 1, arg) == FAILURE) {
    zval_ptr_dtor(&arg[0]);        
    zval_ptr_dtor(retval);
    ZVAL_UNDEF(retval);
  } else if (Z_ISUNDEF_P(retval)) {
    zval_ptr_dtor(&arg[0]);
    ZVAL_NULL(retval);
  }
  zval_ptr_dtor(&arg[0]);
}
