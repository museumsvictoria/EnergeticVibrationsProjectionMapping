#pragma once

#include "ofMain.h"
#include "ofxImGui.h"
#include "GuiTheme.h"
#include "GuiInterface.h"

#include "VisualLayer.h"
#include "Settings.h"
#include "ofxPiMapper.h"

#include "PiGui.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
    
        void setupProjectionWindow();
        void drawProjections(ofEventArgs & args);

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
        ///------------- MAPPING
        ofxPiMapper mapper;
        ofFbo projection_fbo;
    
        ///------------- GUI
        vector<VisualLayer*> layers;
    
        ///------------- GUI
        ofxImGui::Gui gui;
        GuiTheme gui_theme;
        int selected_layer;
    
        GuiInterface gui_interface;
};
