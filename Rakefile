require "bundler/gem_tasks"

require 'rake/extensiontask'
Rake::ExtensionTask.new('handlersocket_ext')

def do_test
  hs = Handlersocket.new("139.162.148.140", 9999)
  puts hs.open_index('0', 'test', 't', 'PRIMARY', ['id', 'col']).inspect
  puts hs.find('0', '>', ['1'], ['100']).inspect
end

def do_bm
  hs = Handlersocket.new("139.162.148.140", 9999)
  start = Time.now
  hs.open_index('0', 'test', 't', 'PRIMARY', ['id', 'col'])
  100.times { hs.find('0', '>', ['1'], ['100']) }
  puts Time.now - start
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
end
