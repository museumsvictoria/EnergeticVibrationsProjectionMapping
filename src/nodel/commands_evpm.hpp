#pragma once
#include "commands.hpp"
#include <memory>
#include <string>

class ofxPiMapper;

namespace op{
  struct LoadPreset : public Operation{
    std::string name;
    LoadPreset(std::string _n) : Operation(), name(_n) {}
    void run(ofxPiMapper &);
    std::string get_type();
  };

  struct SavePreset : public Operation{
    std::string name;
    SavePreset(std::string _n) : Operation(), name(_n) {}
    void run(ofxPiMapper &);
    std::string get_type();
  };

  struct Save: public Operation{
    void run(ofxPiMapper &);
    std::string get_type();
  };

  struct ClearAll: public Operation{
    void run(ofxPiMapper &);
    std::string get_type();
  };

  struct ToggleShaders: public Operation{
    void run(ofxPiMapper &);
    std::string get_type();
  };
  
  struct None : public Operation{
    void run(ofxPiMapper &);
    std::string get_type(){ return "None"; }
  };

  std::unique_ptr<Operation> run_commands(std::string);
};
