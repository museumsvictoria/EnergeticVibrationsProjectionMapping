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

//Hex
vec3 coordToHex(in vec2 coord, in float scale) {
    float q = (1.0 / 3.0 * sqrt(3.0) * coord.x - 1.0 / 3.0 * coord.y) * scale;
    float r = 2.0 / 3.0 * coord.y * scale;
    return vec3(q, r, -q - r);
}

vec3 hexToCell(in vec3 hex, in float m) {
    return fract(hex / m) * 2.0 - 1.0;
}

float absMax(in vec3 v) {
    return max(max(abs(v.x), abs(v.y)), abs(v.z));
}

float nsin(in float value) {
    return sin(value * TWO_PI) * 0.5 + 0.5;
}

float hexToFloat(in vec3 hex, in float amt) {
    return mix(absMax(hex), 1.0 - length(hex) / sqrt(3.0), amt);
}

//Random
float rand(vec2 uv)
{
    return fract(sin(dot(uv, vec2(12.9898, 78.233))) * 43758.5453);
}

mat2 rotate2d(float _angle){
    return mat2(cos(_angle),-sin(_angle),
                sin(_angle),cos(_angle));
}

float easeInExpo(float t) {
    return t == 0.0 ? t : pow(2.0, 10.0 * (t - 1.0));
}

