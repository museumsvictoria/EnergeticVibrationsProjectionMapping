vec3 PatternMesh2D()
{    
    vec2 u = -1.0 + 2.0 * gl_FragCoord.xy / resolution.xy;

    u *= resolution.xy;

    vec4 o = vec4(0.0);

    float speed = remap(param1,0.0,1.0,0.05,1.0);
    float iter = remap(param2,0.0,1.0,10.0,100.0);
    float grid_iter = remap(param3,0.0,1.0,3.0,12.0);


    u *= mat2(1,-1./1.73, 0,2./1.73) * grid_iter/ resolution.y;  // conversion to 
    vec3 g = vec3(u.x-time*speed,u.y,-time*speed-u.x-u.y);       // hexagonal coordinates

    g = abs(fract(g)-.5);
    o += max(max(g.x, max(g.y,g.z)), min(g.x, min(g.y,g.z))*2.) -o;
  //o += min(max(g.x, max(g.y,g.z)), min(g.x, min(g.y,g.z))*2.) -o;
  //o += max(g.x, max(g.y,g.z)) -o;
  //o += min(g.x, min(g.y,g.z)) -o;


    // --- lookup table ------------------
    
#define s(x) (.5+.5*sin(x))
  o = .5+.5*sin(iter*o);                               // arabic version
  //o.r = .5+.5*sin(1.*o.r * sin(time*.4)); 
  //o = .5+.5*sin(10.*o + vec4(0,2.1,-2.1,0));         // psychedelic version
  //o = .5+.5*sin(10.*o + vec4(0,2.1,-2.1,0) * s(time*.4));  
  //  o = mix(o,  s(10.*o + vec4(0,2.1,-2.1,0)), s(time*.4));

    return o.xyz;
}
