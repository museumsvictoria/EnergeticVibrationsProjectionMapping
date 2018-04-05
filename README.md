# Energetic Vibrations Projection Mapping
This project was developed for the Energetic Vibrations Projection Mapping Installation as part of the Beyond Perception exhibition at Scienceworks. It is developed using openFrameworks, GLSL, and a modified version of ofxPiMapper. Multi touch support is also available for Windows touch screens.

![Figure 1-1](https://github.com/JoshuaBatty/EnergeticVibrationsProjectionMapping/blob/master/Wiki/Interface.png "Main Interface")

Click or touch to select a layer. You can then assign a different pattern to that layer by touching one of the patterns on the right. Doing this also chages the sliders on the left to display the patterns interactable parameters. You can change the look of the pattern here by simply moving the sliders, or assigning an audio channel to drive the parameter.

You can also delete the layer by pressing the Remove button in the top right. The Duplicate button next to it will create an extra copy of that layer.

Finally, to add a new layer, either press on the rectangle or the triangle in the top left corner (depending on what shape you want to add). Once added, use the mouse or the touch screen to position and stretch the corners into place. 

![Figure 1-2](https://github.com/JoshuaBatty/EnergeticVibrationsProjectionMapping/blob/master/Wiki/Select%20Layer.png "Select Layer")

# Sending Audio Data Via OSC
If you would like to assign audio control to the shaders you need to send it data via the following OSC address.
"ev/volumes"

There are 3 channels for bass, mid, high. Therefor you should send bass to argument 0, mid to argument 1, and high to argument 2; 

# Adding in Custom Shaders
![Figure 1-3](https://github.com/JoshuaBatty/EnergeticVibrationsProjectionMapping/blob/master/Wiki/CustomShaderPath.png "CustomShaderPath")

```glsl
//------------CONTROLABLE PARAMETERS -----------//
//# PARAM1 = (0.5) #   <--- SLIDER_1
//# PARAM2 = (0.2) #   <--- SLIDER 2
//# PARAM3 = (0.0) #   <--- SLIDER_3

vec3 Template()
{
    // Incoming slider values
    float p1 = remap(param1,0.0,1.0,0.0,1.0);
    float p2 = remap(param2,0.0,1.0,0.0,1.0);
    float p3 = remap(param3,0.0,1.0,0.0,1.0);
    
    // Pixel Coords 0.0 => 1.0
    vec2 uv = gl_FragCoord.xy / resolution.xy;
    
    //------ WRITE YOUR SHADER HERE!

    // Assign the final shaders output to the col variable
    vec3 col = vec3(uv.x,uv.y,p3);
    
    // Return the output mixed with colour
    return col * MixColour();
}
```
