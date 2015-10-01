struct buffer_struct
{
  int position, length;
  char *buf;
};
typedef struct buffer_struct BUFFER;

#define FLUSH_BUFFER_TO(buffer, res) \
  rb_ary_push(res, rb_str_new(buffer.buf, buffer.position)); \
  buffer.position = 0;

#define MAKE_EMPTY_BUFFER(buffer, max_length) \
  buffer.position = 0; \
  buffer.length = max_length; \
  buffer.buf = malloc(max_length * sizeof(int));

#define BUFFER_ITEM(buffer) buffer.buf[buffer.position]
#define IS_VALID_BUFFER(buffer) buffer.position > 0
#define RELEASE_BUFFER(buffer) free(buffer.buf)
