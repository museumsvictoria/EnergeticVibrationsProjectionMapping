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
	// update surface if one of the joints is being dragged
	
	// Tom added

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
		if (joints[i]->isDragged()) {
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
				if(distance < fSnapDistance){
					joints[i]->position = *allVertices[j];
					ofVec2f clickDistance = joints[i]->position - ofVec2f(args.x, args.y);
					joints[i]->setClickDistance(clickDistance);
					break;
				}
			}
		}
	}
}
    
void ProjectionEditorWidget::touchMoved(map<int, ofTouchEventArgs> &active_joint_move_touch) {
	
	for (auto &joint_touch : active_joint_move_touch) {
		//removetomcout << "joint touch" << endl;

		// Tom changed to only pass positions to 
		// joints that are linked to active touches
		// Pass args to joint mouse events
		/*
		for(unsigned int i = 0; i < joints.size(); ++i){
		joints[i]->touchMoved(touch);
		}
		*/


		if (joint_touch.first < joints.size()) {
			if (joints[joint_touch.first]->isDragged()) {
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
					if (distance < fSnapDistance) {
						joints[i]->position = *allVertices[j];
						ofVec2f clickDistance = joints[i]->position - ofVec2f(joint_touch.second.x, joint_touch.second.y);
						joints[i]->setClickDistance(clickDistance);
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

void ProjectionEditorWidget::createJoints(){
	if (surfaceManager == 0) {
		return;
	}
	vector<bool> drags(4);
	vector<bool> selects(4);
	
	{
		auto joints = getJoints();
		for (int i = 0; i < joints->size(); ++i) {
			drags[i] = (*joints)[i]->isDragged();
			selects[i] = (*joints)[i]->isSelected();
		}
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

	/* I don't think this is needed anymore
    // JOSH, check that none of the joints will leave the mapping rect
    // otherwise cancel the move operation
    
    bool is_inside_rect = true;
    
    //JOSH clamp the joints so they stay within the mapping panel rect
    ofRectangle mapping_panel_rect = ofRectangle(422,13,1450,870);

    //cout << "mapping_panel_rect = " << mapping_panel_rect << endl;
    cout << "move by = " << by << endl;
    for(int i = 0; i < vertices.size(); i++){
		cout << vertices[i] << endl;
        if(mapping_panel_rect.inside(vertices[i].x + by.x, vertices[i].y + by.y) == false){
            cout << "outside of rect bitch!" << endl;
            is_inside_rect = false;
            break;
        }
    }
    cout << "inside rect? = " << is_inside_rect << endl;
	*/

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
	/* Could delete this now
	bool isDragged = getJoints()->at(i)->isDragged();
	createJoints();
	getJoints()->at(i)->select();
	if(isDragged){
		getJoints()->at(i)->startDrag();
	}else{
		getJoints()->at(i)->stopDrag();
	}
	*/
	/*
	vector<bool> drags(4);
	vector<bool> selects(4);

	{
		auto joints = getJoints();
		for (int i = 0; i < joints->size(); ++i) {
			drags[i] = (*joints)[i]->isDragged();
			selects[i] = (*joints)[i]->isSelected();
			cout << "id: " << i << " drag: " << (*joints)[i]->isDragged() << " ptr " << (*joints)[i] << endl;

		}
	}*/
	// This clears the old joints before creating
	// new ones
	createJoints();
	/*
	{
		auto joints = getJoints();
		for (int i = 0; i < joints->size(); i++) {
			if (drags[i]) {
				(*joints)[i]->startDrag();
				cout << "drag set on for: " << i << " ptr " << (*joints)[i] << endl;
			}
			if (selects[i]) {
				(*joints)[i]->select();
			}
		}
	}
	*/

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
		joints[i]->draw();
		
	}
}

} // namespace piMapper
} // namespace ofx
