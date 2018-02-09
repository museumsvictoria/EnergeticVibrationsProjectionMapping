#pragma once

#include "Application.h"
#include "ofLog.h"
#include "ofGraphics.h"
#include "StartDragSurfaceCmd.h"
#include "DeselectSurfaceCmd.h"
#include "MvSurfaceVertCmd.h"
#include "SurfaceType.h"
#include "PiGui.h"
#include "ScaleWidget.h"

#include "drag_manager.hpp"

namespace ofx {
namespace piMapper {

class ProjectionMappingMode : public ApplicationBaseMode {

	public:
		static ProjectionMappingMode * instance();
	
		void setup(Application * app);
		void update(Application * app);
		void draw(Application * app);
    
        void onTouchDown(Application * app, map<int, ofTouchEventArgs> & touchMap);
        void onTouchMoved(Application * app, map<int, ofTouchEventArgs> & touchMap);
        void onTouchUp(Application * app, map<int, ofTouchEventArgs> & touchMap);
        void onTouchUp(Application * app, map<int, ofTouchEventArgs> & touchMap, int touch_id);
    
		void onKeyPressed(Application * app, ofKeyEventArgs & args);
		void onMousePressed(Application * app, ofMouseEventArgs & args);
		void onMouseReleased(Application * app, ofMouseEventArgs & args);
		void onMouseDragged(Application * app, ofMouseEventArgs & args);
		void onJointPressed(Application * app, GuiJointEvent & e);
		void onSurfacePressed(Application * app, GuiSurfaceEvent & e);
		void onBackgroundPressed(Application * app, GuiBackgroundEvent & e);
	
		void onGuiEvent(Application * app, GuiEvent & e);

	private:
		ProjectionMappingMode();
	
		static ProjectionMappingMode * _instance;
	
		float _surfaceScaleBeforeTransform;
	
		ofVec2f _clickPosition;
	
		bool _bSurfaceDrag;
		bool _bDrawLayerPanel;
    
    // Tom added for multitracking
    drag_manager::ActiveHits active_hits;
    drag_manager::ActiveJoints active_joints;

};

} // namespace piMapper
} // namespace ofx
