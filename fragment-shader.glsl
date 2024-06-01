#version 400

out vec4 frag_colour;
in vec3 vertex_colour;

void main() {
  float x = (vertex_colour.x + 1) / 2;
  float y = (vertex_colour.y + 1) / 2;
  frag_colour = vec4(x, y, 0.2, 1.0);
}
