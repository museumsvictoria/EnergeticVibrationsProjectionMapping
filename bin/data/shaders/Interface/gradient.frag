uniform vec3  resolution;
uniform int verticle_or_horizontal; // 0 = horizontal, 1 = vertical
uniform float perc;


// Blinn-Wyvill Approximation to the Raised Inverted Cosine
float cosineApprox(float x){
    
    float x2 = x * x;
    float x4 = x2 * x2;
    float x6 = x4 * x4;
    
    float fa = 4.0 / 9.0;
    float fb = 17.0 / 9.0;
    float fc = 22.0 / 9.0;
    
    return fa * x6 - fb * x4 + fc * x2;
}


// Double-Cubic Seat
float doubleCubicSeat(float x, float a, float b){
	   
    float epsilon = 0.00001;
    float min_param_a = 0.0 + epsilon;
    float max_param_a = 1.0 - epsilon;
    float min_param_b = 0.0;
    float max_param_b = 1.0;
    
    a = min(max_param_a, max(min_param_a, a));
    b = min(max_param_b, max(min_param_b, b));
    
    float y = 0.0;
    if(x <= a){
        y = b - b * pow(1.0 - x / a, 3.0);
    } else {
        y = b + (1.0 - b) * pow((x - a) / (1.0 - a), 3.0);
    }
    
    return y;
}

// Double-Cubic Seat with Linear Blend
float doubleCubicSeatLinear(float x, float a, float b){
    
    float epsilon = 0.00001;
    float min_param_a = 0.0 + epsilon;
    float max_param_a = 1.0 - epsilon;
    float min_param_b = 0.0;
    float max_param_b = 1.0;
    
    a = min(max_param_a, max(min_param_a, a));
    b = min(max_param_b, max(min_param_b, b));
    
    b = 1.0 - b;
    
    float y = 0.0;
    if(x <= a){
        y = b * x + (1.0 - b) * a * (1.0 - pow(1.0 - x / a, 3.0 ));
    } else {
        y = b * x + (1.0 - b) * (a + (1.0 - a) * pow((x - a) / (1.0 - a), 3.0));
    }
    
    return y;
}


// Quadratic through a given point
float quadraticPoint(float x, float a, float b){
    
    float epsilon = 0.00001;
    float min_param_a = 0.0 + epsilon;
    float max_param_a = 1.0 - epsilon;
    float min_param_b = 0.0;
    float max_param_b = 1.0;
    
    a = min(max_param_a, max(min_param_a, a));
    b = min(max_param_b, max(min_param_b, b));
    
    float A = (1.0 - b) / (1.0 - a) - (b / a);
    float B = (A * (a * a) - b) / a;
    float y = A * (x * x) - B * (x);
    y = min(1.0, max(0.0, y));
    
    return y;
    
}

void main(void)
{
    vec2 uv = gl_FragCoord.xy / resolution.xy;
    
    //float y = cosineApprox(uv.x);
    //float y = doubleCubicSeat(uv.x, 0.407, 0.720);
    //float y = doubleCubicSeat(uv.x, 0.607, 0.247);
    //float y = doubleCubicSeatLinear(uv.x, 0.640, 0.827);
    //float y = doubleCubicSeatLinear(uv.x, 0.347, 0.887);
    //float y = doublePolynomialSigmoid(uv.x, 0.347, 0.887, 2.0);
    //float y = quadraticPoint(uv.x, 0.500, 0.307);
    
    float gradient = 0.0;
    
    if(verticle_or_horizontal == 0){
        uv.x = gl_FragCoord.x / (perc*resolution.x);
        uv.y = gl_FragCoord.y / resolution.y;
        gradient = quadraticPoint(1.0-uv.x, 0.233, 0.340);
    }
    else if(verticle_or_horizontal == 1){
        uv.y = gl_FragCoord.y / (perc*resolution.y);
        uv.x = gl_FragCoord.x / resolution.x;
        gradient = quadraticPoint(1.0-uv.y, 0.233, 0.340);
    }
    
    
    gl_FragColor = vec4(gradient,0.,0., 1.0);
}
