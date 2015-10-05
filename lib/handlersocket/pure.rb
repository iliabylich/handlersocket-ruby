require 'socket'
require 'handlersocket'

class Handlersocket
  def open_index(idx_id, db_name, tbl_name, idx_name, columns)
    req = [OPEN_IDX_COMMAND_START, idx_id, db_name, tbl_name, idx_name, columns.join(COLUMNS_SEPARATOR)].join(ARGS_SEPARATOR)
    send_req(req)
  end

  def find(idx_id, op, args, extra = [])
    req = [idx_id, op, args.length, *args, *extra].join(ARGS_SEPARATOR)
    send_req(req)
  end

  private

  def socket
    @socket ||= TCPSocket.new(@host, @port)
  end

  def send_req(req)
    self.class.logger.info([LOGGING_REQUEST_PREFIX, (req + END_OF_LINE).inspect].join) if self.class.logger
    socket.puts(req)
    res = socket.gets.chomp.split(ARGS_SEPARATOR)
    self.class.logger.info([LOGGING_RESPONSE_PREFIX, res.inspect].join) if self.class.logger
    res
  end
end
