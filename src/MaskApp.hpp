#pragma once

#include "ofMain.h"

//Masking
#include "ofxProjectionMask.h"
#include "ofxLayerMask.h"

class MaskApp : public ofBaseApp {
public:
	void setup();
	void update();
	void draw();
	void keyReleased(int key);
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);

	// Masking
	ofxProjectionMask masker;
	ofxLayerMask * mask_pattern;
};
