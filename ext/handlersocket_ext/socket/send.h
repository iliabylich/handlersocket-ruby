#include <arpa/inet.h>
#include "socket/buffer.h"

#define SOCKET_WRITE(socket_desc, message) send(*socket_desc, message, strlen(message) , 0)

static void hs_write(int* socket_desc, VALUE ary) {
  char *message;
  int i;
  VALUE item;

  for (i = 0; i < RARRAY_LEN(ary); ++i) {
    item = RARRAY_AREF(ary, i);
    message = StringValuePtr(item);
    SOCKET_WRITE(socket_desc, message);
    if (i + 1 < RARRAY_LEN(ary)) {
      SOCKET_WRITE(socket_desc, "\t");
    }
  }
  SOCKET_WRITE(socket_desc, "\n");
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

static VALUE rb_hs_query(int argc, VALUE* argv, VALUE hs) {
  int* socket_desc;
  VALUE req;

  rb_scan_args(argc, argv, "1", &req);
  Data_Get_Struct(hs, int, socket_desc);

  hs_write(socket_desc, req);
  return hs_read_until_newline(socket_desc);
}
