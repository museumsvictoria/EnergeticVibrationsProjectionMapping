//
//  decode_recv.hpp
//  nodel_interpreter
//
//  Created by Tom Gowan on 20/2/18.
//  Copyright © 2018 Tom Gowan. All rights reserved.
//
#pragma once
#include <memory>
#include "commands_evpm.hpp"
#include <iostream>
#include "ofxNetwork.h"


namespace nodel_interpreter {
  static constexpr int READ_LEN = 300;
  static constexpr auto RECV_IP = "127.0.0.1";
  static constexpr int PORT = 34254;
  class Socket{
	std::shared_ptr<ofxUDPManager> socket;
  public:
	void setup();
	int read(char *);
  };


  class Nodel{
    std::unique_ptr<op::Operation> my_op;
    public:
		Nodel();
    std::string get_type(){ return my_op->get_type(); }
    void set(std::unique_ptr<op::Operation> _op){ my_op = std::move(_op); }
    void run(ofxPiMapper & m){ my_op->run(m); };
  };

  std::unique_ptr<op::Operation> decode_recv(Socket socket);
};
