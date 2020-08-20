#ifndef Player_h
#define Player_h

#include <SFML/Graphics.hpp>
#include "../Collidable.h"
#include <SFML/Audio.hpp>



    /**
        Represents the player
    */
    class Player :public Collision
    {
    public:
        constexpr static int WIDTH = 44;
        constexpr static int HEIGHT = 32;

        Player();

        void inputKeyPress();
        void update(float dt);
        void draw(sf::RenderTarget& target);           

        const sf::Vector2f& getPosition() const { return people.getPosition(); };
        void onCollide(Collision& other) override { is_Alive = false; }
     
        bool isAlive() const;

    private:
        void restart();

        sf::RectangleShape people;     
        sf::Vector2f v_speed;   
        sf::Vector2f origin_pos = { 640, 720 - 10 };

        bool is_Alive = true;        

       
    };

#endif