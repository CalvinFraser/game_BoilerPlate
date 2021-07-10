#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "include/glad/glad.h"
#include "include/glm/glm.hpp"

#include "texture.h"
#include "spriteRenderer.h"

class GameObject
{
public:
    glm::vec2 Position, Size, Velocity; 
    glm::vec3 Colour;
    float Rotation;
    bool IsSolid; 
    bool Destroyed;  

    Texture2D Sprite; 
    GameObject();
    GameObject(glm::vec2 pos, glm::vec2 size, Texture2D sprite, glm::vec3 colour = glm::vec3(1.0f), glm::vec2 velocity = glm::vec2(0.0f, 0.0f));

    virtual void Draw(SpriteRenderer &renderer);
};


#endif 