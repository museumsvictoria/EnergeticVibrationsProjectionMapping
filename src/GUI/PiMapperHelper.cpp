//
//  PiMapperHelper.cpp
//  EnergeticVibrations_ProjectionMapping
//
//  Created by Joshua Batty on 19/1/18.
//
//

#include "PiMapperHelper.h"



//----------------------------------------
void PiMapperHelper::setup(ofxPiMapper& mapper){
    this->mapper = &mapper;
    
    surfaceManager = mapper._application.getSurfaceManager();
    currently_selected_shader = "Shader1";
}

//----------------------------------------
bool PiMapperHelper::check_if_source_sxists(){
    // Don't enable if there is no surface selected
    if(surfaceManager->getSelectedSurface() == 0){
        ofLogNotice("SourcesEditorWidget") << "No surface selected. Not enabling and not showing source list.";
        return false;
    } else {
        return true;
    }
}
//----------------------------------------
BaseSource* PiMapperHelper::get_source(){
    return mapper->_application.getSurfaceManager()->getSelectedSurface()->getSource();
}

//----------------------------------------
void PiMapperHelper::add_triangle_surface(){
    mapper->_application.createSurface(SurfaceType::TRIANGLE_SURFACE);
    SourcesEditorWidget* sourceEditorWidget = &Gui::instance()->getSourcesEditorWidget();
    sourceEditorWidget->setFboSource(currently_selected_shader);
}
//----------------------------------------
void PiMapperHelper::add_quad_surface(){
    mapper->_application.createSurface(SurfaceType::QUAD_SURFACE);
    SourcesEditorWidget* sourceEditorWidget = &Gui::instance()->getSourcesEditorWidget();
    sourceEditorWidget->setFboSource(currently_selected_shader);
}

//----------------------------------------
void PiMapperHelper::update_layer_source(int layer){
    currently_selected_shader = "Shader" + ofToString(layer + 1);

    if(!check_if_source_sxists()) return;
    SourcesEditorWidget* sourceEditorWidget = &Gui::instance()->getSourcesEditorWidget();
    sourceEditorWidget->setFboSource(currently_selected_shader);
}

//----------------------------------------
void PiMapperHelper::remove_surface(){
    int surface_to_delete = surfaceManager->getSelectedSurfaceIndex();
    mapper->_application.eraseSurface(surface_to_delete);
}
//----------------------------------------
void PiMapperHelper::duplicate_surface(){
    mapper->_application.duplicateSurface();
}

//----------------------------------------
int PiMapperHelper::get_selected_source(){
    if(!check_if_source_sxists()) return 0;
    //ascii code numbers start from 48
    // we subtract 1 from this cause our shaders are
    // indexed from 0 not 1
    return (int)(get_source()->getName().back()) - 48 - 1;
}
