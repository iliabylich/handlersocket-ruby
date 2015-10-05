#include <stdio.h>
#include <ruby.h>

VALUE rb_Handlersocket;

#include "constants.h"
#include "logging.h"

#include "socket/send.h"
#include "commands/open_index.h"
#include "commands/find.h"


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
      rb_warn("connect error");
  }

  Data_Get_Struct(hs, int, data);

  *data = socket_desc;

  return Qnil;
}


void Init_handlersocket_ext(void) {
  rb_Handlersocket = rb_const_get(rb_cObject, rb_intern("Handlersocket"));
  init_handlersocket_constants();

  rb_define_alloc_func(rb_Handlersocket, hs_alloc);
  rb_define_method(rb_Handlersocket, "initialize", rb_hs_initialize, 2);
  rb_define_method(rb_Handlersocket, "open_index", rb_hs_open_index, 5);
  rb_define_method(rb_Handlersocket, "find_cmd", hs_find_cmd, -1);
  rb_define_method(rb_Handlersocket, "find", rb_hs_find, -1);
}
