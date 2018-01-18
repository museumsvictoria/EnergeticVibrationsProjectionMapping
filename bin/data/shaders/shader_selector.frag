uniform vec3      resolution;
uniform float     time;
uniform float     iFrame;
uniform float     iChannelTime[4];
uniform vec4      iMouse;
uniform sampler2D iChannel0;

uniform int scene_select;
uniform float hue_offset;
uniform float param1;
uniform float param2;
uniform float param3;

#pragma include "Util/PI.glsl"
#pragma include "Util/easings.glsl"
#pragma include "Util/hue_shift.frag"
#pragma include "Util/colourise.frag"
#pragma include "Util/remap.glsl"
#pragma include "Synths/HexagonGradient.frag" // shader 1
#pragma include "Synths/ColourGradient.frag"  // shader 2
#pragma include "Synths/EscherLike.frag"      // shader 3
#pragma include "Synths/FlowerOfLife.frag"    // shader 4
#pragma include "Synths/TriLattice.frag"      // shader 5
#pragma include "Synths/RadialHexagon.frag" // shader 6
#pragma include "Synths/OpArtTwister.frag"    // shader 7
#pragma include "Synths/2DPatternMesh.frag"   // shader 8


void main(void)
{
    vec3 final_out = vec3(0.0);
    
    if(scene_select == 0){
        final_out = hue(HexagonGradient(),hue_offset);
    }
    else if(scene_select == 1){
        final_out = hue(ColourGradient(),hue_offset);
    }
    else if(scene_select == 2){
        final_out = EscherLike() * mix(vec3(1.0),colourise(hue_offset),remap(hue_offset,0.0,TWO_PI,0.0,1.0));
    }
    else if(scene_select == 3){
        final_out = hue(FlowerOfLife(),hue_offset);
    }
    else if(scene_select == 4){
        final_out = hue(TriLattice(),hue_offset);
    }
    else if(scene_select == 5){
        final_out = RadialHexagon() * mix(vec3(1.0),colourise(hue_offset),remap(hue_offset,0.0,TWO_PI,0.0,1.0));
    }
    else if(scene_select == 6){
        final_out = hue(OpArtTwister(),hue_offset);
    }
    else if(scene_select == 7){
        final_out = PatternMesh2D() * mix(vec3(1.0),colourise(hue_offset),remap(hue_offset,0.0,TWO_PI,0.0,1.0));
    }
    
    gl_FragColor = vec4(final_out,1.0);
}
