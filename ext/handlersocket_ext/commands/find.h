static VALUE hs_find_cmd(int argc, VALUE *argv) {
  VALUE req;
  VALUE idx_id, op, args, extra;
  int args_length, i;

  rb_scan_args(argc, argv, "31", &idx_id, &op, &args, &extra);
  args_length = RARRAY_LEN(args);

  req = rb_str_dup(idx_id);
  rb_str_concat(req, args_separator);
  rb_str_concat(req, op);
  rb_str_concat(req, args_separator);

  rb_str_concat(req, rb_fix2str(INT2NUM(args_length), 10));

  for (i = 0; i < args_length; ++i) {
    rb_str_concat(req, args_separator);
    rb_str_concat(req, RARRAY_AREF(args, i));
  }

  for (i = 0; i < RARRAY_LEN(extra); ++i) {
    rb_str_concat(req, args_separator);
    rb_str_concat(req, RARRAY_AREF(extra, i));
  }

  rb_str_concat(req, end_of_line);

  return req;
}

VALUE rb_hs_find(int argc, VALUE *argv, VALUE hs) {
  VALUE req, res;
  req = hs_find_cmd(argc, argv);
  res = hs_send(hs, req);
  return res;
}
