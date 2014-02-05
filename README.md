CS 426 Project
==============


Controls
--------

**Level Normal Controls**  
AWSD : Move Player / UFO  
Q : Switch Between player and ufo   

**Level Editor Controls**  
1 : Toggle Editor Mode  
Use mouse scroll wheel to zoom.  
Right Click and drag to move camera.  

Editor Modes  
- Move Objects: Use the mouse to move ground points, scenery objects, or level boundaries. 
- Add Points: Use the mouse to add ground points to the ground in this mode. Points will be added between surrounding points.  
- Remove Points: Use the mouse to select and remove ground points.   

**Terminal**  
` or ~ : Toggle on/off  
Commands:  
- "help" : print out commands 
- "off" : turn off terminal 
- "restart" : restart entire game  
- "clear" : clear terminal  
- "version" : prints out version  
- "screen hide" : hide the current screen  
- "screen show" : show the current screen  
- "test" : load test screen
- "exit" or "quit": exit game  
- "screen main" : go to main menu screen  
- "screen store" : go to store screen  
- "screen settings" : go to settings screen  
- "screen game" : go to game screen  
- "screen levelselect" : go to level select screen  
- "screen freeplay" : go to free play screen   

Commands for Level Editor (Must be in screen with one)  
- "editor open" : open level editor  
- "editor close" : close level editor  
- "scenery add tree" : add new tree to level 
- "scenery add 0" : same as previous
- "scenery add sign [text]" : add new sign to level (if text left blank, text will be set to "none"  
- "scenery add 1 [text]" : same as previous  

Commands while in Game Screen
- "level reset" : reset the current level  
- "zoom default" : sets the zoom to 1.0  
- "zoom [double]" : set the level zoom to the sent value  
- "damage ufo [damage]" : damage ufo by amount sent    
- "damage player [damage]" : damage player by amount sent  

Technical Information
---------------------

### Implemented  

* PNG Loading (Use FileHelper::loadPNG(char* file))
* Orthographic Projection 
* Perspective Projection
* 2D Sprite
* 3D Cube
* Matrix Transforms (Use GLM) 
* KeyBoard IO
* Mouse IO
* Text Rendering 
* UI Screens
* UI Buttons 
* UI Checkbox
* Texture Atlas Stucture
* Basic Collision Detection Functions 
* Settings (And Settings Save/Load) 

### Libraries

**SDL**  
[http://www.libsdl.org/](http://www.libsdl.org/)  
Used for 
- GUI's   
- Threads  
- Timing  

**GLEW**   
[http://glew.sourceforge.net/](http://glew.sourceforge.net/)  
Used to access newer OpenGL functions
 
**GLM**  
[http://glm.g-truc.net/0.9.5/index.html](http://glm.g-truc.net/0.9.5/index.html)  
Used for matrix math

**SOIL**  
[http://www.lonesock.net/soil.html](http://www.lonesock.net/soil.html)  
Used to load texture files 

OpenGL Headers for linux
------------------------

You will need to get the OpenGL headers if you are compiling the code on linux. You can either look for there here..  

[http://www.opengl.org/registry/](http://www.opengl.org/registry/)  
[http://www.khronos.org/registry/](http://www.khronos.org/registry/)  

or run these commands. The freeglut library might not be nessesary.   

    sudo apt-get update  
    sudo apt-get install libglu1-mesa-dev freeglut3-dev mesa-common-dev  

Credits
-------

**Jonathan Haslow-Hall**  

Programming   
Art  

**James Dressel**  

Programming  

**Andrew Geyster**  

Programming  

