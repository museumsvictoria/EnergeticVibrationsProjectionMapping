//------------CONTROLABLE PARAMETERS -----------//
//# ITER_SIZE = (1.0) #   <--- SLIDER_1
//# GRID_ITER = (0.0) #   <--- SLIDER 2
//# ZOOM = (1.0) #        <--- SLIDER_3

vec3 OpArtTwister()
{
    //remap(param3,0.0,1.0,1.0,4.0)
    float t = time;
    
    vec2 uv0 = -1.0 + 2.0 * gl_FragCoord.xy / resolution.xy;

    uv0 *= (resolution.xy*remap(param3,0.0,1.0,0.0001,0.0005));
 
    vec2 m = vec2(0.0);
    m.x = 0.5+sin(time*0.03)*.5;
    m += .5+.5*vec2(cos(t),sin(.6*t)); m.y*=m.x;
    vec2 uv = uv0*remap(param2,0.0,1.0,2.0,4.0), iuv=floor(uv);
    float d = mod(iuv.x+iuv.y,2.), s = mod(iuv.y,2.);
    uv = fract (uv); if (d==1.) uv.x = 1.-uv.x; // checkered tile coordinates
    uv = uv + vec2(-uv.y,uv.x); // rotate 45deg
    
    
    float q = sign(s-.5)*sign(d-.5) * 1.5;
    float size0 = m.x+m.y*cos(.5*3.1415927*uv.y) *q;
    float l = abs(uv.x)-size0;
    float v = smoothstep(0.,.1,abs(l));
    float v0 = step(0.,l);
    
    float size = m.x+m.y*cos(.5*3.1415927*uv.x),
    ofs = (1.-size)*q; // corner distance
    l = (uv.y-1.)-ofs;
    float   v1 = step(0.,l),
    d0 =  mod(s+v1,2.),
    d1 =  mod(s+d+v1,2.); // corner area
    v0 = d1<1. ? v0 : 0.; // background
    v = (d1<1. ? v : 1.)*smoothstep(0.,.1,abs(l)); // contour
    float col = v0 *(cos(4.*31.4*uv0.x)*cos(4.*31.4*uv0.y))
    + (1.-v0)*( d1==1. ? cos(1.*31.4*( q>0. ? 2.-uv.y : uv.y )*m.x/(size*remap(param1,0.0,1.0,6.0,2.0)))
               : cos(1.*31.4*(uv.x*m.x/size0)) );
    
    vec3 final = vec3(col,col*v,col*v);
    
    return final * 2.0 * MixColour();
//    return hue(final*2.0,hue_offset);
}
