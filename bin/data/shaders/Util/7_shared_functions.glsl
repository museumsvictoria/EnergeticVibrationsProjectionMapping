// segment function by FabriceNeyret2
float segment(vec2 p, vec2 a, vec2 b) {
    vec2 pa = p - a;
    vec2 ba = b - a;
    float h = clamp(dot(pa, ba) / dot(ba, ba), 0.0, 1.0);
    float d = length(pa - ba * h);
    return d;
}

vec2 perp(vec2 r) {
    return vec2(-r.y,r.x);
}

int imod(int n, int m) {
    int k = n - n/m*m;
    if (k < 0) return k+m;
    else return k;
}

vec3 getcol0(int i) {
    if (i == 0) return vec3(1,0,0);
    if (i == 1) return vec3(0,0,1);
    if (i == 2) return vec3(0,1,0);
    if (i == 3) return vec3(1,1,0);
    if (i == 4) return vec3(1,0,1);
    if (i == 5) return vec3(0,1,1);
    if (i == 6) return vec3(1,1,1);
    return vec3(1,1,1);
}

vec3 getcol1(ivec2 s) {
    // http://www.iquilezles.org/www/articles/palettes/palettes.htm
    float t = 0.1*time + 0.1*0.618*float(s.x+s.y);
    vec3 a = vec3(0.4);
    vec3 b = vec3(0.6);
    vec3 c = vec3(1,1,1);
    vec3 d = vec3(0,0.33,0.67);
    vec3 col = a + b*cos(TWO_PI*(c*t+d));
    return col;
}
