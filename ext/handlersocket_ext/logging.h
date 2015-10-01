static void hs_log(VALUE s) {
  VALUE logger;
  logger = rb_funcall(rb_Handlersocket, rb_intern("logger"), 0);
  rb_funcall(logger, rb_intern("info"), 1, s);
}

static void hs_log_req(VALUE req) {
  VALUE s = rb_str_plus(logging_req_prefix, rb_funcall(req, rb_intern("inspect"), 0));
  hs_log(s);
}

static void hs_log_res(VALUE res) {
  VALUE s = rb_str_plus(logging_res_prefix, rb_funcall(res, rb_intern("inspect"), 0));
  hs_log(s);
}
