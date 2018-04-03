//------------CONTROLABLE PARAMETERS -----------//
//# GLOW = (0.3) #   <--- SLIDER_1
//# THICKNESS = (0.0) #   <--- SLIDER 2
//# GRID_SIZE = (0.3) #    <--- SLIDER_3

float formula(in vec2 tx, in float time) {
    float len = length(tx.y) * sin(time);
    vec3 hex = coordToHex(tx, remap(param3,0.0,1.0,2.0,20.0));
    vec3 cell = hexToCell(hex, 1.0);
    float value = hexToFloat(cell,nsin(time + len));
    return value;
}

vec3 FlowerOfLife()
{
    float displace = 0.05;
    
    //remap(param2,0.0,1.0,0.2,0.6);
    vec2 tx = (gl_FragCoord.xy / resolution.xy) - 0.5;
    tx.x *= resolution.x / resolution.y;
    float time = time * 0.2;
    vec3 rgb = vec3(0.0, 0.0, 0.0);
    for (int i = 0; i < 3; i++) {
        float time2 = time + float(i) * displace;
        rgb[i] += pow(formula(tx, time2), remap(param2 - (param1*0.2),0.0,1.0,20.0,8.0));
    }
    vec3 final = vec3(rgb * remap(param1,0.0,1.0,1.0,12.0));
    return hue(final,hue_offset);
}
