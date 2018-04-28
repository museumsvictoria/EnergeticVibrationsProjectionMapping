#pragma once

#include "ofEvents.h"
#include "BaseSurface.h"

#include "GuiBaseWidget.h"
#include "ScaleWidget.h"
#include "LayerPanelWidget.h"
#include "SurfaceHighlightWidget.h"
#include "TextureHighlightWidget.h"
#include "TextureEditorWidget.h"
#include "ProjectionEditorWidget.h"
#include "SourcesEditorWidget.h"

namespace ofx {
namespace piMapper {

struct GuiEvent{
	ofMouseEventArgs args;
	ofTouchEventArgs touch;
	GuiBaseWidget * widget;
};

// TODO: compress the following structs into something like:
// struct GuiEvent{
//   ofMouseEventArgs args;
//   GuiObject obj;
// };
// It could be then possible to check the object in question
// to decide what to do next.
struct GuiJointEvent{
	ofMouseEventArgs args;
    ofTouchEventArgs touch;
	int jointIndex;
};

struct GuiSurfaceEvent{
	ofMouseEventArgs args;
    ofTouchEventArgs touch;
	BaseSurface * surface;
};

struct GuiBackgroundEvent{
	ofMouseEventArgs args;
    ofTouchEventArgs touch;
};

class Gui {
	public:
		static Gui * instance();
	
		// TODO: combine the following events into one
		ofEvent <GuiJointEvent> jointPressedEvent;
		ofEvent <GuiJointEvent> jointReleasedEvent;
		ofEvent <GuiJointEvent> jointDraggedEvent;
	
		void notifyJointPressed(ofMouseEventArgs & args, int jointIndex);
		void notifyJointReleased(ofMouseEventArgs & args, int jointIndex);
		void notifyJointDragged(ofMouseEventArgs & args, int jointIndex);
    
        void notifyJointPressed(ofTouchEventArgs & touch, int jointIndex);
        void notifyJointReleased(ofTouchEventArgs & touch, int jointIndex);
        void notifyJointDragged(ofTouchEventArgs & touch, int jointIndex);
	
		ofEvent <GuiSurfaceEvent> surfacePressedEvent;
		ofEvent <GuiSurfaceEvent> surfaceReleasedEvent;
		ofEvent <GuiSurfaceEvent> surfaceDraggedEvent;
	
		void notifySurfacePressed(ofMouseEventArgs & args, BaseSurface * surface);
		void notifySurfaceReleased(ofMouseEventArgs & args, BaseSurface * surface);
		void notifySurfaceDragged(ofMouseEventArgs & args, BaseSurface * surface);
    
        void notifySurfacePressed(ofTouchEventArgs & touch, BaseSurface * surface);
        void notifySurfaceReleased(ofTouchEventArgs & touch, BaseSurface * surface);
        void notifySurfaceDragged(ofTouchEventArgs & touch, BaseSurface * surface);
	
		ofEvent <GuiBackgroundEvent> backgroundPressedEvent;
	
		void notifyBackgroundPressed(ofMouseEventArgs & args);
        void notifyBackgroundPressed(ofTouchEventArgs & touch);
	
		ScaleWidget & getScaleWidget();
		LayerPanelWidget & getLayerPanelWidget();
		SurfaceHighlightWidget & getSurfaceHighlightWidget();
		TextureHighlightWidget & getTextureHighlightWidget();
		TextureEditorWidget & getTextureEditorWidget();
		ProjectionEditorWidget & getProjectionEditorWidget();
		SourcesEditorWidget & getSourcesEditorWidget();
	
		// Consider these as a part of the application states/modes.
		void onMousePressed(ofMouseEventArgs & args);
		void onMouseReleased(ofMouseEventArgs & args);
		void onMouseDragged(ofMouseEventArgs & args);
	
        // JOSH adding in touch events
        void touchDown(map<int, ofTouchEventArgs> & touchMap);
        void touchMoved(map<int, ofTouchEventArgs> & touchMap);
        void touchUp(map<int, ofTouchEventArgs> & touchMap);
        
		void onScaleWidgetEvent(GuiWidgetEvent & event);
	
		ofEvent <GuiEvent> guiEvent;
	
	private:
		Gui();
		~Gui();
	
		static Gui * _instance;
	
		ScaleWidget _scaleWidget;
		LayerPanelWidget _layerPanelWidget;
		SurfaceHighlightWidget _surfaceHighlightWidget;
		TextureHighlightWidget _textureHighlightWidget;
		TextureEditorWidget _textureEditorWidget;
		ProjectionEditorWidget _projectionEditorWidget;
		SourcesEditorWidget _sourcesEditorWidget;
};

} // piMapper
} // ofx
