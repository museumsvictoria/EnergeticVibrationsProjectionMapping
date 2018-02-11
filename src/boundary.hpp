#pragma once
#include "ofVec2f.h"
#include "ofRectangle.h"

namespace boundary {
	static const ofRectangle BOUNDARY_RECT = ofRectangle(422, 13, 1450, 870);
	ofVec2f bounded_position(ofVec2f);
	ofVec2f bounded_move(const vector<ofVec3f> &, ofVec2f);
	void test_this();
};