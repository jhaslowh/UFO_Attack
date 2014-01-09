CS 426 Project
==============

Implemented 
-----------

* PNG Loading (Use FileHelper::loadPNG(char* file))
* Orthographic Projection 
* 2D Sprites 
* Matrix Transforms (Use GLM) 

Notes on commits
----------------
Please do not commit anything from the release or debug directories that can be compiled. You can do this by cleaning the build before committing or just not committing those files. Also, do not commit the SQL file or the "ipch" folder.

Libraries
---------

**GLFW**  
[http://www.glfw.org/](http://www.glfw.org/)  
Used for GUI's

**GLEW**   
[http://glew.sourceforge.net/](http://glew.sourceforge.net/)  
Used to access newer OpenGL functions
 
**GLM**  
[http://glm.g-truc.net/0.9.5/index.html](http://glm.g-truc.net/0.9.5/index.html)  
Used for matrix math

**SOIL**  
[http://www.lonesock.net/soil.html](http://www.lonesock.net/soil.html)  
Used to load texture files 