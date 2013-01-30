//
//  TextureLoader.h
//  ParticleSystem
//
//  Created by Patrick Stapfer on 28.01.13.
//  Copyright (c) 2013 Patrick Stapfer. All rights reserved.
//

#ifndef __ParticleSystem__TextureLoader__
#define __ParticleSystem__TextureLoader__

#include <iostream>
#include <map>
#include "LOpenGL.h"

class TextureLoader
{
public:
    TextureLoader(const std::string texture_directory);
    ~TextureLoader();
    
    //Forwarding method, takes the initialized texture_directory as directory parameter
    GLuint loadTexture(const std::string texture_name);
    GLuint loadTexture(const std::string texture_name, const std::string directory);
    
    
    //@texture_name: Name of the texture + extension to load
    //@directory: Folderpath to load the texture from 
    void unloadTexture(const std::string texture_name);
    bool isTextureLoaded(const std::string texture_name);
    
    GLuint getTexture(const std::string texture_name);
    
    //GETTER
    std::string getTextureDirectory() const;
    
private:
    const std::string m_texture_directory;
    std::map<const std::string, GLuint> m_texture_map;
};

#endif /* defined(__ParticleSystem__TextureLoader__) */
