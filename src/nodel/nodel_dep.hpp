#pragma once
#include <vector>

class ofxPiMapper;
class VisualLayer;

namespace nodel_interpreter {
	struct NodelDep {
		ofxPiMapper & mapper;
		std::vector<VisualLayer *> & layers;

		NodelDep(ofxPiMapper & _m, std::vector<VisualLayer  *> & _l) :
			mapper(_m), layers(_l) {}
  };
};
