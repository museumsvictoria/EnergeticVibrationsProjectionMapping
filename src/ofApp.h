#pragma once
#define WINDOWS_TOUCH

#include "ofMain.h"
#include "ofxImGui.h"
#include "GuiTheme.h"
#include "GuiInterface.h"

#include "VisualLayer.h"
#include "Settings.h"
#include "ofxPiMapper.h"

//----------------WINDOWS ONLY
#ifdef WINDOWS_TOUCH
#include "ofxWinTouchHook.h"
#endif

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
		
        //----------------WINDOWS ONLY
#ifdef WINDOWS_TOUCH
        // Touches //
        void touchDown(ofTouchEventArgs & touch);
        void touchMoved(ofTouchEventArgs & touch);
        void touchUp(ofTouchEventArgs & touch);
        map<int, ofTouchEventArgs> touchMap;
#endif

        ///------------- MAPPING
        ofxPiMapper mapper;
        ofFbo projection_fbo;
    
        ///------------- GUI
        vector<VisualLayer*> layers;
    
        ///------------- GUI
        ofxImGui::Gui gui;
        GuiTheme gui_theme;
		int clear_touch_in_two_frames;
    
        GuiInterface gui_interface;
	
};
