#version 120


uniform sampler2DRect tex0;

uniform sampler2DRect cam1;

uniform sampler2DRect framebufferDelay;

uniform float mixxx;

uniform float lumavalue;

uniform float lumathreshold;

uniform float delayscale;

varying vec2 texCoordVarying;




void main()
{
    
   
	vec4 color = vec4(0.0, 0.0, 0.0, 0.0);
    
    vec2 cam1Scale=0.5*texCoordVarying;
    
    vec4 fb1_color = texture2DRect(tex0,texCoordVarying);
    
    vec4 fbdelay_color = texture2DRect(framebufferDelay,delayscale*texCoordVarying);
    
  

    
    vec4 cam1color=texture2DRect(cam1,cam1Scale);
    
    
    float bright=.33*cam1color.r+.5*cam1color.g+.16*cam1color.b;
    
    
  
    
    
    
   // color=mix(cam1color,fb1_color,mixxx);
    
    color=mix(cam1color,fbdelay_color,mixxx);
    
    if((bright<lumavalue+lumathreshold)&&((bright>lumavalue-lumathreshold))){
        color=fbdelay_color;
        
    }
    
    
    gl_FragColor = color;

   
}
