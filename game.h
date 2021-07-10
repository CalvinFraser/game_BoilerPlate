#ifndef GAME_H
#define GAME_H

#include<algorithm>

#include "include/glad/glad.h"
#include "include/GLFW/glfw3.h"

#include "resourceManager.h"
#include "spriteRenderer.h"
#include <vector>
#include <iostream>
#include "ballObject.h"
#include "Particle_Gen.h"
#include "textRenderer.h"

enum GameState {GAME_ACTIVE, GAME_MENU, GAME_WIN};
enum Direction {UP, RIGHT, DOWN, LEFT};
class Game
{
public: 
        GameState state; 
        bool keys[1024];
        bool KeysProcessed[1024];
        unsigned int Width, Height; 
        SpriteRenderer  *Renderer;

        GameObject *Sprite; 
        TextRenderer *Text;        
        ParticleGenerator *Particles; 
        typedef std::tuple<bool, Direction, glm::vec2> Collision; 

        Game(unsigned int width, unsigned int height);
        ~Game();

        void init(); 
        void processInput(float dt);
        void update(float dt);
        void render();
        void doCollisions(float dt);

private:
        const glm::vec2 SPIRTE_SIZE = glm::vec2(100.0f, 100.0f);
        const float PLAYER_VELOCITY = 500.0f;
        const float rotation = 0.0f; 
        Collision CheckCollision(BallObject &one, GameObject &two);
        Direction VectorDirection(glm::vec2 target);


};

#endif 