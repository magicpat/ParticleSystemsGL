//
//  ShaderLoader.h
//  ParticleSystemsGL
//
//  Created by Patrick Stapfer on 06.02.13.
//  Copyright (c) 2013 Patrick Stapfer. All rights reserved.
//

#ifndef __ParticleSystemsGL__ShaderLoader__
#define __ParticleSystemsGL__ShaderLoader__

#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <vector>
#include <string>
#include "LOpenGL.h"

class ShaderLoader
{
public:
    ShaderLoader();
    ShaderLoader(const std::string shader_directory);
    
    //type: GL_VERTEX_SHADER | GL_FRAGMENT_SHADER
    GLuint compileFile(GLenum type, const char *filepath);
    GLuint createProgram(const std::vector<GLuint> &shaderList);
    
private:
    const std::string m_shader_directory;
    
    
    bool shaderLoadSource(const std::string& filename, std::string& out);
};

#endif /* defined(__ParticleSystemsGL__ShaderLoader__) */
