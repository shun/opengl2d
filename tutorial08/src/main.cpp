#define GLFW_DLL

#include <GL/glfw.h>
#include <cstdlib>
#include <fstream>
#include <vector>

bool setupTexture(
	const GLuint id,
	const char *file)
{
	std::ifstream fstr(file,
					   std::ios::binary);

	if (!fstr) return false;

	const size_t file_size = static_cast<size_t>(fstr.seekg(0, fstr.end).tellg());

	fstr.seekg(0, fstr.beg);

	std::vector<char> texture_buffer(file_size);

	fstr.read(&texture_buffer[0],
			  file_size);

	glBindTexture(GL_TEXTURE_2D, id);
	glTexImage2D(GL_TEXTURE_2D,
				 0, GL_RGBA, 256, 256,
				 0, GL_RGBA,
				 GL_UNSIGNED_BYTE,
				 &texture_buffer[0]);
	glTexParameteri(GL_TEXTURE_2D,
					GL_TEXTURE_MAG_FILTER,
					GL_LINEAR);

	glTexParameteri(GL_TEXTURE_2D,
					GL_TEXTURE_MIN_FILTER,
					GL_LINEAR);

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

	GLuint texture_id;
	glGenTextures(1, &texture_id);

	if (!setupTexture(texture_id, "sample.raw"))
	{
		glDeleteTextures(1, &texture_id);
		glfwTerminate();
		return EXIT_FAILURE;
	}
	
	glfwSwapInterval(1);

	while(glfwGetWindowParam(GLFW_OPENED))
	{
		glClearColor(0.0f,	// red:0.0-1.0
					 0.0f,	// green
					 0.0f,	// blue
					 0.0f);	// alpha
		glClear(GL_COLOR_BUFFER_BIT);

		static const GLfloat vtx[] = {
			-0.5f, -0.5f,
			0.5f, -0.5f,
			0.5f, 0.5f,
			-0.5f, 0.5f};
			
		glVertexPointer(2,
						GL_FLOAT,
						0,
						vtx);

		static const GLfloat texture_uv[] = {
			0.0f, 0.0f,
			1.0f, 0.0f,
			1.0f, 1.0f,
			0.0f, 1.0f};

		glTexCoordPointer(2, GL_FLOAT, 0, texture_uv);

		glEnable(GL_TEXTURE_2D);

		glEnableClientState(GL_VERTEX_ARRAY);
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		
		glDrawArrays(GL_QUADS,
					 0,
					 4);
		glDisableClientState(GL_VERTEX_ARRAY);
		glDisableClientState(GL_TEXTURE_COORD_ARRAY);
		glDisable(GL_TEXTURE_2D);
		glfwSwapBuffers();
	}
	glDeleteTextures(1, &texture_id);
	glfwTerminate();

	return EXIT_SUCCESS;
}
