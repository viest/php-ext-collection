/**********************************************************\
|                                                          |
|                       vcollec                            |
|                                                          |
| Official WebSite: http://www.vikin.cc                    |
|                                                          |
\**********************************************************/

/**********************************************************\
 *                                                        *
 * v_macroable.c                                          *
 *                                                        *
 *                                                        *
 * LastModified: Dec 18, 2016                             *
 * Author: Jiexin Wang <vikindev@outlook.com>             *
 *                                                        *
\**********************************************************/

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "../php_vcollect.h"
#include "v_macroable.h"

#include "ext/standard/php_var.h"

zend_class_entry *vcollect_macroable_trait_ce;

ZEND_BEGIN_ARG_INFO_EX(macro_arg, 0, 0, 2)
                ZEND_ARG_INFO(0, name)
                ZEND_ARG_INFO(0, macro)
ZEND_END_ARG_INFO()

PHP_METHOD(vcollect_macroable_trait, macro) {

    zval        *macros, *macro;
    zend_string *name;

    ZEND_PARSE_PARAMETERS_START(2, 2)
            Z_PARAM_STR(name)
            Z_PARAM_OBJECT(macro)
    ZEND_PARSE_PARAMETERS_END();

    macros = zend_read_static_property(vcollect_macroable_trait_ce, ZEND_STRL("macros"), 0);

    if (Z_TYPE_P(macros) != IS_ARRAY) {
        array_init(macros);
    }

    add_assoc_zval(macros, ZSTR_VAL(name), macro);

    ZVAL_COPY(return_value, macros);

    zval_ptr_dtor(macros);
    call_user_function_ex()
}

PHP_METHOD(vcollect_macroable_trait, call) {
    zval *zclosure, *newthis, closure_result;
    zend_closure *closure;
    zend_fcall_info fci;
    zend_fcall_info_cache fci_cache;
    zval *my_params;
    int my_param_count = 0;
    zend_function my_function;
    zend_object *newobj;

    if (zend_parse_parameters(ZEND_NUM_ARGS(), "o*", &newthis, &my_params, &my_param_count) == FAILURE) {
        return;
    }

    zclosure = getThis();
    closure = (zend_closure *) Z_OBJ_P(zclosure);

    newobj = Z_OBJ_P(newthis);

    if (!zend_valid_closure_binding(closure, newthis, Z_OBJCE_P(newthis))) {
        return;
    }

    /* This should never happen as closures will always be callable */
    if (zend_fcall_info_init(zclosure, 0, &fci, &fci_cache, NULL, NULL) != SUCCESS) {
        ZEND_ASSERT(0);
    }

    fci.retval = &closure_result;
    fci.params = my_params;
    fci.param_count = my_param_count;
    fci.object = fci_cache.object = newobj;
    fci_cache.initialized = 1;
    fci_cache.called_scope = Z_OBJCE_P(newthis);

    if (fci_cache.function_handler->common.fn_flags & ZEND_ACC_GENERATOR) {
        zval new_closure;
        zend_create_closure(&new_closure, fci_cache.function_handler, Z_OBJCE_P(newthis), closure->called_scope, newthis);
        closure = (zend_closure *) Z_OBJ(new_closure);
        fci_cache.function_handler = &closure->func;
    } else {
        memcpy(&my_function, fci_cache.function_handler, fci_cache.function_handler->type == ZEND_USER_FUNCTION ? sizeof(zend_op_array) : sizeof(zend_internal_function));
        /* use scope of passed object */
        my_function.common.scope = Z_OBJCE_P(newthis);
        fci_cache.function_handler = &my_function;

        /* Runtime cache relies on bound scope to be immutable, hence we need a separate rt cache in case scope changed */
        if (ZEND_USER_CODE(my_function.type) && closure->func.common.scope != Z_OBJCE_P(newthis)) {
            my_function.op_array.run_time_cache = emalloc(my_function.op_array.cache_size);
            memset(my_function.op_array.run_time_cache, 0, my_function.op_array.cache_size);
        }
    }

    if (zend_call_function(&fci, &fci_cache) == SUCCESS && Z_TYPE(closure_result) != IS_UNDEF) {
        if (Z_ISREF(closure_result)) {
            zend_unwrap_reference(&closure_result);
        }
        ZVAL_COPY_VALUE(return_value, &closure_result);
    }

    if (fci_cache.function_handler->common.fn_flags & ZEND_ACC_GENERATOR) {
        /* copied upon generator creation */
        --GC_REFCOUNT(&closure->std);
    } else if (ZEND_USER_CODE(my_function.type) && closure->func.common.scope != Z_OBJCE_P(newthis)) {
        efree(my_function.op_array.run_time_cache);
    }
}

const zend_function_entry macroable_functions[] = {
        PHP_ME(vcollect_macroable_trait, macro, macro_arg, ZEND_ACC_PUBLIC | ZEND_ACC_STATIC)
        PHP_ME(vcollect_macroable_trait, call, NULL, ZEND_ACC_PUBLIC | ZEND_ACC_STATIC)
        PHP_FE_END
};

VCOLLECT_STARTUP_FUNCTION(macroable) {
    zend_class_entry ce;

    INIT_NS_CLASS_ENTRY(ce, "Vikin\\Traits", "Macroable", macroable_functions);
    vcollect_macroable_trait_ce = zend_register_internal_class(&ce TSRMLS_CC);
    vcollect_macroable_trait_ce->ce_flags |= ZEND_ACC_TRAIT;

    zend_declare_property_null(vcollect_macroable_trait_ce, ZEND_STRL("macros"),   ZEND_ACC_PROTECTED | ZEND_ACC_STATIC);

    return SUCCESS;
}