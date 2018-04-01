#version 410

uniform vec3      iResolution;           // viewport resolution (in pixels)
uniform float     iTime;           // shader playback time (in seconds)
uniform float     iTimeDelta;            // render time (in seconds)
uniform int       iFrame;                // shader playback frame
uniform float     iChannelTime[4];       // channel playback time (in seconds)
uniform vec3      iChannelResolution[4]; // channel resolution (in pixels)
uniform vec4      iMouse;                // mouse pixel coords. xy: current (if MLB down), zw: click
uniform sampler2D iChannel0;          // input channel. XX = 2D/Cube
uniform sampler2D iChannel1;          // input channel. XX = 2D/Cube
uniform sampler2D iChannel2;          // input channel. XX = 2D/Cube
uniform vec4      iDate;                 // (year, month, day, time in seconds)
uniform float     iSampleRate;

// inputs
in vec2 vTexCoord;

// outputs
out vec4 outputColor;


void main( void )
{
    // The screen coordinates.
    vec2 uv = vTexCoord; // Screen coordinates. Range: [0, 1]
    
    uv.y *= -1.;
    uv.y += 1.0;
    
    vec4 shape_tex = texture(iChannel0,uv);
    
    vec4 tex1 = texture(iChannel1,uv);
    vec4 tex2 = texture(iChannel2,uv);
    
    if(shape_tex.rgb == vec3(0.0)){
        discard;
    } else {
        outputColor = tex1 + tex2;
    }
    
    //outputColor =  mix(tex1 , tex2 , 0.5);
}

