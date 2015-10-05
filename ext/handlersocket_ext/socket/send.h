#include <arpa/inet.h>
#include <sys/ioctl.h>

#define SOCKET_WRITE(socket_desc, message) send(*socket_desc, message, strlen(message) , 0)

void concat(char **s1, char *s2, int l2) {
  int l1;
  char *res;

  l1 = *s1 ? strlen(*s1) : 0;
  res = realloc(*s1, l1 + l2 + 1);

  if (res) {
    memcpy(res + l1, s2, l2);
    res[l1 + l2] = 0;
    *s1 = res;
  }
}

static void hs_write(int *socket_desc, VALUE ary) {
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

  SOCKET_WRITE(socket_desc, message);
}


static char* hs_read_until_newline(int* socket_desc) {
  int buffer_length = 100, bytes_read = 0;
  char buf[buffer_length];
  char *result = NULL;
  int end_of_line_matched = 0;

  while (!end_of_line_matched) {
    bytes_read = read(*socket_desc, buf, buffer_length);
    concat(&result, buf, bytes_read);
    if (buf[bytes_read - 1] == '\n') {
      end_of_line_matched = 1;
    }
  }

  return result;
}

static VALUE hs_parse_response(char* raw_response) {
  VALUE ary;
  char *token;

  ary = rb_ary_new();

  while ((token = strsep(&raw_response, "\t\n")) != NULL) {
    if (strlen(token) > 0) {
      rb_ary_push(ary, rb_str_new2(token));
    }
  }

  free(raw_response);
  free(token);

  return ary;
}

static VALUE rb_hs_query(VALUE hs, VALUE req) {
  int* socket_desc;
  char *raw_result;

  Data_Get_Struct(hs, int, socket_desc);

  hs_write(socket_desc, req);
  raw_result = hs_read_until_newline(socket_desc);
  return hs_parse_response(raw_result);
}
