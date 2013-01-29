//
//  TextureLoader.cpp
//  ParticleSystem
//
//  Created by Patrick Stapfer on 28.01.13.
//  Copyright (c) 2013 Patrick Stapfer. All rights reserved.
//

#include "TextureLoader.h"
#include <FreeImagePlus.h>

TextureLoader::TextureLoader(const char* texture_directory) : m_texture_directory(texture_directory), m_texture_map()
{
    ;
}

TextureLoader::~TextureLoader()
{
    std::map<const std::string, GLuint>::iterator iter;
    
    for(iter=m_texture_map.begin(); iter != m_texture_map.end(); ++iter)
    {
        //Delete the OpenGL allocated texture
        glDeleteTextures(1, &iter->second);
    }
}

GLuint TextureLoader::loadTexture(const std::string texture_name)
{
    //If the texture is already loaded, do nothing
    if(isTextureLoaded(texture_name))
    {
        return getTexture(texture_name);
    }
    
    //Getting the path of the texture
    const std::string path = std::string(m_texture_directory) + "/" + texture_name;
    
    //Detect the fileformat and load the image
    FREE_IMAGE_FORMAT formato = FreeImage_GetFileType(path.c_str(), 0);
    FIBITMAP* imagen = FreeImage_Load(formato, path.c_str());
    
    FIBITMAP* temp = imagen;
    imagen = FreeImage_ConvertTo32Bits(imagen);
    FreeImage_Unload(temp);
    
    int width = FreeImage_GetWidth(imagen);
    int height = FreeImage_GetHeight(imagen);
    
    GLubyte* textura = new GLubyte[4*width*height];
    char* pixeles = (char*)FreeImage_GetBits(imagen);
    
    //FreeImage loads in BGR format, so you need to swap some bytes(Or use GL_BGR).
    for(int j= 0; j<width*height; j++){
        textura[j*4+0]= pixeles[j*4+2];
        textura[j*4+1]= pixeles[j*4+1];
        textura[j*4+2]= pixeles[j*4+0];
        textura[j*4+3]= pixeles[j*4+3];
    }
    
    GLuint tmpIndex; // temporary index to old the place of our texture
    
    //Allocate memory for one texture
    glGenTextures(1, &tmpIndex);
    
    //Add the index of our newly created texture to the map
    m_texture_map.insert(std::pair<const std::string, GLuint>(texture_name, tmpIndex));
    
    //Use the new texture
    glBindTexture(GL_TEXTURE_2D, tmpIndex);
    gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, width , height, GL_RGBA, GL_UNSIGNED_BYTE, textura); // genereate MipMap levels for our texture
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); // give the best result for texture magnification
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); //give the best result for texture minification
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP); // don't repeat texture
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP); // don't repeat texture
    
    //Check for errors
    GLenum huboError = glGetError();
    if(huboError){
        std::cerr << "There was an error loading texture with path: '" << path << "'" << std::endl;
    }
    
    return tmpIndex;
}

void TextureLoader::unloadTexture(const std::string texture_name)
{
    //Get the key
    GLuint toUnload = getTexture(texture_name);
    
    //Only delete if there is a key-value-pair to delete
    if(toUnload > 0)
    {
        //Delete the OpenGL allocated texture
        glDeleteTextures(1, &toUnload);
        
        //Remove the key-value-pair from the map
        m_texture_map.erase(texture_name);
    }
    
    
}

bool TextureLoader::isTextureLoaded(const std::string texture_name)
{
    return m_texture_map.find(texture_name) != m_texture_map.end();
}

GLuint TextureLoader::getTexture(const std::string texture_name)
{
    std::map<const std::string, GLuint>::iterator iter = m_texture_map.find(texture_name);
    
    //Only return a value if there is an entry with the given texture_name
    if(iter != m_texture_map.end())
    {
        return m_texture_map.find(texture_name)->second;
    }
    
    return 0;
}