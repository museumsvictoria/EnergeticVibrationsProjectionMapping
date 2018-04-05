# Energetic Vibrations Projection Mapping
This project was developed for the Energetic Vibrations Projection Mapping Installation as part of the Beyond Perception exhibition at Scienceworks. It is developed using openFrameworks, GLSL, and a modified version of ofxPiMapper. Multi touch support is also available for Windows touch screens.

![Figure 1-1](https://github.com/JoshuaBatty/EnergeticVibrationsProjectionMapping/blob/master/Wiki/Interface.png "Main Interface")

Click or touch to select a layer. You can then assign a different pattern to that layer by touching one of the patterns on the right. Doing this also chages the sliders on the left to display the patterns interactable parameters. You can change the look of the pattern here by simply moving the sliders, or assigning an audio channel to drive the parameter.

You can also delete the layer by pressing the Remove button in the top right. The Duplicate button next to it will create an extra copy of that layer.

Finally, to add a new layer, either press on the rectangle or the triangle in the top left corner (depending on what shape you want to add). Once added, use the mouse or the touch screen to position and stretch the corners into place. 

![Figure 1-2](https://github.com/JoshuaBatty/EnergeticVibrationsProjectionMapping/blob/master/Wiki/Select%20Layer.png "Select Layer")

## Sending Audio Data Via OSC
If you would like to assign audio control to the shaders you need to send it data via the following OSC address
"ev/volumes" on OSC port 9002.

There are 3 channels for bass, mid, high. Therefor you should send bass to argument 0, mid to argument 1, and high to argument 2.

Below is a simple example of how you could set that up using MaxMSP
![Figure 1-2](https://github.com/JoshuaBatty/EnergeticVibrationsProjectionMapping/blob/master/Wiki/MaxOSC.png "Select Layer")

## Adding in Custom Shaders
![Figure 1-3](https://github.com/JoshuaBatty/EnergeticVibrationsProjectionMapping/blob/master/Wiki/CustomShaderPath.png "CustomShaderPath")
There is support for users to add their own custom shaders. In order to do so, use the Template.frag file as a starting point. Once we edit this shader we will be able to control it's parameters using sliders and audio reactivity. The file is found in the above location. 


If you open the file in a text editor it will look like this. 
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

---
```glsl
//------------CONTROLABLE PARAMETERS -----------//
//# PARAM1 = (0.5) #   <--- SLIDER_1
//# PARAM2 = (0.2) #   <--- SLIDER 2
//# PARAM3 = (0.0) #   <--- SLIDER_3
```
Up the top of the file you have 3 parameters that you can assign to control various parts of the shader that you either make or import from the web. 

The words PARAM1, PARAM2, PARAM3 are place holders for the 'name' that shows up ontop of the slider in the application. Change these to reflect the effect it has on the pattern (eg. SPEED, ZOOM etc..). The number inside the ( ) is the default value that you would like the pattern to start with. This number must be within a range of 0.0 to 1.0. 

For example, if we wanted the sliders to show Angle, Width and Copies as their names and default to 1.0 for the first 2 sliders, and 0.5 for the third you would change the above example to the following.  
```glsl
//------------CONTROLABLE PARAMETERS -----------//
//# ANGLE = (1.0) #   <--- SLIDER_1
//# WIDTH = (1.0) #   <--- SLIDER 2
//# COPIES = (0.5) #  <--- SLIDER_3
```

---
Next is the name of our main function. **This must be the EXACT same name of the file**. 
```glsl
vec3 Template()
```

For example if you duplicate the Template.frag file and call it MyAwesomeShader.frag, then the name of the function must be MyAwesomeShader() like so. 
```glsl
vec3 MyAwesomeShader()
```

---
The incoming values the the sliders are between 0.0 and 1.0. The next few lines of code allow you to __remap__ this range to another that may be more suitable to the parameter you are controlling. Simply change the last 2 values inside the remap() function to the ranges you would like the value to constrain within. Finally, use the p1, p2, p3 variables to hook the interface into parts of the shader. 
```glsl
// Incoming slider values
float p1 = remap(param1,0.0,1.0,0.0,0.5);
float p2 = remap(param2,0.0,1.0,0.1,1.0);
float p3 = remap(param3,0.0,1.0,1.0,12.0);
```
