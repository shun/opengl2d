#define GLFW_DLL
#define GLEW_STATIC

#include <GL/glfw.h>
#include <cstdlib>
#include <fstream>
#include <vector>

struct Vertex
{
	GLfloat x;
	GLfloat y;
};

struct Color
{
	GLfloat red;
	GLfloat green;
	GLfloat blue;
};

struct TextureCoord
{
	GLfloat u;
	GLfloat v;
};

bool setupTexture(const GLuint id,
				  const char *file,
				  const int width,
				  const int height)
{
	std::ifstream fstr(file, std::ios::binary);
	if (!fstr) return false;

	const size_t filesz = static_cast<size_t>(fstr.seekg(0, fstr.end).tellg());
	fstr.seekg(0, fstr.beg);

	std::vector<char> texture_buffer(filesz);
	fstr.read(&texture_buffer[0],
			  filesz);

	glBindTexture(GL_TEXTURE_2D, id);
	glTexImage2D(GL_TEXTURE_2D,
				 0, GL_RGBA, width, height,
				 0, GL_RGBA,
				 GL_UNSIGNED_BYTE, &texture_buffer[0]);

	glTexParameteri(GL_TEXTURE_2D,
					GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,
					GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	return true;
}

int main()
{
	if (!glfwInit())
		return EXIT_FAILURE;

	if (!glfwOpenWindow(0, 0, 0, 0, 0, 0, 0, 0, GLFW_WINDOW))
	{
		glfwTerminate();
		return EXIT_FAILURE;
	}

	glfwSwapInterval(1);

	GLuint texture_id;
	glGenTextures(1, &texture_id);

	if (!setupTexture(texture_id, "../sample.raw", 256, 256))
	{
		glDeleteTextures(1, &texture_id);
		glfwTerminate();

		return EXIT_FAILURE;
	}

	while(glfwGetWindowParam(GLFW_OPENED))
	{
		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		struct Body
		{
			Vertex vtx;
			Color  col;
			TextureCoord tex;
		};

		static const Body body[] = {
			{{-0.8f, -0.8f},
			 {1.0f, 0.0f, 0.0f},
			 {0.0f, 0.0f}},
			{{-0.1f, -0.8f},
			 {0.0f, 1.0f, 0.0f},
			 {1.0f, 0.0f}},
			{{-0.1f, -0.1f},
			 {1.0f, 1.0f, 0.0f},
			 {1.0f, 1.0f}},
			{{-0.8f, -0.1f},
			 {0.0f, 0.0f, 1.0f},
			 {0.0f, 1.0f}},

			{{0.8f, 0.8f},
			 {1.0f, 0.0f, 1.0f},
			 {0.0f, 0.0f}},
			{{0.1f, 0.8f},
			 {0.0f, 1.0f, 1.0f},
			 {1.0f, 0.0f}},
			{{0.1f, 0.1f},
			 {1.0f, 1.0f, 1.0f},
			 {1.0f, 1.0f}},
			{{0.8f, 0.1f},
			 {0.0f, 0.0f, 0.0f},
			 {0.0f, 1.0f}}};

		const GLvoid * tmp = body;
		const GLbyte *ptr = static_cast<const GLbyte *>(tmp);

		glVertexPointer(2, GL_FLOAT, sizeof(Body), body);
		glColorPointer(3, GL_FLOAT, sizeof(Body), ptr + offsetof(Body, col));

		glTexCoordPointer(2, GL_FLOAT, sizeof(Body), ptr + offsetof(Body, tex));

		glEnable(GL_TEXTURE_2D);
		glEnableClientState(GL_VERTEX_ARRAY);
		glEnableClientState(GL_COLOR_ARRAY);
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);

		glDrawArrays(GL_QUADS, 0, 8);

		glDisableClientState(GL_VERTEX_ARRAY);
		glDisableClientState(GL_COLOR_ARRAY);
		glDisableClientState(GL_TEXTURE_COORD_ARRAY);

		glDisable(GL_TEXTURE_2D);
		glfwSwapBuffers();
	}

	glDeleteTextures(1, &texture_id);

	glfwTerminate();

	return EXIT_SUCCESS;
}
