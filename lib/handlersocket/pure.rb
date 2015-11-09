require 'socket'
require 'handlersocket'

# Pure Ruby implementation of HS protocol
#
# Sockets implementation is very slow in MRI, use HandlerSocket::Ext for better performance
#
class Handlersocket
  # Returns a memoized instance of TCP socket
  #
  # @return [TCPSocket]
  #
  def socket
    @socket ||= TCPSocket.new(@host, @port)
  end

  # Sends request to a HS server and returns a reply
  #
  # @param [Array<String>] req
  #
  # @return [Array<String>]
  #
  def query(req)
    socket.puts(req.join("\t"))
    socket.gets.chomp.split("\t")
  end
end
