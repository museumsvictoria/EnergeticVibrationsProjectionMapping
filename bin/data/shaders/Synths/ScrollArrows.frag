//------------CONTROLABLE PARAMETERS -----------//
//# ANGLE = (1.0) #   <--- SLIDER_1
//# WIDTH = (1.0) #   <--- SLIDER 2
//# COPIES = (0.5) #  <--- SLIDER_3

vec3 ScrollArrows()
{
    // Incoming slider values
    float p1 = remap(param1,0.0,1.0,0.0,0.5);
    float p2 = remap(param2,0.0,1.0,0.1,1.0);
    float p3 = remap(param3,0.0,1.0,1.0,12.0);
    
    // Pixel Coords 0.0 => 1.0
    vec2 uv = gl_FragCoord.xy / resolution.xy;

    float num_stripes =  p3;
    float smooth_width = 0.04;
    float angle_stripes = p1;
    float stripe_width = p2;
    
    vec2 rotatedUv = uv;
    
    // rotate context
    rotatedUv -= vec2(0.5);
    if ( rotatedUv.x < 0.0 ) {
        rotatedUv *= rotate2d( PI * angle_stripes );
    } else {
        rotatedUv *= rotate2d( -(PI * angle_stripes) );
    }
    rotatedUv += vec2(0.5);
    
    vec2 stripeUv = rotatedUv;
    float gradient = 1.0 - fract( floor( ( rotatedUv.y ) * num_stripes ) / num_stripes + (time*0.8) );
    
    stripeUv.y = 1.0 - fract( stripeUv.y * num_stripes );
    float stripeWidth = stripe_width * gradient;
    
    float stripes = smoothstep( ( 1. - stripeWidth ) - smooth_width, ( 1. - stripeWidth ) + smooth_width, stripeUv.y);
    stripes -= 1.0 - smoothstep( 1.0, 1.0 - smooth_width * 2.0, stripeUv.y);
    
    
    float col = stripes * gradient * gradient;
    
    // Return the output mixed with colour
    return vec3( col ) * pow(MixColour(),vec3(2.0));
}
