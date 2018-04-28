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
		socket->Bind(PORT);
		socket->SetNonBlocking(true);

	}

	int Socket::read(char * data) {

		return socket->Receive(data, READ_LEN);

	}

	NodelMessage::NodelMessage() : my_op(std::make_unique<op::None>()) {}

	std::unique_ptr<op::Operation> Nodel::decode_recv(Socket my_socket) {
		char data[READ_LEN];
		my_socket.read(data);
		std::string msg(data);
		if (msg.size() <= 0) {
			return std::make_unique<op::None>();
		}
		else {
			return op::runnable_command(msg, deps);
		}
	}

	void Nodel::setup(NodelDep nd) {
		my_socket.setup();
		deps = make_shared<NodelDep>(nd);

	}

	void Nodel::try_run() {
		nodel_message.set(decode_recv(my_socket));

		nodel_message.run();

	}
};
