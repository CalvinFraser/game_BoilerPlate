#include "Particle_Gen.h"

ParticleGenerator::ParticleGenerator(Shader shader, Texture2D texture, unsigned int amount) : shader(shader), texture(texture), amount(amount)
{
    init();
}

void ParticleGenerator::Update(float dt, GameObject &object, unsigned int newParticles, glm::vec2 offset)
{
    for(unsigned int i = 0; i < newParticles; ++i)
    {
        int unusedParticle = firstUnusedParticle();
        respawnParticle(Particles[unusedParticle], object, offset);
    }

    for(unsigned int i = 0; i < amount; ++i)
    {
        Particle &p = Particles[i];
        p.Life -= dt;
        if(p.Life > 0.0f)
        {
            p.Position -= p.Velocity * dt; 
            p.Colour.a -= dt *2.5f; 
        } 
    }
}

void ParticleGenerator::Draw()
{
    glBlendFunc(GL_SRC_ALPHA, GL_ONE);
    shader.Use();

    for(Particle particle : Particles)
    {
        shader.SetVector2f("offset", particle.Position);
        shader.SetVector4f("color", particle.Colour);
        texture.Bind();

        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 6);
        glBindVertexArray(0);
    }

    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void ParticleGenerator::init()
{
        unsigned int VBO;
    float particle_quad[] = {
        0.0f, 1.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 0.0f,

        0.0f, 1.0f, 0.0f, 1.0f,
        1.0f, 1.0f, 1.0f, 1.0f,
        1.0f, 0.0f, 1.0f, 0.0f
    }; 
    
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(particle_quad), particle_quad, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
    glBindVertexArray(0);
    

    //Init default particles 
     for(unsigned int i = 0; i < amount; ++i)
     {
         Particles.push_back(Particle());
     }
}


unsigned int lastUsedParticle = 0; 
unsigned int ParticleGenerator::firstUnusedParticle()
{
    for(unsigned int i = lastUsedParticle; i < amount; ++i)
    {
        if(Particles[i].Life <= 0.0f)
        {
            lastUsedParticle = i; 
            return i; 
        }
    }

    for(unsigned int i = 0; i < lastUsedParticle; ++i)
    {
        if(Particles[i].Life <= 0.0f)
        {
            lastUsedParticle = i; 
            return i; 
        }
    }

    lastUsedParticle = 0; 
    return 0; 
}


void ParticleGenerator::respawnParticle(Particle &particle, GameObject &object,glm::vec2 offset)
{
    float random = ((rand() % 100) - 50) / 10.0f; 
    float rColour = 0.5f + ((rand() % 100) / 100.0f);
    particle.Position = object.Position + random + offset; 
    particle.Colour = glm::vec4(rColour, rColour, rColour, 1.0f); 
    particle.Life = 1.0f; 
    particle.Velocity = object.Velocity * 0.1f; 
}