#pragma once

#include "GuiBaseWidget.h"
#include "SurfaceManager.h"

namespace ofx {
namespace piMapper {

class SurfaceHighlightWidget : public GuiBaseWidget {
	public:
		SurfaceHighlightWidget();
	
		void setup(){}
		void update(){}
		void draw();
	
		void onMousePressed(ofMouseEventArgs & args){}
		void onMouseReleased(ofMouseEventArgs & args){}
		void onMouseDragged(ofMouseEventArgs & args){}
	
		bool inside(float x, float y){ return false; }
	
		void setSurfaceManager(SurfaceManager * sm){ _sm = sm; }
		void drawAllSurfaceOutlines();
		void drawSurfaceOutlines(BaseSurface * s);
	
        void set_surface_colour(ofVec3f surface_colour);
	private:
		SurfaceManager * _sm;
    
        ofVec3f surface_colour;
};

} // namespace piMappe
} // namespace ofx
