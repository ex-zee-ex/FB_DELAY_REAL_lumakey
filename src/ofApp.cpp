
#include "ofApp.h"


#include <iostream>


float ss=.5;
int dd=0;

float ff=.1;
float gg=.1;

float hh=1.0;

const int fbob=15;

//this buffers the framebuffers from the final screen draws
ofFbo framebufferDelay[fbob];



//--------------------------------------------------------------
void ofApp::setup() {
    ofSetFrameRate(30);
	ofSetVerticalSync(true);
	//ofBackground(0);
	//ofSetLogLevel(OF_LOG_VERBOSE);
	
    
  
    
    

    //load the shaders
    shaderMix.load("shadersGL2/shaderMix");

    
   
    
    //allocate and clear the framebuffers
    
    framebuffer0.allocate(ofGetWidth(), ofGetHeight());
    framebuffer1.allocate(ofGetWidth(), ofGetHeight());
    
    
   
    
    framebuffer1.begin();

    ofClear(0,0,0,255);
 
    framebuffer1.end();
    
    framebuffer0.begin();
    ofClear(0,0,0,255);
    framebuffer0.end();
    
    
    //allocate and clear the variable delay final draw buffers
    
    
    for(int i=0;i<fbob;i++){
        
        framebufferDelay[i].allocate(ofGetWidth(), ofGetHeight());
        framebufferDelay[i].begin();
        ofClear(0,0,0,255);
        framebufferDelay[i].end();
        
    
    }//endifor
    
    
    
    
    
   
    
    //camerabiz
    cam1.listDevices();
    cam1.setVerbose(true);
    cam1.setDeviceID(0);
    cam1.initGrabber(640, 480);
    
   
    
    
    
    
}


//--------------------------------------------------------------
void ofApp::update() {
    cam1.update();
 

}

//--------------------------------------------------------------
void ofApp::draw() {
    
    

   
 
    
    /***shaderbix**/
    
 
  
    
    
    //________------____--_---__---_-_---//
    
    framebuffer0.begin();
    
    shaderMix.begin();
   
    shaderMix.setUniform1f("mixxx", ss);
    
    shaderMix.setUniform1f("lumavalue", ff);
    
    shaderMix.setUniform1f("lumathreshold", gg);
    
    shaderMix.setUniform1f("delayscale",hh);

  
    //this gets bound to tex0 when u do this way
    framebuffer1.draw(0,0);
 
    //send the camera texture over
    shaderMix.setUniformTexture("cam1",cam1.getTexture(),1);
    
    
    shaderMix.setUniformTexture("framebufferDelay",framebufferDelay[abs(dd)%fbob],2);
  
    
    
    shaderMix.end();
    
    framebuffer0.end();
    
    //-------------_--_----____---_--_--_??//
    
    /*this part gets drawn to screen*/
   
    framebuffer0.draw(0, 0);
    
    
    
  
    
    
    
    /*this part getsdrawn to the feedback buffer*/
    
    framebuffer1.begin();
    framebuffer0.draw(0, 0);
    framebuffer1.end();

   
    
    
    //feed some stuffs into the delay buffer
    //so we will keep the last 15 frames which will be 1/2 second of delay in total
    //they will b stored in the buffer array with the most recent frame at position 0 and
    //the most unrecent one at position 14
    
    //feed the previous frame into position 0
    
    framebufferDelay[0].begin();
    framebuffer0.draw(0,0);
    framebufferDelay[0].end();
    
    
    for(int i=fbob-1;i>0;i--){
        framebufferDelay[i].begin();
        framebufferDelay[i-1].draw(0,0);
        framebufferDelay[i].end();
        
    }
   

    
    
    
    ofSetHexColor(0xFFFFFF);
    ofDrawBitmapString("to mix between camera and framebuffer press s and x"+ofToString(ss)+" to change delay amount press d and c "+ofToString(abs(dd)%fbob)+"framerate "+ofToString(ofGetFrameRate())+"lumavalue"+ofToString(ff)+"lumathresh "+ofToString(gg)+"rescale "+ofToString(hh)
                      ,
                       10, ofGetHeight()-5 );
    
   
}


 
 /****************************************************/



//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
    if(key=='1'){
        
        framebuffer1.begin();
        
        ofClear(0,0,0,255);
        
        framebuffer1.end();
        for(int i=0;i<fbob;i++){
            
            framebufferDelay[i].allocate(ofGetWidth(), ofGetHeight());
            framebufferDelay[i].begin();
            ofClear(0,0,0,255);
            framebufferDelay[i].end();
            
            
        }//endifor
        
    }
    //if(key=='q'){sw1==0;}
    
    if(key=='s'){ss+=0.01;}
    if(key=='x'){ss-=0.01;}
    
    if(key=='d'){dd+=1;}
    if(key=='c'){dd-=1;}
    
    if(key=='f'){ff+=0.01;}
    if(key=='v'){ff-=0.01;}
    if(key=='g'){gg+=0.01;}
    if(key=='b'){gg-=0.01;}
    
    if(key=='h'){hh+=0.001;}
    if(key=='n'){hh-=0.001;}
    

}

/************************/
//--------------------------------------------------------------
void ofApp::exit() {
	
	
	
}

//--------------------------------------------------------------



//--------------------------------------------------------------
void ofApp::keyReleased(int key) {
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
   
}


//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
   
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {
}

//--------------------------------------------------------------
void ofApp::mouseReleased() {
}
