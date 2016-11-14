# computer_graphics_fall_2016
This repository contains implementations of various graphics related algorithms in OpenGL as a part of Computer graphics course taught in fall of 2016.

## Algorithms
The repository contains the following algorithms.

### Line
* DDA
* Breshenham's
* Dashed line

### Circle
* Mid-point
* Parametric
* Polynomial

### Polygon Filling
* Scan Line Polygon Filling (WIP)

### Transformations and Projection
* 3D transformations
* Window to Viewport
* Orthographic and Perspective Projections

### Clipping
* Cohen-Sutherland
* Liang-Barsky
* Cyrus-Beck

### Curve Generation
* Beizer Curve
* Hermite Curve

## Running the Algorithms
The individual `.c`/`.cpp` files can be directly compiled using `gcc`/`g++` provided `GLUT` is installed. `OpenGL` and `GLUT` is installed on macOS by default.

> macOS: `$(CC) $(file) -o main -framework OpenGL -framework GLUT`
> posix: `$(CC) $(file) -o main -lGL - lGLU -lGLUT -lm`  
