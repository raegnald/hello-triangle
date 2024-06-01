
https://learnopengl.com/Getting-started/Hello-Triangle
https://antongerdelan.net/opengl/hellotriangle.html

The OpenGL graphics pipeline has two steps:

1. Projecting points in 3d space into points in the 2d plane (aka. the
   screen).

2. Coloring the points in the plane as shapes.

A shader is a program that runs in parallel in the GPU. For the two
steps of the pipeline there are corresponding shaders, namely vertex
shaders and fragment shaders
