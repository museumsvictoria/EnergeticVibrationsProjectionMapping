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
#pragma include "Util/remap.glsl"
#pragma include "Synths/2DPatternMesh.frag"   // shader 1
#pragma include "Synths/ColourGradient.frag"  // shader 2
#pragma include "Synths/EscherLike.frag"      // shader 3
#pragma include "Synths/FlowerOfLife.frag"    // shader 4
#pragma include "Synths/TriLattice.frag"      // shader 5
#pragma include "Synths/RadialHexagon.frag" // shader 6
#pragma include "Synths/OpArtTwister.frag"    // shader 7
#pragma include "Synths/HexagonGradient.frag" // shader 8


void main(void)
{
    vec3 final_out = vec3(0.0);
    
    if(scene_select == 0){
        final_out = PatternMesh2D();
    }
    else if(scene_select == 1){
        final_out = ColourGradient();
    }
    else if(scene_select == 2){
        final_out = EscherLike();
    }
    else if(scene_select == 3){
        final_out = FlowerOfLife();
    }
    else if(scene_select == 4){
        final_out = TriLattice();
    }
    else if(scene_select == 5){
        final_out = RadialHexagon();
    }
    else if(scene_select == 6){
        final_out = OpArtTwister();
    }
    else if(scene_select == 7){
        final_out = HexagonGradient();
    }
    
    gl_FragColor = vec4(hue(final_out,hue_offset),1.0);
}
