#include "ofApp.h"


//--------------------------------------------------------------
void ofApp::setup(){
    ofSetFrameRate(60);
    ofDisableArbTex(); // Use GL_TEXTURE_2D Textures (normalized texture coordinates 0..1)
    ofBackground(0);
    ofEnableSmoothing();

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
    
    projection_fbo.allocate(1450,870,GL_RGBA);
    
    //----------------WINDOWS ONLY
#ifdef WINDOWS_TOUCH
    /* Essential setup */
    ofxWin8TouchSetup();
    ofRegisterTouchEvents(this);
#endif

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
    mapper.update();
    
    vector<float> volumes;
    volumes.push_back(ofNoise(ofGetElapsedTimef() * 2.0));
    volumes.push_back(ofNoise(10000+ofGetElapsedTimef() * 2.0));
    volumes.push_back(ofNoise(200000+ofGetElapsedTimef() * 2.0));
    gui_interface.update_volumes(volumes);
    
    gui_interface.update_audio_reactivity(layers);
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

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    mapper.keyPressed(key);
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    mapper.keyReleased(key);
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    mapper.mouseDragged(x, y, button);
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
            mapper.mousePressed(x, y, button);
        }
    }
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    mapper.mouseReleased(x, y, button);
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
}

//--------------------------------------------------------------
void ofApp::touchMoved(ofTouchEventArgs & touch){
    touchMap[touch.id] = touch;
}

//--------------------------------------------------------------
void ofApp::touchUp(ofTouchEventArgs & touch){
    touchMap.erase(touch.id);
}

//--------------------------------------------------------------
void ofApp::touchDoubleTap(ofTouchEventArgs & touch){
    
}

//--------------------------------------------------------------
void ofApp::touchCancelled(ofTouchEventArgs & touch){
    touchMap.erase(touch.id);
}
#endif
