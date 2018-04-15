#include "ofMain.h"
#include "ofApp.h"
#include "ofAppGLFWWindow.h"

//========================================================================
int main( ){
    ofGLFWWindowSettings settings;
    settings.setGLVersion(2, 1);
    settings.width =  1920;
    settings.height = 1080;
    settings.setPosition(ofVec2f(0,0));
    settings.resizable = true;
	settings.windowMode = ofWindowMode::OF_FULLSCREEN;
    shared_ptr<ofAppBaseWindow> mainWindow = ofCreateWindow(settings);
    
    settings.width = 1920;
    settings.height = 1080;
    settings.setPosition(ofVec2f(0,0));
    settings.resizable = true;
    settings.windowMode = ofWindowMode::OF_WINDOW;
	settings.decorated = true;
    // uncomment next line to share main's OpenGL resources with gui
    settings.shareContextWith = mainWindow;
    shared_ptr<ofAppBaseWindow> projectionWindow = ofCreateWindow(settings);
    projectionWindow->setVerticalSync(true);
    
    shared_ptr<ofApp> mainApp(new ofApp);
    mainApp->assign_second_window_ptr(projectionWindow);
    mainApp->setupProjectionWindow();
    ofAddListener(projectionWindow->events().draw,mainApp.get(),&ofApp::drawProjections);
    ofAddListener(projectionWindow->events().keyPressed,mainApp.get(),&ofApp::keyPressedProjectionWindow);
    
    ofRunApp(mainWindow, mainApp);
    ofRunMainLoop();
    
}
