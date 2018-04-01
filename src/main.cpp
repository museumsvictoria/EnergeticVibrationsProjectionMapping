#include "ofMain.h"
#include "ofApp.h"
#include "ofAppGLFWWindow.h"

//========================================================================
int main( ){
    ofGLFWWindowSettings settings;
    settings.setGLVersion(2, 1);
    settings.width =  1920;
    settings.height = 1080;
    settings.setPosition(ofVec2f(600,0));
    settings.resizable = true;
	settings.windowMode = ofWindowMode::OF_WINDOW;
    shared_ptr<ofAppBaseWindow> mainWindow = ofCreateWindow(settings);
    
    settings.width = 1920/5;
    settings.height = 1080/5;
    settings.setPosition(ofVec2f(0,0));
    settings.resizable = true;
    // uncomment next line to share main's OpenGL resources with gui
    settings.shareContextWith = mainWindow;
    shared_ptr<ofAppBaseWindow> projectionWindow = ofCreateWindow(settings);
    projectionWindow->setVerticalSync(true);
    
    shared_ptr<ofApp> mainApp(new ofApp);
    mainApp->setupProjectionWindow();
    ofAddListener(projectionWindow->events().draw,mainApp.get(),&ofApp::drawProjections);
    
    ofRunApp(mainWindow, mainApp);
    ofRunMainLoop();
    
}
