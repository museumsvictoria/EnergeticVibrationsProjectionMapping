#pragma once

#include "ofMain.h"
#include "Settings.h"
#include "ofxOsc.h"
#include "ofxImGui.h"
#include "GuiTheme.h"
#include "GuiInterface.h"
#include "ofxJSON.h"

#include "ShaderVariable.h"
#include "SurfaceMask.h"
#include "VisualLayer.h"
#include "ofxPiMapper.h"

#include "nodel/nodel_interpreter.hpp"

//----------------WINDOWS ONLY
#ifdef WINDOWS_TOUCH
#include "ofxWinTouchHook.h"
#endif

#include <fstream>


class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
    
        void build_shader_src();
    
        void create_shader_source(int idx);
        void remove_shader_source(int idx);
    
		void set_multiple_windows(bool multiple_windows);
        void assign_second_window_ptr(shared_ptr<ofAppBaseWindow> projectionWindow);
        void setupProjectionWindow();
        void drawProjections(ofEventArgs & args);
        void keyPressedProjectionWindow(ofKeyEventArgs & key);
		
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
		
        // Second Window
        ofRectangle get_projector_dimensions();
        shared_ptr<ofAppBaseWindow> projectionWindow;
		bool multiple_windows;
    
        //----------------WINDOWS ONLY
#ifdef WINDOWS_TOUCH
        // Touches //
        void touchDown(ofTouchEventArgs & touch);
        void touchMoved(ofTouchEventArgs & touch);
        void touchUp(ofTouchEventArgs & touch);
        map<int, ofTouchEventArgs> touchMap;
#endif
        ///------------- OSC
        void update_osc();
        ofxOscReceiver receiver;
        vector<float> volumes;

        ///------------- MAPPING
        ofxPiMapper mapper;
        ofFbo projection_fbo;
        SurfaceMask surface_mask;
    
        ///------------- LAYERS
        vector<VisualLayer*> layers;
        ofShader scene_shader;
        ofShader temp_scene_shader;
        bool isShaderDirty;
        vector<vector<ShaderVariable> > shader_variables;

        ///------------- GUI
        ofxImGui::Gui gui;
        GuiTheme gui_theme;
		int clear_touch_in_two_frames;
    
        // Gui Themes Colour
        ofVec4f theme_colour;
    
        GuiInterface gui_interface;

private:
		// Tom added to turn mouse on / off
		bool mouse;
		void toggle_shaders();
		nodel_interpreter::Nodel nodel;
		void allocate_buffers();
};
