vec3 colourise(float t) {
    vec3 p = abs(fract(t + vec3(1.0, 2.0 / 3.0, 1.0 / 3.0)) * 6.0 - 3.0);
    return (clamp(p - 1.0, 0.0, 1.0));
}

vec3 MixColour(){
    return mix(vec3(1.0),colourise(hue_offset),remap(hue_offset,0.0,TWO_PI,0.0,1.0));
}
