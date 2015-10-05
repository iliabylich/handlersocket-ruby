HOST = '139.162.148.140'
PORT = 9999
USERNAME = 'root'

require 'bundler/setup'
require 'benchmark/ips'

require 'handlersocket/pure'
class Handlersocket
  alias_method :pure_query, :query
  undef_method :query
end
pure_socket = Handlersocket.new(HOST, PORT)
pure_socket.pure_query(['P', '0', 'test', 't', 'PRIMARY', 'id', 'col'])

require 'handlersocket/ext'
class Handlersocket
  alias_method :ext_query, :query
  undef_method :query
end
ext_socket = Handlersocket.new(HOST, PORT)
ext_socket.ext_query(['P', '0', 'test', 't', 'PRIMARY', 'id', 'col'])

require 'mysql2'
mysql_client = Mysql2::Client.new(host: HOST, username: USERNAME, database: 'test')

Benchmark.ips do |x|
  x.config time: 5, warmup: 2

  x.report 'pure HS' do |times|
    pure_socket.pure_query(['0', '=', '1', times.to_s, '100'])
  end

  x.report 'ext HS' do |times|
    ext_socket.ext_query(['0', '=', '1', times.to_s, '100'])
  end

  x.report 'mysql2' do |times|
    mysql_client.query("SELECT * FROM t where id = #{times} LIMIT 100").to_a
  end

  x.compare!
end
