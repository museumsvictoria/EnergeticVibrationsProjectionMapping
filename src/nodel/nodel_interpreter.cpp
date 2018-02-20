//
//  main.cpp
//  nodel_interpreter
//
//  Created by Tom Gowan on 20/2/18.
//  Copyright © 2018 Tom Gowan. All rights reserved.
//

#include "nodel_interpreter.hpp"
#include <string>
#include <iostream>

namespace nodel_interpreter {
	Nodel::Nodel() : my_op(std::make_unique<op::None>()) {}
  std::unique_ptr<op::Operation> decode_recv(std::shared_ptr<Socket> my_socket){
    char data[READ_LEN];
    auto length = my_socket->socket.receive(boost::asio::buffer(data, READ_LEN), 0, my_socket->err);
    std::string msg(data, length);
    std::cout << "msg: " << msg << std::endl;
    return op::run_commands(msg);
  }

};
