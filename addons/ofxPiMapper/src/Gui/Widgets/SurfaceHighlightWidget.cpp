#include "SurfaceHighlightWidget.h"

namespace ofx {
namespace piMapper {

SurfaceHighlightWidget::SurfaceHighlightWidget(){
	_sm = 0;
    surface_colour = ofVec3f(255,26,34);
}

void SurfaceHighlightWidget::draw(){
	if(_sm == 0){
		return;
	}
	
	drawAllSurfaceOutlines();
	
	if(_sm->getSelectedSurface() == 0){
		return;
	}
	
	ofPushStyle();
	ofSetLineWidth(4);
	ofSetColor(surface_colour.x,surface_colour.y,surface_colour.z);
	
	drawSurfaceOutlines(_sm->getSelectedSurface());
	
	ofPopStyle();
}
    
void SurfaceHighlightWidget::set_surface_colour(ofVec3f surface_colour){
    this->surface_colour = surface_colour;
}

void SurfaceHighlightWidget::drawAllSurfaceOutlines(){
	if(_sm == 0){
		return;
	}
	
	ofPushStyle();
	ofSetColor(255, 255, 255, 150);
	ofSetLineWidth(2);
	for(unsigned int i = 0; i < _sm->size(); ++i){
		if(_sm->getSurface(i) != _sm->getSelectedSurface()){
			drawSurfaceOutlines(_sm->getSurface(i));
		}
	}
	ofPopStyle();
}

void SurfaceHighlightWidget::drawSurfaceOutlines(BaseSurface * s){
	// TODO: Use Surface::drawOutline here
	if(s->getType() == SurfaceType::QUAD_SURFACE &&
		((QuadSurface *)s)->getPerspectiveWarping()){
		ofPolyline line = s->getHitArea();
		line.draw();
	}else if(s->getType() == SurfaceType::GRID_WARP_SURFACE){
		s->getMesh().drawWireframe();
	}else if(s->getType() == SurfaceType::HEXAGON_SURFACE){
		s->getMesh().drawWireframe();
	}else{
		ofPolyline p;
		for(unsigned int i = 0;
			i < s->getMesh().getVertices().size();
			++i){
			
			p.addVertex(ofPoint(
				s->getMesh().getVertices()[i]));
		}
		p.close();
		p.draw();
	}
}

} // namespace piMapper
} // namespace ofx
