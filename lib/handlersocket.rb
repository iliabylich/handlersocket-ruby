require "handlersocket/version"

# Class for establising connection to MySQL's HandlerSocket
#
# @example
#   hs = Handlersocket.new('0.0.0.0', 9999)
#
class Handlersocket
  # @param [String] host
  # @param [Fixnum] port
  #
  def initialize(host, port)
    @host = host
    @port = port
  end

  # Sends a query to Handlersocket server and returns a reply
  #
  # @param [Array<String>] args
  #
  # @return [Array<String>]
  #
  def query(*args)
    # A stub method
  end

  # Opens an an index for requests
  #
  # @param [String] idx_id id of index
  # @param [String] db_name name of the database
  # @param [String] tbl_name name of the table
  # @param [String] idx_name name of the index
  # @param [Array<String>] columns you want to get
  #
  # @return [Array<String>]
  #
  def open_index(idx_id, db_name, tbl_name, idx_name, columns)
    req = ["P", idx_id, db_name, tbl_name, idx_name, columns.join(",")]
    query(req)
  end

  # Runs a find statement on HandlerSocket server and returns matched rows
  #
  # @param [String] idx_id id of index
  # @param [String] op operation ('=', '>', '<')
  # @param [Array<String>] args arguments for comparison
  # @param [Array<String>] extra arguments like limit and offset
  #
  # @return [Array<String>] matched rows
  #
  def find(idx_id, op, args, extra = [])
    req = [idx_id, op, args.length.to_s, *args, *extra]
    query(req)
  end
end

# require 'handlersocket/pure'
# require 'handlersocket/ext'
