#include "ofApp.h"
#include "nodel/nodel_dep.hpp"

//changed
//--------------------------------------------------------------
void ofApp::setup(){
    ofSetFrameRate(60);
    ofDisableArbTex(); // Use GL_TEXTURE_2D Textures (normalized texture coordinates 0..1)
    ofBackground(0);
    ofEnableSmoothing();

	mouse = true;
	//----------------WINDOWS ONLY
#ifdef WINDOWS_TOUCH
	mouse = false;
	// enable the Windows Touch Hook
	ofxWinTouchHook::EnableTouch();

	// add touch listeners
	ofAddListener(ofxWinTouchHook::touchDown, this, &ofApp::touchDown);
	ofAddListener(ofxWinTouchHook::touchMoved, this, &ofApp::touchMoved);
	ofAddListener(ofxWinTouchHook::touchUp, this, &ofApp::touchUp);
#endif


    static int num_layers = 7;
    
    for(int i = 0; i < num_layers; i++){
        VisualLayer *layer = new VisualLayer();
        layers.push_back(layer);
        layers[i]->setup("Shader" + ofToString(1+i), i);
        
        mapper.registerFboSource(layers[i]);
    }
    
    ofx::piMapper::VideoSource::enableAudio = false;
    ofx::piMapper::VideoSource::useHDMIForAudio = false;
    mapper.setup();
    
  
    //load fonts first
    gui_theme.load_font();
    
    //required call
    gui.setup();
    
    //load theme
    gui_theme.init_theme();
    
    gui_interface.setup(gui, mapper);
    gui_interface.setup_shader_toggles(layers);
    
	clear_touch_in_two_frames = 0;

    projection_fbo.allocate(1450,870,GL_RGBA);
    
    // OSC
    volumes = {1.0f,1.0f,1.0f};
    receiver.setup(OSC_PORT);
	nodel_interpreter::NodelDep nodel_dep(mapper, layers);
	nodel.setup(nodel_dep);
}



//--------------------------------------------------------------
void ofApp::setupProjectionWindow(){
   ofSetBackgroundColor(0);
   mapper._application.getSurfaceManager()->assign_projection_fbo(&projection_fbo);

}

//--------------------------------------------------------------
void ofApp::drawProjections(ofEventArgs & args){
   ofShowCursor();
 
   if(projection_fbo.isAllocated()){
        projection_fbo.getTexture().draw(0,0,ofGetWidth(), ofGetHeight());
    }
}

//--------------------------------------------------------------
void ofApp::update(){
	// This is hear incase we really need to start hacking ImGui
	// TO enable mouse events to be set from the touch screen. 
	// We need to call this function 2 frames after the last touch event happened 
	// So that button is hovered can be cleared. https://github.com/ocornut/imgui/issues/1470
	//if (ofGetFrameNum() - clear_touch_in_two_frames == 2) {
	//	ImGuiIO *io = &ImGui::GetIO();
	//	io->MousePos = ImVec2(-FLT_MAX, -FLT_MAX);
	//	cout << "frame cleared! -- frame num = " << ofGetFrameNum() << endl;
	//}

    update_osc();
    mapper.update();
	gui_interface.update_volumes(volumes);
    gui_interface.update_audio_reactivity(layers);
		
	
}

//--------------------------------------------------------------
void ofApp::update_osc(){
    // check for waiting messages
    while(receiver.hasWaitingMessages()){
        // get the next message
        ofxOscMessage m;
        receiver.getNextMessage(m);
        
        if(m.getAddress() == "/caco/0"){
            volumes[0] = m.getArgAsFloat(0);
            volumes[1] = m.getArgAsFloat(1);
            volumes[2] = m.getArgAsFloat(2);
        }
    }
}

//--------------------------------------------------------------
void ofApp::draw(){

	ofShowCursor();
    this->gui.begin();
    
    int selected_layer = gui_interface.get_selected_shader();
    gui_interface.draw(layers[selected_layer]->shader_params[selected_layer]);
    
    this->gui.end();

    ofSetColor(255,255);
    mapper.draw();

//    int size = 100;
//    for(int i = 0; i < layers.size(); i++){
//        layers[i]->FboSource::drawPreview(i * size, ofGetHeight()-size, size, size);
//    }
    //layers[0]->hue_fbo.fbo.draw(0,0,ofGetWidth(),ofGetHeight());

    //cout << "selected surface = " << mapper._application.getSurfaceManager()->getSelectedSurface() << endl;
    
//    mapper._application.Gui::getSourcesEditorWidget();
//    ofx::piMapper::Gui::getSourcesEditorWidget().getLoadedTexCount();
}

void ofApp::toggle_shaders() {
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	switch (key) {
	case 'm': 
		mouse = !mouse;
		if (mouse) {
			cout << "Mouse mode on" << endl;
		}
		else {
			cout << "Touch mode on" << endl;
		}
			  break;
	case 'v':
		toggle_shaders();
		cout << "toggle shadders" << endl;
			  break;
	case 'c': 
		mapper.clear_all();
		mapper.save_temp();
		cout << "Clear all" << endl;
		break;
	case 'y':
		mapper.clear_all();
		mapper.loadProject("presets/test_p.xml");
		mapper.save_temp();
		cout << "Preset Loaded" << endl;
		break;
	case 'r':
		mapper.save_with_name("presets/test_p2.xml");
		mapper.save_temp();
		cout << "Preset Loaded" << endl;
		break;
	case 'w':
		mapper.clear_all();
		mapper.loadProject("presets/test_p2.xml");
		mapper.save_temp();
		cout << "Preset Loaded" << endl;
		break;
	case 'u':
		nodel.try_run();
		/*
		cout << "checking udp" << endl;
		nodel_result.set(nodel_interpreter::decode_recv(nodel_socket));

		std::cout << "Type: " << nodel_result.get_type() << std::endl;
		nodel_result.run(mapper);
		*/
		break;
	}

	mapper.keyPressed(key);
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
		//mapper.keyReleased(key);

}


//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
	if (mouse) {
		mapper.mouseDragged(x, y, button);
	}
	
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    // allow the ImGui duplicate and remove buttons to take precedence
    // over the layer selection and deselection. otherwise the layers
    // deselect when the button is clicked. This results in no selected objects
    if(!gui_interface.is_mouse_over_mapping_toggles()){
        // Make sure that the mouse is actually within the mapping
        // rectangle before registering mouse events so we dont
        // deselect the currently selected layer.
        if(gui_interface.is_mouse_inside_mapping_rect()){
			if (mouse) {
				mapper.mousePressed(x, y, button);
			}
        }
    }
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
	if (mouse) {
		mapper.mouseReleased(x, y, button);
	}

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}


#ifdef WINDOWS_TOUCH
//----------------WINDOWS ONLY
//--------------------------------------------------------------
void ofApp::touchDown(ofTouchEventArgs & touch){
    touchMap[touch.id] = touch;
	gui_interface.touchDown(touchMap);
	if (!mouse) {
		mapper.touchDown(touchMap);
	}

	// This is hear incase we really need to start hacking ImGui
	// TO enable mouse events to be set from the touch screen. 
	//ImGuiIO *io = &ImGui::GetIO();
	//io->MousePos = ImVec2(touch.x, touch.y);
	//io->MouseDown[0] = true;
}

//--------------------------------------------------------------
void ofApp::touchMoved(ofTouchEventArgs & touch){
    touchMap[touch.id] = touch;
	gui_interface.touchMoved(touchMap);
	if (!mouse) {
		mapper.touchMoved(touchMap);
	}

}

//--------------------------------------------------------------
void ofApp::touchUp(ofTouchEventArgs & touch){
  //TODO this probably needs to be erased after passing in?
	touchMap[touch.id] = touch;
	gui_interface.touchUp(touchMap);
	if (!mouse) {
		mapper.touchUp(touchMap);
	}
	touchMap.erase(touch.id);

	// This is hear incase we really need to start hacking ImGui
	// TO enable mouse events to be set from the touch screen. 
	//ImGuiIO *io = &ImGui::GetIO();
	//io->MouseDown[0] = false;
	//clear_touch_in_two_frames = ofGetFrameNum();
}
#endif
