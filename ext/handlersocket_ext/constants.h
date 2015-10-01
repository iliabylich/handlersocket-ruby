#include <stdio.h>
#include <ruby.h>

static VALUE args_separator;
static VALUE columns_separator;
static VALUE end_of_line;
static VALUE index_command_start;
static VALUE logging_req_prefix;
static VALUE logging_res_prefix;

void init_handlersocket_constants(void) {
  index_command_start = rb_str_new2("P");
  args_separator = rb_str_new2("\t");
  columns_separator = rb_str_new2(",");
  end_of_line = rb_str_new2("\n");
  logging_req_prefix = rb_str_new2("HS Request: ");
  logging_res_prefix = rb_str_new2("HS Response: ");
}
