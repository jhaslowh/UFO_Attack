UFO Attack
==============

About
-----
In this game you play an alien space bear. Use your high tech ship and weapons to conquer the Earth. Your ship is equipped with an abduction ray that can be used to abduct people from the planet. You use these people to gain new weapons and cause more destruction.  

In the docs folder above you can find some screenshots and details on the NPCs.  

Building / Running
--------

OpenGL 3.0 or greater is required to run the game.  
There is a precompiled version of the game for both ubuntu and windows in the build folder.   

A zip file containing the builds only can be downloaded from the release page. 
[https://github.com/jhaslowh/UFO_Attack/releases/tag/v1.0](https://github.com/jhaslowh/UFO_Attack/releases/tag/v1.0)    

**Windows**  
To compile on windows, run the project with Visual Studio 2010 or greater and build it.  

**Linux**  
To compile on linux, navigate to the src folding and run make. The build will be in the Build folder and will be named "UFOAttack".  
If you get errors while building on linux, you may need the opengl header files (See below).  

Controls
--------

**Level Normal Controls**  
_Player/UFO_  
AWSD : Move Player / UFO  
Q : Switch Between player and ufo   
R : Reload  
F : Switch weapon   

_Player_  
Space: Jump  
E : Interact    

_UFO_  
E : Abduction Ray  

**Level Editor Controls**  
1 : Toggle Editor Mode  
Use mouse scroll wheel to zoom.  
Right Click and drag to move camera.  

Editor Modes  
- Move Objects: Use the mouse to move ground points, scenery objects, or level boundaries. 
- Add Points: Use the mouse to add ground points to the ground in this mode. Points will be added between surrounding points.  
- Remove Points: Use the mouse to select and remove ground points.   

**Terminal Commands**  
` or ~ : Toggle on/off  
Commands:  
- "help" : print out commands  
- "help [page]" : print out command page [1-3]    
- "off" : turn off terminal  
- "restart" : restart entire game  
- "clear" : clear terminal  
- "version" : prints out version  
- "screen hide" : hide the current screen  
- "screen show" : show the current screen  
- "exit" or "quit": exit game  
- "screen main" : go to main menu screen  
- "screen store" : go to store screen  
- "screen settings" : go to settings screen  
- "screen game" : resume game screen  
- "screen newgame" : make a new game screen  
- "screen levelselect" : go to level select screen  
- "delete savedata" : delete savedata file and set to default values  
- "delete settings" : delete settings and set to default values  
- "screensize [width] [height]" : reset the width and height of the screen  
- "fullscreen [on | off]" : toggle fullscreen  
- "unlockAllGuns" : unlock all guns in game  
- "tutorial [on|off]" : toggle tutorial  

Commands for Level Editor (Must be in screen with one)  
- "saveFile [file].[x].[y].[difficulty].[levelrequirement]" : save current level to file. It will be added to the master level file and the (x,y) values sent will be its location on the level select map.    
- "save [file]" : save current level to file. This command will not add it to the master level file.  
- "editor open" : open level editor  
- "editor close" : close level editor  
- "scenery add tree" : add new tree to level 
- "scenery add sign [text]" : add new sign to level (if text left blank, text will be set to "none"  
- "scenery add tree" : add new tree to level  
- "scenery add sign [text]" : add new sign to level 
- "scenery add hayBale" : add new hay bale to level    
- "scenery add crate" : add new crate  
- "scenery add fence" : add new fence   
- "scenery add longCrate" : add new long crate  
- "scenery add tallCrate" : add new tall crate  
- "scenery add barn" : add new barn  
- "scenery add houseBrown" : add new brown house  
- "scenery add houseBlue" : add new blue house  
- "scenery add barracks" : add new barracks  
- "npc add soldier" : add new soldier npc to level  
- "npc add sniper" : add new sniper npc to level  
- "npc add stinger" : add new stinger npc to level  
- "npc add cow" : add new cow npc to level  
- "npc add hsoldier" : add new heavy soldier npc to level  
- "npc add tank" : add new tank npc to level  
- "npc add turret" : add new turret npc to level  
- "npc add sam" : add new sam site npc to level  
- "npc add civilian" : add new civilian to level  

Commands while in Game Screen
- "level reset" : reset the current level  
- "zoom default" : sets the zoom to 1.0  
- "zoom [double]" : set the level zoom to the sent value  
- "damage ufo [damage]" : damage ufo by amount sent    
- "damage player [damage]" : damage player by amount sent  
- "invincible" : player takes no further damage  
- "nodamage" : player takes no further damage  
- "mortal" : player can start taking damage  
- "time [0-24]" : set time of day to the sent value  
- "timeSpeed [value]" : set how fast the time of day progresses  
- "tutorial skip" : skip tutorial if in it  

Commands while in Level Select
- "unlockall" : unlocks all levels  

Technical Information
---------------------

### Implemented  

The following is a list of all engine specific implemented features.  

* Image Loading (using SOIL)  
* OpenGL Wrapper   
* Orthographic Projection  
* Perspective Projection  
* 2D Lighting with Linear Light Blending & FBO  
* 2D Sprite  
* 3D Cube  
* 2D Camera   
* Matrix Transforms (Using GLM)  
* KeyBoard IO  
* Mouse IO  
* Text Rendering  
* UI Screen & Screen System   
* UI Button  
* UI Checkbox  
* UI Combobox  
* UI Scrollbar  
* UI Value Slider  
* Screen Transitioning  
* Debug Terminal  
* Texture Atlas Stucture  
* Basic Collision Detection Functions for AABB's and Line segments's  
* Settings (And Settings IO)  
* Savedata (And Savedata IO)   
* Sound Effect & Music system  

### Libraries

**SDL**  
[http://www.libsdl.org/](http://www.libsdl.org/)  
Used for 
- GUI's   
- Threads  
- Timing  

**SDL mixer 2.0**  
[http://www.libsdl.org/projects/SDL_mixer/](http://www.libsdl.org/projects/SDL_mixer/)  
Used for  
- Sounds & Music  

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

**Created by**  
Jonathan Haslow-Hall  
James Dressel  
Andrew Geyster  

**Character Designs**  
Chris Dike  
Lucy Niedbala  

