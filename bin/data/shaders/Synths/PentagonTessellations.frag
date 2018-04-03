//------------CONTROLABLE PARAMETERS -----------//
//# SPEED = (0.5) #  <--- SLIDER_1
//# GLOW = (0.2) #   <--- SLIDER 2
//# SIZE = (0.0) #   <--- SLIDER_3

////////////////////////////////////////////////////////////////////////////////
//
// Created by Matthew Arcus, 2018
// Wythoff construction for dual snub quadrille tessellation
//
// Fold down to square fundamental region. Draw lines to "Wythoff point".
// Keep track of folding for consistent coloring.
//
// Now with extra colors:
// 'c' changes color scheme to one per tile type
// 'r' shows fundamental region
//
////////////////////////////////////////////////////////////////////////////////

vec3 getcolor1(ivec2 s) {
    return getcol1(s);
}

ivec2 nextcell(ivec2 s, int q) {
    q = imod(q,4);
    if (q == 0) s.x++;
    else if (q == 1) s.y--;
    else if (q == 2) s.x--;
    else if (q == 3) s.y++;
    return s;
}

vec3 PentagonTessellations()
{
    float scale = 3.3;
    float lwidth = 0.025;
    // Half the width of the AA line edge
    float awidth = 1.5*scale/resolution.y;
    vec2 q,p =(2.0 * gl_FragCoord.xy - resolution.xy) / resolution.y;
    // Just bouncing around
    q = mod(0.3*time*vec2(1,1.618),2.0);
    q = min(q,2.0-q);
    p *= scale;
    ivec2 s = ivec2(floor(p));
    p = mod(p,2.0)-1.0; // Fold down to ±1 square
    int parity = int((p.y < 0.0) != (p.x < 0.0)); // Reflection?
    int quad = 2*int(p.x < 0.0) + parity; // Quadrant
    p = abs(p);
    if (parity != 0) p.xy = p.yx;
    // Lines from triangle vertices to Wythoff point
    float d = 1e8;
    d = min(d,segment(p,vec2(0,0),q));
    d = min(d,segment(p,vec2(1,0),q));
    d = min(d,segment(p,vec2(1,1),q));
    d = min(d,segment(p,vec2(-q.y,q.x),vec2(q.y,-q.x)));
    d = min(d,segment(p,vec2(-q.y,q.x),vec2(q.y,2.0-q.x)));
    d = min(d,segment(p,vec2(2.0-q.y,q.x),vec2(q.y,2.0-q.x)));
    // Color - what side of the lines are we?
    float a = dot(p-q,perp(vec2(0,0)-q));
    float b = dot(p-q,perp(vec2(1,0)-q));
    float c = dot(p-q,perp(vec2(1,1)-q));
    bool unit = s == ivec2(0);
    if (b > 0.0) {
        if (c < 0.0) s = nextcell(s,quad);
    } else {
        if (a > 0.0) s = nextcell(s,quad+1);
    }
    vec3 col = getcolor1(s);
    col = mix(col,vec3(1),0.1);
    col *= 0.75;
    col = mix(vec3(0),col,smoothstep(lwidth-awidth,lwidth+awidth,d));
    
    return hue(sqrt(col), hue_offset);
}

