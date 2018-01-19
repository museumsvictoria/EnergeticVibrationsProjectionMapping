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
    
}

//----------------------------------------
BaseSource* PiMapperHelper::get_source(){
    return mapper->_application.getSurfaceManager()->getSelectedSurface()->getSource();
}

//----------------------------------------
void PiMapperHelper::update_layer_source(int layer){
    // Don't enable if there is no surface selected
    if(surfaceManager->getSelectedSurface() == 0){
        ofLogNotice("SourcesEditorWidget") << "No surface selected. Not enabling and not showing source list.";
        return;
    }
    string path = "Shader1";// get_source->getName();
    cout << "source name = " << path << endl;
    SourcesEditorWidget* sourceEditorWidget = &Gui::instance()->getSourcesEditorWidget();
    sourceEditorWidget->setFboSource(path);
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
