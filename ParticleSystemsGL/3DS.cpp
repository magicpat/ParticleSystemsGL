/*
 Program name:Combat of Death
 Description source file: this class loads 3ds models
 Copyright (C) 2005  Hylke Donker
 
 This program is free software; you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation; either version 2 of the License, or
 (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with this program; if not, write to the Free Software
 Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA
 */

/**
 \file 3DS.cpp
 \brief The cpp file of 3DS.h
 
 This is the place were all the functions are 'defined'
 */

#include "3DS.h"
#include "gl_math.h"
#include <FreeImagePlus.h>

// constructor, enables and set properties of texture coordinate generation and set the current frame
Model::Model(TextureLoader* texture_loader) : curFrame(0), lightEnabled(glIsEnabled(GL_LIGHTING)), m_texture_loader(texture_loader)
{
    ;
}

// destructor, free up memory and disable texture generation
Model::~Model()
{
    //If the file isn't freed yet
	if(file)
    {
		lib3ds_file_free(file);
    }
    
    //Disable texture generation
	for(unsigned int i = 0;i < textureIndices.size();i++)
    {
		glDeleteTextures(1, &textureIndices.at(i));
    }
}

// load the model, and if the texture has textures, then apply them on the geometric primitives
void Model::loadFile(const char *name)
{
    //Set the internal filename
	filename = name;
    
    //Set full path of filename
    m_file_path = std::string(filename); //TODO: Seems like filename equals filepath, still do a seperate instance variable
    
    //Set full path of file folder
    size_t last = m_file_path.find_last_of('/');
    m_folder_path = m_file_path.substr(0,last+1);
	
    //Try to load file
	file = lib3ds_file_load(filename);
    
    //If the file could not be loaded - report and exit
	if(!file)
	{
        std::string event = "Error loading: ";
        std::string online = "On line 61 in file ";
		online.append(__FILE__);
		event.append(filename);
        std::cout << event << std::endl;
        std::cout << online << std::endl;
		exit(1);
	}
    
    //Set current frame to 0
	lib3ds_file_eval(file, 0);
    
	//Apply texture to all meshes that have texels
	Lib3dsMesh *mesh;
	for(mesh = file->meshes;mesh != 0;mesh = mesh->next)
	{
        //If there's texels for the mesh
		if(mesh->texels)
        {
			applyTexture(mesh); //then apply texture to it
        }
	}
    
    //If there is light
	if(file->lights)
    {
		createLightList();
    }
}

void Model::createLightList()
{
	lightListIndex = glGenLists(1);
	glNewList(lightListIndex, GL_COMPILE_AND_EXECUTE);
	Lib3dsLight *light; // temporary variable to store our lights
	GLint curlight = GL_LIGHT0;
	for(light = file->lights;light != 0;light = light->next)
	{
		if(light->off) //if our light is off
			continue; //Move to the next light
        
		GLfloat diff[4], amb[4], pos[4];
        
		for(int j = 0;j < 3;j++)
		{
			diff[j] = light->color[j];
			amb[j] = light->color[j] / 4.5; // We might wanna change this;
			pos[j] = light->position[j];
		}
        
		diff[3] = amb[3] = pos[3] = 1.0;
        
		curlight++;
		// Start setting light
		glLightfv(GL_LIGHT0, GL_DIFFUSE, diff); //set the diffuse color
		glLightfv(GL_LIGHT0, GL_POSITION, pos); //set the position of the light
		glLightfv(GL_LIGHT0, GL_AMBIENT, amb); // set the ambient color of the light
		glLightfv(GL_LIGHT0, GL_SPECULAR, diff); // set the specular color of the light
        
		if(light->spot) // if it's a light spot
		{
			for(int i = 0;i < 3;i++) // get position of the light
				pos[i] = light->spot[i] - light->position[i];
			pos[3] = light->spot[2] - light->position[2]; //TODO: Check if this code works because before, there was light->position[3] with a warning
			glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, pos); //specify that we have a spot at position 'pos'
		}
	}
	glEndList();
}

// what is basicly does is, set the properties of the texture for our mesh
void Model::applyTexture(Lib3dsMesh *mesh)
{    
    for(unsigned int i = 0;i < mesh->faces;i++)
	{
		Lib3dsFace *f = &mesh->faceL[i];
		if(! f->material[0])
			continue;
        
		Lib3dsMaterial *mat;
		
		mat = lib3ds_file_material_by_name(file, f->material);
        
        
        
        bool found = false;
		for(unsigned int i = 0;i < textureFilenames.size();i++)
		{
			if(strcmp(mat->texture1_map.name, textureFilenames.at(i).c_str()) == 0)
			{
				textureIndices.push_back(textureIndices.at(i));
				textureFilenames.push_back(mat->texture1_map.name);
				found = true;
				break;
			}
		}
		if(!found)
		{
            GLuint tmpIndex = m_texture_loader->loadTexture(mat->texture1_map.name, m_folder_path);
            textureIndices.push_back(tmpIndex);
		}
	}    
}

// this code is rewritten from player.c example that came with lib3ds
// what it does is render a node from our model
void Model::renderNode(Lib3dsNode *node)
{
	ASSERT(file); //this is for debugging
	{
		Lib3dsNode *tmp;
		for(tmp = node->childs;tmp != 0;tmp = tmp->next)
        {
			renderNode(tmp); //render all child nodes of this note
        }
	}
    
    //Check wheter the node is a 3ds node
	if(node->type == LIB3DS_OBJECT_NODE) 
	{
        //Wheter we have a list or not, if not we're gonna create one
		if(!node->user.d) 
		{
            //Get all the meshes of the current node
			Lib3dsMesh *mesh = lib3ds_file_mesh_by_name(file, node->name);
            
            //For debugging in case we don't have a mesh
            ASSERT(mesh);
            
			if(!mesh)
            {
				return;
            }
            
            //Allocate memory for one list
			node->user.d = glGenLists(1);
			
            //Check for node errors
			if(glGetError() != GL_NO_ERROR)
			{
                std::cout << "ERROR while rendering Node!\n" << std::endl;
                //TODO: Logging?
			}
			
			glNewList(node->user.d, GL_COMPILE); //here we create our list
			{
				unsigned p;
				Lib3dsVector *normals;
                
                //Allocate memory for our normals
				normals = static_cast<float(*)[3]> (std::malloc (3*sizeof(Lib3dsVector)*mesh->faces)); 
				{
					Lib3dsMatrix m;
                    
                    //Copy the matrix of the mesh in our temporary matrix
					lib3ds_matrix_copy(m, mesh->matrix);
					lib3ds_matrix_inv(m);
                    
                    //Adjust our current matrix to the matrix of the mesh
					glMultMatrixf(&m[0][0]); 
				}
                
                //Calculate the normals of the mesh
				lib3ds_mesh_calculate_normals(mesh, normals); 
				int j = 0;
				for(p = 0; p < mesh->faces; p++)
				{
					Lib3dsFace *f = &mesh->faceL[p];
					Lib3dsMaterial *mat=0;
                    
                    //If the face of the mesh has material properties
					if(f->material[0])
                    {
						mat = lib3ds_file_material_by_name(file, f->material); //read material properties from file
                    }
                    
                    //If we have material
					if(mat)
					{
						static GLfloat ambient[4] = { 0.0, 0.0, 0.0, 1.0 };
						
                        glMaterialfv(GL_FRONT, GL_AMBIENT, ambient); // Ambient color
						glMaterialfv(GL_FRONT, GL_DIFFUSE, mat->diffuse); //diffuse color
						glMaterialfv(GL_FRONT, GL_SPECULAR, mat->specular); //specular color
                        
						float shine;
						shine = pow(2, 10.0 * mat->shininess);
						
                        if(shine > 128.0)
                        {
							shine = 128.0;
                        }
						glMaterialf(GL_FRONT, GL_SHININESS, shine);
					}
                    
                    //If we do not have material properties, we have to set them manually
					else 
					{
						GLfloat diff[4] = { 0.75, 0.75, 0.75, 1.0 }; // color: white/grey
						GLfloat amb[4] = { 0.25, 0.25, 0.25, 1.0 }; //color: black/dark gray
						GLfloat spec[4] = { 0.0, 0.0, 0.0, 1.0 }; //color: completly black
                        
						glMaterialfv(GL_FRONT, GL_DIFFUSE, diff);
						glMaterialfv(GL_FRONT, GL_AMBIENT, amb);
						glMaterialfv(GL_FRONT, GL_AMBIENT, spec);
					}
                    
					{
						if(mesh->texels)
						{
							glBindTexture(GL_TEXTURE_2D, textureIndices.at(j));
							j++;
						}
						glBegin(GL_TRIANGLES);
						for(int i = 0;i < 3;i++)
						{
							glNormal3fv(normals[3*p+i]); //set normal vector of that point
							if(mesh->texels)
                            {
								glTexCoord2f(mesh->texelL[f->points[i]][0], mesh->texelL[f->points[i]][1]);
                            }
							glVertex3fv(mesh->pointL[f->points[i]].pos); //Draw the damn triangle
						}
						glEnd();
					}
				}
                
                //Free up memory
				free(normals); 
			}
            
            //End of list
			glEndList();
		}
        
        //If we have created a link list (with glNewList)
		if(node->user.d) 
		{
			Lib3dsObjectData *tmpdat;
			glPushMatrix(); 
                //Get the position data
                tmpdat = &node->data.object;
            
                //Adjust matrix according to the node
                //glMultMatrixf(&node->matrix[0][0]);
            
                //Move to the right place;
                glTranslatef(-tmpdat->pivot[0], -tmpdat->pivot[1], -tmpdat->pivot[2]);
            
            
                //Render node
                glCallList(node->user.d); 
			glPopMatrix(); 
		}
	}
}

// this function actually renders the model at place (x, y, z) and then rotated around the y axis by 'angle' degrees
void Model::renderModel()
{
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glShadeModel(GL_SMOOTH);
    
	if(file->lights) //if we have lights in the model
	{
		enableLights(); //enable all lights
		glCallList(lightListIndex); //set lights.
	}
    
	Lib3dsNode *nodes;
	for(nodes = file->nodes;nodes != 0;nodes = nodes->next) // Render all nodes
		renderNode(nodes);
    
    
	if(file->lights)
		disableLights(); // disable lighting, we don't want it have it enabled longer than necessary
    
	curFrame++;
	if(curFrame > file->frames) //if the next frame doesn't exist, go to frame 0
		curFrame = 0;
	lib3ds_file_eval(file, curFrame); // set current frame
    
	glDisable(GL_CULL_FACE);
	glShadeModel(GL_FLAT);
}

void Model::enableLights()
{
	glEnable(GL_LIGHTING);
	GLuint lightNum = GL_LIGHT0;
	Lib3dsLight *light;
	for(light = file->lights;light != 0;light = light->next)
	{
		if(!glIsEnabled(lightNum))
			glEnable(lightNum);
		lightNum++;
	}
}

void Model::disableLights()
{
	glDisable(GL_LIGHTING);
	GLuint lightNum = GL_LIGHT0;
	Lib3dsLight *light;
	for(light = file->lights;light != 0;light = light->next)
	{
		if(glIsEnabled(lightNum))
			glDisable(lightNum);
		lightNum++;
	}
}

void Model::update(double delta)
{
    ;
}

void Model::draw()
{
    glPushMatrix();
    glColor4f(1,1,1,1);
    glEnable(GL_TEXTURE_2D);
    Drawable::draw();
    renderModel();
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();
}

Lib3dsFile * Model::get3DSPointer()
{
	return file;
}

std::string Model::getFilename()
{
	std::string returnvalue = filename;
	return returnvalue;
}