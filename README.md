CS 426 Project
==============

Implemented 
-----------

* PNG Loading (Use FileHelper::loadPNG(char* file))
* Orthographic Projection 
* Perspective Projection
* 2D Sprite
* 3D Cube
* Matrix Transforms (Use GLM) 
* KeyBoard IO
* Text Rendering 

Notes on commits
----------------

Please do not commit anything from the release or debug directories that can be compiled. You can do this by cleaning the build before committing or just not committing those files. Also, do not commit the SQL file or the "ipch" folder.

Libraries
---------

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