#include <stdio.h>
#include <ruby.h>

VALUE rb_Handlersocket;

#ifndef RARRAY_AREF
  #define RARRAY_AREF(ary,n) (RARRAY_PTR(ary)[n])
#endif

struct SocketData {
  int socket_desc;
  char* host;
  int port;
};
typedef struct SocketData SOCKET_DATA;

#include "socket/send.h"


static void hs_free(SOCKET_DATA *data) {
  close(data->socket_desc);
}

static VALUE hs_alloc(VALUE hs) {
  SOCKET_DATA *data;
  data = malloc(sizeof(SOCKET_DATA));
  return Data_Wrap_Struct(hs, NULL, hs_free, data);
}

static VALUE rb_hs_disconnect(VALUE hs) {
  SOCKET_DATA *data;
  Data_Get_Struct(hs, SOCKET_DATA, data);
  hs_free(data);

  return Qnil;
}

static VALUE rb_hs_connect(VALUE hs) {
  SOCKET_DATA *data;
  struct sockaddr_in server;

  Data_Get_Struct(hs, SOCKET_DATA, data);

  if (data->socket_desc == -1) {
    hs_free(data);
  }

  data->socket_desc = socket(AF_INET , SOCK_STREAM , 0);
  if (data->socket_desc == -1) {
      rb_warn("Could not create socket");
  }

  server.sin_addr.s_addr = inet_addr(data->host);
  server.sin_family = AF_INET;
  server.sin_port = htons(data->port);

  if (connect(data->socket_desc , (struct sockaddr *)&server , sizeof(server)) < 0) {
    rb_raise(rb_eStandardError, "HS: connect error");
  }

  return Qnil;
}

static VALUE rb_hs_reconnect(VALUE hs) {
  rb_hs_disconnect(hs);
  rb_hs_connect(hs);

  return Qnil;
}

static VALUE rb_hs_initialize(VALUE hs, VALUE host, VALUE port) {
  SOCKET_DATA *data;
  Data_Get_Struct(hs, SOCKET_DATA, data);

  data->host = StringValuePtr(host);
  data->port = NUM2INT(port);
  data->socket_desc = -1;

  rb_hs_connect(hs);

  return Qnil;
}


void Init_handlersocket_ext(void) {
  rb_Handlersocket = rb_const_get(rb_cObject, rb_intern("Handlersocket"));

  rb_define_alloc_func(rb_Handlersocket, hs_alloc);
  rb_define_method(rb_Handlersocket, "initialize", rb_hs_initialize, 2);
  rb_define_method(rb_Handlersocket, "connect", rb_hs_connect, 0);
  rb_define_method(rb_Handlersocket, "disconnect", rb_hs_disconnect, 0);
  rb_define_method(rb_Handlersocket, "reconnect", rb_hs_reconnect, 0);
  rb_define_method(rb_Handlersocket, "query", rb_hs_query, 1);
}
