//
//  PiMapperHelper.cpp
//  EnergeticVibrations_ProjectionMapping
//
//  Created by Joshua Batty on 19/1/18.
//
//

#include "PiMapperHelper.h"


//----------------------------------------
PiMapperHelper::~PiMapperHelper(){
}

//----------------------------------------
void PiMapperHelper::setup(ofxPiMapper& mapper){
    this->mapper = &mapper;
    
    surfaceManager = mapper._application.getSurfaceManager();
    currently_selected_shader = "Shader1";
    current_src_idx = 0;
}

//----------------------------------------
void PiMapperHelper::set_theme_colour(ofVec3f theme_colour){
    Gui::instance()->getSurfaceHighlightWidget().set_surface_colour(theme_colour);

    Gui::instance()->getProjectionEditorWidget().set_joint_colour(theme_colour);    
}

//----------------------------------------
SurfaceManager* PiMapperHelper::get_surface_manager(){
    return surfaceManager;
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
    current_src_idx = layer;
    cout << "currently_selected_shader = " << currently_selected_shader << endl;
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
std::string first_numberstring(std::string const & str)
{
    std::size_t const n = str.find_first_of("0123456789");
    if (n != std::string::npos)
    {
        std::size_t const m = str.find_first_not_of("0123456789", n);
        return str.substr(n, m != std::string::npos ? m-n : m);
    }
    return std::string();
}

//----------------------------------------
int PiMapperHelper::get_selected_source(){
    if(!check_if_source_sxists()) return 0;
    
    // If no source layer is currently selected, then use the last
    // current source shader index
    if(get_source()->getName() == ""){
        return current_src_idx;
    }
    else {
        string name = get_source()->getName();
        string number = first_numberstring(name);
        // we subtract 1 from this cause our shaders are
        // indexed from 0 not 1
        current_src_idx = ofToInt(number) - 1;
        return current_src_idx;
    }
}
