

#pragma include "Util/1_uniforms.glsl"
#pragma include "Util/2_PI.glsl"
#pragma include "Util/3_remap.glsl"
#pragma include "Util/4_easings.glsl"
#pragma include "Util/5_hue_shift.frag"
#pragma include "Util/6_colourise.frag"
#pragma include "Util/7_shared_functions.glsl"
#pragma include "Synths/2DPatternMesh.frag"   // shader 1
#pragma include "Synths/ColourGradient.frag"  // shader 2
#pragma include "Synths/EscherLike.frag"      // shader 3
#pragma include "Synths/FlowerOfLife.frag"    // shader 4
#pragma include "Synths/TriLattice.frag"      // shader 5
#pragma include "Synths/RadialHexagon.frag"   // shader 6
#pragma include "Synths/OpArtTwister.frag"    // shader 7
#pragma include "Synths/HexagonGradient.frag" // shader 8
#pragma include "Synths/PolygonPatterns.frag" // shader 9
#pragma include "Synths/SnubQuadrille.frag"   // shader 10
#pragma include "Synths/PentagonTessellations.frag" // shader 11

void main(void)
{
//    vec3 final_out = vec3(0.0);
//    
//    if(scene_select == 0){
//        final_out = hue(HexagonGradient(),hue_offset);
//    }
//    else if(scene_select == 1){
//        final_out = hue(ColourGradient(),hue_offset);
//    }
//    else if(scene_select == 2){
//        final_out = EscherLike() * MixColour();
//    }
//    else if(scene_select == 3){
//        final_out = hue(FlowerOfLife(),hue_offset);
//    }
//    else if(scene_select == 4){
//        final_out = hue(TriLattice(),hue_offset);
//    }
//    else if(scene_select == 5){
//        final_out = RadialHexagon() * MixColour();
//    }
//    else if(scene_select == 6){
//        final_out = hue(OpArtTwister(),hue_offset);
//    }
//    else if(scene_select == 7){
//        final_out = PatternMesh2D() * MixColour();
//    }
//    else if(scene_select == 8){
//        final_out = PolygonPatterns() * MixColour();
//    }
//    else if (scene_select == 9){
//        final_out = hue(SnubQuadrille(), hue_offset);
//    }
//    else if (scene_select == 10){
//        final_out = hue(PentagonTessellations(), hue_offset);
//    }

//    gl_FragColor = vec4(final_out,1.0);
}
