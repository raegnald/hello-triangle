#include <stdlib.h>
#include <stdio.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#define assert(condition, ...) {                                  \
    if (!(condition)) {                                           \
      fprintf(stderr, "[%s, line %d] Assertion failed (%s):\n  ", \
              __FILE__, __LINE__, #condition);                    \
      fprintf(stderr, __VA_ARGS__);                               \
      fprintf(stderr, "\n");                                      \
      exit(EXIT_FAILURE);                                         \
    }                                                             \
  }

#define failwith(...) {                            \
    fprintf(stderr, "[%s, line %d] Failure:\n  ",  \
            __FILE__, __LINE__);                   \
    fprintf(stderr, __VA_ARGS__);                  \
    fprintf(stderr, "\n");                         \
    exit(EXIT_FAILURE);                            \
  }

#define VERTEX_SHADER_FILE   "vertex-shader.glsl"
#define FRAGMENT_SHADER_FILE "fragment-shader.glsl"

char *read_file(const char *filename) {
  FILE *stream = fopen(filename, "r");
  assert(stream != NULL, "Could not open file '%s'", filename);

  fseek(stream, 0, SEEK_END);
  size_t length = ftell(stream);
  rewind(stream);

  char *buffer = malloc((length + 1) * sizeof(char));
  fread(buffer, sizeof(char), length, stream);
  buffer[length] = '\0';

  fclose(stream);
  return buffer;
}

int main(void) {
  assert(glfwInit(), "Could not initialise GLFW 3");

  GLFWwindow *window = glfwCreateWindow(640, 480, "Hello Triangle", NULL, NULL);
  if (!window) {
    glfwTerminate();
    failwith("Could not create window");
  }

  glfwMakeContextCurrent(window);

  glewExperimental = GL_TRUE;
  glewInit();

  /* ... shader processing ... */

  float points[] = {
     0.0f,  0.5f,  0.0f,
     0.5f, -0.5f,  0.0f,
    -0.5f, -0.5f,  0.0f
  };

  GLuint vbo;                   /* Vertex buffer object: GPU array of points */
  glGenBuffers(1 /* amount of buffers */, &vbo); /* Generate empty buffers */
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(points), &points, GL_STATIC_DRAW);

  GLuint vao;                   /* Vertex array object: it can hold
                                   multiple VBOs */
  glGenVertexArrays(1 /* how many distinct inputs to pass to vertex shader */,
                    &vao);
  glBindVertexArray(vao);
  glEnableVertexAttribArray(0 /* attribute number */);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glVertexAttribPointer(0 /* attribute number */, 3, GL_FLOAT,
                        GL_FALSE /* are components noramlised? */,
                        0 /* stride/skip */, 0 /* offset to start of vec3's */);

  const char *vertex_shader = read_file(VERTEX_SHADER_FILE);
  const char *fragment_shader = read_file(FRAGMENT_SHADER_FILE);

  GLuint vs = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vs, 1, &vertex_shader, NULL);
  glCompileShader(vs);
  GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fs, 1, &fragment_shader, NULL);
  glCompileShader(fs);

  free((char *) vertex_shader);
  free((char *) fragment_shader);

  GLuint shader_program = glCreateProgram();
  glAttachShader(shader_program, fs);
  glAttachShader(shader_program, vs);
  glLinkProgram(shader_program);

  while (!glfwWindowShouldClose(window)) {
    /* ... render here... */
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(shader_program);
    glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLES, 0, 3);

    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  glfwTerminate();
  return EXIT_SUCCESS;
}
