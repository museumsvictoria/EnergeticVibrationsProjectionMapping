#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetFrameRate(60);
    ofDisableArbTex(); // Use GL_TEXTURE_2D Textures (normalized texture coordinates 0..1)
    ofBackground(0);


    static int num_layers = 1;
    
    for(int i = 0; i < num_layers; i++){
        VisualLayer *layer = new VisualLayer();
        layers.push_back(layer);
        layers[i]->setup("Shader" + ofToString(1+i));
        layers[i]->load_shader("shaders/shader" + ofToString(1+i) + ".frag");
        
        mapper.registerFboSource(layers[i]);
    }
    
    ofx::piMapper::VideoSource::enableAudio = false;
    ofx::piMapper::VideoSource::useHDMIForAudio = false;
    mapper.setup();
    
}

//--------------------------------------------------------------
void ofApp::setupGui(){
    ofSetBackgroundColor(0);
    
    //load fonts first
    gui_theme.load_font();
    
    //required call
    gui.setup();
    
    //load theme
    gui_theme.init_theme();
}

//--------------------------------------------------------------
void ofApp::drawGui(ofEventArgs & args){
    this->gui.begin();
    
    auto mainSettings = ofxImGui::Settings();
    mainSettings.windowPos = ofVec2f(0, 0);
    
    if (ofxImGui::BeginWindow("Shader control", mainSettings, false))
    {
        // Basic columns
        if (ofxImGui::BeginTree("Shader", mainSettings)){
            //ImGui::SliderFloat("Param1",&params.scale_speed,0.0,1.0);
            //ImGui::SliderFloat("Param2",&params.rot_speed,0.0,1.0);
            //ImGui::SliderFloat("Param3",&params.grid_offset,0.0,1.0);
            //ImGui::SliderFloat("Hue Shift",&params.shape_morph,0.0,1.0);
            ofxImGui::EndTree(mainSettings);
        }
    }
    ofxImGui::EndWindow(mainSettings);
    
    this->gui.end();
    
    
}

//--------------------------------------------------------------
void ofApp::update(){
    mapper.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
    mapper.draw();
    
    //layers[0]->hue_fbo.fbo.draw(0,0,ofGetWidth(),ofGetHeight());

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
    mapper.mousePressed(x, y, button);
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
