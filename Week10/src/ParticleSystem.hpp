//
//  ParticleSystem.hpp
//  ParticleHW
//
//  Created by Aaron Lee on 11/12/16.
//
//

#pragma once
#include "ofMain.h"
#include "particle.hpp"

#ifndef ParticleSystem_hpp
#define ParticleSystem_hpp

#include <stdio.h>

class ParticleSystem {
public:
    ParticleSystem(ofVec2f position, ofVec2f force, float red, float green, float blue) ;
//    void update(ofVec2f force) ;
    void update() ;
    void draw() ;
    
    vector<particle> mParticleList ;
    
    ofVec2f mPosition ;
    int mEmitRate ;
    bool mIsAddingParticles ;
    ofVec2f mForce ;
    float mRed ;
    float mGreen ;
    float mBlue ;
    
};

#endif /* ParticleSystem_hpp */