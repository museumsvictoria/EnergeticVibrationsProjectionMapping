vec3 HexagonGradient()
{
    float speed = remap(param1,0.0,1.0,0.25,1.5);
    float circle_iter = remap(param2,0.0,1.0,0.75,5.0);
    float iter = remap(param3,0.0,1.0,4.0,10.0);
    
    vec4 O = vec4(0.0);
    vec2 U = gl_FragCoord.xy;
    
    vec2 uv = U / resolution.xy;
    U *= mat2(1,-1./1.73, 0,2./1.73) *6.0/ resolution.y;  // conversion to
    vec3 g = vec3(U, 1.-U.x-U.y), g2;                     // hexagonal coordinates
    
    g = fract(g);                                         // diamond coords
    g2 = abs(circle_iter*g-(circle_iter*0.5));            // distance to borders
    
    
    float t = time * speed;
    float res = length(abs(uv.y*.5));
    O = sin(iter*length(res-g2)-2.* t) +O-O;
    O.r *= sin(iter*length(res-g2-1.0)-1.5*(t*2.0)) +O.r-O.r;
    O.b += (sin(iter*length(res-g2-1.0)-1.55*(t*2.0)) +O.b-O.b)*0.1;
    
    return O.rgb;
}
