#include <arpa/inet.h>
#include "socket/buffer.h"

#define SOCKET_WRITE(socket_desc, message) send(*socket_desc, message, strlen(message) , 0)

static void hs_write(int* socket_desc, VALUE ary) {
  char *message, *buffer;
  int i, l1, l2;
  VALUE item;
  message = NULL;

  for (i = 0; i < RARRAY_LEN(ary); ++i) {
    item = RARRAY_AREF(ary, i);
    buffer = StringValuePtr(item);
    l1 = message ? strlen(message) : 0;
    l2 = buffer  ? strlen(buffer)  : 0;
    if (l1 == 0) {
      message = realloc(message, l2);
      strcpy(message, buffer);
    } else {
      message = realloc(message, l1 + l2 + 2);
      message[l1] = '\t';
      memcpy(message + l1 + 1, buffer, l2);
      message[l1 + l2 + 1] = 0;
    }
  }
  l1 = strlen(message);
  message = realloc(message, l1 + 2);
  message[l1] = '\n';
  message[l1 + 1] = 0;

  // rb_warn("Writing: '%s'", message);
  SOCKET_WRITE(socket_desc, message);
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

static VALUE rb_hs_query(VALUE hs, VALUE req) {
  int* socket_desc;

  Data_Get_Struct(hs, int, socket_desc);

  hs_write(socket_desc, req);
  return hs_read_until_newline(socket_desc);
}
