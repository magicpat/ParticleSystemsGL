//
//  ShaderLoader.cpp
//  ParticleSystemsGL
//
//  Created by Patrick Stapfer on 06.02.13.
//  Copyright (c) 2013 Patrick Stapfer. All rights reserved.
//

#include "ShaderLoader.h"

ShaderLoader::ShaderLoader()
{
    ;
}

ShaderLoader::ShaderLoader(const std::string shader_directory) : m_shader_directory(shader_directory)
{
    ;
}

GLuint ShaderLoader::compileFile(GLenum type, const char *filepath)
{
    std::string source;
	GLuint shader;
	GLint length, result;
    
	/* get shader source */
	shaderLoadSource(filepath, source);
    
	if(source.empty())
		return 0;
    
    //Create the shader
	shader = glCreateShader(type);
    
    //Provide source for the shader and compile
	length = (GLint)source.length();
	glShaderSource(shader, 1, (const char **)&source, &length);
	glCompileShader(shader);
    
	/* make sure the compilation was successful */
	glGetShaderiv(shader, GL_COMPILE_STATUS, &result);
	if(result == GL_FALSE) {
        GLint infoLogLength;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLogLength);
        
        GLchar *strInfoLog = new GLchar[infoLogLength + 1];
        glGetShaderInfoLog(shader, infoLogLength, NULL, strInfoLog);
        
        const char *strShaderType = NULL;
        switch(type)
        {
            case GL_VERTEX_SHADER: strShaderType = "vertex"; break;
            case GL_GEOMETRY_SHADER: strShaderType = "geometry"; break;
            case GL_FRAGMENT_SHADER: strShaderType = "fragment"; break;
        }
        
        fprintf(stderr, "Compile failure in %s shader:\n%s\n", strShaderType, strInfoLog);
        delete[] strInfoLog;
	}
    
	return shader;
}

bool ShaderLoader::shaderLoadSource(const std::string& filename, std::string& out) {
    std::ifstream file;
    file.open(filename.c_str());
    
    if (!file) {
        return false;
    }
    
    std::stringstream stream;
    
    stream << file.rdbuf();
    
    file.close();
    
    out = stream.str();
    
    return true;
}

GLuint ShaderLoader::createProgram(const std::vector<GLuint> &shaderList)
{
    GLuint program = glCreateProgram();
    
    for(size_t iLoop = 0; iLoop < shaderList.size(); iLoop++)
    	glAttachShader(program, shaderList[iLoop]);
    
    glLinkProgram(program);
    
    GLint status;
    glGetProgramiv (program, GL_LINK_STATUS, &status);
    if (status == GL_FALSE)
    {
        GLint infoLogLength;
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &infoLogLength);
        
        GLchar *strInfoLog = new GLchar[infoLogLength + 1];
        glGetProgramInfoLog(program, infoLogLength, NULL, strInfoLog);
        fprintf(stderr, "Linker failure: %s\n", strInfoLog);
        delete[] strInfoLog;
    }
    
    for(size_t iLoop = 0; iLoop < shaderList.size(); iLoop++)
        glDetachShader(program, shaderList[iLoop]);
    
    return program;
}