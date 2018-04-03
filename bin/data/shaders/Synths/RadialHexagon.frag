//------------CONTROLABLE PARAMETERS -----------//
//# CIRCLE_ITER = (0.0) #  <--- SLIDER_1
//# GRID_SIZE = (1.0) #    <--- SLIDER 2
//# TIME_SKIP = (0.0) #    <--- SLIDER_3

vec3 RadialHexagon()
{    
    vec4 O;
    vec2 uv = gl_FragCoord.xy;
    
    vec2 R = resolution.xy,
    U = uv = (uv-R/2.)/R.y * remap(param2,0.0,1.0,1.0,4.0) *  1.73/2.;          // centered coords
    
    U *= mat2(1,-1./1.73, 0,2./1.73);                     // conversion to
    vec3 g = vec3(U, 1.-U.x-U.y), g2,                     // hexagonal coordinates
    id = floor(g);                                   // cell id
    
    g = fract(g); g.z = 1.-g.x-g.y;                       // triangle coords
    g2 = abs(2.*g-1.);                                    // distance to borders
    
    U = id.xy * mat2(1,.5, 0.,1.73/2.);
    float l00 = length(U-uv),                    // screenspace distance to nodes
    l10 = length(U+vec2(1.,0.)-uv),
    l01 = length(U+vec2(.5,1.73/2.)-uv),
    l11 = length(U+vec2(1.5,1.73/2.)-uv),
    l = min(min(l00, l10), min( l01, l11)); // closest node: l=dist, C=coord
    vec2 C = U + ( l==l00 ? vec2(0) : l==l10 ? vec2(1.,0.) : l==l01 ? vec2(.5,1.73/2.) : vec2(1.5,1.73/2.) );
    U = uv-C;
    float  s = 2.*mod(ceil(C.x+C.y),2.)-1.,
    r = length(U)/(1.73/2.)*3.,
    a = atan(U.y,U.x) - 3.*time + remap(param3,0.0,1.0,0.0,40.0);
    //  spiral                   // fade with radius   // rainbow color scheme
    float iter = remap(param1,0.0,1.0,0.0,10.0);
    O = pow(.5+.5*s*sin(iter*log(r)+a),1.) * exp(-.03*r*r) * sin(r+vec4(1,1.,1.,0));
    
    return O.rgb * MixColour();
}
