#include <arpa/inet.h>
#include "socket/buffer.h"

static void hs_write(int* socket_desc, VALUE req) {
  char *message;
  message = StringValuePtr(req);
  send(*socket_desc , message , strlen(message) , 0);
}

static VALUE hs_read_until_newline(int* socket_desc) {
  BUFFER buffer;
  VALUE res;
  MAKE_EMPTY_BUFFER(buffer, 100);
  res = rb_ary_new();

  while (buffer.position < buffer.length && read(*socket_desc, &(BUFFER_ITEM(buffer)), 1) == 1) {
    if (IS_VALID_BUFFER(buffer) && BUFFER_ITEM(buffer) == '\n') {
      FLUSH_BUFFER_TO(buffer, res);
      buffer.position++;
      break;
    }
    if (IS_VALID_BUFFER(buffer) && BUFFER_ITEM(buffer) == '\t') {
      FLUSH_BUFFER_TO(buffer, res);
    } else {
      buffer.position++;
    }
  }

  RELEASE_BUFFER(buffer);

  return res;
}

static VALUE hs_send(VALUE hs, VALUE req) {
  int* socket_desc;
  VALUE res;

  Data_Get_Struct(hs, int, socket_desc);

  hs_log_req(req);
  hs_write(socket_desc, req);
  res = hs_read_until_newline(socket_desc);
  hs_log_res(res);

  return res;
}
