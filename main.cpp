#include <SFML/Graphics.hpp>
#include <SFML/Main.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Config.hpp>
#include <SFML/Audio.hpp>
#include <time.h>
#include <SFML/OpenGL.hpp>
#include <iostream>
#include <cstdlib>
#include <string>

using namespace std;

bool check_oob(sf::Sprite spr)
{
    if (spr.getPosition().x >= 750 || spr.getPosition().x <= 0 || spr.getPosition().x + 40 >= 750 || spr.getPosition().x - 40 <= 0 || spr.getPosition().y + 50 >= 480)
    {
        return true;
    }
    return false;
}

bool check_ball_poss(sf::CircleShape shape, sf::Sprite spr)
{
    if (spr.getGlobalBounds().intersects(shape.getGlobalBounds()))
    {
        return true;
    }
    return false;
}

bool check_ground(sf::Sprite spr)
{
    if (spr.getPosition().y < 340)
    {
        return false;
    }
    return true;
}

// bool check_ball_hit(sf::CircleShape shape, sf::RectShape crt, sf::Sprite spr, sf::Sprite, spr)
// {
// }

void run_game()
{
    string name1, name2;
    cout << "Enter Names" << endl;
    cin >> name1;
    cin >> name2;
    sf::RenderWindow game_window(sf::VideoMode(750, 480), "Gameplay");
    sf::Text player_1_text;
    sf::Text player_2_text;
    sf::Text score_1_text;
    int score_1 = 0;
    sf::Text score_2_text;
    int score_2 = 0;

    sf::Texture player_1_texture;
    sf::Texture hoop_texture;
    sf::CircleShape ball(10);
    ball.setFillColor(sf::Color(250, 150, 100));

    if (!player_1_texture.loadFromFile("/Users/aadrijupadya/Downloads/player_new.png"))
    {
        cout << "Error loading texture" << endl;
    }

    if (!hoop_texture.loadFromFile("/Users/aadrijupadya/Downloads/hoop.png"))
    {
        cout << "Error loading texture" << endl;
    }

    sf::Sprite player_1_image;
    sf::Sprite player_2_image;

    sf::Sprite left_hoop;
    sf::Sprite right_hoop;

    sf::Texture background;
    sf::RectangleShape court;

    sf::Font font;
    sf::Keyboard keys;
    sf::Event event;
    bool p1_left = false, p2_left = false, p1_right = false, p2_right = false;

    float gravity = 0.0001f;
    float jumpvel = -0.15f;
    float yvel_1 = 0, yvel_2 = 0;
    const float maxY = 330;
    const float max_ballY = 215;
    float ballvel = 0.03f;
    bool jump_1 = false,
         jump_2 = false;
    bool player_1_poss = false, player_2_poss = false;
    bool collisionOccurred = false;

    if (!font.loadFromFile("/Users/aadrijupadya/Downloads/roboto/Roboto-Medium.ttf"))
    {
        cout << "Error loading fonts" << endl;
    }
    cout << to_string(score_1) << endl;

    score_1_text.setFont(font);
    score_1_text.setString(to_string(score_1));
    score_1_text.setCharacterSize(20);
    score_1_text.setFillColor(sf::Color::Red);
    score_1_text.setStyle(sf::Text::Bold);
    score_1_text.setPosition(565.f, 20.f);

    score_2_text.setFont(font);
    score_2_text.setString(to_string(score_2));
    score_2_text.setCharacterSize(20);
    score_2_text.setFillColor(sf::Color::Blue);
    score_2_text.setStyle(sf::Text::Bold);
    score_2_text.setPosition(700.f, 20.f);

    player_1_text.setFont(font);
    player_1_text.setString(name1);
    player_1_text.setCharacterSize(20);
    player_1_text.setFillColor(sf::Color::Red);
    player_1_text.setStyle(sf::Text::Bold);
    player_1_text.setPosition(465.f, 20.f);

    player_2_text.setFont(font);
    player_2_text.setString(name2);
    player_2_text.setCharacterSize(20);
    player_2_text.setFillColor(sf::Color::Blue);
    player_2_text.setStyle(sf::Text::Bold);
    player_2_text.setPosition(600.f, 20.f);

    player_1_image.setTexture(player_1_texture);
    player_1_image.scale(0.2, 0.22f);
    player_1_image.setPosition(250, 340);

    player_2_image.setTexture(player_1_texture);
    player_2_image.scale(-0.2f, 0.22f);
    player_2_image.setPosition(500, 340);

    left_hoop.setTexture(hoop_texture);
    left_hoop.scale(0.2, 0.2);
    left_hoop.setPosition(-50, 70);

    right_hoop.setTexture(hoop_texture);
    right_hoop.scale(-0.2, 0.2);
    right_hoop.setPosition(800, 70);

    ball.setPosition(360, 280);

    court.setSize(sf::Vector2f(750, 30));
    court.setPosition(0.f, 450.f);
    court.setFillColor(sf::Color(150, 75, 0));

    while (game_window.isOpen())
    {
        // p1_left = false;
        // p1_right = false;
        // p2_left = false;
        // p2_right = false;
        while (game_window.pollEvent(event))
        {
            // std::cout << "Here is the game" << std::endl;

            if (event.type == sf::Event::Closed)
            {
                game_window.close();
            }
            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Right)
                {
                    p2_right = true;
                }

                if (event.key.code == sf::Keyboard::Left)
                {
                    p2_left = true;
                }

                if (event.key.code == sf::Keyboard::A)
                {
                    p1_left = true;
                }

                if (event.key.code == sf::Keyboard::D)
                {
                    p1_right = true;
                }
                if (event.key.code == sf::Keyboard::W)
                {
                    if (!(check_ground(player_1_image)))
                    {
                        jump_1 = false;
                    }
                    else
                    {
                        yvel_1 = jumpvel;
                        jump_1 = true;
                    }
                }
                if (event.key.code == sf::Keyboard::Up)
                {
                    if (!(check_ground(player_2_image)))
                    {
                        jump_2 = false;
                    }
                    else
                    {
                        yvel_2 = jumpvel;
                        jump_2 = true;
                    }
                }
            }
            else if (event.type == sf::Event::KeyReleased)
            {
                if (event.key.code == sf::Keyboard::Left)
                {
                    p2_left = false;
                }
                else if (event.key.code == sf::Keyboard::Right)
                {
                    p2_right = false;
                }

                if (event.key.code == sf::Keyboard::A)
                {
                    p1_left = false;
                }
                else if (event.key.code == sf::Keyboard::D)
                {
                    p1_right = false;
                }
                else if (event.key.code == sf::Keyboard::W)
                {
                    jump_1 = false;
                }
                else if (event.key.code == sf::Keyboard::Up)
                {
                    jump_2 = false;
                }
            }
        }
        if (p1_right)
        {
            if (!(check_oob(player_1_image)))
            {
                player_1_image.move(0.05, 0);
            }
            else
            {
                player_1_image.setPosition(player_1_image.getPosition().x - 10, 330);
            }
        }
        if (p1_left)
        {
            if (!(check_oob(player_1_image)))
            {
                cout << player_1_image.getPosition().x;
                player_1_image.move(-0.05, 0);
            }
            else
            {
                cout << "ok" << endl;
                player_1_image.setPosition(player_1_image.getPosition().x + 10, 330);
            }
        }
        if (p2_right)
        {
            if (!(check_oob(player_2_image)))
            {
                player_2_image.move(0.05, 0);
            }
            else
            {
                player_2_image.setPosition(player_2_image.getPosition().x - 10, 330);
            }
        }
        if (p2_left)
        {
            if (!(check_oob(player_2_image)))
            {
                player_2_image.move(-0.05, 0);
            }
            else
            {
                cout << "aight" << endl;
                player_2_image.setPosition(player_2_image.getPosition().x + 10, 330);
            }
        }
        player_1_image.move(0, yvel_1);
        player_2_image.move(0, yvel_2);

        if (jump_1)
        {
            if (!(check_ground(player_1_image)))
            {
                yvel_1 += gravity;
            }
            else if ((player_1_image.getPosition().y <= maxY))
            {
                jump_1 = false;
                yvel_1 = 0;
            }
        }
        else
        {
            if (!(check_ground(player_1_image)))
            {
                yvel_1 += gravity;
            }
            else
            {
                yvel_1 = 0;
            }
        }

        if (jump_2)
        {
            if (!(check_ground(player_2_image)))
            {
                yvel_2 += gravity;
            }
            else if ((player_2_image.getPosition().y <= maxY))
            {
                jump_2 = false;
                yvel_2 = 0;
            }
        }
        else
        {
            if (!(check_ground(player_2_image)))
            {
                yvel_2 += gravity;
            }
            else
            {
                yvel_2 = 0;
            }
        }
        if (check_ball_poss(ball, player_1_image) && !player_2_poss)
        {
            ball.setPosition(player_1_image.getPosition().x + 60, player_1_image.getPosition().y + 50);
            player_1_poss = true;
        }
        if (check_ball_poss(ball, player_2_image) && !player_1_poss)
        {
            ball.setPosition(player_2_image.getPosition().x - 60, player_2_image.getPosition().y + 50);
            player_2_poss = true;
        }
        // if (!player_1_poss && !player_2_poss)
        // {
        //     ballvel = 0.01f;
        // }
        if ((ball.getGlobalBounds().intersects(court.getGlobalBounds()) && !collisionOccurred) || ball.getPosition().y <= max_ballY)
        {
            ballvel = -ballvel;
            // cout << ballvel << endl;
            collisionOccurred = true;
        }
        else if (!ball.getGlobalBounds().intersects(court.getGlobalBounds()))
        {
            collisionOccurred = false;
        }
        if (!player_1_poss && !player_2_poss)
        {
            ball.move(0, ballvel);
        }

        game_window.clear();
        game_window.draw(player_1_text);
        game_window.draw(player_2_text);
        game_window.draw(score_1_text);
        game_window.draw(score_2_text);
        game_window.draw(player_1_image);
        game_window.draw(player_2_image);
        game_window.draw(court);

        game_window.draw(left_hoop);
        game_window.draw(right_hoop);
        game_window.draw(ball);
        game_window.display();
    }
}

void start_screen()
{
    sf::RenderWindow window(sf::VideoMode(640, 480), "Fantastical Basketball");
    sf::RectangleShape left_button;
    sf::RectangleShape right_button;
    sf::Text opening_text;
    sf::Text left_text;
    sf::Text right_text;
    sf::Texture logo_texture;
    sf::Sprite logo;

    sf::Texture background;
    sf::Font font;
    sf::Keyboard keys;
    sf::Event event;

    if (!font.loadFromFile("/Users/aadrijupadya/Downloads/roboto/Roboto-Medium.ttf"))
    {
        cout << "Error loading fonts" << endl;
    }

    if (!logo_texture.loadFromFile("/Users/aadrijupadya/Downloads/logo.png"))
    {
        cout << "Error loading image" << endl;
    }

    left_button.setSize(sf::Vector2f(150, 50));
    left_button.setPosition(80.f, 100.f);
    left_button.setFillColor(sf::Color::White);

    right_button.setSize(sf::Vector2f(150, 50));
    right_button.setPosition(400.f, 100.f);
    right_button.setFillColor(sf::Color::White);

    left_text.setFont(font);
    left_text.setString("Play");
    left_text.setCharacterSize(30);
    left_text.setFillColor(sf::Color::Red);
    left_text.setStyle(sf::Text::Bold);
    left_text.setPosition(120.f, 100.f);

    right_text.setFont(font);
    right_text.setString("Rules");
    right_text.setCharacterSize(30);
    right_text.setFillColor(sf::Color::Red);
    right_text.setStyle(sf::Text::Bold);
    right_text.setPosition(440.f, 100.f);

    opening_text.setFont(font);
    opening_text.setString("Fantastical Basketball");
    opening_text.setCharacterSize(20);
    opening_text.setFillColor(sf::Color::White);
    opening_text.setStyle(sf::Text::Bold);
    opening_text.setPosition(200.f, 20.f);

    logo.setTexture(logo_texture);
    logo.setPosition(400.f, 260.f);
    while (window.isOpen())
    {
        sf::Event event;

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::MouseButtonPressed)
            {
                if ((event.mouseButton.x <= 230) && (event.mouseButton.x >= 80) && (event.mouseButton.y >= 200) && (event.mouseButton.y <= 250))
                {
                    run_game();
                }
                else if ((event.mouseButton.x <= 550) && (event.mouseButton.x >= 400) && (event.mouseButton.y >= 200) && (event.mouseButton.y <= 250))
                {
                    sf::RenderWindow rules_window(sf::VideoMode(500, 600), "Rules");

                    while (rules_window.isOpen())
                    {
                        while (rules_window.pollEvent(event))
                        {
                            if (event.type == sf::Event::Closed)
                                rules_window.close();
                        }
                        rules_window.clear();

                        rules_window.display();
                    }
                }
            }
        }

        window.clear();
        window.draw(left_button);
        window.draw(right_button);
        window.draw(opening_text);
        window.draw(left_text);
        window.draw(right_text);
        window.display();
    }
}

int main()
{
    start_screen();
    return 0;
}
