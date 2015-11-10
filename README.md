[![Build Status](https://travis-ci.org/iliabylich/handlersocket-ruby.svg?branch=master)](https://travis-ci.org/iliabylich/handlersocket-ruby)
[![Code Climate](https://codeclimate.com/github/iliabylich/handlersocket-ruby/badges/gpa.svg)](https://codeclimate.com/github/iliabylich/handlersocket-ruby)

# HandlerSocket

Ruby/C -based zero dependency implementation of MySQL's HandlerSocket protocol.

# What is HandlerSocket

HandlerSocket is a NoSQL plugin for MySQL. It works as a daemon inside the mysqld process, accepting TCP connections, and executing requests from clients. HandlerSocket does not support SQL queries. Instead, it supports simple CRUD operations on tables.

HandlerSocket can be much faster than mysqld/libmysql in some cases because it has lower CPU, disk, and network overhead:

To lower CPU usage it does not parse SQL.
Next, it batch-processes requests where possible, which further reduces CPU usage and lowers disk usage.
Lastly, the client/server protocol is very compact compared to mysql/libmysql, which reduces network usage

## Installation

Add this line to your application's Gemfile:

```ruby
# If you want to use Ruby-based implementation
gem 'handlersocket-rb', require: 'handlersocket/pure'

# If you want to use C-based implementation
gem 'handlersocket-rb', require: 'handlersocket/ext'
```

And then execute:

    $ bundle

Or install it yourself as:

    $ gem install handlersocket-rb

## Usage

First of all, you need to install [handlersocket](http://yoshinorimatsunobu.blogspot.com.by/2010/10/using-mysql-as-nosql-story-for.html) plugin.

If you are using Percona Server or MariaDB, you already have all necessary libraries.

``` sql
INSTALL PLUGIN handlersocket SONAME 'handlersocket.so';
```

And add the following code to mysql config file to `mysqld` section:
```
handlersocket_address="127.0.0.1"
handlersocket_port="9998"
handlersocket_port_wr="9999"
```

Reload MySQL server and run `show processlist;`. You should see a lot of connections from HandlerSocket.

To create a connection to HandlerSocket run:
``` ruby
hs = Handlersocket.new('host', port)
```

To open an index run:
``` ruby
hs.open_index('0', 'hs_test', 'users', 'PRIMARY', ['id', 'email'])
# where:
# '0' - index name, you should pass it later to query method
# 'hs_test' - database name
# 'users' - table name
# 'PRIMARY' - index name
# ['id', 'name'] - columns that you want to read/write
```

To read the data run:
``` ruby
hs.find('0', '=', ['12'], ['100]'])
# This query opens index '0' (primary index from the previous example)
# and finds 100 rows with 'indexed value' = '12'
# similar to
# SELECT id, name FROM hs_test.users WHERE id = 12 LIMIT 100
```

## Benchmarks

See `rake:benchmark`.

```
Calculating -------------------------------------
             pure HS     2.000  i/100ms
              ext HS     3.149k i/100ms
              mysql2   669.000  i/100ms
-------------------------------------------------
             pure HS     49.979  (± 2.0%) i/s -    250.000
              ext HS    110.369M (±15.7%) i/s -    467.793M
              mysql2      5.218M (±16.3%) i/s -     23.869M

Comparison:
              ext HS: 110369437.2 i/s
              mysql2:  5218120.6 i/s - 21.15x slower
             pure HS:       50.0 i/s - 2208314.91x slower
```

Where:
+ `ext HS` is a C-based implementation of HandlerSocket protocol
+ `mysql2` is a default mysql2 adapter
+ `pure HS` is a Ruby-based implementation of HandlerSocket protocal

## Development

After checking out the repo, run `bin/setup` to install dependencies.
Fill `handlersocket.yml` and `mysql.yml` in a root directory of the project.
Run `rake test:db:create` to create a default database that is used in tests.
Then, run `rake` to (re)compile the code and run the tests.
You can also run `bin/console` for an interactive prompt that will allow you to experiment.

To install this gem onto your local machine, run `bundle exec rake install`.
To release a new version, update the version number in `version.rb`,
and then run `bundle exec rake release`,
which will create a git tag for the version,
push git commits and tags,
and push the `.gem` file to [rubygems.org](https://rubygems.org).

Run `rake benchmark` to compare the performance of Ruby HS/C HS/Mysql2.

## Contributing

Bug reports and pull requests are welcome on GitHub at https://github.com/iliabylich/handlersocket-ruby.
This project is intended to be a safe, welcoming space for collaboration,
and contributors are expected to adhere to the [Contributor Covenant](contributor-covenant.org) code of conduct.


## License

The gem is available as open source under the terms of the [MIT License](http://opensource.org/licenses/MIT).

