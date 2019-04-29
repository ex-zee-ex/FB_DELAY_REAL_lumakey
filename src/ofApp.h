
#pragma once

#include "ofMain.h"


class ofApp : public ofBaseApp {
	
public:
	
	void setup();
	void update();
	void draw();
	void exit();
	
	void keyPressed(int key);
	void keyReleased(int key);
	
	void mouseMoved(int x, int y );
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased();
	
	
    
    ofShader shaderMix;
   
 
    ofFbo framebuffer0;
    ofFbo framebuffer1;
    
  
    
    ofVideoGrabber cam1;
    
  


};
