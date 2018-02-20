//
//  decode_recv.hpp
//  nodel_interpreter
//
//  Created by Tom Gowan on 20/2/18.
//  Copyright © 2018 Tom Gowan. All rights reserved.
//
#pragma once
#include <boost/asio.hpp>
#include <memory>
#include "commands_evpm.hpp"
#include <iostream>


namespace nodel_interpreter {
  static constexpr int READ_LEN = 300;
  struct Socket{
    boost::asio::ip::udp::socket socket;
    boost::system::error_code err;
    Socket(boost::asio::io_service & io_service,
    boost::asio::ip::udp::endpoint remote_endpoint,
    boost::system::error_code _err) :
      socket(io_service, remote_endpoint), 
      err(_err) {}
	~Socket() { std::cout << "killing socket" << std::endl; }
  };


  class Nodel{
    std::unique_ptr<op::Operation> my_op;
    public:
		Nodel();
    std::string get_type(){ return my_op->get_type(); }
    void set(std::unique_ptr<op::Operation> _op){ my_op = std::move(_op); }
    void run(ofxPiMapper & m){ my_op->run(m); };
  };

  std::unique_ptr<op::Operation> decode_recv(std::shared_ptr<Socket> socket);
};
