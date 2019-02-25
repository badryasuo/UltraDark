#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <string>
#include <fstream>
#include <sstream>
#include <regex>
#include <iostream>
class Shader
{

public:
	Shader(const char* name, bool Geometry) {
		std::string vertCode;
		std::string fragCode;
		std::string geometryCode;
		std::ifstream vertFile;
		std::ifstream fragFile;
		std::ifstream geometryFile;

		try
		{
			std::string path(name);
			// Make it work in Unix-Systems by replacing the backslash with a forward slash
			std::replace(path.begin(), path.end(), '\\', '/');
			// Automatically search for extensions
			vertFile.open(path + ".vs");
			fragFile.open(path + ".fs");
			std::stringstream vShaderStream, fShaderStream;
			vShaderStream << vertFile.rdbuf();
			fShaderStream << fragFile.rdbuf();
			vertFile.close();
			fragFile.close();
			vertCode.append(vShaderStream.str());
			fragCode.append(fShaderStream.str());
			// GLSL may not recognize '\r' as a new line but as a carriage return character which will corrupt your code
			// and lead to confusing errors, so replacing it to '\n' is a lot safer for all operating systems.
			std::replace(vertCode.begin(), vertCode.end(), '\r', '\n');
			std::replace(fragCode.begin(), fragCode.end(), '\r', '\n');
			if (Geometry) // if Geometry is equal to true, It'd seacr
			{
				geometryFile.open(path + ".gs");
				std::stringstream gShaderStream;
				gShaderStream << geometryFile.rdbuf();
				geometryFile.close();
				geometryCode.append(gShaderStream.str());
				std::replace(geometryCode.begin(), geometryCode.end(), '\r', '\n');
			}

		}
		catch (std::ifstream::failure &e)
		{
			std::cout << "ERROR::SHADER:UNABLE_TO_READ_FILE\n";
		}
		const GLchar* vShaderCode = vertCode.c_str();
		const GLchar* fShaderCode = fragCode.c_str();
		const GLchar* gShaderCode;
		if (Geometry)
			gShaderCode = geometryCode.c_str();
		GLuint vertex, fragment, geometry;
		vertex = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertex, 1, &vShaderCode, NULL);
		glCompileShader(vertex);
		checkErrors(vertex, VERTEX_SHADER);

		fragment = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragment, 1, &fShaderCode, NULL);
		glCompileShader(fragment);
		checkErrors(fragment, FRAGMENT_SHADER);

		if (Geometry)
		{
			geometry = glCreateShader(GL_GEOMETRY_SHADER);
			glShaderSource(geometry, 1, &gShaderCode, NULL);
			glCompileShader(geometry);
			checkErrors(geometry, GEOMETRY_SHADER);
		}

		shaderProgram = glCreateProgram();
		glAttachShader(shaderProgram, vertex);
		glAttachShader(shaderProgram, fragment);
		if (Geometry)
			glAttachShader(shaderProgram, geometry);
		glLinkProgram(shaderProgram);
		checkErrors(shaderProgram, PROGRAM);
	}
	void bind()
	{
		glUseProgram(shaderProgram);
	}
	GLuint getAttribLocation(const char * attribute)
	{
		return glGetAttribLocation(shaderProgram, attribute);
	}
	GLuint getProgramID()
	{
		return shaderProgram;
	}
	void setInt(const char * var, GLint value)
	{
		glUniform1i(glGetUniformLocation(shaderProgram, var), value);
	}
	void setFloat(const char * var, GLfloat value)
	{
		glUniform1f(glGetUniformLocation(shaderProgram, var), value);
	}
	void setMat4(const char * var, glm::mat4 matrix)
	{
		glUniformMatrix4fv(glGetUniformLocation(shaderProgram, var), 1, GL_FALSE, glm::value_ptr(matrix));
	}
private:
	enum SHADERS {
		PROGRAM,
		VERTEX_SHADER,
		FRAGMENT_SHADER,
		GEOMETRY_SHADER,
	};
	GLuint shaderProgram;
	void checkErrors(GLuint shader, SHADERS type)
	{
		char log[1024];
		int success;
		switch (type) {
		case PROGRAM:
			glGetProgramiv(shader, GL_LINK_STATUS, &success);
			if (!success) {
				glGetProgramInfoLog(shader, sizeof(log), NULL, log);
				std::cout << " REPORT::PROGRAM::LINK_FAILED\n\n" << log
					<< "#-- " << std::string(51, '-') << " --!\n";
			}
			break;
		case VERTEX_SHADER:
			glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
			if (!success) {
				glGetShaderInfoLog(shader, sizeof(log), NULL, log);
				std::cout << " REPORT::SHADER::VERTEX::COMPILATION_FAILED\n\n" << log
					<< "#-- " << std::string(51, '-') << " --!\n";
			}
			break;
		case FRAGMENT_SHADER:
			glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
			if (!success) {
				glGetShaderInfoLog(shader, sizeof(log), NULL, log);
				std::cout << " REPORT::SHADER::FRAGMENT::COMPILATION_FAILED\n\n" << log
					<< "#-- " << std::string(51, '-') << " --!\n";
			}
			break;
		case GEOMETRY_SHADER:
			glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
			if (!success) {
				glGetShaderInfoLog(shader, sizeof(log), NULL, log);
				std::cout << " REPORT::SHADER::GEOMTERY::COMPILATION_FAILED\n\n" << log
					<< "#-- " << std::string(51, '-') << " --!\n";
			}
			break;
		}
	}
};