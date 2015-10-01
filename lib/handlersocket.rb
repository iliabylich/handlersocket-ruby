require 'logger'
require "handlersocket/version"

class Handlersocket
  def initialize(host, port)
    @host = host
    @port = port
  end

  class << self
    attr_accessor :logger
  end

  self.logger = Logger.new('/dev/null')
end

# require 'handlersocket/pure'
# require 'handlersocket/ext'
