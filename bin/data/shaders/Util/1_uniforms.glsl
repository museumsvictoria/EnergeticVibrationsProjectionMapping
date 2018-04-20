#version 120

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
