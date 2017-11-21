vec3 coordToHex(in vec2 coord, in float scale) {
    float q = (1.0 / 3.0 * sqrt(3.0) * coord.x - 1.0 / 3.0 * coord.y) * scale;
    float r = 2.0 / 3.0 * coord.y * scale;
    return vec3(q, r, -q - r);
}

vec3 hexToCell(in vec3 hex, in float m) {
    return fract(hex / m) * 2.0 - 1.0;
}

float absMax(in vec3 v) {
    return max(max(abs(v.x), abs(v.y)), abs(v.z));
}

float nsin(in float value) {
    return sin(value * TWO_PI) * 0.5 + 0.5;
}

float hexToFloat(in vec3 hex, in float amt) {
    return mix(absMax(hex), 1.0 - length(hex) / sqrt(3.0), amt);
}

float formula(in vec2 tx, in float time) {
    float len = length(tx.y) * sin(time);
    vec3 hex = coordToHex(tx, remap(param3,0.0,1.0,5.0,30.0));
    vec3 cell = hexToCell(hex, 1.0);
    float value = hexToFloat(cell,nsin(time + len));
    return value;
}

vec3 FlowerOfLife()
{
    const float displace = 0.05;
    
    vec2 tx = (gl_FragCoord.xy / resolution.xy) - 0.5;
    tx.x *= resolution.x / resolution.y;
    float time = time * remap(param2,0.0,1.0,0.2,0.6);
    vec3 rgb = vec3(0.0, 0.0, 0.0);
    for (int i = 0; i < 3; i++) {
        float time2 = time + float(i) * displace;
        rgb[i] += pow(formula(tx, time2), 6.0);
    }
    vec3 final = vec3(rgb * remap(param1,0.0,1.0,1.0,12.0));
    return final;
}
