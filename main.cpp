#include <SFML/Graphics.hpp>
#include <SFML/Main.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Config.hpp>
#include <SFML/Audio.hpp>
#include <SFML/OpenGL.hpp>

#include <iostream>
#include <cstdlib>
#include <string>

using namespace std;

void run_game()
{
    string name1, name2;
    cout << "Enter Names" << endl;
    cin >> name1;
    cin >> name2;
    sf::RenderWindow game_window(sf::VideoMode(800, 480), "Gameplay");
    sf::Text player_1_text;
    sf::Text player_2_text;
    sf::Text score_1_text;
    int score_1 = 0;
    sf::Text score_2_text;
    int score_2 = 0;

    sf::Texture background;
    sf::Font font;
    sf::Keyboard keys;
    sf::Event event;

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

    while (game_window.isOpen())
    {
        while (game_window.pollEvent(event))
        {
            // std::cout << "Here is the game" << std::endl;

            if (event.type == sf::Event::Closed)
                game_window.close();
        }
        game_window.clear();
        game_window.draw(player_1_text);
        game_window.draw(player_2_text);
        game_window.draw(score_1_text);
        game_window.draw(score_2_text);
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

    sf::Texture background;
    sf::Font font;
    sf::Keyboard keys;
    sf::Event event;

    if (!font.loadFromFile("/Users/aadrijupadya/Downloads/roboto/Roboto-Medium.ttf"))
    {
        cout << "Error loading fonts" << endl;
    }

    left_button.setSize(sf::Vector2f(150, 50));
    left_button.setPosition(80.f, 200.f);
    left_button.setFillColor(sf::Color::White);

    right_button.setSize(sf::Vector2f(150, 50));
    right_button.setPosition(400.f, 200.f);
    right_button.setFillColor(sf::Color::White);

    left_text.setFont(font);
    left_text.setString("Play");
    left_text.setCharacterSize(30);
    left_text.setFillColor(sf::Color::Red);
    left_text.setStyle(sf::Text::Bold);
    left_text.setPosition(120.f, 200.f);

    right_text.setFont(font);
    right_text.setString("Rules");
    right_text.setCharacterSize(30);
    right_text.setFillColor(sf::Color::Red);
    right_text.setStyle(sf::Text::Bold);
    right_text.setPosition(440.f, 200.f);

    opening_text.setFont(font);
    opening_text.setString("Fantastical Basketball");
    opening_text.setCharacterSize(20);
    opening_text.setFillColor(sf::Color::White);
    opening_text.setStyle(sf::Text::Bold);
    opening_text.setPosition(200.f, 20.f);

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
                    std::cout << "Ready to play!" << std::endl;
                    run_game();
                }
                else if ((event.mouseButton.x <= 550) && (event.mouseButton.x >= 400) && (event.mouseButton.y >= 200) && (event.mouseButton.y <= 250))
                {
                    sf::RenderWindow rules_window(sf::VideoMode(500, 600), "Rules");

                    while (rules_window.isOpen())
                    {
                        while (rules_window.pollEvent(event))
                        {
                            std::cout << "Here are the rules" << std::endl;

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
