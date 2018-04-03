#include "ProjectionMappingMode.h"
#include "boundary.hpp"

namespace ofx {
namespace piMapper {

ProjectionMappingMode::ProjectionMappingMode(){
	_surfaceScaleBeforeTransform = 0.10f;
	_bDrawLayerPanel = false;
}

ProjectionMappingMode * ProjectionMappingMode::_instance = 0;

ProjectionMappingMode * ProjectionMappingMode::instance(){
	if(_instance == 0){
		_instance = new ofx::piMapper::ProjectionMappingMode();
	}
	return _instance;
}

void ProjectionMappingMode::setup(Application *app){
	Gui::instance()->getSurfaceHighlightWidget().setSurfaceManager(app->getSurfaceManager());
	Gui::instance()->getLayerPanelWidget().setSurfaceManager(app->getSurfaceManager());
	Gui::instance()->getProjectionEditorWidget().setSurfaceManager(app->getSurfaceManager());
}

void ProjectionMappingMode::update(Application * app){
	Gui::instance()->getProjectionEditorWidget().update();
	//Gui::instance()->getScaleWidget().update();
}

void ProjectionMappingMode::draw(Application * app){
	ofPushStyle();
	ofSetColor(255, 255, 255, 255);
	app->getSurfaceManager()->draw();
	ofPopStyle();
	
	Gui::instance()->getProjectionEditorWidget().draw();
	
    // JOSH, disabling drawing scale widget, seems to get in
    // the way.
    
    /*
	// Draw scale widget. The size of the widget is being set on surface select.
	BaseSurface * selectedSurface = app->getSurfaceManager()->getSelectedSurface();
	if(selectedSurface != 0){
		Gui::instance()->getScaleWidget().draw();
	}
	*/
    
	if(_bDrawLayerPanel){
		Gui::instance()->getLayerPanelWidget().draw();
	}
	
	Gui::instance()->getSurfaceHighlightWidget().draw();
}

void ProjectionMappingMode::onKeyPressed(Application * app, ofKeyEventArgs & args){
	switch(args.key){
		 
	 case 't':
		 app->createSurface(SurfaceType::TRIANGLE_SURFACE);
		 break;

	 case 'q':
		 app->createSurface(SurfaceType::QUAD_SURFACE);
		 break;
		 
	 case 'g':
		 app->createSurface(SurfaceType::GRID_WARP_SURFACE);
		 break;
		
	 case 'h':
		 app->createSurface(SurfaceType::HEXAGON_SURFACE);
		 break;

	 case OF_KEY_BACKSPACE:
		 app->eraseSurface(app->getSurfaceManager()->getSelectedSurfaceIndex());
		 break;
	 
	 case 'p':
		 app->togglePerspective();
		 break;
	 
	 case '}':
		 app->addGridRow();
		 break;
	
	 case '{':
		 app->removeGridRow();
		 break;
	 
	 case ']':
		 app->addGridColumn();
		 break;
		 
	 case '[':
		 app->removeGridColumn();
		 break;
		 
	 case '.':
		 app->selectNextSurface();
		 break;
		 
	 case ',':
		 app->selectPrevSurface();
		 break;
		 
	 case '>':
		 app->selectNextVertex();
		 break;
	 
	 case '<':
		 app->selectPrevVertex();
		 break;
	 
	 case OF_KEY_UP:
		 if(app->isShiftKeyDown()){
			app->moveSelection(ofVec2f(0.0f, -10.0f));
		 }else{
			app->moveSelection(ofVec2f(0.0f, -1.0f));
		 }
		 break;
		 
	 case OF_KEY_DOWN:
		 if(app->isShiftKeyDown()){
			app->moveSelection(ofVec2f(0.0f, 10.0f));
		 }else{
			app->moveSelection(ofVec2f(0.0f, 1.0f));
		 }
		 break;
		 
	 case OF_KEY_LEFT:
		 if(app->isShiftKeyDown()){
			app->moveSelection(ofVec2f(-10.0f, 0.0f));
		 }else{
			app->moveSelection(ofVec2f(-1.0f, 0.0f));
		 }
		 break;
	 
	 case OF_KEY_RIGHT:
		 if(app->isShiftKeyDown()){
			app->moveSelection(ofVec2f(10.0f, 0.0f));
		 }else{
			app->moveSelection(ofVec2f(1.0f, 0.0f));
		 }
		 break;
		 
	 case ' ':
		 app->togglePause();
		 break;
		 
	 case OF_KEY_TAB:
		 app->setNextSource();
		 break;
	
	 case 'd':
		 app->duplicateSurface();
		 break;
		 
	 case '0': // Move selected surface up the layer stack
		 app->moveLayerUp();
		 break;
		
	 case '9': // Move selected surface down the layer stack
		 app->moveLayerDown();
		 break;
		 
	 case '+': // Scale surface up
		 app->scaleUp();
		 break;

	 case '-': // Scale surface down
		 app->scaleDown();
		 break;

	 case 'l':
		 _bDrawLayerPanel = !_bDrawLayerPanel;
		 break;

	/*
	 case 'n': // Set next preset
		 app->getSurfaceManager()->setNextPreset();
		 break;
	*/
		 
	 default:
		 break;
	}
}

// JOSH additions
void ProjectionMappingMode::onTouchDown(Application * app, map<int, ofTouchEventArgs> & touchMap){
    Gui::instance()->touchDown(touchMap);

    for (auto &t : touchMap) {
        auto &touch = t.second;

		// Only check down touches
		if (touch.type != ofTouchEventArgs::down) {
			continue;
		}
        CircleJoint * hitJoint = 0;
        int hitJointIndex = -1;
        BaseSurface * hitSurface = 0;
        
        hitJoint = Gui::instance()->getProjectionEditorWidget().hitTestJoints(ofVec2f(touch.x, touch.y));
        
        if(hitJoint){
            for(int i = Gui::instance()->getProjectionEditorWidget().getJoints()->size() - 1; i >= 0 ; --i){
                if((*Gui::instance()->getProjectionEditorWidget().getJoints())[i] == hitJoint){
                    hitJointIndex = i;
                    // Tom added multitouch
					// link hitjoint to current touch
                    active_joints.touches[i] =  touch.id;
                    break;
                }
            }
        }else{
			if (app->getSurfaceManager()->getSelectedSurface() == 0 || (active_hits.touches.size() <= 0 && active_joints.touches.size() <= 0) ) {
				for (int i = app->getSurfaceManager()->size() - 1; i >= 0; --i) {
					if (app->getSurfaceManager()->getSurface(i)->hitTest(ofVec2f(touch.x, touch.y))) {

						hitSurface = app->getSurfaceManager()->getSurface(i);
						// Tom added multitouch
						// add touch id to set of "currently touching this surface"
						active_hits.touches.insert(touch.id);
						break;
					}
				}
			} else if (app->getSurfaceManager()->getSelectedSurface()->hitTest(ofVec2f(touch.x, touch.y))) {
				hitSurface = app->getSurfaceManager()->getSelectedSurface();
				active_hits.touches.insert(touch.id);
			}
        }
        
		int size = active_joints.touches.size();
        if(Gui::instance()->getScaleWidget().inside(touch.x, touch.y)){
            //
        }else if(hitJoint){
            hitJoint->select();
            hitJoint->startDrag();
            Gui::instance()->notifyJointPressed(touch, hitJointIndex);
        }else if(hitSurface){
            // TODO: redesign this so we can use a kind of
            //       display stack.
            // Tom changed to link last position to individual touches
            last_touch_positions[touch.id] = ofVec2f(touch.x, touch.y);
            _bSurfaceDrag = true; // TODO: Should be something like `hitSurface->startDrag()`
            Gui::instance()->notifySurfacePressed(touch, hitSurface);
        }else{
			// Tom changed. Only deselect if there are no active touches or joints
			if (active_hits.touches.size() <= 0 && active_joints.touches.size() <= 0 && boundary::inside_mapping( ofVec2f(touch.x, touch.y) ) ) {
				Gui::instance()->notifyBackgroundPressed(touch);
			}
        }
    }
}

    
void ProjectionMappingMode::onTouchUp(Application * app, map<int, ofTouchEventArgs> & touchMap){
    Gui::instance()->touchUp(touchMap);
	// Tom added for multitouch
    
	// Get the id of the touch with type up
	// or return
	int touch_id;
    int count = 0;
    for(auto const & t : touchMap){
        if(t.second.type == ofTouchEventArgs::up){
            touch_id = t.second.id;
            break;
        }
        count++;
    }
    if(count == touchMap.size()){
        //No up touch
        return;
    }
    
	// Check if any touches are still on the surface
	// if not set drag to false
    if(touchMap.size() > 0){
        _bSurfaceDrag = drag_manager::stop_surface_drag(touch_id, active_hits); // TODO: handle this locally
    }

	/*	Get the joint that matches this touch
		if there  it exsists then
		stop the drag on this joint
		unlink the touch and joint
	*/

	int joint_index = drag_manager::current_joint_index(touch_id, active_joints);
	
    if(joint_index != -1){
        auto joints = *(Gui::instance()->getProjectionEditorWidget().getJoints());
		if (joints.size() > 0) {
			joints[joint_index]->stopDrag();
			joints[joint_index]->unselect();
		}

		active_joints.touches.erase(joint_index);
    }
    // End Tom
	/*	Dont need this anymore because
		drags are stopped per joint-touch 
    Gui::instance()->getProjectionEditorWidget().stopDragJoints();
	*/

}
    
void ProjectionMappingMode::onTouchMoved(Application * app, map<int, ofTouchEventArgs> & touchMap){
    
    // I need to make sure the i look up the vertices of the ucrrently selectd object and make sure it doesn't go out of bounds
    //vector <ofVec3f> & vertices = app->getSurfaceManager()->getSelectedSurface()->getVertices();
	
	/*
	Tom added
	This block checks that we are only using
	active hits or joints.
	It seperates them out into lists for use later
	*/
	vector<ofTouchEventArgs> active_hit_move_touch;
	map<int, ofTouchEventArgs> active_joint_move_touch;
	auto ah_end = active_hits.touches.end();
	for (auto const & t : touchMap) {
		if (t.second.type == ofTouchEventArgs::move){
			if (active_hits.touches.find(t.first) != ah_end) {
				active_hit_move_touch.push_back(t.second);
			}
			int joint_index = drag_manager::current_joint_index(t.first, active_joints);
			if (joint_index != -1) {
				active_joint_move_touch[joint_index] = (t.second);
			}

		}
	}
	if (active_hit_move_touch.size() <= 0 && active_joint_move_touch.size() <= 0) {
		//No active move touch
		return;
	}

    
    Gui::instance()->touchMoved(touchMap);
	// Tom changed to send active joints to editor
    Gui::instance()->getProjectionEditorWidget().touchMoved(active_joint_move_touch);

    //JOSH clamp the joints so they stay within the mapping panel rect
    ofRectangle mapping_panel_rect = ofRectangle(434,95,998,899);
    for (auto &touch : active_hit_move_touch) {
        

        
        
        // TODO: Handle app->getGui()->clickPosition and app->getGui()->bDrag locally.
        if(_bSurfaceDrag && active_hits.touches.find(touch.id) != ah_end){
			touch.x = ofClamp(touch.x, mapping_panel_rect.x, mapping_panel_rect.x + mapping_panel_rect.width);
			touch.y = ofClamp(touch.y, mapping_panel_rect.y, mapping_panel_rect.y + mapping_panel_rect.height);

            ofVec2f touchPosition = ofVec2f(touch.x, touch.y);
            // Tom changed to use last position of this touch
			// defaults to current touch position
            auto last_touch = last_touch_positions.find(touch.id);
            auto last_touch_pos = touchPosition;
            if(last_touch != last_touch_positions.end()){
                last_touch_pos = last_touch->second;
            }
            
            ofVec2f distance = touchPosition - last_touch_pos;
            Gui::instance()->getProjectionEditorWidget().moveSelectedSurface(distance);
            
			//Tom changed to update the last touch position for this touch
            last_touch_positions[touch.id] = touchPosition;
        }
    }
}
    
void ProjectionMappingMode::onMousePressed(Application * app, ofMouseEventArgs & args){
	Gui::instance()->onMousePressed(args);
	
	CircleJoint * hitJoint = 0;
	int hitJointIndex = -1;
	BaseSurface * hitSurface = 0;

	hitJoint = Gui::instance()->getProjectionEditorWidget().hitTestJoints(ofVec2f(args.x, args.y));
		
	if(hitJoint){
		for(int i = Gui::instance()->getProjectionEditorWidget().getJoints()->size() - 1; i >= 0 ; --i){
			if((*Gui::instance()->getProjectionEditorWidget().getJoints())[i] == hitJoint){
				hitJointIndex = i;
				break;
			}
		}
	}else{
		for(int i = app->getSurfaceManager()->size() - 1; i >= 0; --i){
			if(app->getSurfaceManager()->getSurface(i)->hitTest(ofVec2f(args.x, args.y))){
				hitSurface = app->getSurfaceManager()->getSurface(i);
				break;
			}
		}
	}
		
	if(Gui::instance()->getScaleWidget().inside(args.x, args.y)){
		//
	}else if(hitJoint){
		hitJoint->select();
		hitJoint->startDrag();
		Gui::instance()->notifyJointPressed(args, hitJointIndex);
	}else if(hitSurface){
		_clickPosition = ofVec2f(args.x, args.y); // TODO: redesign this so we can use a kind of
												  //       display stack.
		_bSurfaceDrag = true; // TODO: Should be something like `hitSurface->startDrag()`
		Gui::instance()->notifySurfacePressed(args, hitSurface);
	}else{
		Gui::instance()->notifyBackgroundPressed(args);
	}
}

void ProjectionMappingMode::onMouseReleased(Application * app, ofMouseEventArgs & args){
	Gui::instance()->onMouseReleased(args);
	_bSurfaceDrag = false; // TODO: handle this locally
	Gui::instance()->getProjectionEditorWidget().stopDragJoints();
}

void ProjectionMappingMode::onMouseDragged(Application * app, ofMouseEventArgs & args){
    
    // I need to make sure the i look up the vertices of the ucrrently selectd object and make sure it doesn't go out of bounds
    //vector <ofVec3f> & vertices = app->getSurfaceManager()->getSelectedSurface()->getVertices();
    
    //JOSH clamp the joints so they stay within the mapping panel rect
    ofRectangle mapping_panel_rect = ofRectangle(434,95,998,899);
    args.x = ofClamp(args.x,mapping_panel_rect.x,mapping_panel_rect.x + mapping_panel_rect.width);
    args.y = ofClamp(args.y,mapping_panel_rect.y,mapping_panel_rect.y+mapping_panel_rect.height);
    
	Gui::instance()->onMouseDragged(args);
	Gui::instance()->getProjectionEditorWidget().mouseDragged(args);
	
	// TODO: Handle app->getGui()->clickPosition and app->getGui()->bDrag locally.
	if(_bSurfaceDrag){
		ofVec2f mousePosition = ofVec2f(args.x, args.y);
		ofVec2f distance = mousePosition - _clickPosition;
		Gui::instance()->getProjectionEditorWidget().moveSelectedSurface(distance);
		_clickPosition = mousePosition;
	}
}

void ProjectionMappingMode::onJointPressed(Application * app, GuiJointEvent & e){
	app->getCmdManager()->exec(new SelVertexCmd(app->getSurfaceManager(), e.jointIndex));
	app->getCmdManager()->exec(new MvSurfaceVertCmd(
		e.jointIndex,
		app->getSurfaceManager()->getSelectedSurface()));
}

void ProjectionMappingMode::onSurfacePressed(Application * app, GuiSurfaceEvent & e){
	if(app->getSurfaceManager()->getSelectedSurface() != e.surface){
		app->getCmdManager()->exec(new SelSurfaceCmd(app->getSurfaceManager(), e.surface ));
	}
	
	app->getCmdManager()->exec(new StartDragSurfaceCmd(e.surface));
}

void ProjectionMappingMode::onBackgroundPressed(Application * app, GuiBackgroundEvent & e){
	if(app->getSurfaceManager()->getSelectedSurface() != 0){
		app->getCmdManager()->exec(new DeselectSurfaceCmd(app->getSurfaceManager()));
	}
}

void ProjectionMappingMode::onGuiEvent(Application * app, GuiEvent & e){
	
    /*
	// Scale widget now. More widgets later.
	if(e.widget == &Gui::instance()->getScaleWidget()){
		if(e.args.type == e.args.Pressed){
			if(app->getSurfaceManager()->getSelectedSurface() == 0){
				return;
			}
			
			_surfaceScaleBeforeTransform =
				app->getSurfaceManager()->getSelectedSurface()->getScale();
		}else if(e.args.type == e.args.Released){
			if(app->getSurfaceManager()->getSelectedSurface() == 0){
				return;
			}
			
			if(_surfaceScaleBeforeTransform !=
				app->getSurfaceManager()->getSelectedSurface()->getScale()){
				
				app->getCmdManager()->exec(new ScaleSurfaceFromToCmd(
					app->getSurfaceManager()->getSelectedSurface(),
					_surfaceScaleBeforeTransform,
					app->getSurfaceManager()->getSelectedSurface()->getScale()));
			}
		}else if(e.args.type == e.args.Dragged){
			app->getSurfaceManager()->getSelectedSurface()->scaleTo(e.widget->getScale());
		}
	}
    */
}

} // namespace piMapper
} // namespace ofx
