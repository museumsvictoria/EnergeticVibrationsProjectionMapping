#include "boundary.hpp"


namespace boundary {
	ofVec2f bounded_position(ofVec2f position) {
		position.x = ofClamp(position.x, BOUNDARY_RECT.x, BOUNDARY_RECT.x + BOUNDARY_RECT.width);
		position.y = ofClamp(position.y, BOUNDARY_RECT.y, BOUNDARY_RECT.y + BOUNDARY_RECT.height);
		return position;
	}

	ofVec2f find_bounded_position(ofRectangle bound_box, ofVec2f move_by) {
		auto new_move = move_by;
		auto new_pos = bound_box;
		new_pos.translate(new_move);
		if (BOUNDARY_RECT.inside(new_pos)) {
			return new_move;
		}
		new_move = move_by;
		new_move.x *= -1.0;
		new_pos = bound_box;
		new_pos.translate(new_move);
		if (BOUNDARY_RECT.inside(new_pos)) {
			return new_move;
		}
		new_move = move_by;
		new_move.x *= -1.0;
		new_move.y *= -1.0;
		new_pos = bound_box;
		new_pos.translate(new_move);
		if (BOUNDARY_RECT.inside(new_pos)) {
			return new_move;
		}
		new_move = move_by;
		new_move.y *= -1.0;
		new_pos = bound_box;
		new_pos.translate(new_move);
		if (BOUNDARY_RECT.inside(new_pos)) {
			return new_move;
		}

		return ofVec2f(BOUNDARY_RECT.getCenter() - bound_box.getCenter());

	}

	ofVec2f reduced_move_amount(ofVec3f vertex, ofVec2f move) {
		ofVec2f new_pos = vertex + move;
		ofVec2f amount(0,0);
		float width = BOUNDARY_RECT.x + BOUNDARY_RECT.width;
		float height = BOUNDARY_RECT.y + BOUNDARY_RECT.height;
		amount.x += std::min(width - new_pos.x, 0.0f);
		amount.x += std::max(BOUNDARY_RECT.x - new_pos.x, 0.0f);
		amount.y += std::min(height - new_pos.y, 0.0f);
		amount.y += std::max(BOUNDARY_RECT.y - new_pos.y, 0.0f);
		return amount;
	}

	ofVec2f bounded_move(const vector<ofVec3f> & verticies, ofVec2f move) {
		for (auto const & v : verticies) {
			move += reduced_move_amount(v, move);
		}
		return move;
	}

	void test_bounded_move() {
		//Tests
		vector<ofVec3f> shape;
		shape.push_back(ofVec3f(450, 20, 0));
		shape.push_back(ofVec3f(1800, 20, 0));
		shape.push_back(ofVec3f(1000, 800, 0));
		ofVec2f test_move(0, 0);
		test_move = boundary::bounded_move(shape, test_move);
		cout << "was: " << test_move << endl;
		assert(test_move.x == 0);
		assert(test_move.y == 0);
		// before x
		test_move = ofVec2f(-100, 0);
		test_move = boundary::bounded_move(shape, test_move);
		cout << "was: " << test_move << endl;
		assert(test_move.x == -28);
		assert(test_move.y == 0);
		// past width
		test_move = ofVec2f(100, 0);
		test_move = boundary::bounded_move(shape, test_move);
		cout << "was: " << test_move << endl;
		assert(test_move.x == 72);
		assert(test_move.y == 0);
		// above y
		test_move = ofVec2f(0, -19);
		test_move = boundary::bounded_move(shape, test_move);
		cout << "was: " << test_move << endl;
		assert(test_move.x == 0);
		assert(test_move.y == -7);
		// below height
		test_move = ofVec2f(0, 100);
		test_move = boundary::bounded_move(shape, test_move);
		cout << "was: " << test_move << endl;
		assert(test_move.x == 0);
		assert(test_move.y == 83);
	}

	bool inside_mapping(ofVec3f p) {
		return BOUNDARY_RECT.inside(p);
	}


	using ofx::piMapper::CircleJoint;
	bool is_collided_joint(const ofVec2f & touch_pos, ofx::piMapper::CircleJoint * j, std::vector<ofx::piMapper::CircleJoint *> & joints){
		for (auto oj : joints) {
			if (j == oj) {
				continue;
			}
			if (oj->hitTestJoint(touch_pos) ) {
				return true;
			}
		}
		return false;
	}
}
