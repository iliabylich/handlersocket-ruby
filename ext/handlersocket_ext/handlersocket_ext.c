#include <stdio.h>
#include <ruby.h>

VALUE rb_Handlersocket;

#ifndef RARRAY_AREF
  #define RARRAY_AREF(ary,n) (RARRAY_PTR(ary)[n])
#endif

#include "socket/send.h"


static void hs_free(int *socket_desc) {
  close(*socket_desc);
}

static VALUE hs_alloc(VALUE hs) {
  int *socket_desc;
  socket_desc = malloc(sizeof(int));
  return Data_Wrap_Struct(hs, NULL, hs_free, socket_desc);
}

static VALUE rb_hs_initialize(VALUE hs, VALUE r_host, VALUE r_port) {
  int socket_desc, port;
  char *host;
  int *data;

  struct sockaddr_in server;

  host = StringValuePtr(r_host);
  port = NUM2INT(r_port);

  socket_desc = socket(AF_INET , SOCK_STREAM , 0);
  if (socket_desc == -1) {
      rb_warn("Could not create socket");
  }

  server.sin_addr.s_addr = inet_addr(host);
  server.sin_family = AF_INET;
  server.sin_port = htons(port);

  // connect
  if (connect(socket_desc , (struct sockaddr *)&server , sizeof(server)) < 0) {
    rb_raise(rb_eStandardError, "HS: connect error");
  }

  Data_Get_Struct(hs, int, data);

  *data = socket_desc;

  return Qnil;
}


void Init_handlersocket_ext(void) {
  rb_Handlersocket = rb_const_get(rb_cObject, rb_intern("Handlersocket"));
  // init_handlersocket_constants();

  rb_define_alloc_func(rb_Handlersocket, hs_alloc);
  rb_define_method(rb_Handlersocket, "initialize", rb_hs_initialize, 2);
  rb_define_method(rb_Handlersocket, "query", rb_hs_query, 1);
}
