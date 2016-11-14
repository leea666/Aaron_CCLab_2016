//
//  particle.cpp
//  ParticleHW
//
//  Created by Aaron Lee on 11/12/16.
//
//

#include "particle.hpp"

//-------------------------------
particle::particle(ofVec2f pos, float red, float green, float blue) {
    mPosition = pos ;
    mVelocity = ofVec2f(ofRandom(-2.f, 2.f), ofRandom(-2.f,2.f)) ;
    mAcceleration = ofVec2f(0,0) ;
    mLifeSpan = 255.f ;
    mRed = red ;
    mGreen = green ;
    mBlue = blue ;
}


//-------------------------------
void particle::update(float multiplier) {
    mVelocity += mAcceleration ;
    mPosition += mVelocity * multiplier ;
    if (mLifeSpan > 0) {
        mLifeSpan -= 2.f ;
    }
}

//-------------------------------
void particle::draw() {
    
    if(mLifeSpan > 100) {
        ofSetColor(mLifeSpan) ;
    } else if(mLifeSpan <= 100) {
        ofSetColor(ofRandom(0,255)) ;
    }
    ofSetColor(mRed, mGreen, mBlue) ;
    ofDrawCircle(mPosition, 3.f*ofMap(mLifeSpan,0,255.f, 0, 1.f)) ;
}

//-------------------------------
void particle::applyForce(ofVec2f force) {
    //adding force to acceleration
    float angle = ofRandom(0, M_TWO_PI) ;
//    mAcceleration = mAcceleration + force * sin(angle) ;
    mAcceleration += force * cos(angle) ;
//    mAcceleration += force ;
//    mAcceleration = mAcceleration + sin(force.x)+ cos(force.y) ;
}

//-------------------------------
void particle::resetForce() {
    mAcceleration *= 0 ;
}
