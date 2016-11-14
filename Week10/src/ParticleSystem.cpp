//
//  ParticleSystem.cpp
//  ParticleHW
//
//  Created by Aaron Lee on 11/12/16.
//
//

#include "ParticleSystem.hpp"

//-------------------------------
ParticleSystem::ParticleSystem(ofVec2f position, ofVec2f force, float red, float green, float blue) {
    mPosition = position ;
    mEmitRate = 10 ;
    mIsAddingParticles = true ;
    mForce = force ;
    mRed = red ;
    mGreen = green ;
    mBlue = blue ;
}

//-------------------------------
void ParticleSystem::update() {
    if(mIsAddingParticles) {
        //pushing particles into the array
        particle particle(mPosition, mRed, mGreen, mBlue) ;
        mParticleList.push_back(particle) ;
    }
    
    for(int i = 0 ; i < mParticleList.size(); i++) {
        //calculate the difference between center and particle position
        ofVec2f diff = ofVec2f(abs(mParticleList[i].mPosition.x - mPosition.x), abs(mParticleList[i].mPosition.y-mPosition.y)) ;
        
        mParticleList[i].resetForce() ;
        mParticleList[i].applyForce(mForce) ;
        mParticleList[i].update(ofMap(sin(diff.length()), 0, 200, 4, 1)) ;
        
        if(diff.length() >= ofRandom(200,400)) {
            //stop adding particle if there is any particle's diff higher than a certain length
            mIsAddingParticles = false ;
            
            if(mParticleList.size() > 0) {
                mParticleList.erase(mParticleList.begin() + i) ;
            }
        }
    }
}

//-------------------------------
void ParticleSystem::draw() {
    for(int i = 0 ; i < mParticleList.size() ; i++) {
        
        mParticleList[i].draw() ;
    }
    
}