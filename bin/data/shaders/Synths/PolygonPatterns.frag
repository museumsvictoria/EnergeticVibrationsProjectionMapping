float shape(vec2 p, float angle) {
    float d = 100.0;
    vec2 a = vec2(1.0, 0.0), b;
    vec2 rot = vec2(cos(angle), sin(angle));
    
    for (int i = 0; i < 6; ++i) {
        b = a;
        for (int j = 0; j < 8; ++j) {
            b = vec2(b.x*rot.x - b.y*rot.y, b.x*rot.y + b.y*rot.x);
            d = min(d, segment(p,  a, b));
        }
        a = vec2(a.x*rot.x - a.y*rot.y, a.x*rot.y + a.y*rot.x);
    }
    return d;
}


vec3 PolygonPatterns()
{    
    vec2 uv = gl_FragCoord.xy / resolution.xy;
    vec2 cc = (-resolution.xy + 2.0*gl_FragCoord.xy) / resolution.y;
        
    float col = shape(abs(cc*.5), cos(remap(param1,0.0,1.0,0.01,0.071)*(time+2000.))*TWO_PI);
    col *= 0.5 + remap(param3,0.0,1.0,1.5,4.5)*pow(uv.x*uv.y*(1.0-uv.x)*(1.0-uv.y), 0.3);
    col *= 1.0;
    
    vec4 col1 = vec4(vec3(pow(1.0-col, 1.945)),1.0);
    vec4 col2 = vec4(vec3(pow(col, 1.945)),1.0);

    return mix(col1,col2,param3).rgb * MixColour();
}
