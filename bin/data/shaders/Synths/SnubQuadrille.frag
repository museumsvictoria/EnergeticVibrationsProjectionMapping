////////////////////////////////////////////////////////////////////////////////
//
// Created by Matthew Arcus, 2018
// Wythoff construction for snub quadrille tessellation.
// This is what https://www.shadertoy.com/view/XlBBWG is dual of
//
// Fold down to square fundamental region. Draw lines to "Wythoff point".
//
// 'd' shows dual tessellation edges
// 'r' shows square fundamental region
//
////////////////////////////////////////////////////////////////////////////////


vec3 getcolor0(int i) {
    return 0.25+0.75*getcol0(i);
}

vec3 SnubQuadrille()
{    
    float scale = 2.3;
    float lwidth = 0.015;
    

    // Half the width of the AA line edge
    float awidth = 1.5*scale/resolution.y;
    vec2 q,p =(2.0 * gl_FragCoord.xy - resolution.xy) / resolution.y;

    p *= scale;
    float r = cos(0.1*time);
    float t = time;
    q = r*vec2(sin(t),cos(t));
    q *= min(1.0/abs(sin(t)),1.0/abs(cos(t)));
    q = 0.5*(q+1.0);
    
    ivec2 s = ivec2(floor(p));
    p = mod(p,2.0)-1.0; // Fold down to ±1 square
    int parity = int((p.y < 0.0) != (p.x < 0.0)); // Reflection?
    int quad = 2*int(p.x < 0.0) + parity; // Quadrant
    p = abs(p);
    if (parity != 0) p.xy = p.yx;
    vec3 col = vec3(1);
    if (true) {
        vec2 q0 = q.yx;
        vec2 q1 = vec2(2.0-q.x,q.y);
        vec2 q2 = vec2(q.x,-q.y);
        vec2 q3 = vec2(-q.x,q.y);
        vec2 q4 = vec2(-q.y,2.0-q.x);
        vec2 q5 = vec2(q.x,2.0-q.y);
        bool l1 = dot(p-q0,perp(q1-q0)) <= 0.0;
        bool l2 = dot(p-q0,perp(q2-q0)) <= 0.0;
        bool l3 = dot(p-q0,perp(q3-q0)) <= 0.0;
        bool l4 = dot(p-q0,perp(q4-q0)) <= 0.0;
        bool l5 = dot(p-q0,perp(q5-q0)) <= 0.0;
        int colindex = 0;
        //if (l2 && !l3) colindex = 0;
        if (l3 && !l4) colindex = imod(quad-1,4)/2+2;
        if (l4 && !l5) colindex = imod(quad+1,4)/2+2;
        if (l5 && !l1) colindex = 1;
        if (l1 && !l2) colindex = quad/2+2;
        col = getcolor0(colindex);
        vec2 p0 = 2.0*(p-0.5);
        float t = atan(p0.y,p0.x);
        float r = length(p0);
        r *= min(1.0/abs(sin(t)),1.0/abs(cos(t)));
        float d = 1e8;
        d = min(segment(p,q0,q1),segment(p,q0,q2));
        d = min(d,segment(p,q0,q3));
        d = min(d,segment(p,q0,q4));
        d = min(d,segment(p,q0,q5));
        d = min(d,segment(p,q1,q2));
        col = mix(vec3(0),col,smoothstep(lwidth-awidth,lwidth+awidth,d));
    }
    return sqrt(col);
}

