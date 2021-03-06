#pragma once

#include "ofMain.h"
#include "BaseSurface.h"
#include "SurfaceType.h"
#include "HomographyHelper.h"

namespace ofx {
namespace piMapper {

class QuadSurface : public BaseSurface {
	public:
		QuadSurface();
		~QuadSurface();

		void setup();
		void setup(ofVec2f p1, ofVec2f p2, ofVec2f p3, ofVec2f p4, ofVec2f t1,
				   ofVec2f t2, ofVec2f t3, ofVec2f t4, BaseSource * newSource);

		void draw();
	
		void setVertex(int index, ofVec2f p);
		void setNewVertex(int index, ofVec2f p);
		void setVertices(vector<ofVec2f> v);
		void setVertices(vector<ofVec3f> v);
	
		void setTexCoord(int index, ofVec2f t);
		void setTexCoords(vector<ofVec2f> t);
	
		void moveBy(ofVec2f v);

		int getType();
		bool hitTest(ofVec2f p);
		ofVec2f getVertex(int index);
		ofVec2f getTexCoord(int index);
		ofPolyline getHitArea();
		ofPolyline getTextureHitArea();
		vector <ofVec3f> & getVertices();
		vector <ofVec2f> & getTexCoords();
	
		void setPerspectiveWarping(bool b);
		bool getPerspectiveWarping();
	
		ofRectangle getMeshBoundingBox();
	
		BaseSurface * clone();

		bool is_concave();

	private:
		void calculateHomography();
		int GetAngleABC(ofVec2f a, ofVec2f b, ofVec2f c);
	
		float _matrix[16];
		bool _perspectiveWarping;
};

} // namespace piMapper
} // namespace ofx