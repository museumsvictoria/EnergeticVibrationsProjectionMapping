#include "ProjectionMappingMode.h"

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
        
        CircleJoint * hitJoint = 0;
        int hitJointIndex = -1;
        BaseSurface * hitSurface = 0;
        
        hitJoint = Gui::instance()->getProjectionEditorWidget().hitTestJoints(ofVec2f(touch.x, touch.y));
        
        if(hitJoint){
            for(int i = Gui::instance()->getProjectionEditorWidget().getJoints()->size() - 1; i >= 0 ; --i){
                if((*Gui::instance()->getProjectionEditorWidget().getJoints())[i] == hitJoint){
                    hitJointIndex = i;
                    //Tom added multitouch
                    active_joints.touches.insert( std::pair<int, int>(touch.id, i) );
                    break;
                }
            }
        }else{
            for(int i = app->getSurfaceManager()->size() - 1; i >= 0; --i){
                if(app->getSurfaceManager()->getSurface(i)->hitTest(ofVec2f(touch.x, touch.y))){
                    hitSurface = app->getSurfaceManager()->getSurface(i);
                    //Tom added multitouch
                    active_hits.touches.insert(touch.id);
                    break;
                }
            }
        }
        
        if(Gui::instance()->getScaleWidget().inside(touch.x, touch.y)){
            //
        }else if(hitJoint){
            hitJoint->select();
            hitJoint->startDrag();
            Gui::instance()->notifyJointPressed(touch, hitJointIndex);
        }else if(hitSurface){
            _clickPosition = ofVec2f(touch.x, touch.y); // TODO: redesign this so we can use a kind of
            //       display stack.
            _bSurfaceDrag = true; // TODO: Should be something like `hitSurface->startDrag()`
            Gui::instance()->notifySurfacePressed(touch, hitSurface);
        }else{
            Gui::instance()->notifyBackgroundPressed(touch);
        }
    }
}
    //Tom added this for overload
    // TODO tidy up
    void ProjectionMappingMode::onTouchUp(Application * app, map<int, ofTouchEventArgs> & touchMap){
        onTouchUp(app, touchMap, 1);
    }
    
void ProjectionMappingMode::onTouchUp(Application * app, map<int, ofTouchEventArgs> & touchMap, int touch_id){
    Gui::instance()->touchUp(touchMap);

    // Tom added for multitouch
    if(touchMap.size() > 0){
        _bSurfaceDrag = drag_manager::stop_surface_drag(touch_id, active_hits); // TODO: handle this locally
    }
    if(drag_manager::stop_joints_drag(touch_id, active_joints)){
        auto joint = (*Gui::instance()->getProjectionEditorWidget().getJoints())[ active_joints.touches[touch_id] ];
        joint->stopDrag();
        active_joints.touches.erase( active_joints.touches.find(touch_id) );
    }
    // End Tom
#if 0
    Gui::instance()->getProjectionEditorWidget().stopDragJoints();
#endif
}
    
void ProjectionMappingMode::onTouchMoved(Application * app, map<int, ofTouchEventArgs> & touchMap){
    
    // I need to make sure the i look up the vertices of the ucrrently selectd object and make sure it doesn't go out of bounds
    //vector <ofVec3f> & vertices = app->getSurfaceManager()->getSelectedSurface()->getVertices();
    
    Gui::instance()->touchMoved(touchMap);
    Gui::instance()->getProjectionEditorWidget().touchMoved(touchMap);

    //JOSH clamp the joints so they stay within the mapping panel rect
    ofRectangle mapping_panel_rect = ofRectangle(422,13,1450,870);
    for (auto &t : touchMap) {
        auto &touch = t.second;
        
        touch.x = ofClamp(touch.x,mapping_panel_rect.x,mapping_panel_rect.x + mapping_panel_rect.width);
        touch.y = ofClamp(touch.y,mapping_panel_rect.y,mapping_panel_rect.y+mapping_panel_rect.height);
        
       // Gui::instance()->onMouseDragged(args);
        
        // TODO: Handle app->getGui()->clickPosition and app->getGui()->bDrag locally.
        if(_bSurfaceDrag){
            ofVec2f touchPosition = ofVec2f(touch.x, touch.y);
            ofVec2f distance = touchPosition - _clickPosition;
            Gui::instance()->getProjectionEditorWidget().moveSelectedSurface(distance);
            _clickPosition = touchPosition;
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
    ofRectangle mapping_panel_rect = ofRectangle(422,13,1450,870);
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
