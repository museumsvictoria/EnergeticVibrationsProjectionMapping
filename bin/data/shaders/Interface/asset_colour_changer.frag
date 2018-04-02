uniform vec3      iResolution;           // viewport resolution (in pixels)
uniform float     iTime;           // shader playback time (in seconds)
uniform float     iTimeDelta;            // render time (in seconds)
uniform int       iFrame;                // shader playback frame
uniform float     iChannelTime[4];       // channel playback time (in seconds)
uniform vec3      iChannelResolution[4]; // channel resolution (in pixels)
uniform vec4      iMouse;                // mouse pixel coords. xy: current (if MLB down), zw: click
uniform sampler2D iChannel0;          // input channel. XX = 2D/Cube
uniform sampler2D iChannel1;          // input channel. XX = 2D/Cube
uniform sampler2D iChannel2;          // input channel. XX = 2D/Cube
uniform vec4      iDate;                 // (year, month, day, time in seconds)
uniform float     iSampleRate;

uniform vec3  base_colour;

const float eps = 0.0000001;

vec3 rgb2hsv( in vec3 c)
{
    vec4 k = vec4(0.0, -1.0/3.0, 2.0/3.0, -1.0);
    vec4 p = mix(vec4(c.zy, k.wz), vec4(c.yz, k.xy), (c.z<c.y) ? 1.0 : 0.0);
    vec4 q = mix(vec4(p.xyw, c.x), vec4(c.x, p.yzx), (p.x<c.x) ? 1.0 : 0.0);
    float d = q.x - min(q.w, q.y);
    return vec3(abs(q.z + (q.w - q.y) / (6.0*d+eps)), d / (q.x+eps), q.x);
}

vec3 rgb2hsl( vec3 col )
{
    float minc = min( col.r, min(col.g, col.b) );
    float maxc = max( col.r, max(col.g, col.b) );
    vec3  mask = step(col.grr,col.rgb) * step(col.bbg,col.rgb);
    vec3 h = mask * (vec3(0.0,2.0,4.0) + (col.gbr-col.brg)/(maxc-minc + eps)) / 6.0;
    return vec3( fract( 1.0 + h.x + h.y + h.z ),              // H
                (maxc-minc)/(1.0-abs(minc+maxc-1.0) + eps),   // S
                (minc+maxc)*0.5 );                            // L
}

vec3 hsl2rgb( in vec3 c )
{
    vec3 rgb = clamp( abs(mod(c.x*6.0+vec3(0.0,4.0,2.0),6.0)-3.0)-1.0, 0.0, 1.0 );
    return c.z + c.y * (rgb-0.5)*(1.0-abs(2.0*c.z-1.0));
}

void main( void )
{
    // The screen coordinates.
    vec2 uv = gl_FragCoord.xy / iResolution.xy;
    vec4 tex = texture2D(iChannel0,uv);

    vec3 o_hsv = rgb2hsl(tex.rgb);
    vec3 t_hsv = rgb2hsl(base_colour);
    
    float s = 0.0;
    float diff = 0.0;
    if(o_hsv.g < t_hsv.g) {
        diff = o_hsv.g - t_hsv.g;
        s = o_hsv.g - diff;
    } else {
        diff = t_hsv.g - o_hsv.g;
        s = t_hsv.g + diff;
    }
    
    vec3 f_hsv = vec3(t_hsv.r, o_hsv.g * t_hsv.g, o_hsv.b);
    tex.rgb = hsl2rgb(f_hsv);
    
    gl_FragColor = tex;
}

