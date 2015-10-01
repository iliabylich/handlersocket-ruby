require 'socket'
require 'handlersocket'

class Handlersocket
  def open_index(idx_id, db_name, tbl_name, idx_name, columns)
    req = ['P', idx_id, db_name, tbl_name, idx_name, columns.join(',')].join("\t")
    send_req(req)
  end

  def find(idx_id, op, args, extra = [])
    req = [idx_id, op, args.length, *args, *extra].join("\t")
    send_req(req)
  end

  private

  def socket
    @socket ||= TCPSocket.new(@host, @port)
  end

  def send_req(req)
    self.class.logger.info("HS Request: #{(req + "\n").inspect}")# if self.class.logger
    socket.puts(req)
    res = socket.gets.chomp.split("\t")
    self.class.logger.info("HS Response: #{res.inspect}")# if self.class.logger
    res
  end
end
