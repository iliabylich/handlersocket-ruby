require "bundler/gem_tasks"

require 'rake/extensiontask'
Rake::ExtensionTask.new('handlersocket_ext')

require 'bundler/setup'
require 'mysql2'
mysql_config = YAML.load_file(File.expand_path('../mysql.yml', __FILE__))
client = Mysql2::Client.new(mysql_config)

namespace :test do
  namespace :db do
    desc 'Drops tests database'
    task :drop do
      client.query("DROP DATABASE IF EXISTS hs_test")
    end

    desc 'Prepares test database'
    task :create do
      client.query("CREATE DATABASE hs_test")
      client.query("use hs_test")
      client.query <<-SQL
        CREATE TABLE users (
          id int(11) NOT NULL AUTO_INCREMENT,
          email varchar(255) NOT NULL DEFAULT '',
          PRIMARY KEY (id)
        )
      SQL
    end

    desc 'Seeds test database'
    task :seed do
      count = ENV.fetch('SEED_COUNT', 100)
      1.upto(count) do |i|
        client.query("INSERT INTO users(email) VALUES ('email#{i}@email')")
      end
    end
  end
end

desc 'Runs benchmark hs_pure/hs_ext/mysql2'
task :benchmark do
  mysql_config = YAML.load_file(File.expand_path('../mysql.yml', __FILE__))
  hs_config    = YAML.load_file(File.expand_path('../handlersocket.yml', __FILE__))

  require 'bundler/setup'
  require 'benchmark/ips'

  require 'handlersocket/pure'
  class Handlersocket
    alias_method :pure_query, :query
    undef_method :query
  end
  pure_socket = Handlersocket.new(hs_config['host'], hs_config['port'])
  pure_socket.pure_query(['P', '0', 'hs_test', 'users', 'PRIMARY', 'id', 'col'])

  require 'handlersocket/ext'
  class Handlersocket
    alias_method :ext_query, :query
    undef_method :query
  end
  ext_socket = Handlersocket.new(hs_config['host'], hs_config['port'])
  ext_socket.ext_query(['P', '0', 'hs_test', 'users', 'PRIMARY', 'id', 'col'])

  require 'mysql2'
  mysql_client = Mysql2::Client.new(mysql_config)

  Benchmark.ips do |x|
    x.config time: 5, warmup: 2

    x.report 'pure HS' do |times|
      pure_socket.pure_query(['0', '=', '1', times.to_s, '100'])
    end

    x.report 'ext HS' do |times|
      ext_socket.ext_query(['0', '=', '1', times.to_s, '100'])
    end

    x.report 'mysql2' do |times|
      mysql_client.query("SELECT * FROM users where id = #{times} LIMIT 100").to_a
    end

    x.compare!
  end
end

require 'rspec/core/rake_task'
RSpec::Core::RakeTask.new(:spec)

task default: [:clobber, :compile, :spec]
