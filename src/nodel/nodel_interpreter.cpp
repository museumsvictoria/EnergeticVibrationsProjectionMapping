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
	void Socket::setup() {
		socket = make_shared<ofxUDPManager>();
		socket->Create();
		//socket.Connect(RECV_IP, PORT);
		std::cout << "Bound? " << socket->Bind(PORT) << std::endl;
		socket->SetNonBlocking(true);

	}

	int Socket::read(char * data) {

		return socket->Receive(data, READ_LEN);

	}

	Nodel::Nodel() : my_op(std::make_unique<op::None>()) {}

	std::unique_ptr<op::Operation> decode_recv(Socket my_socket) {
		char data[READ_LEN];
		my_socket.read(data);
		std::string msg(data);
		std::cout << "msg: " << msg << std::endl;
		return op::run_commands(msg);
	}

};
