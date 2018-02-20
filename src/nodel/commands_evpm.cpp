#include "commands_evpm.hpp"
#include "json.hpp"
#include <iostream>
#include "ofxPiMapper.h"

namespace op{
  void LoadPreset::run(ofxPiMapper & mapper){ 
	  mapper.clear_all();
	  mapper.loadProject(name + ".xml");
	  mapper.save_temp();
	  cout << "Preset Loaded as: " << name << endl;
  }
  std::string LoadPreset::get_type(){ return "LoadPreset"; }

  void SavePreset::run(ofxPiMapper & mapper){ 
	  mapper.save_with_name(name + ".xml");
	  mapper.save_temp();
	  cout << "Preset Saved as: " << name << endl;
  }
  std::string SavePreset::get_type(){ return "SavePreset"; }

  void Save::run(ofxPiMapper & mapper){
	  mapper.save_temp();
	  cout << "Preset Saved" << endl;
  }
  std::string Save::get_type(){ return "Save"; }

  void ClearAll::run(ofxPiMapper & mapper){
	  mapper.clear_all();
	  mapper.save_temp();
	  cout << "Clear all" << endl;
  }
  std::string ClearAll::get_type(){ return "ClearAll"; }

  void ToggleShaders::run(ofxPiMapper & mapper){}
  std::string ToggleShaders::get_type(){ return "ToggleShaders"; }

  void None::run(ofxPiMapper & mapper) {}

  std::unique_ptr<Operation> run_commands(std::string msg){
    using json = nlohmann::json;
    std::unique_ptr<op::Operation> my_op = std::make_unique<op::None>();
    try{
      auto j = json::parse(msg);

      if(auto it = j.find("LoadPreset") != j.end() ){
        std::vector<std::string> data = j["LoadPreset"];
        my_op = std::make_unique<op::LoadPreset>(data[0]);
      }else if(auto it = j.find("SavePreset") != j.end() ){
        std::vector<std::string> data = j["SavePreset"];
        my_op = std::make_unique<op::SavePreset>(data[0]);
      }else if(auto it = j.find("Save") != j.end() ){
        my_op = std::make_unique<op::Save>();
      }else if(auto it = j.find("ClearAll") != j.end() ){
        my_op = std::make_unique<op::ClearAll>();
      }else if(auto it = j.find("ToggleShaders") != j.end() ){
        my_op = std::make_unique<op::ToggleShaders>();
      }
    }catch(json::parse_error & e){
      std::cout << "Bad message: " << e.what() << std::endl;
    }
    return my_op;
  }
};
