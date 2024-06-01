#version 400

in vec3 v; // the three components in the float array
// if there were more components, we would declare them here
out vec3 vertex_colour;

void main() {
  gl_Position = vec4(v, 1.0);
  vertex_colour = v;
}
