//
//  ShaderLoaderTests.cpp
//  ParticleSystemsGL
//
//  Created by Patrick Stapfer on 09.02.13.
//  Copyright (c) 2013 Patrick Stapfer. All rights reserved.
//

#include "ShaderLoaderTests.h"
#include "GL/glew.h"

TEST(ShaderLoaderTest, CreateInstance)
{
    ShaderLoader sl;
    sl.compileFile(GL_VERTEX_SHADER, "/Users/ps/Projects/ParticleSystemsGL/ParticleSystemsGL/shaders/vertex_shader.txt");
}