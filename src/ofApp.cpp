#include "ofApp.h"


//--------------------------------------------------------------
void ofApp::setup(){
    ofSetFrameRate(60);
    ofDisableArbTex(); // Use GL_TEXTURE_2D Textures (normalized texture coordinates 0..1)
    ofBackground(0);


    static int num_layers = 8;
    
    for(int i = 0; i < num_layers; i++){
        VisualLayer *layer = new VisualLayer();
        layers.push_back(layer);
        layers[i]->setup("Shader" + ofToString(1+i), i);
        
        mapper.registerFboSource(layers[i]);
    }
    
    ofx::piMapper::VideoSource::enableAudio = false;
    ofx::piMapper::VideoSource::useHDMIForAudio = false;
    mapper.setup();
    
    selected_layer = 0;
    
    // SetupGui() is called in main.cpp before layers has had a chance to fill up
    // hence the reason we need to call this funciton here.
    gui_interface.setup_shader_toggles(layers);
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
    
    gui_interface.setup(gui);
}

char *convert(const std::string & s) {
    char *pc = new char[s.size()+1];
    std::strcpy(pc, s.c_str());
    return pc;
}

//--------------------------------------------------------------
void ofApp::drawGui(ofEventArgs & args){

    ofShowCursor();
    this->gui.begin();
//    
//    auto mainSettings = ofxImGui::Settings();
//    mainSettings.windowPos = ofVec2f(0, 0);
//    
//    if (ofxImGui::BeginWindow("Shader control", mainSettings, false))
//    {
//        vector<float> *params = &layers[selected_layer]->shader_params[selected_layer].params;
//
//        vector<char*> names_char;
//        vector<string> names = layers[selected_layer]->shader_params[selected_layer].names;
//        transform(names.begin(), names.end(), back_inserter(names_char), convert);
//
//        // Basic columns
//        if (ofxImGui::BeginTree("Shader", mainSettings)){
//            ImGui::SliderFloat(names_char[0],&params->at(0),0.0,1.0);
//            ImGui::SliderFloat(names_char[1],&params->at(1),0.0,1.0);
//            ImGui::SliderFloat(names_char[2],&params->at(2),0.0,1.0);
//            ImGui::SliderFloat("Hue Shift",&layers[selected_layer]->hue_offset,0.0,PI*2);
//            ofxImGui::EndTree(mainSettings);
//        }
//    }
//    ofxImGui::EndWindow(mainSettings);
//    
    gui_interface.draw(gui);

    this->gui.end();
    
}


//--------------------------------------------------------------
void ofApp::update(){
    mapper.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
    mapper.draw();
    
    int size = 100;
    for(int i = 0; i < layers.size(); i++){
        layers[i]->FboSource::drawPreview(i * size, ofGetHeight()-size, size, size);
    }
    //layers[0]->hue_fbo.fbo.draw(0,0,ofGetWidth(),ofGetHeight());

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    mapper.keyPressed(key);
    
    switch (key) {
        case '1':
            selected_layer = 0;
            break;
        case '2':
            selected_layer = 1;
            break;
        case '3':
            selected_layer = 2;
            break;
        case '4':
            selected_layer = 3;
            break;
        case '5':
            selected_layer = 4;
            break;
        case '6':
            selected_layer = 5;
            break;
        case '7':
            selected_layer = 6;
            break;
        case '8':
            selected_layer = 7;
            break;
        default:
            break;
    }
    
    cout << "selected latyer = " << selected_layer << endl;
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

