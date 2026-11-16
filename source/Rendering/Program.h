#ifndef PROGRAM_H
#define PROGRAM_H

#include "GL/glew.h"
#include "Uniform.h"
#include <vector>
#include <string>
#include <map>
#include <iostream>
#include "utils.h"
#include "config.h"
namespace Cosmo
{
	class Program
	{   
	public:
		Program()
		{
			m_id = 0;
		}

        template<typename T, typename... TArgs>
        void addShaders(const std::string& shaderSource,T value, TArgs... shader)
        {
            addShader(shaderSource,value);
            this->addShaders(shaderSource,shader...);

        }


		void addShader(const std::string& shaderSource, GLenum shaderType)
		{
            std::string shaderDir = SHADER_DIR;

            std::string completePath = SHADER_DIR + shaderSource + getExtension(shaderType);
            if (m_shader.find(shaderType) == m_shader.end())
			{
				m_shader.insert({ shaderType,Shader() });
                m_shader[shaderType].source = completePath;
			}
			else
			{
				std::cout << "Shader already Set" << std::endl;
			}
		}

		GLuint getID() const
		{
			return m_id;
		}

		void create()
		{
			if (m_shader.find(GL_GEOMETRY_SHADER) != m_shader.end())
			{
				GLuint v = RenderUtils::createShader(m_shader[GL_VERTEX_SHADER].source, GL_VERTEX_SHADER);
				GLuint f = RenderUtils::createShader(m_shader[GL_FRAGMENT_SHADER].source, GL_FRAGMENT_SHADER);
				GLuint g = RenderUtils::createShader(m_shader[GL_GEOMETRY_SHADER].source, GL_GEOMETRY_SHADER);
				m_id = RenderUtils::createProgram(v, g, f);
			}
			else
			{
				GLuint v = RenderUtils::createShader(m_shader[GL_VERTEX_SHADER].source, GL_VERTEX_SHADER);
				GLuint f = RenderUtils::createShader(m_shader[GL_FRAGMENT_SHADER].source, GL_FRAGMENT_SHADER);
				m_id = RenderUtils::createProgram(v, f);
			}
		}

		template <typename T>
		void addUniform(const std::string& nameInShader, T* pointer)
		{
			if (m_id != 0)
			{
				Uniform<T>* uniform = new Uniform<T>(m_id, nameInShader, pointer);
				m_uniforms.emplace_back(uniform);
			}
			else
			{
				std::cout << "Program not created" << std::endl;
			}
		}

		void use()
		{
			glUseProgram(m_id);
		}

		void updateUniforms()
		{
			for (UniformBase* uniform : m_uniforms)
			{
				uniform->update();
			}
		}

	private:

        //for parameter pack
        void addShaders(const std::string& shader)
        {
            return;
        }


        std::string getExtension(GLenum type)
        {
            switch(type)
            {
            case GL_VERTEX_SHADER:
                return ".vs";
            case GL_FRAGMENT_SHADER:
                return ".fs";
            case GL_GEOMETRY_SHADER:
                return ".gs";
            case GL_TESS_CONTROL_SHADER:
                return ".tcs";
            case GL_TESS_EVALUATION_SHADER:
                return ".tes";
            default:
                return "";
            }
        }

		struct Shader
		{
			Shader()
				: source("")
			{}
			std::string source;
		};

		std::map<GLenum, Shader> m_shader;

		GLuint m_id;
		std::vector<UniformBase*> m_uniforms;
	};
}

#endif //PROGRAM_H
