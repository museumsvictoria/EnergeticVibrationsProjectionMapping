//
//  PiMapperHelper.h
//  EnergeticVibrations_ProjectionMapping
//
//  Created by Joshua Batty on 19/1/18.
//
//

#pragma once 

#include "ofMain.h"
#include "ofxPiMapper.h"

//Importing this so we can access the Gui instance in ofxPiMapper
using namespace ofx::piMapper;

class PiMapperHelper{
public:
    void setup(ofxPiMapper& mapper);
    bool check_if_source_sxists();
    
    void update_layer_source(int layer);
    
    void remove_surface();
    void duplicate_surface();
    
    int get_selected_source();
    


private:
    BaseSource* get_source();
    ofxPiMapper* mapper;
    SurfaceManager * surfaceManager;
};
