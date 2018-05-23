
#include "Settings.h"
#include "ofMain.h"
#include "ofApp.h"
#include "ofAppGLFWWindow.h"

#pragma comment(linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"")

//========================================================================
int main( ){
	

	ofGLFWWindowSettings settings;
	settings.setGLVersion(2, 1);
	settings.width = 1920 * 2;
	settings.height = 1080;
	settings.multiMonitorFullScreen = true;
	settings.windowMode = OF_WINDOW;
	ofCreateWindow(settings);

	ofRunApp(new ofApp);
}
