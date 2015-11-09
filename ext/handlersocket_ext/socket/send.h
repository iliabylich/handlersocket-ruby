#include <arpa/inet.h>
#include <sys/ioctl.h>

// Writes passed message to a socket
//
// @param [int] socket_desc
// @param [char*] message
//
#define SOCKET_WRITE(socket_desc, message) send(socket_desc, message, strlen(message) , 0)


// Concatenates a string +s1+ and a string +s2+ with the length +l2+
// Result will be placed into +s1+
//
// @param [char**] s1
// @param [char*] s2
// @param [int] l2
//
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

// Writes an array of Ruby strings to passed socket
//
// @param [int] socket_desc
// @param [Array<String>] ary
//
static void hs_write(int socket_desc, VALUE ary) {
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

// Reads all available data from the passed socket until the new line
//
// @param [int] socket_desc
//
// @return [char*] reply from the server
//
// @raise [StandardError] when socket is closed
//
static char* hs_read_until_newline(int socket_desc) {
  int buffer_length = 100, bytes_read = 0;
  char buf[buffer_length];
  char *result = NULL;
  int end_of_line_matched = 0;

  while (!end_of_line_matched) {
    bytes_read = read(socket_desc, buf, buffer_length);
    if (!bytes_read) {
      rb_raise(rb_eStandardError, "HS: closed socket");
    }
    concat(&result, buf, bytes_read);
    if (buf[bytes_read - 1] == '\n') {
      end_of_line_matched = 1;
    }
  }

  return result;
}

// Parses "\t"-terminated response from the HS server
//
// @param [char*] raw_response
//
// @return [Array<String>] parsed reply
//
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

// Sends a query to the HS server and parses response
//
// @param [Handlersocket] hs
// @param [Array<String>] req request data
//
// @return [Array<String>] reply
//
static VALUE rb_hs_query(VALUE hs, VALUE req) {
  SOCKET_DATA *data;
  char *raw_result;

  Data_Get_Struct(hs, SOCKET_DATA, data);

  hs_write(data->socket_desc, req);
  raw_result = hs_read_until_newline(data->socket_desc);
  return hs_parse_response(raw_result);
}
