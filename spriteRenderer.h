#ifndef SPRITE_RENDERER_H
#define SPRITE_RENDERER_H

#include "include/glad/glad.h"
#include "include/glm/glm.hpp"
#include "include/glm/gtc/matrix_transform.hpp"

#include "shader.h"
#include "texture.h"

class SpriteRenderer
{
public: 
    SpriteRenderer(Shader shader);
    ~SpriteRenderer();

    void drawSprite(Texture2D texture, glm::vec2 position, glm::vec2 size = glm::vec2(10.0f, 10.0f), float rotate = 0.0f, glm::vec3 colour = glm::vec3(1.0f));
private:
    Shader shader; 
    unsigned int quadVAO; 
    void initRenderData();
};

#endif  