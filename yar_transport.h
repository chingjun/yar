/*
  +----------------------------------------------------------------------+
  | Yar - Light, concurrent RPC framework                                |
  +----------------------------------------------------------------------+
  | Copyright (c) 1997-2011 The PHP Group                                |
  +----------------------------------------------------------------------+
  | This source file is subject to version 3.01 of the PHP license,      |
  | that is bundled with this package in the file LICENSE, and is        |
  | available through the world-wide-web at the following url:           |
  | http://www.php.net/license/3_01.txt                                  |
  | If you did not receive a copy of the PHP license and are unable to   |
  | obtain it through the world-wide-web, please send a note to          |
  | license@php.net so we can mail you a copy immediately.               |
  +----------------------------------------------------------------------+
  | Author:  Xinchen Hui   <laruence@php.net>                            |
  |          Zhenyu  Zhang <engineer.zzy@gmail.com>                      |
  +----------------------------------------------------------------------+
*/

/* $Id$ */

#ifndef PHP_YAR_TRANSPORT_H
#define PHP_YAR_TRANSPORT_H

typedef int yar_concurrent_client_callback(zval *calldata, void *gcallback, char *ret, size_t len TSRMLS_DC);
typedef int yar_concurrent_client_error_callback(zval *calldata, void *callback, int code, char *msg TSRMLS_DC);

typedef struct _yar_transport_interface {
	void *data;
	int  (*open)(struct _yar_transport_interface *self, char *address, uint len, char *hostname, long options TSRMLS_DC);
	int  (*send)(struct _yar_transport_interface *self, char *payload, size_t len TSRMLS_DC);
	int  (*exec)(struct _yar_transport_interface *self, char **response, size_t *len, uint *code, char **msg TSRMLS_DC);
	int  (*reset)(struct _yar_transport_interface *self TSRMLS_DC);
	int  (*calldata)(struct _yar_transport_interface *self, zval *calldata TSRMLS_DC);
	void (*close)(struct _yar_transport_interface *self TSRMLS_DC);
} yar_transport_interface_t;

typedef struct _yar_transport_multi_interface {
    void *data;
	int (*add)(struct _yar_transport_multi_interface *self, yar_transport_interface_t *cp TSRMLS_DC);
    int (*exec)(struct _yar_transport_multi_interface *self, yar_concurrent_client_callback *callback,
			yar_concurrent_client_error_callback *error_callback, void *opaque1, void *opaque2 TSRMLS_DC);
	void (*close)(struct _yar_transport_multi_interface *self TSRMLS_DC);
} yar_transport_multi_interface_t;

typedef struct _yar_transport_multi {
	struct _yar_transport_multi_interface * (*init)(TSRMLS_D);
} yar_transport_multi_t;

typedef struct _yar_transport {
	const char *name;
	struct _yar_transport_interface * (*init)(TSRMLS_D);
	void (*destroy)(yar_transport_interface_t *self TSRMLS_DC);
	yar_transport_multi_t *multi;
} yar_transport_t;

PHP_YAR_API yar_transport_t * php_yar_transport_get(char *name, int nlen TSRMLS_DC);
PHP_YAR_API int php_yar_transport_register(yar_transport_t *transport TSRMLS_DC);

#endif	/* PHP_YAR_TRANSPORT_H */

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
