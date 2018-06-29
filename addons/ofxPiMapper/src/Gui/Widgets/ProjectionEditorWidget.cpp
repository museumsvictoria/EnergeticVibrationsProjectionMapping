#include "ProjectionEditorWidget.h"
#include "drag_manager.hpp"
#include "boundary.hpp"

namespace ofx {
namespace piMapper {

ProjectionEditorWidget::ProjectionEditorWidget(){
	surfaceManager = 0;
	bShiftKeyDown = false;
	fSnapDistance = 10.0f;
}

void ProjectionEditorWidget::update(){
	// Tom changed. Removed logic that was cyclic 
	// and unnecessary

	if (surfaceManager->getSelectedSurface() == 0) {
		joints.clear();
	}
	
	
}

void ProjectionEditorWidget::draw(){
	if(surfaceManager == 0){
		return;
	}
	if(surfaceManager->getSelectedSurface() == 0){
		return;
	}
	if(joints.size() <= 0){
		createJoints();
	}
	drawJoints();
}

void ProjectionEditorWidget::mouseDragged(ofMouseEventArgs & args){
	
	// Pass args to joint mouse events
	for(unsigned int i = 0; i < joints.size(); ++i){
		if (joints[i]->isDragged() && !boundary::is_collided_joint(ofVec2f(args.x, args.y), joints[i], joints)) {
			surfaceManager->getSelectedSurface()->setVertex(i,
				boundary::bounded_position(args));
		}
	}
	
	ofVec2f mousePosition = ofVec2f(args.x, args.y);

	// Collect all vertices of the projection surfaces
	vector <ofVec3f *> allVertices;
	for(int i = 0; i < surfaceManager->size(); i++){
		BaseSurface * surface = surfaceManager->getSurface(i);
		if(surface == surfaceManager->getSelectedSurface()){
			continue; // Don't add vertices of selected surface
		}
		for(int j = 0; j < surface->getVertices().size(); j++){
			allVertices.push_back(&surface->getVertices()[j]);
		}
	}

	// Snap currently dragged joint to nearest vertex
	for(int i = 0; i < joints.size(); i++){
		if(joints[i]->isDragged()){
			for(int j = 0; j < allVertices.size(); j++){
				float distance = mousePosition.distance(*allVertices[j]);
				if(distance < fSnapDistance && !boundary::is_collided_joint(ofVec2f(args.x, args.y), joints[i], joints)){
					joints[i]->position = *allVertices[j];
					ofVec2f clickDistance = joints[i]->position - ofVec2f(args.x, args.y);
					joints[i]->setClickDistance(clickDistance);
					if (joints[i]->isDragged()) {
						surfaceManager->getSelectedSurface()->setVertex(i,
							boundary::bounded_position(joints[i]->position));
					}
					break;
				}
			}
		}
	}
}
    
void ProjectionEditorWidget::touchMoved(map<int, ofTouchEventArgs> &active_joint_move_touch) {

	for (auto &joint_touch : active_joint_move_touch) {
		auto bounded = boundary::bounded_position(joint_touch.second);
		joint_touch.second.x = bounded.x;
		joint_touch.second.y = bounded.y;
		// Tom changed to only set active dragging joints
		if (joint_touch.first < joints.size() && 
			joints[joint_touch.first]->isDragged()) {
			if (!boundary::is_collided_joint(joint_touch.second, joints[joint_touch.first], joints) ) {
				surfaceManager->getSelectedSurface()->setVertex(joint_touch.first,
					boundary::bounded_position(joint_touch.second));
			}
		}
	
		ofVec2f touchPosition = ofVec2f(joint_touch.second.x, joint_touch.second.y);

		// Collect all vertices of the projection surfaces
		vector <ofVec3f *> allVertices;
		for (int i = 0; i < surfaceManager->size(); i++) {
			BaseSurface * surface = surfaceManager->getSurface(i);
			if (surface == surfaceManager->getSelectedSurface()) {
				continue; // Don't add vertices of selected surface
			}
			for (int j = 0; j < surface->getVertices().size(); j++) {
				allVertices.push_back(&surface->getVertices()[j]);
			}
		}

		// Snap currently dragged joint to nearest vertex
		for (int i = 0; i < joints.size(); i++) {
			if (joints[i]->isDragged()) {
				for (int j = 0; j < allVertices.size(); j++) {
					float distance = touchPosition.distance(*allVertices[j]);
					if (distance < fSnapDistance && !boundary::is_collided_joint(joint_touch.second, joints[joint_touch.first], joints)) {
						joints[i]->position = *allVertices[j];
						ofVec2f clickDistance = joints[i]->position - ofVec2f(joint_touch.second.x, joint_touch.second.y);
						joints[i]->setClickDistance(clickDistance);
						if (joint_touch.first < joints.size() &&
							joints[joint_touch.first]->isDragged()) {
							surfaceManager->getSelectedSurface()->setVertex(i,
								boundary::bounded_position(joints[i]->position));
						}
						break;
					}
				}
			}
		}
		
	}
}


void ProjectionEditorWidget::gotMessage(ofMessage & msg){
	if(msg.message == "surfaceSelected"){
		clearJoints();
		createJoints();
	}
}

void ProjectionEditorWidget::setSurfaceManager(SurfaceManager * newSurfaceManager){
	if(surfaceManager != 0){
		ofRemoveListener(surfaceManager->vertexChangedEvent, this,
			&ProjectionEditorWidget::onVertexChanged);
		ofRemoveListener(surfaceManager->verticesChangedEvent, this,
			&ProjectionEditorWidget::onVerticesChanged);
		ofRemoveListener(surfaceManager->surfaceSelectedEvent, this,
			&ProjectionEditorWidget::onSurfaceSelected);
		ofRemoveListener(surfaceManager->vertexSelectedEvent, this,
			&ProjectionEditorWidget::onVertexSelected);
		ofRemoveListener(surfaceManager->vertexUnselectedEvent, this,
			&ProjectionEditorWidget::onVertexUnselected);
	}
	
	surfaceManager = newSurfaceManager;
	
	ofAddListener(surfaceManager->vertexChangedEvent, this,
		&ProjectionEditorWidget::onVertexChanged);
	ofAddListener(surfaceManager->verticesChangedEvent, this,
		&ProjectionEditorWidget::onVerticesChanged);
	ofAddListener(surfaceManager->surfaceSelectedEvent, this,
		&ProjectionEditorWidget::onSurfaceSelected);
	ofAddListener(surfaceManager->vertexSelectedEvent, this,
		&ProjectionEditorWidget::onVertexSelected);
	ofAddListener(surfaceManager->vertexUnselectedEvent, this,
		&ProjectionEditorWidget::onVertexUnselected);
}

void ProjectionEditorWidget::clearJoints(){
	while(joints.size()){
		delete joints.back();
		joints.pop_back();
	}
}
    
void ProjectionEditorWidget::set_joint_colour(ofVec3f theme_colour){
    this->theme_colour = theme_colour;
}
    
void ProjectionEditorWidget::createJoints(){
	if (surfaceManager == 0) {
		return;
	}

    /*
	Save drag and surface settigns
	*/
	vector<bool> drags(4);
	vector<bool> selects(4);

	for (int i = 0; i < joints.size(); ++i) {
		drags[i] = joints[i]->isDragged();
		selects[i] = joints[i]->isSelected();
	}

	// This clears the old joints before creating
	// new ones
	clearJoints();

	if(surfaceManager->getSelectedSurface() == 0){
		ofLog(OF_LOG_WARNING, "Trying to create joints while no surface selected.");
		return;
	}

	vector <ofVec3f> & vertices =
		surfaceManager->getSelectedSurface()->getVertices();
	
	for(int i = 0; i < vertices.size(); i++){
		joints.push_back(new CircleJoint());
		joints.back()->position = ofVec2f(vertices[i].x, vertices[i].y);
	}

	/*
	relaod saved drag and selected settings
	*/
	for (int i = 0; i < joints.size(); i++) {
		if (drags[i]) {
			joints[i]->startDrag();
		}
		if (selects[i]) {
			joints[i]->select();
		}
	}
	

}

void ProjectionEditorWidget::updateJoints(){
    
	if(surfaceManager->getSelectedSurface()){
		vector <ofVec3f> & vertices =
			surfaceManager->getSelectedSurface()->getVertices();
		for(int i = 0; i < vertices.size(); i++){
			joints[i]->position = ofVec2f(vertices[i].x,vertices[i].y);
		}
	}

}

void ProjectionEditorWidget::unselectAllJoints(){
	for(int i = 0; i < joints.size(); i++){
		joints[i]->unselect();
	}
}

void ProjectionEditorWidget::moveSelectedSurface(ofVec2f by){
	if(surfaceManager == 0){
		return;
	}
	if(surfaceManager->getSelectedSurface() == 0){
		return;
	}
	
	vector <ofVec3f> & vertices = surfaceManager->getSelectedSurface()->getVertices();

	/*	Tom
		This adjusts the "by" vec so
		that it can't move the surface outside
		the boundary
	*/
	by = boundary::bounded_move(vertices, by);
    surfaceManager->getSelectedSurface()->moveBy(by);
    updateJoints();

}

void ProjectionEditorWidget::stopDragJoints(){
	for(int i = 0; i < joints.size(); i++){
		joints[i]->stopDrag();
	}
}

void ProjectionEditorWidget::setSnapDistance(float newSnapDistance){
	fSnapDistance = newSnapDistance;
}

CircleJoint * ProjectionEditorWidget::hitTestJoints(ofVec2f pos){
	if(surfaceManager->getSelectedSurface() == 0){
		return 0;
	}
	for(int i = 0; i < joints.size(); i++){
		if(joints[i]->hitTest(pos)){
			return joints[i];
		}
	}
	return 0;
}

vector <CircleJoint *> * ProjectionEditorWidget::getJoints(){
	return &joints;
}

/*	Tom changed to pass through all current drags
	This passes along the selected
	and dragged states to joints when they are recreated.
	Because there can now be multiple in a true state.
*/
void ProjectionEditorWidget::onVertexChanged(int & i) {
	createJoints();
}

void ProjectionEditorWidget::onVerticesChanged(vector<ofVec3f> & vertices){
	createJoints();
}

void ProjectionEditorWidget::onSurfaceSelected(int & surfaceIndex){
	createJoints();
}

void ProjectionEditorWidget::onVertexSelected(int & vertexIndex){
	if(getJoints()->size() == 0){
		return;
	}
	
	unselectAllJoints();
	getJoints()->at(vertexIndex)->select();
}

void ProjectionEditorWidget::onVertexUnselected(int & vertexIndex){
	if(getJoints()->size() == 0){
		return;
	}
	
	unselectAllJoints();
}

void ProjectionEditorWidget::drawJoints(){
	for(int i = 0; i < joints.size(); i++){
        joints[i]->set_joint_colour(theme_colour);
		joints[i]->draw();
	}
}

} // namespace piMapper
} // namespace ofx
