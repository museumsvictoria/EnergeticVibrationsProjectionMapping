#pragma once
#include "ofVec2f.h"
#include "ofRectangle.h"
#include "CircleJoint.h"

namespace boundary {
	// hardcoded boundary coordinates
	static const ofRectangle BOUNDARY_RECT = ofRectangle(434,95,998,899);
	// Takes a position and returns that position clamped
	// to BOUNDARY_RECT
	ofVec2f bounded_position(ofVec2f);
	/*	Takes 
		vector of Vec3: surface mesh
		Vec3: the amount you're trying to move the
		surafce by
		Returns
		Vec3: an adjusted amount so that the mesh won't
		leave the BOUNDARY_RECT
	*/
	ofVec2f bounded_move(const vector<ofVec3f> &, ofVec2f);
	// run this to test bounded_move
	void test_bounded_move();

	bool inside_mapping(ofVec3f);

	bool is_collided_joint(const ofVec2f &, ofx::piMapper::CircleJoint * j, std::vector<ofx::piMapper::CircleJoint *> & joints);
};
