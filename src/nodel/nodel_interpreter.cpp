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

	NodelMessage::NodelMessage() : my_op(std::make_unique<op::None>()) {}

	std::unique_ptr<op::Operation> Nodel::decode_recv(Socket my_socket) {
		char data[READ_LEN];
		my_socket.read(data);
		std::string msg(data);
		std::cout << "msg: " << msg << std::endl;
		return op::runnable_command(msg, deps);
	}

	void Nodel::setup(NodelDep nd) {
		my_socket.setup();
		deps = make_shared<NodelDep>(nd);

	}

	void Nodel::try_run() {
		cout << "checking udp" << endl;
		nodel_message.set(decode_recv(my_socket));

		std::cout << "Type: " << nodel_message.get_type() << std::endl;
		nodel_message.run();

	}
};
