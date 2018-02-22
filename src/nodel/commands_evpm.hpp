#pragma once
#include "commands.hpp"
#include <memory>
#include <string>
#include "nodel_dep.hpp"

class ofxPiMapper;

namespace op {
	class LoadPresetCmd {
		ofxPiMapper & mapper;
	public:
		LoadPresetCmd(ofxPiMapper & _m) : mapper(_m) {}
		void run(std::string);
	};

	struct LoadPreset : public Operation {
		LoadPresetCmd cmd;
		std::string name;
		LoadPreset(LoadPresetCmd _cmd, std::string _n) : Operation(), cmd(_cmd), name(_n) {}
		void run() { cmd.run(name); }
		std::string get_type();
	};

	class SavePresetCmd {
		ofxPiMapper & mapper;
	public:
		SavePresetCmd(ofxPiMapper & _m) : mapper(_m) {}
		void run(std::string);
	};

	struct SavePreset : public Operation {
		SavePresetCmd cmd;
		std::string name;
		SavePreset(SavePresetCmd _cmd, std::string _n) : Operation(), cmd(_cmd), name(_n) {}
		void run() { cmd.run(name); }
		std::string get_type();
	};

	class SaveCmd {
		ofxPiMapper & mapper;
	public:
		SaveCmd(ofxPiMapper & _m) : mapper(_m) {}
		void run();
	};

	struct Save : public Operation {
		SaveCmd cmd;
		Save(SaveCmd _cmd) : cmd(_cmd) {}
		std::string get_type();
		void run() { cmd.run(); }
	};

	class ClearAllCmd {
		ofxPiMapper & mapper;
	public:
		ClearAllCmd(ofxPiMapper & _m) : mapper(_m) {}
		void run();
	};

	struct ClearAll : public Operation {
		ClearAllCmd cmd;
		ClearAll(ClearAllCmd _cmd) : cmd(_cmd) {}
		void run() { cmd.run(); }
		std::string get_type();
	};

	class ToggleShadersCmd {
		std::vector<VisualLayer *> & layers;
	public:
		ToggleShadersCmd(std::vector<VisualLayer *> & _l) : layers(_l) {}
		void run();
	};
	
	struct ToggleShaders : public Operation {
		ToggleShadersCmd cmd;
		ToggleShaders(ToggleShadersCmd _cmd) : cmd(_cmd) {}
		void run() { cmd.run(); }
		std::string get_type();
	};

	struct None : public Operation {
		void run();
		std::string get_type() { return "None"; }
	};

	std::unique_ptr<Operation> runnable_command(std::string, std::shared_ptr<nodel_interpreter::NodelDep>);
};
