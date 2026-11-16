#include "utils.h"
#include <iostream>
#include "../utils.h"

namespace RenderUtils
{

	void checkShader(GLuint shader, const std::string &name)
	{
		GLint success = 0;

		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

		if (success == GL_FALSE)
		{
			std::cout << "compilation of shader failed." << name << std::endl;
		}
		else
		{
			std::cout << "successfully compiled shader." << name << std::endl;
		}

        int log_len = 0;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &log_len);

		if (log_len > 1)
		{
            char *log = static_cast<char*>(calloc(std::size_t(log_len), 1));
			int chars_written = 0;

			glGetShaderInfoLog(shader, log_len, &chars_written, log);
			std::cout << log << std::endl;
			free(log);
		}
	}

	GLuint createShader(const std::string &source, GLenum shaderType)
	{
		GLuint shader = glCreateShader(shaderType);

		std::string shaderDir("");

		std::string shaderSource = readFile(shaderDir + source);

		std::cout << source << std::endl;
		const char* shaderSourceCStr = shaderSource.c_str();

        glShaderSource(shader, 1, &shaderSourceCStr, nullptr);
		glCompileShader(shader);
		checkShader(shader, source);

		return shader;
	}

    GLuint createProgram(GLuint vertexShader, GLuint fragmentShader)
    {
        GLuint program = glCreateProgram();

        glAttachShader(program, vertexShader);
        glAttachShader(program, fragmentShader);

        glLinkProgram(program);

        {
            int log_len = 0;
            glGetProgramiv(program, GL_INFO_LOG_LENGTH, &log_len);

            if (log_len > 1)
            {
                char *log = static_cast<char*>(calloc(std::size_t(log_len), 1));
                int chars_written = 0;

                glGetProgramInfoLog(program, log_len, &chars_written, log);
                printf("%s\n", log);
                free(log);
            }
        }

        glDetachShader(program, vertexShader);
        glDetachShader(program, fragmentShader);

        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);

        return program;
    }

    GLuint createProgram(GLuint vertexShader, GLuint geometryShader, GLuint fragmentShader)
    {
        GLuint program = glCreateProgram();

        glAttachShader(program, vertexShader);
        glAttachShader(program, geometryShader);
        glAttachShader(program, fragmentShader);


        glLinkProgram(program);

        {
            int log_len = 0;
            glGetProgramiv(program, GL_INFO_LOG_LENGTH, &log_len);

            if (log_len > 1)
            {
                char *log = static_cast<char*>(calloc(std::size_t(log_len), 1));
                int chars_written = 0;

                glGetProgramInfoLog(program, log_len, &chars_written, log);
                printf("%s\n", log);
                free(log);
            }
        }

        glDetachShader(program, vertexShader);
        glDetachShader(program, geometryShader);
        glDetachShader(program, fragmentShader);

        glDeleteShader(vertexShader);
        glDeleteShader(geometryShader);
        glDeleteShader(fragmentShader);

        return program;
    }


}
