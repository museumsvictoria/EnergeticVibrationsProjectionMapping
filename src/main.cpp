
#include "Settings.h"
#include "ofMain.h"
#include "ofApp.h"
#include "ofAppGLFWWindow.h"

#pragma comment(linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"")

//========================================================================
int main( ){
	glfwInit();
	int count;
	GLFWmonitor** monitors = glfwGetMonitors(&count);
	std::cout << count << std::endl;

    ofGLFWWindowSettings settings;
    settings.setGLVersion(2, 1);
    settings.width =  1920;
    settings.height = 1080;
    settings.setPosition(ofVec2f(0,0));
    settings.resizable = true;
	settings.windowMode = ofWindowMode::OF_WINDOW;
	//settings.decorated = false;
    shared_ptr<ofAppBaseWindow> mainWindow = ofCreateWindow(settings);

	if (count > 1) {
        settings.setGLVersion(2, 1);
#ifdef PORTRAIT_MODE
        cout << "portrait" << endl;
		settings.width = 1080;
		settings.height = 1920;
#else
        cout << "landscape" << endl;
        settings.width = 1920;
        settings.height = 1080;
#endif
		settings.setPosition(ofVec2f(1920, 0));
		settings.resizable = true;
		settings.windowMode = ofWindowMode::OF_WINDOW;
		settings.decorated = false;
		// uncomment next line to share main's OpenGL resources with gui
		settings.shareContextWith = mainWindow;
		shared_ptr<ofAppBaseWindow> projectionWindow = ofCreateWindow(settings);
		projectionWindow->setVerticalSync(true);

		shared_ptr<ofApp> mainApp(new ofApp);
		mainApp->assign_second_window_ptr(projectionWindow);
        mainApp->set_multiple_windows(true);
		mainApp->setupProjectionWindow();
		ofAddListener(projectionWindow->events().draw, mainApp.get(), &ofApp::drawProjections);
		ofAddListener(projectionWindow->events().keyPressed, mainApp.get(), &ofApp::keyPressedProjectionWindow);
		ofRunApp(mainWindow, mainApp);
	}
	else {
		shared_ptr<ofApp> mainApp(new ofApp);
		mainApp->set_multiple_windows(false);
        mainApp->assign_second_window_ptr(mainWindow);
		ofRunApp(mainWindow, mainApp);

	}

	
	glfwWindowHint(GLFW_FLOATING, GL_TRUE);
	glfwWindowHint(GLFW_DECORATED, GL_FALSE);
	glfwWindowHint(GLFW_AUTO_ICONIFY, GL_FALSE);
	
    ofRunMainLoop();
    
}
