#define GLFW_DLL
#define GLEW_STATIC

#include <GL/glfw.h>
#include <cstdlib>
#include <fstream>
#include <vector>
#include <cmath>
#if defined(__APPLE__)
//#include <OpenGL/glext.h>
#endif	// __APPLE__

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

	GLfloat vtx[100 * 2];

	for (int i = 0; i < 100; ++i)
	{
		vtx[i * 2] = (rand() % 1000 / 500.0f - 1.0f);
		vtx[i * 2 + 1] = (rand() % 1000 / 500.0f - 1.0f);
		glVertexPointer(2, GL_FLOAT, 0, vtx);
	}
	
	while(glfwGetWindowParam(GLFW_OPENED))
	{
		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glPointSize(32.0f);

		glEnable(GL_TEXTURE_2D);
		glEnable(GL_POINT_SPRITE);

		glTexEnvi(GL_POINT_SPRITE,
				  GL_COORD_REPLACE,
				  GL_TRUE);

		glPointParameteri(GL_POINT_SPRITE_COORD_ORIGIN,
						  GL_UPPER_LEFT);
		glEnableClientState(GL_VERTEX_ARRAY);
		glDrawArrays(GL_POINTS, 0, 100);

		glDisableClientState(GL_VERTEX_ARRAY);

		glDisable(GL_TEXTURE_2D);
		glDisable(GL_POINT_SPRITE);
		
		glfwSwapBuffers();
	}

	glDeleteTextures(1, &texture_id);

	glfwTerminate();

	return EXIT_SUCCESS;
}
