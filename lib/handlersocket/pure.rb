require 'socket'
require 'handlersocket'

class Handlersocket
  def socket
    @socket ||= TCPSocket.new(@host, @port)
  end

  def query(req)
    socket.puts(req.join("\t"))
    socket.gets.chomp.split("\t")
  end
end
