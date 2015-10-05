#include <stdio.h>
#include <ruby.h>

static VALUE args_separator;
static VALUE columns_separator;
static VALUE end_of_line;
static VALUE index_command_start;
static VALUE logging_req_prefix;
static VALUE logging_res_prefix;

void init_handlersocket_constants(void) {
  index_command_start = rb_const_get(rb_Handlersocket, rb_intern("OPEN_IDX_COMMAND_START"));
  args_separator      = rb_const_get(rb_Handlersocket, rb_intern("ARGS_SEPARATOR"));
  columns_separator   = rb_const_get(rb_Handlersocket, rb_intern("COLUMNS_SEPARATOR"));
  end_of_line         = rb_const_get(rb_Handlersocket, rb_intern("END_OF_LINE"));
  logging_req_prefix  = rb_const_get(rb_Handlersocket, rb_intern("LOGGING_REQUEST_PREFIX"));
  logging_res_prefix  = rb_const_get(rb_Handlersocket, rb_intern("LOGGING_RESPONSE_PREFIX"));
}
