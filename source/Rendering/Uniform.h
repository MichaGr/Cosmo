#ifndef UNIFORM_H
#define UNIFORM_H

#include "GL/glew.h"
#include <string>
#include "../../glm-0.9.9.3/glm/gtc/matrix_transform.hpp"
#include "Lighting/DirectionalLight.h"
#include "Lighting/PointLight.h"
#include "utils.h"
#include <iostream>
namespace Cosmo
{
	class UniformBase
	{
	public:
		virtual ~UniformBase() {}

		virtual void update() = 0;
	};

	template <typename T>
	class Uniform : public UniformBase
	{
	public:
        Uniform(GLuint program, const std::string& name, T* pointer = nullptr)
		{}
		~Uniform() override {}
		void update() override
		{}

	private:
        GLuint m_program;
        GLint m_id;
		std::string m_name;
		T* m_dataPointer;
	};

	template <>
	class Uniform<float> : public UniformBase
	{
	public:
        Uniform(GLuint program, const std::string& name, float* pointer)
			: m_program(program),
			m_name(name),
			m_dataPointer(pointer)
		{
			m_id = glGetUniformLocation(m_program, name.c_str());
			glUniform1fv(m_id, 1, m_dataPointer);
		}

		~Uniform() override {}

		void update() override
		{
			glUniform1fv(m_id, 1, m_dataPointer);
		}

	private:
		GLuint m_program;
        GLint m_id;
		std::string m_name;
		float* m_dataPointer;
	};

	template <>
	class Uniform<glm::mat4> : public UniformBase
	{
	public:
		Uniform(GLuint program, const std::string& name, glm::mat4* pointer)
			: m_program(program),
			m_name(name),
			m_dataPointer(pointer)
		{
			m_id = glGetUniformLocation(m_program, name.c_str());
			glUniformMatrix4fv(m_id, 1, GL_FALSE, &(*m_dataPointer)[0][0]);
		}

		~Uniform() override {}

		void update() override
		{
			glUniformMatrix4fv(m_id, 1, GL_FALSE, &(*m_dataPointer)[0][0]);
		}

	private:
		GLuint m_program;
        GLint m_id;
		std::string m_name;
		glm::mat4* m_dataPointer;
	};

	template <>
	class Uniform<glm::mat3> : public UniformBase
	{
	public:
		Uniform(GLuint program, const std::string& name, glm::mat3* pointer)
			: m_program(program),
			m_name(name),
			m_dataPointer(pointer)
		{
			m_id = glGetUniformLocation(m_program, name.c_str());
			glUniformMatrix3fv(m_id, 1, GL_FALSE, &(*m_dataPointer)[0][0]);
		}

		~Uniform() override {}

		void update() override
		{
			glUniformMatrix3fv(m_id, 1, GL_FALSE, &(*m_dataPointer)[0][0]);
		}

	private:
		GLuint m_program;
        GLint m_id;
		std::string m_name;
		glm::mat3* m_dataPointer;
	};

	template <>
	class Uniform<glm::vec3> : public UniformBase
	{
	public:
		Uniform(GLuint program, const std::string& name, glm::vec3* pointer)
			: m_program(program),
			m_name(name),
			m_dataPointer(pointer)
		{
			m_id = glGetUniformLocation(m_program, name.c_str());
			glUniform3fv(m_id, 1, &(*m_dataPointer)[0]);
		}

		~Uniform() override {}

		void update() override
		{
			glUniform3fv(m_id, 1, &(*m_dataPointer)[0]);
		}

	private:
		GLuint m_program;
        GLint m_id;
		std::string m_name;
		glm::vec3* m_dataPointer;
	};

	template <>
	class Uniform<DirectionalLight> : public UniformBase
	{
	public:
		Uniform(GLuint program, const std::string& name, DirectionalLight* pointer)
			: m_program(program),
			m_name(name),
			m_dataPointer(pointer)
		{
            m_id = new GLint[4];

			std::string dirStr = name + ".Direction";
			std::string colorStr = name + ".Base.Color";
			std::string ambStr = name + ".Base.AmbientIntensity";
			std::string diffStr = name + ".Base.DiffuseIntensity";
			m_id[0] = glGetUniformLocation(m_program, dirStr.c_str());
			m_id[1] = glGetUniformLocation(m_program, colorStr.c_str());
			m_id[2] = glGetUniformLocation(m_program, ambStr.c_str());
			m_id[3] = glGetUniformLocation(m_program, diffStr.c_str());

			glUniform3fv(m_id[0], 1, &(m_dataPointer->direction[0]));
			glUniform3fv(m_id[1], 1, &(m_dataPointer->color[0]));
			glUniform1fv(m_id[2], 1, &(m_dataPointer->ambientIntensity));
			glUniform1fv(m_id[3], 1, &(m_dataPointer->diffuseIntensity));

            if (m_id[0] == int(RenderUtils::INVALID_UNIFORM_LOCATION))
			{
				std::cout << "Invalid: " << 0 << std::endl;
			}

            if (m_id[1] == int(RenderUtils::INVALID_UNIFORM_LOCATION))
			{
				std::cout << "Invalid: " << 1 << std::endl;
			}

            if (m_id[2] == int(RenderUtils::INVALID_UNIFORM_LOCATION))
			{
				std::cout << "Invalid: " << 2 << std::endl;
			}

            if (m_id[3] == int(RenderUtils::INVALID_UNIFORM_LOCATION))
			{
				std::cout << "Invalid: " << 3 << std::endl;
			}
		}

		void update() override
		{
			glUniform3fv(m_id[0], 1, &(m_dataPointer->direction[0]));
			glUniform3fv(m_id[1], 1, &(m_dataPointer->color[0]));
			glUniform1fv(m_id[2], 1, &(m_dataPointer->ambientIntensity));
			glUniform1fv(m_id[3], 1, &(m_dataPointer->diffuseIntensity));
		}

		~Uniform() override
		{
			delete[] m_id;
		}

	private:
		GLuint m_program;
        GLint* m_id;
		std::string m_name;
		DirectionalLight* m_dataPointer;
	};

    template<>
    class Uniform<PointLight> : public UniformBase
    {
    public:
        Uniform(GLuint program, const std::string& name, PointLight* pointer)
            : m_program(program),
              m_name(name),
              m_dataPointer(pointer)
        {
            m_id = new GLint[7];

            std::string dirStr = name + ".Position";
            std::string colorStr = name + ".Base.Color";
            std::string ambStr = name + ".Base.AmbientIntensity";
            std::string diffStr = name + ".Base.DiffuseIntensity";
            std::string constStr = name + ".Atten.constant";
            std::string linearStr = name + ".Atten.linear";
            std::string expStr = name + ".Atten.exp";
            m_id[0] = glGetUniformLocation(m_program, dirStr.c_str());
            m_id[1] = glGetUniformLocation(m_program, colorStr.c_str());
            m_id[2] = glGetUniformLocation(m_program, ambStr.c_str());
            m_id[3] = glGetUniformLocation(m_program, diffStr.c_str());
            m_id[4] = glGetUniformLocation(m_program,constStr.c_str());
            m_id[5] = glGetUniformLocation(m_program, linearStr.c_str());
            m_id[6] = glGetUniformLocation(m_program, expStr.c_str());

            glUniform3fv(m_id[0], 1, &(m_dataPointer->position[0]));
            glUniform3fv(m_id[1], 1, &(m_dataPointer->color[0]));
            glUniform1fv(m_id[2], 1, &(m_dataPointer->ambientIntensity));
            glUniform1fv(m_id[3], 1, &(m_dataPointer->diffuseIntensity));
            glUniform1fv(m_id[4], 1, &(m_dataPointer->attenuation.constant));
            glUniform1fv(m_id[5], 1, &(m_dataPointer->attenuation.linear));
            glUniform1fv(m_id[6], 1, &(m_dataPointer->attenuation.exp));

        }

        void update() override
        {
            glUniform3fv(m_id[0], 1, &(m_dataPointer->position[0]));
            glUniform3fv(m_id[1], 1, &(m_dataPointer->color[0]));
            glUniform1fv(m_id[2], 1, &(m_dataPointer->ambientIntensity));
            glUniform1fv(m_id[3], 1, &(m_dataPointer->diffuseIntensity));
            glUniform1fv(m_id[4], 1, &(m_dataPointer->attenuation.constant));
            glUniform1fv(m_id[5], 1, &(m_dataPointer->attenuation.linear));
            glUniform1fv(m_id[6], 1, &(m_dataPointer->attenuation.exp));
        }

        ~Uniform() override
        {
            delete[] m_id;
        }

    private:
        GLuint m_program;
        GLint* m_id;
        std::string m_name;
        PointLight* m_dataPointer;
    };


}

#endif //UNIFORM_H
