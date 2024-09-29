# Raytracer
A raytracer that allows for defining scenes in a lua file and creating ppm images as renders.

## Build
This project depends on the lau5.4 library, simply compile all sources and link against the library. The makefile provided works on linux and may need slight changes to work on other platforms.

## Usage
Run the executable with the following arguments: (scene.lua out.ppm size max_bounces)

Some examples of scenes are provided.
