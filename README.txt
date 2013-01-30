-----------------------------------------
ParticleSystem
-----------------------------------------
OpenGL - Demonstration for following techniques:
- Simple Level-Of-Detail
- Loading of 3DS-Files with textures
- Implementation of a simple fontain particle-system
- Transparent-Geometry with depth-sorting
- FPS-Camera view with mouse and keyboard control
- Simple skybox
-----------------------------------------

-----------------------------------------
LIB-DEPENDENCIES
-----------------------------------------
- XQUARTZ (http://xquartz.macosforge.org/landing/)
- FREEGLUT 2.8.0 - OpenGL Utility (http://prdownloads.sourceforge.net/freeglut/freeglut-2.8.0.tar.gz?download)
- LIB3DS 1.3 - For loading the 3DS-files (http://lib3ds.googlecode.com/files/lib3ds-1.3.0.zip)
- LIBFREEIMAGE 3.15.4 - For loading textures in different file formats (http://freeimage.sourceforge.net/download.html)

-----------------------------------------
INSTALLATION OF THE LIBRARIES LISTED ABOVE
-----------------------------------------
* XQUARTZ is required for the obsolete X11 on OSX - only needed if the program should be built on a MAC
* FREEGLUT needs to be installed in "/opt/X11/include" as stated in following tutorial: http://lazyfoo.net/tutorials/OpenGL/01_hello_opengl/mac/index.php
* LIB3DS and LIBFREEIMAGE needs to be compiled manually (I put them in "/usr/local/lib")

-----------------------------------------
PRECOMPILED BINARIES FOR OSX
-----------------------------------------
Can be found in "[GIT-Repo]/bin"
* Contains the binary to start the program on OSX
* Contains the resource-folder with all assets

-----------------------------------------
RUN NOTES (BINARY)
-----------------------------------------
* The compiled binary takes only one Var-Arg argument for the [resource_path], 
that means this path should point to the right assets-folder called "resources" located in the same folder as the binary
* If you want to build this project with XCode, make sure to set the right [resource_path] "Run Arguments" in the Run-Scheme

Running the binary on the commandline (Terminal):
cd ~/my_git_repos/ParticleSystem/bin
./ParticleSystem "resources/"

-----------------------------------------
CONTROLS
-----------------------------------------
The camera can be moved by following keys:
* W - Move forward
* A - Strafe left
* S - Move backwards
* D - Strafe right
* Space - Move upwards
* CTRL - Move downwards

* SHIFT + [Movement-Key] enables auto-move, it will stop moving by pressing SHIFT again
* Mouse - Camera rotation