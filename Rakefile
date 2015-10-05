require "bundler/gem_tasks"

require 'rake/extensiontask'
Rake::ExtensionTask.new('handlersocket_ext')

HOST = "139.162.148.140"
PORT = 9999
USERNAME = 'root'
BM_COUNT = 10

def do_test
  hs = Handlersocket.new(HOST, PORT)
  puts hs.open_index('0', 'test', 't', 'PRIMARY', ['id', 'col']).inspect
  puts hs.find('0', '>', ['1'], ['100']).inspect
end

def do_bm
  hs = Handlersocket.new(HOST, PORT)
  start = Time.now
  hs.open_index('0', 'test', 't', 'PRIMARY', ['id', 'col'])
  BM_COUNT.times { hs.query(['0', '=', '1', '1', '100']) }
  puts Time.now - start
end

def do_mysql_bm
  client = Mysql2::Client.new(host: HOST, username: USERNAME, database: 'test')
  start = Time.now
  BM_COUNT.times { client.query("SELECT * FROM t LIMIT 100") }
  puts Time.now - start
end

def check_commands
  hs = Handlersocket.new(HOST, 9999)
  100_000.times do
    puts hs.find_cmd('0', '>', ['1'], ['100'])
  end
end

namespace :smoke_test do
  desc 'Pure test'
  task :pure do
    require 'handlersocket/pure'
    do_test
  end

  desc 'Ext test'
  task :ext do
    require 'handlersocket/ext'
    do_test
  end
end

namespace :check_commands do
  desc 'Ext'
  task :ext do
    require 'handlersocket/ext'
    check_commands
  end
end

namespace :bm do
  desc 'Pure BM'
  task :pure do
    require 'handlersocket/pure'
    do_bm
  end

  desc 'Ext BM'
  task :ext do
    require 'handlersocket/ext'
    do_bm
  end

  desc 'Mysql2 BM'
  task :mysql2 do
    require 'mysql2'
    do_mysql_bm
  end
end
