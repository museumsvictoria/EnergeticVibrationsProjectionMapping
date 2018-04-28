#pragma once
#include "commands.hpp"
#include <memory>
#include <string>
#include "nodel_dep.hpp"

class ofxPiMapper;

namespace op {
	struct LoadPreset : public Operation {
		ofxPiMapper & mapper;
		std::string name;
		LoadPreset(ofxPiMapper & _m, std::string _n) : Operation(), mapper(_m), name(_n) {}
		void run();
		std::string get_type();
	};

	struct SavePreset : public Operation {
		ofxPiMapper & mapper;
		std::string name;
		SavePreset(ofxPiMapper & _m, std::string _n) : Operation(), mapper(_m), name(_n) {}
		void run();
		std::string get_type();
	};

	struct Save : public Operation {
		ofxPiMapper & mapper;
		Save(ofxPiMapper & _m) : mapper(_m) {}
		std::string get_type();
		void run();
	};

	struct ClearAll : public Operation {
		ofxPiMapper & mapper;
		ClearAll(ofxPiMapper & _m) : mapper(_m) {}
		void run();
		std::string get_type();
	};

	struct ToggleShaders : public Operation {
		std::vector<VisualLayer *> & layers;
		ToggleShaders(std::vector<VisualLayer *> & _l) : layers(_l) {}
		void run();
		std::string get_type();
	};

	struct SetMaxSurfaces : public Operation {
		ofxPiMapper & mapper;
		int num;
		SetMaxSurfaces(ofxPiMapper & _m, int _n) : mapper(_m), num(_n)  {}
		void run();
		std::string get_type();
	};

	struct None : public Operation {
		void run();
		std::string get_type() { return "None"; }
	};

	std::unique_ptr<Operation> runnable_command(std::string, std::shared_ptr<nodel_interpreter::NodelDep>);
};
