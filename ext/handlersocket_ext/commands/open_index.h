static VALUE hs_open_index_cmd(VALUE idx_id, VALUE db_name, VALUE tbl_name, VALUE idx_name, VALUE columns) {
  VALUE req, concatenated_columns;

  req = rb_str_to_str(index_command_start);
  rb_str_concat(req, args_separator);
  rb_str_concat(req, idx_id);
  rb_str_concat(req, args_separator);
  rb_str_concat(req, db_name);
  rb_str_concat(req, args_separator);
  rb_str_concat(req, tbl_name);
  rb_str_concat(req, args_separator);
  rb_str_concat(req, idx_name);
  rb_str_concat(req, args_separator);

  concatenated_columns = rb_ary_join(columns, columns_separator);
  rb_str_concat(req, concatenated_columns);
  rb_str_concat(req, end_of_line);

  return req;
}

VALUE rb_hs_open_index(VALUE hs, VALUE idx_id, VALUE db_name, VALUE tbl_name, VALUE idx_name, VALUE columns) {
  VALUE req, res;
  req = hs_open_index_cmd(idx_id, db_name, tbl_name, idx_name, columns);
  res = hs_send(hs, req);
  return res;
}
