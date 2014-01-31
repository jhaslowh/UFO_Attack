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

Commands While in Level Editor
- "scenery add tree" : add new tree to level 
- "scenery add 0" : also adds new tree to level 

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

### Notes on commits

Please do not commit anything from the release or debug directories that can be compiled. You can do this by cleaning the build before committing or just not committing those files. Also, do not commit the SQL file or the "ipch" folder.

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

Credits
-------

**Jonathan Haslow-Hall**  

Programming   
Art  

**James Dressel**  

Programming  

**Andrew Geyster**  

Programming  

