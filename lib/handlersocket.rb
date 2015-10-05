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

  self.logger = Logger.new(STDOUT)

  OPEN_IDX_COMMAND_START = "P"
  ARGS_SEPARATOR = "\t"
  COLUMNS_SEPARATOR = ","
  END_OF_LINE = "\n"
  LOGGING_REQUEST_PREFIX = "HS Request: "
  LOGGING_RESPONSE_PREFIX = "HS Response: "
end

# require 'handlersocket/pure'
# require 'handlersocket/ext'
