# Handlersocket

Welcome to your new gem! In this directory, you'll find the files you need to be able to package up your Ruby library into a gem. Put your Ruby code in the file `lib/handlersocket`. To experiment with that code, run `bin/console` for an interactive prompt.

TODO: Delete this and the text above, and describe your gem

## Installation

Add this line to your application's Gemfile:

```ruby
gem 'handlersocket'
```

And then execute:

    $ bundle

Or install it yourself as:

    $ gem install handlersocket

## Usage

TODO: Write usage instructions here

## Benchmarks

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

## Development

After checking out the repo, run `bin/setup` to install dependencies. Then, run `rake false` to run the tests. You can also run `bin/console` for an interactive prompt that will allow you to experiment.

To install this gem onto your local machine, run `bundle exec rake install`. To release a new version, update the version number in `version.rb`, and then run `bundle exec rake release`, which will create a git tag for the version, push git commits and tags, and push the `.gem` file to [rubygems.org](https://rubygems.org).

## Contributing

Bug reports and pull requests are welcome on GitHub at https://github.com/[USERNAME]/handlersocket. This project is intended to be a safe, welcoming space for collaboration, and contributors are expected to adhere to the [Contributor Covenant](contributor-covenant.org) code of conduct.


## License

The gem is available as open source under the terms of the [MIT License](http://opensource.org/licenses/MIT).

