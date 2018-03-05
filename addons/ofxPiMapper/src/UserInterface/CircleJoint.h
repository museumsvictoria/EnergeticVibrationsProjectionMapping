#pragma once

#include "ofMain.h"
#include "BaseJoint.h"

namespace ofx {
namespace piMapper {
class CircleJoint : public BaseJoint {

	public:
		CircleJoint();

		void update();
		void draw();
		bool hitTest(ofVec2f position);
		bool hitTestJoint(const ofVec2f & position);

	private:
		float radius;

		void setDefaultProperties();

};

} // namespace piMapper
} // namespace ofx