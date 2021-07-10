#ifndef PARTICLEGEN_H
#define PARTICLEGEN_H
#include <vector>


#include "include/glm/glm.hpp"
#include "include/glad/glad.h"

#include "shader.h"
#include "texture.h"
#include "gameObject.h"

//Represents a single particle 
struct Particle
{
    glm::vec2 Position, Velocity;
    glm::vec4 Colour; 
    float Life; 

    Particle() : Position(0.0f), Velocity(0.0f), Colour(1.0f), Life(0.0f) {}

};

//Controls the particles attached to an object. Repeatedly spawns and respawns particles from a set pool. 
class ParticleGenerator
{
public: 
        ParticleGenerator(Shader shader, Texture2D texture, unsigned int amount);
        void Update(float dt, GameObject &object, unsigned int newParticles, glm::vec2 offset = glm::vec2(0.0f, 0.0f));

        void Draw();
private:
        //State : Stores all particles 
        std::vector<Particle> Particles; 
        unsigned int amount; 

        //Render state
        Shader shader; 
        Texture2D texture; 
        unsigned int VAO; 

        void init();
        //Retrieves the first unused particle in Particles so it can be respawned 
        unsigned int firstUnusedParticle();

        //respawns a particle if its life has expired 
        void respawnParticle(Particle &particle, GameObject &object,glm::vec2 offset = glm::vec2(0.0f, 0.0f));
};

#endif 