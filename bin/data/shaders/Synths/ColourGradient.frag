//------------CONTROLABLE PARAMETERS -----------//
//# COLOUR_ITER_X = (0.4) #    <--- SLIDER 1
//# COLOUR_ITER_Y = (0.4) #   <--- SLIDER_2
//# SPEED = (0.0) #            <--- SLIDER_3

vec3 ColourGradient()
{
    vec2 p = -1.0 + 2.0 * gl_FragCoord.xy / resolution.xy;
    p = abs(p);
    p = fract(p * (0.5+param3*(PI-0.55)));
    
    
    float speed = time * 0.5;
    float x = p.x;
    float y = p.y;
    float mov0 = x+y+cos(sin(speed)*2.0)*100.+sin(x/100.)*1000.;
    float mov1 = y / remap(param2,0.0,1.0,2.96,0.2) +  speed;
    float mov2 = x / remap(param1,0.0,1.0,2.96,0.2);
    float c1 = abs(sin(mov1+speed)/2.+mov2/2.-mov1-mov2+speed);
    float c2 = abs(sin(c1+sin(mov0/1000.+time)+sin(y/40.+speed)+sin((x+y)/100.)*3.));
    float c3 = abs(sin(c2+cos(mov1+mov2+c2)+cos(mov2)+sin(x/1000.)));
    vec4 final = vec4(c1,c2,c3,1);
    
    return hue(final.rgb,hue_offset);
}
