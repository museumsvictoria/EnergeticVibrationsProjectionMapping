#pragma include "Util/PI.glsl"
#pragma include "Util/easings.glsl"
#pragma include "Util/hue_shift.frag"
#pragma include "Util/remap.glsl"

uniform vec3      resolution;
uniform float     time;
uniform float     iFrame;
uniform float     iChannelTime[4];
uniform vec4      iMouse;
uniform sampler2D iChannel0;

uniform float hue_offset;

void main(void)
{
    vec2 uv = gl_FragCoord.xy / resolution.xy;
    vec2 q = uv - vec2(0.5,0.5);
    
    float pct =  bounceInOut(abs(fract(time*0.1)*2.0-01.) );
    
    vec3 color = vec3(uv,0.5+0.5*cos(uv.y*time* (backInOut(abs(sin(time*0.04)))*0.088)));
    
    //    float r = 0.12 + 0.3* cos(atan(q.y, q.y) * 2600.0 + (sin(iTime*0.375)*8000.0) * q.x + 0.1);
    float r = 0.175*sin(atan(q.y)*time) + .40 * q.y;
    
    vec3 color2 = color*vec3(r*8.0);
    
    vec3 tex = mix(color,color2,pct);
    
    gl_FragColor = vec4(hue(tex,hue_offset),1.0);
}
