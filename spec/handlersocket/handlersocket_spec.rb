require 'spec_helper'

describe Handlersocket do
  subject(:hs) { Handlersocket.new(HS_HOST, HS_PORT) }

  it 'takes a host and port' do
    expect { hs }.to_not raise_error
  end

  context 'open index command' do
    it 'opens an index in the database' do
      expect {
        hs.open_index('0', 'hs_test', 'users', 'PRIMARY', ['id', 'email'])
      }.to_not raise_error
    end

    it 'parses tabbed response' do
      response = hs.open_index('1', 'hs_test', 'users', 'PRIMARY', ['id', 'email'])
      expect(response).to eq(['0', '1'])
    end

    it 'returns an error when wrong arguments were passed' do
      response = hs.open_index('2', 'missing-db', 'missing-table', 'missing-idx', [])
      expect(response).to eq(['1', '1', 'open_table'])
    end
  end

  context 'find command' do
    before { hs.open_index('0', 'hs_test', 'users', 'PRIMARY', ['id', 'email']) }

    it 'returns records that match passed pattern' do
      response = hs.find('0', '=', ['12'], ['100'])
      expect(response).to eq(['0', '2', '12', 'email12@email'])
    end
  end
end
