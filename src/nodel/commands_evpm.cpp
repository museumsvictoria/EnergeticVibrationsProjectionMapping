#include "commands_evpm.hpp"
#include "json.hpp"
#include <iostream>
#include "ofxPiMapper.h"
#include "video_controller.h"
#include "VisualLayer.h"
#include "SurfaceManager.h"

namespace op {

	std::string LoadPreset::get_type() { return "LoadPreset"; }

	void LoadPreset::run() {
		mapper.clear_all();
		mapper.loadProject("presets/" + name + ".xml");
		mapper.save_temp();
		cout << "Preset Loaded as: " << name << endl;
	}

	void SavePreset::run() {
		mapper.save_with_name("presets/" + name + ".xml");
		mapper.save_temp();
		cout << "Preset Saved as: " << name << endl;
	}
	std::string SavePreset::get_type() { return "SavePreset"; }

	void Save::run() {
		mapper.save_temp();
		cout << "Preset Saved" << endl;
	}
	std::string Save::get_type() { return "Save"; }

	void ClearAll::run() {
		mapper.clear_all();
		mapper.save_temp();
		cout << "Clear all" << endl;
	}
	std::string ClearAll::get_type() { return "ClearAll"; }

	void ToggleShaders::run() {
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

	void SetMaxSurfaces::run() {
		ofx::piMapper::SurfaceManager::setMaxSurfaces(num);
		mapper.save_temp();
			cout << "Set max surfaces to: " << num << endl;
	}
	std::string SetMaxSurfaces::get_type() { return "ToggleShaders"; }

	void None::run() {}

	std::unique_ptr<Operation> runnable_command(std::string msg, std::shared_ptr<nodel_interpreter::NodelDep> deps) {
		using json = nlohmann::json;
		std::unique_ptr<op::Operation> my_op = std::make_unique<op::None>();
		try {
			auto j = json::parse(msg);

			if (auto it = j.find("LoadPreset") != j.end()) {
				std::vector<std::string> data = j["LoadPreset"];
				my_op = std::make_unique<op::LoadPreset>(deps->mapper, data[0]);
			}
			else if (auto it = j.find("SavePreset") != j.end()) {
				std::vector<std::string> data = j["SavePreset"];
				my_op = std::make_unique<op::SavePreset>(deps->mapper, data[0]);
			}
			else if (auto it = j.find("Save") != j.end()) {
				my_op = std::make_unique<op::Save>(deps->mapper);
			}
			else if (auto it = j.find("ClearAll") != j.end()) {
				my_op = std::make_unique<op::ClearAll>(deps->mapper);
			}
			else if (auto it = j.find("ToggleShaders") != j.end()) {
				my_op = std::make_unique<op::ToggleShaders>(deps->layers);
			}
			else if (auto it = j.find("SetMaxSurfaces") != j.end()) {
				std::vector<std::string> data = j["SetMaxSurfaces"];
				try {
					my_op = std::make_unique<op::SetMaxSurfaces>(deps->mapper, std::stoi(data[0]));
				}
				catch (std::invalid_argument &e) {
					std::cout << "Not a number: " << e.what() << std::endl;
				}
			}
			else {
				std::cout << "Wrong message format or not found. Use {\"Command\": [\"arg\"] } or {\"Command\": [] }" << std::endl;
			}
		}
		catch (json::parse_error & e) {
			std::cout << "Bad message: " << e.what() << std::endl;
		}
		catch (json::type_error & e) {
			std::cout << "Bad message: " << e.what() << std::endl;
		}
		return my_op;
	}
};
