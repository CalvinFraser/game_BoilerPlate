#include "game.h"

Game::Game(unsigned int width, unsigned int height) : state(GAME_MENU), keys(), Width(width), Height(height)
{

}

Game::~Game() { delete Renderer; }
void Game::init()
{
    ResourceManager::LoadTexture("res/background.jpg", false, "background");
    ResourceManager::LoadTexture("res/face.png", true, "face");
    ResourceManager::LoadShader("shader/SpriteVertexShader.vs", "shader/SpriteFragmentShader.fs", nullptr, "sprite");
    glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(Width), static_cast<float>(Height), 0.0f, -1.0f, 1.0f);
    ResourceManager::GetShader("sprite").Use().SetInteger("image", 0);
    ResourceManager::GetShader("sprite").SetMatrix4("projection", projection);
    Renderer = new SpriteRenderer(ResourceManager::GetShader("sprite"));


    Text = new TextRenderer(Width, Height);
    Text->Load("fonts/OCRAEXT.TTF", 24);

    
    glm::vec2 Pos = glm::vec2(260.0f, 200.0f);
    Sprite = new GameObject(Pos, SPIRTE_SIZE, ResourceManager::GetTexture("face"));
}
void Game::update(float dt)
{
    Sprite->Rotation += 0.5;
}
    


void Game::processInput(float dt)
{

}
void Game::render()
{
    
    Renderer->drawSprite(ResourceManager::GetTexture("background"), glm::vec2(0.0f, 0.0f), glm::vec2(this->Width, this->Height), 0.0f);
    Sprite->Draw(*Renderer);
    Text->RenderText("EXAMPLE TEXT", 250.0f, Height / 2, 1.0f);
    Text->RenderText("Some more example text", 245.0f, Height / 2 + 20.0f, 0.75f);

}

void Game::doCollisions(float dt)
{
    

}





Game::Collision Game::CheckCollision(BallObject &one, GameObject &two) // AABB - Circle collision
{
    // get center point circle first 
    glm::vec2 center(one.Position + one.Radius);
    // calculate AABB info (center, half-extents)
    glm::vec2 aabb_half_extents(two.Size.x / 2.0f, two.Size.y / 2.0f);
    glm::vec2 aabb_center(two.Position.x + aabb_half_extents.x, two.Position.y + aabb_half_extents.y);
    // get difference vector between both centers
    glm::vec2 difference = center - aabb_center;
    glm::vec2 clamped = glm::clamp(difference, -aabb_half_extents, aabb_half_extents);
    // now that we know the the clamped values, add this to AABB_center and we get the value of box closest to circle
    glm::vec2 closest = aabb_center + clamped;
    // now retrieve vector between center circle and closest point AABB and check if length < radius
    difference = closest - center;

    if (glm::length(difference) < one.Radius) // not <= since in that case a collision also occurs when object one exactly touches object two, which they are at the end of each collision resolution stage.
        return std::make_tuple(true, VectorDirection(difference), difference);
    else
        return std::make_tuple(false, UP, glm::vec2(0.0f, 0.0f));
}



// calculates which direction a vector is facing (N,E,S or W)
Direction Game::VectorDirection(glm::vec2 target)
{
    glm::vec2 compass[] = {
        glm::vec2(0.0f, 1.0f),	// up
        glm::vec2(1.0f, 0.0f),	// right
        glm::vec2(0.0f, -1.0f),	// down
        glm::vec2(-1.0f, 0.0f)	// left
    };
    float max = 0.0f;
    unsigned int best_match = -1;
    for (unsigned int i = 0; i < 4; i++)
    {
        float dot_product = glm::dot(glm::normalize(target), compass[i]);
        if (dot_product > max)
        {
            max = dot_product;
            best_match = i;
        }
    }
    return (Direction)best_match;
}

