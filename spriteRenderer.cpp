#include "spriteRenderer.h"


SpriteRenderer::SpriteRenderer(Shader Shader)
{
    shader = Shader; 
    initRenderData();
}

SpriteRenderer::~SpriteRenderer()
{
    glDeleteVertexArrays(1, &this->quadVAO);
}

void SpriteRenderer::initRenderData()
{

    unsigned int VBO; 
    float vertices[] = 
    {
        0.0f, 1.0f, 0.0f, 1.0f, 
        1.0f, 0.0f, 1.0f, 0.0f, 
        0.0f, 0.0f, 0.0f, 0.0f,

        0.0f, 1.0f, 0.0f, 1.0f, 
        1.0f, 1.0f, 1.0f, 1.0f, 
        1.0f, 0.0f, 1.0f, 0.0f  
    };
    
    glGenVertexArrays(1, &quadVAO);
    glGenBuffers(1, &VBO);
   
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    
    glBindVertexArray(quadVAO);
    
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    
}

void SpriteRenderer::drawSprite(Texture2D texture, glm::vec2 position, glm::vec2 size, float rotate, glm::vec3 colour)
{
    shader.Use();
        glm::mat4 model = {
    1.0f, 0.0f, 0.0f, 0.0f,
    0.0f, 1.0f, 0.0f, 0.0f,
    0.0f, 0.0f, 1.0f, 0.0f,
    0.0f, 0.0f, 0.0f, 1.0f
    };
    model = glm::translate(model, glm::vec3(position, 1.0f));

    //As the origin of the quad (0,0) is in the top left, this makes rotating it weird as it will rotate by that axis. 
    //Instead we translate it by half it's length and width so that rotations take place at the centre of the quad. 
    //Then translate by the inverse to ensure its back to its original place. 
    model = glm::translate(model, glm::vec3(0.5f * size.x, 0.5f * size.y, 0.0f));
    model = glm::rotate(model, glm::radians(rotate), glm::vec3(0.0f, 0.0f, 1.0f)); 
    model = glm::translate(model, glm::vec3(-0.5f * size.x, -0.5f * size.y, 0.0f));

    model = glm::scale(model, glm::vec3(size, 1.0f));
    shader.SetMatrix4("model", model);
    shader.SetVector3f("spriteColour", colour);

    glActiveTexture(GL_TEXTURE0);
    texture.Bind();
    glBindVertexArray(quadVAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);


}