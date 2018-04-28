//------------CONTROLABLE PARAMETERS -----------//
//# OFFSET = (0.0) #      <--- SLIDER_1
//# POSITION = (0.5) #    <--- SLIDER 2
//# ZOOM = (0.0) #        <--- SLIDER_3

vec3 EscherLike()
{
    vec4 output_tex;
    
    vec2 U = (gl_FragCoord.xy / resolution.xy) - 0.5;
    
    U *= remap(param3,0.0,1.0,4.0,16.0);//resolution.y;
    output_tex-=output_tex;
    float iter = remap(param2,0.0,1.0,1.0,2.0);
    
    vec2 f = floor(U), u = iter*fract(U)-(iter*.5);  // ceil cause line on some OS
    float b = mod(f.x+f.y,2.), y;
    
    for(int i=0; i<4; i++)
        u *= mat2(0,-1,1,0.),
        y = 2.*fract(.12*time+U.y*.01)-1.,
        output_tex += smoothstep(.5,.45, length(u-vec2(param1,(1.0 + (iter * 0.5))*y)));
    
    if (b>0.) output_tex = 1.-output_tex; // try also without :-)
    
    return output_tex.rgb * pow(MixColour(),vec3(2.0));
}
