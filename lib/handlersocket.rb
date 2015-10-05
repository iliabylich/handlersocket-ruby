require "handlersocket/version"

class Handlersocket
  def initialize(host, port)
    @host = host
    @port = port
  end

  def open_index(idx_id, db_name, tbl_name, idx_name, columns)
    req = ["P", idx_id, db_name, tbl_name, idx_name, columns.join(",")]
    query(req)
  end

  def find(idx_id, op, args, extra = [])
    req = [idx_id, op, args.length.to_s, *args, *extra]
    query(req)
  end
end

# require 'handlersocket/pure'
# require 'handlersocket/ext'
