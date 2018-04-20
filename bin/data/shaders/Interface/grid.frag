#version 120
uniform vec3  resolution;

const vec3 cWhite1 = vec3(.3,.3,.3);
const vec3 cWhite2 = vec3(.5,.5,.5);
const float grid_size = 39.48;

void main(void)
{
    float asp = resolution.y/resolution.x;
    vec2 uv = (gl_FragCoord.xy / resolution.xy);
    
    float offset = 27.0;
    
    vec2 uvR = floor(uv*resolution.xy);
    vec2 g = step(2.0,mod(vec2(uvR.x+offset,uvR.y),grid_size));
    vec3 bgcol = mix(vec3(cWhite1),mix(vec3(cWhite1),vec3(0.0),g.x),g.y);
    
    g = step(2.0,mod(vec2(uvR.x+offset,uvR.y),grid_size*2.0));
    vec3 bgcol2 = mix(vec3(cWhite2),mix(vec3(cWhite2),bgcol,g.x),g.y);
    gl_FragColor = vec4(bgcol2,1.0);
    
}
