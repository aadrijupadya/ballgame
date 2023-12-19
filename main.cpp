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

/**
 * @brief Calculates the velocities for a ground shoot.
 *
 * @param player The player sprite.
 * @param ball The ball circle.
 * @param hoop The hoop sprite.
 * @return vector<float> A vector containing the x and y velocities.
 */
vector<float> groundShoot(sf::Sprite player, sf::CircleShape ball, sf::Sprite hoop)
{
    float offsetX = 1.f;
    float offsetY = 80.f;

    sf::Vector2f playerPos = player.getPosition();
    sf::Vector2f hoopPos = hoop.getPosition();

    ball.setPosition(playerPos.x + offsetX, playerPos.y + offsetY);

    float xDiff = hoopPos.x - (playerPos.x + offsetX);
    float yDiff = hoopPos.y - (playerPos.y + offsetY);
    float angle = atan2(yDiff, xDiff);
    cout << angle << endl;
    float speed = 0.07f;

    float velocityX = cos(angle) * speed;
    float velocityY = sin(angle) * speed;

    vector<float> velocities;
    velocities.push_back(velocityX);
    velocities.push_back(velocityY);

    return velocities;
}

/**
 * @brief Calculates the velocities for a jump shoot.
 *
 * @param player The player sprite.
 * @param ball The ball circle.
 * @param hoop The hoop sprite.
 * @return vector<float> A vector containing the x and y velocities.
 */
vector<float> jumpShoot(sf::Sprite player, sf::CircleShape ball, sf::Sprite hoop)
{
    float offsetX = 0.f;
    float offsetY = 0.f;

    sf::Vector2f playerPos = player.getPosition();
    sf::Vector2f hoopPos = hoop.getPosition();

    ball.setPosition(playerPos.x + offsetX, playerPos.y + offsetY);

    float xDiff = hoopPos.x - (playerPos.x + offsetX);
    float yDiff = hoopPos.y - (playerPos.y + offsetY);
    float angle = atan2(yDiff, xDiff);
    float speed = 0.1f;

    float velocityX = cos(angle) * speed;
    float velocityY = sin(angle) * speed;

    vector<float> velocities;
    velocities.push_back(velocityX);
    velocities.push_back(velocityY);

    return velocities;
}

/**
 * @brief Checks if a sprite is out of bounds.
 *
 * @param spr The sprite to check.
 * @return true if the sprite is out of bounds, false otherwise.
 */
bool check_oob(sf::Sprite spr)
{
    if (spr.getPosition().x >= 750 || spr.getPosition().x <= 0 ||
        spr.getPosition().x + 40 >= 750 || spr.getPosition().x - 40 <= 0 || spr.getPosition().y + 50 >= 480)
    {
        return true;
    }
    return false;
}

/**
 * @brief Checks if the ball possesses a sprite.
 *
 * @param shape The ball circle.
 * @param spr The sprite to check against.
 * @return true if the ball possesses the sprite, false otherwise.
 */
bool check_ball_poss(sf::CircleShape shape, sf::Sprite spr)
{
    if (spr.getGlobalBounds().intersects(shape.getGlobalBounds()))
    {
        return true;
    }
    return false;
}

/**
 * @brief Checks for collision with the backboard, rim, or swish for player 2's ball.
 *
 * @param shape The ball circle.
 * @param hoop The hoop sprite.
 * @return int The collision type (1 for backboard, 2 for rim, 3 for swish, 0 for no collision).
 */
int check_ball_collision_2(sf::CircleShape shape, sf::Sprite hoop)

{
    // backboard
    if (shape.getGlobalBounds().intersects(hoop.getGlobalBounds()) &&
        shape.getPosition().x >= 0 && shape.getPosition().x <= 20)
    {
        return 1;
    }
    // hits the rim
    else if (shape.getGlobalBounds().intersects(hoop.getGlobalBounds()) &&
             shape.getPosition().x >= 87 && shape.getPosition().x <= 92 && shape.getPosition().y <= 183 && shape.getPosition().y >= 181)
    {
        return 2;
    }
    // swish
    else if (shape.getGlobalBounds().intersects(hoop.getGlobalBounds()) &&
             shape.getPosition().x >= 30 && shape.getPosition().x <= 85 && shape.getPosition().y <= 184 && shape.getPosition().y >= 160)
    {
        return 3;
    }
    return 0;
}

/**
 * @brief Checks for collision with the backboard, rim, or swish for player 1's ball.
 *
 * @param shape The ball circle.
 * @param hoop The hoop sprite.
 * @return int The collision type (1 for backboard, 2 for rim, 3 for swish, 0 for no collision).
 */
int check_ball_collision_1(sf::CircleShape shape, sf::Sprite hoop)

{
    // backboard
    if (shape.getGlobalBounds().intersects(hoop.getGlobalBounds()) &&
        shape.getPosition().x >= 730 && shape.getPosition().x <= 740)
    {
        return 1;
    }
    // hits the rim
    else if (shape.getGlobalBounds().intersects(hoop.getGlobalBounds()) &&
             shape.getPosition().x >= 660 && shape.getPosition().x <= 665 && shape.getPosition().y <= 183 && shape.getPosition().y >= 181)
    {
        return 2;
    }
    // swish
    else if (shape.getGlobalBounds().intersects(hoop.getGlobalBounds()) &&
             shape.getPosition().x >= 665 && shape.getPosition().x <= 720 && shape.getPosition().y <= 183 && shape.getPosition().y >= 181)
    {
        return 3;
    }
    return 0;
}

/**
 * @brief Checks the score based on the ball position.
 *
 * @param ball The ball circle.
 * @return int The score (0, 1, or 2).
 */
int check_score(sf::CircleShape ball)
{
    if (ball.getPosition().x >= 20 && ball.getPosition().x <= 80 && ball.getPosition().y >= 175 && ball.getPosition().y <= 185)
    {
        return 2;
    }
    else if (ball.getPosition().x >= 670 && ball.getPosition().x <= 735 && ball.getPosition().y >= 175 && ball.getPosition().y <= 185)
    {
        return 1;
    }

    return 0;
}

/**
 * @brief Checks if a sprite is on the ground.
 *
 * @param spr The sprite to check.
 * @return true if the sprite is on the ground, false otherwise.
 */
bool check_ground(sf::Sprite spr)
{
    if (spr.getPosition().y < 340)
    {
        return false;
    }
    return true;
}

/**
 * @brief Runs the main game loop.
 */
void run_game()
{
    string name1, name2;

    // taking in team name input
    cout << "Enter Names" << endl;
    cin >> name1;
    cin >> name2;

    // initializing all our graphic sfml variables

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
    ball.setFillColor(sf::Color(250, 150, 100)); // rgb color coding

    // loading images and font files that are necessary

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

    // declaring some constants, variables, and flags that will be used later in the program
    bool ballshot1 = false, ballshot2 = false;
    bool p1_left = false, p2_left = false, p1_right = false, p2_right = false;

    float gravity = 0.0001f;
    float jumpvel = -0.15f;
    float yvel_1 = 0, yvel_2 = 0;
    const float maxY = 330;
    const float max_ballY = 0;
    float ballvely = 0.03f;
    float ballvelx = 0.f;

    bool jump_1 = false,
         jump_2 = false;
    bool player_1_poss = false, player_2_poss = false;
    bool collisionOccurred = false;

    if (!font.loadFromFile("/Users/aadrijupadya/Downloads/roboto/Roboto-Medium.ttf"))
    {
        cout << "Error loading fonts" << endl;
    }

    // setting sprite and text values to be displayed on screen
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
    vector<float> velocities;

    // initializing game loop
    while (game_window.isOpen())

    {
        // display constantly updating score text
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
        float playerBottomY = player_1_image.getPosition().y + player_1_image.getLocalBounds().height;

        // polling for events (ex: user input like mouse or keyboard)
        while (game_window.pollEvent(event))
        {
            if (event.type == sf::Event::MouseButtonPressed)
            {
                cout << event.mouseButton.x << " " << event.mouseButton.y << endl;
            }
            // std::cout << "Here is the game" << std::endl;

            if (event.type == sf::Event::Closed)
            {
                game_window.close();
            }

            // check for different key inputs, trigger different flag based on what is clicked
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
                // this is for when a player shoots
                if (event.key.code == sf::Keyboard::Down)
                {

                    if (playerBottomY >= 340 && player_2_poss)
                    {
                        ballshot2 = true;
                        velocities = groundShoot(player_2_image, ball, left_hoop);
                    }
                    else if (playerBottomY >= 340 && player_2_poss)
                    {
                        ballshot2 = true;
                        velocities = jumpShoot(player_1_image, ball, left_hoop);
                    }
                    else
                    {
                        velocities.push_back(0);
                        velocities.push_back(0);
                    }
                }
                if (event.key.code == sf::Keyboard::S)
                {

                    if (playerBottomY >= 340 && player_1_poss)
                    {
                        ballshot1 = true;
                        velocities = groundShoot(player_1_image, ball, right_hoop);
                    }
                    else if (playerBottomY >= 340 && player_1_poss)
                    {
                        ballshot1 = true;
                        velocities = jumpShoot(player_1_image, ball, right_hoop);
                    }
                    else
                    {
                        velocities.push_back(0);
                        velocities.push_back(0);
                    }
                }
            }
            // check if released, want smooth, nonconstant movement
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
        // different flag conditions and set movement accordingly
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
                player_1_image.move(-0.05, 0);
            }
            else
            {
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

        // checking for posession and setting ball posession depending on this
        if (check_ball_poss(ball, player_1_image) && !player_2_poss && !ballshot2 && !ballshot1)
        {
            ball.setPosition(player_1_image.getPosition().x + 60, player_1_image.getPosition().y + 50);
            player_1_poss = true;
        }
        if (check_ball_poss(ball, player_2_image) && !player_1_poss && !ballshot1 && !ballshot2)
        {
            ball.setPosition(player_2_image.getPosition().x - 60, player_2_image.getPosition().y + 50);
            player_2_poss = true;
        }

        // check if ball hits court, should bounce back up to max y (ceiling)
        if ((ball.getGlobalBounds().intersects(court.getGlobalBounds()) && !collisionOccurred) || ball.getPosition().y <= max_ballY)
        {
            ballvelx = 0;
            ballvely = -ballvely;
            // cout << ballvel << endl;
            collisionOccurred = true;
        }
        else if (!ball.getGlobalBounds().intersects(court.getGlobalBounds()))
        {
            collisionOccurred = false;
        }
        if (!player_1_poss && !player_2_poss && !ballshot2 && !ballshot1)
        {
            ball.move(ballvelx, ballvely);
        }

        // if ball is shot, we have two different logic cases to handle depending on player that shot

        if (ballshot2)
        {
            player_1_poss = false;
            player_2_poss = false;
            while ((ball.getPosition().x <= 800 || !((check_ball_collision_2(ball, left_hoop)) == 0) || !(ball.getGlobalBounds().intersects(player_1_image.getGlobalBounds()))))
            {
                cout << ball.getPosition().x << " " << ball.getPosition().y << endl;

                ball.move(velocities[0], velocities[1]);
                if (check_ball_collision_2(ball, left_hoop) == 1 || check_ball_collision_2(ball, left_hoop) == 2)
                {
                    ballvelx = -(velocities[0] * 0.5);
                    ballvely = -(velocities[1] * 2);
                    ballshot2 = false;
                    break;
                }

                if (check_ball_collision_1(ball, left_hoop) == 3)
                {
                    score_1 += 1;
                    // reset_position();
                    break;
                }
                // reset_position();

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

            // cout << "ok" << endl;
            // cout << velocities[0] << " " << velocities[1] << endl;
            // ball.move(5, 10);
        }
        if (ballshot1)
        {

            player_1_poss = false;
            player_2_poss = false;
            while ((ball.getPosition().x <= 770 || !((check_ball_collision_1(ball, right_hoop)) == 0) || !(ball.getGlobalBounds().intersects(player_2_image.getGlobalBounds()))))
            {
                cout << ball.getPosition().x << " " << ball.getPosition().y << endl;

                ball.move(velocities[0], velocities[1]);
                if (check_ball_collision_1(ball, right_hoop) == 1 || check_ball_collision_1(ball, right_hoop) == 2)
                {
                    ballvelx = -(velocities[0] * 0.5);
                    ballvely = -(velocities[1] * 2);
                    ballshot1 = false;
                    break;
                }

                if (check_ball_collision_1(ball, right_hoop) == 3)
                {
                    score_1 += 1;
                    // reset_position();
                    break;
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
        // constantly check if basket has been made, update score and reset position if so
        if (check_score(ball) == 1)
        {
            score_1 += 1;
            ball.setPosition(500, 340);
            player_1_image.setPosition(250, 340);
            player_2_image.setPosition(500, 340);

            // reset_position();
        }
        else if (check_score(ball) == 2)
        {
            score_2 += 1;
            ball.setPosition(250, 340);
            player_1_image.setPosition(250, 340);
            player_2_image.setPosition(500, 340);
            // reset_position();
        }

        // game winning condition
        if (score_1 >= 11 || score_2 >= 11)
        {
            if (score_1 >= score_2)
            {
                cout << "Winner: Player 1"
            }
            else
            {
                cout << "Winner: Player 2"
            }
            break;
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

/**
 * @brief Displays the rules window.
 */
void display_rules()
{
    sf::RenderWindow rules_window(sf::VideoMode(800, 300), "Rules");
    sf::Text rules_text;
    sf::Font font;
    sf::Event event;

    if (!font.loadFromFile("/Users/aadrijupadya/Downloads/roboto/Roboto-Medium.ttf"))
    {
        cout << "Error loading fonts" << endl;
    }

    rules_text.setFont(font);
    rules_text.setString("1. Two players can play this game at a time.\n2. One player uses the arrow keys (up to jump, right, and left for horizontal movement) while the other uses the WASD keys.\n3. Shoot the ball into the basket that you are facing to score points. \n4. All shots are worth the same amount, score more than your opponent to win.\n5. If you miss a shot, you can rebound it by moving your player near the ball so they catch it. \n6. Prevent your opponent from scoring by blocking their shot with your player.\n7. The first player to score 11 points will win the game.");
    rules_text.setCharacterSize(15);
    rules_text.setFillColor(sf::Color::Red);
    rules_text.setStyle(sf::Text::Bold);

    while (rules_window.isOpen())
    {
        while (rules_window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                rules_window.close();
        }
        rules_window.clear();
        rules_window.draw(rules_text);
        rules_window.display();
    }
}

/**
 * @brief Displays the home screen.
 */
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
    logo.setPosition(140.f, 120.f);
    while (window.isOpen())
    {
        sf::Event event;

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::MouseButtonPressed)
            {
                if ((event.mouseButton.x <= 230) && (event.mouseButton.x >= 80) && (event.mouseButton.y >= 100) && (event.mouseButton.y <= 150))
                {
                    run_game();
                }
                else if ((event.mouseButton.x <= 550) && (event.mouseButton.x >= 400) && (event.mouseButton.y >= 100) && (event.mouseButton.y <= 150))
                {
                    display_rules();
                }
            }
        }

        window.clear();
        window.draw(left_button);
        window.draw(right_button);
        window.draw(opening_text);
        window.draw(left_text);
        window.draw(logo);
        window.draw(right_text);
        window.display();
    }
}

/**
 * @brief displays initial screen, which links to other screens and functions.
 */
int main()
{
    start_screen();
    return 0;
}
