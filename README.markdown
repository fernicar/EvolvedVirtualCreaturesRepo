# Virtual Creatures

A virtual creature evolution simulation originally written by Eric Laukien.
It is based on simulations such as Karl Sim's Evolved Virtual Creatures Evolution Simulation.
Creatures are created from blocks and are controlled via neural networks.
These creatures live in a voxel landscape.

Uses Bullet physics and a homebrew graphics engine using OpenGL.

To compile, link to these libraries:
- OpenGL
- GLEW
- SDL
- SDL_image
- Bullet Physics
- LUA
- OpenAL
- LibOgg
- LibVorbis

## License
[zlib](http://www.gzip.org/zlib/zlib_license.html)

To build you will need git and https://github.com/Microsoft/vcpkg installed.
Doing so will allow you to install most of the requided libs using one line command:

c:\src\vcpkg>vcpkg.exe install bullet3 freeglut glew libjpeg-turbo libogg libpng libvorbis lua openal-soft sdl2 zlib

also search, download, install and build if needed:
freealut
SDL2_image
Visual Leak Detector for Visual C++ 2008-2015