//
//  particle.hpp
//  ParticleHW
//
//  Created by Aaron Lee on 11/12/16.
//
//
#pragma once

#include "ofMain.h"
#ifndef particle_hpp
#define particle_hpp

#include <stdio.h>

class particle {
    public:
    particle(ofVec2f pos, float red, float green, float blue) ;
    
    void resetForce() ;
    void applyForce(ofVec2f force) ;
    void update(float multiplier) ;
    void draw() ;
    
    ofVec2f mPosition, mVelocity, mAcceleration ;
    float mLifeSpan ;
    
    float mRed ;
    float mGreen ;
    float mBlue ;
};


#endif /* particle_hpp */
