#ifndef SHADER_HPP
#define SHADER_HPP

#include <scop.hpp>

class Shader
{
    public:
        unsigned int ID;

        Shader(const char *vertexPath, const char *fragmentPath);
        ~Shader();
        unsigned int getID();
        void use();
        void setBool(const std::string &name, bool value) const;
        void setInt(const std::string &name, int value) const;
        void setFloat(const std::string &name, float value) const;
};

#endif
