//------------CONTROLABLE PARAMETERS -----------//
//# PARAM1 = (0.5) #   <--- SLIDER_1
//# PARAM2 = (0.2) #   <--- SLIDER 2
//# PARAM3 = (0.0) #   <--- SLIDER_3


vec3 Template()
{
    // Incoming slider values
    float p1 = remap(param1,0.0,1.0,0.0,1.0);
    float p2 = remap(param2,0.0,1.0,0.0,1.0);
    float p3 = remap(param3,0.0,1.0,0.0,1.0);
    
    // Pixel Coords 0.0 => 1.0
    vec2 uv = gl_FragCoord.xy / resolution.xy;
    
    // Pixel Coords -1.0 => 1.0
    //uv = -1.0 + 2.0 * gl_FragCoord.xy / resolution.xy;



    // Assign the final shaders output to the col variable
    vec3 col = vec3(uv.x,uv.y,p3);
    
    // Return the output mixed with colour
    return col * MixColour();
}
