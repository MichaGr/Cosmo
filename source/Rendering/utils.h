#ifndef RENDERING_UTILS_H
#define RENDERING_UTILS_H

#include "GL/glew.h"
#include <string>

namespace RenderUtils
{
	void checkShader(GLuint shader, const std::string &name);
	GLuint createShader(const std::string &source, GLenum shaderType);
    GLuint createProgram(GLuint vertexShader, GLuint fragmentShader);
    GLuint createProgram(GLuint vertexShader, GLuint geometryShader, GLuint fragmentShader);

//    template<typename T>
//    void attachShader(GLuint program, T shader)
//    {
//        glAttachShader(program,shader);
//    }

////    void attachShader(GLuint program)
////    {
////        return;
////    }

//    template<typename T, typename... TArgs>
//    void attachShader(GLuint program, T shader, TArgs... shaders)
//    {
//        attachShader(program,shader);
//        attachShader(program,shaders...);
//    }


//    template<typename T>
//    void detachShader(GLuint program, T shader)
//    {
//        glDetachShader(program,shader);
//    }

////    void detachShader(GLuint program)
////    {
////        return;
////    }

//    template<typename T, typename... TArgs>
//    void detachShader(GLuint program, T shader, TArgs... shaders)
//    {
//        detachShader(program,shader);
//        detachShader(program,shaders...);
//    }

//    template<typename T>
//    void deleteShader(T shader)
//    {
//        glDeleteShader(shader);
//    }

////    void deleteShader()
////    {
////        return;
////    }

//    template<typename T, typename... TArgs>
//    void deleteShader(T shader, TArgs... shaders)
//    {
//        deleteShader(shader);
//        deleteShader(shaders...);
//    }


//    template<typename T, typename... TArgs>
//    GLuint createProgram(T shader, TArgs... shaders)
//    {
//        GLuint program = glCreateProgram();

//        attachShader(program,shader, shaders...);

//        {
//            int log_len = 0;
//            glGetProgramiv(program, GL_INFO_LOG_LENGTH, &log_len);

//            if (log_len > 1)
//            {
//                char *log = static_cast<char*>(calloc(std::size_t(log_len), 1));
//                int chars_written = 0;

//                glGetProgramInfoLog(program, log_len, &chars_written, log);
//                printf("%s\n", log);
//                free(log);
//            }
//        }

//        detachShader(program,shader, shaders...);

//        deleteShader(shader, shaders...);

//        return program;
//    }

constexpr auto INVALID_UNIFORM_LOCATION = 0xffffffff;

}

#endif //RENDERING_UTILS_H
