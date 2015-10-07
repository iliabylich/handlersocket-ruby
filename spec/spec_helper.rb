require 'bundler/setup'
Bundler.require
require 'yaml'

hs_version = ENV.fetch('HS_VERSION') { 'pure' }
require "handlersocket/#{hs_version}"

hs_config = YAML.load_file(File.expand_path('../../handlersocket.yml', __FILE__))
HS_HOST = hs_config['host']
HS_PORT = hs_config['port']

RSpec.configure do |config|
  config.expect_with :rspec do |expectations|
    expectations.include_chain_clauses_in_custom_matcher_descriptions = true
  end

  config.mock_with :rspec do |mocks|
    mocks.verify_partial_doubles = true
  end
end
