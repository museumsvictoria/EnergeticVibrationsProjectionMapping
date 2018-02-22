#include "commands_evpm.hpp"
#include "json.hpp"
#include <iostream>
#include "ofxPiMapper.h"
#include "video/video_controller.h"
#include "VisualLayer.h"

namespace op {

	std::string LoadPreset::get_type() { return "LoadPreset"; }

	void LoadPresetCmd::run(string name) {
		mapper.clear_all();
		mapper.loadProject("presets/" + name + ".xml");
		mapper.save_temp();
		cout << "Preset Loaded as: " << name << endl;
	}

	void SavePresetCmd::run(string name) {
		mapper.save_with_name("presets/" + name + ".xml");
		mapper.save_temp();
		cout << "Preset Saved as: " << name << endl;
	}
	std::string SavePreset::get_type() { return "SavePreset"; }

	void SaveCmd::run() {
		mapper.save_temp();
		cout << "Preset Saved" << endl;
	}
	std::string Save::get_type() { return "Save"; }

	void ClearAllCmd::run() {
		mapper.clear_all();
		mapper.save_temp();
		cout << "Clear all" << endl;
	}
	std::string ClearAll::get_type() { return "ClearAll"; }

	void ToggleShadersCmd::run() {
		auto loader = video_controller::load();
		for (int i = 0; i < layers.size(); i++) {
			auto l = layers[i];
			l->toggle_shader();
			if (!l->is_shader()) {
				if (loader.has_next()) {
					l->load_movie(loader.next());
				}
			}
		}
	}
	std::string ToggleShaders::get_type() { return "ToggleShaders"; }

	void None::run() {}

	std::unique_ptr<Operation> runnable_command(std::string msg, std::shared_ptr<nodel_interpreter::NodelDep> deps) {
		using json = nlohmann::json;
		std::unique_ptr<op::Operation> my_op = std::make_unique<op::None>();
		try {
			auto j = json::parse(msg);

			if (auto it = j.find("LoadPreset") != j.end()) {
				std::vector<std::string> data = j["LoadPreset"];
				my_op = std::make_unique<op::LoadPreset>(LoadPresetCmd(deps->mapper), data[0]);
			}
			else if (auto it = j.find("SavePreset") != j.end()) {
				std::vector<std::string> data = j["SavePreset"];
				my_op = std::make_unique<op::SavePreset>(SavePresetCmd(deps->mapper), data[0]);
			}
			else if (auto it = j.find("Save") != j.end()) {
				my_op = std::make_unique<op::Save>( SaveCmd(deps->mapper) );
			}
			else if (auto it = j.find("ClearAll") != j.end()) {
				my_op = std::make_unique<op::ClearAll>( ClearAllCmd(deps->mapper) );
			}
			else if (auto it = j.find("ToggleShaders") != j.end()) {
				my_op = std::make_unique<op::ToggleShaders>( ToggleShadersCmd(deps->layers) );
			}
			else {
				std::cout << "Wrong message format or not found. Use {\"Command\": [\"arg\"] } or {\"Command\": [] }" << std::endl;
			}
		}
		catch (json::parse_error & e) {
			std::cout << "Bad message: " << e.what() << std::endl;
		}
		return my_op;
	}
};
