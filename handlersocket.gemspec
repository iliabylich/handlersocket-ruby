# coding: utf-8
lib = File.expand_path('../lib', __FILE__)
$LOAD_PATH.unshift(lib) unless $LOAD_PATH.include?(lib)
require 'handlersocket/version'

Gem::Specification.new do |spec|
  spec.name          = "handlersocket-rb"
  spec.version       = Handlersocket::VERSION
  spec.authors       = ["Ilya Bylich"]
  spec.email         = ["ibylich@gmail.com"]

  spec.summary       = %q{Zero-dependency implementation of HandlerSocket protocol}
  spec.homepage      = "https://github.com/iliabylich/handlersocket-ruby"
  spec.license       = "MIT"

  spec.files         = `git ls-files -z`.split("\x0").reject { |f| f.match(%r{^(test|spec|features)/}) }
  spec.bindir        = "exe"
  spec.executables   = spec.files.grep(%r{^exe/}) { |f| File.basename(f) }
  spec.require_paths = ["lib"]

  spec.add_development_dependency "bundler", "~> 1.10"
  spec.add_development_dependency "rake", "~> 10.0"
  spec.add_development_dependency "rake-compiler"
  spec.add_development_dependency "rspec"
end
