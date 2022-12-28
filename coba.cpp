#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <string>
#include <ctime>
using namespace std;
struct Birdblock
{
    sf::Sprite bird;
    sf::Texture texture;
    float x = 250, y = 384, timefall = 0;
    float scale_ratio = 0.1588f;
    sf::Vector2f scale;
    float width = 272 * scale_ratio, height = 225 * scale_ratio;
    Birdblock()
    {
        if (!texture.loadFromFile("redbird.png"))
            cout << "Error";
        bird.setTexture(texture);
        bird.setOrigin(sf::Vector2f(136.f, 112.5f));
        bird.setScale(sf::Vector2f(scale_ratio, scale_ratio));
        scale = bird.getScale();
        bird.setPosition(x, y);
    }
    void update(float window_width, float window_height)
    {
        bird.setPosition(sf::Vector2f(x, y));
    }
    void draw(sf::RenderWindow &window)
    {
        window.draw(bird);
    }
    void moveleft(float window_width, float window_height)
    {
        bird.setScale(scale.x * -1, scale.y * 1);
        if (bird.getRotation() != 45)
            bird.setRotation(bird.getRotation() + 45);
        x += -0.4;
        y += -0.4;
        timefall = 0;
        if (x - width / 2 <= 0)
            x = 0 + width / 2;
    }
    void moveright(float window_width, float window_height)
    {
        bird.setScale(scale.x * 1, scale.y * 1);
        if (bird.getRotation() != 315)
            bird.setRotation(bird.getRotation() + 315);
        x += 0.4;
        y += -0.4;
        timefall = 0;
        if (x + width / 2 >= window_width)
            x = window_width - width / 2;
    }
    void fall(float window_width, float window_height)
    {
        if (bird.getRotation() <= 45 && bird.getRotation() > 0)
        {
            bird.setRotation(bird.getRotation() - 5);
        }
        if (bird.getRotation() >= 315 && bird.getRotation() < 360)
        {
            bird.setRotation(bird.getRotation() + 5);
        }
        y += timefall;
        timefall += 0.001;
        if (x + width / 2 == window_width)
        {
            bird.setScale(scale.x * -1, scale.y * 1);
            x += -50;
            y += -40;
        }
        if (x - width / 2 == 0)
        {
            bird.setScale(scale.x * 1, scale.y * 1);
            x += 50;
            y += -40;
        }
    }
    void falldown(float window_width, float window_height)
    {
        y += timefall;
        timefall += 0.002;
        bird.setRotation(bird.getRotation() + 1);
    }
};

struct Background
{
    sf::Sprite background;
    sf::Texture texture;
    float x = 0, y = 0;
    float scale = 1.f;
    float width = 432 * scale, height = 768 * scale;

    Background()
    {
        if (!texture.loadFromFile("background.png"))
        {
            cout << "Error" << endl;
        }
        background.setTexture(texture);
        background.setScale(sf::Vector2f(scale, scale));
    }

    void update(float window_width, float window_height)
    {
    }

    void draw(sf::RenderWindow &window)
    {
        window.draw(background);
    }
};
struct Endgame
{
    sf::Sprite endgame;
    sf::Texture texture;
    float x = 0, y = 0;
    float scale = 1.f;
    float width = 432 * scale, height = 768 * scale;

    Endgame()
    {
        if (!texture.loadFromFile("endgame.png"))
        {
            cout << "Error" << endl;
        }
        endgame.setTexture(texture);
        endgame.setScale(sf::Vector2f(scale, scale));
    }
    void draw(sf::RenderWindow &window)
    {
        window.draw(endgame);
    }
};
struct Startgame
{
    sf::Sprite startgame;
    sf::Texture texture;
    float x = 0, y = 0;
    float scale = 1.f;
    float width = 432 * scale, height = 768 * scale;

    Startgame()
    {
        if (!texture.loadFromFile("startgame.png"))
        {
            cout << "Error" << endl;
        }
        startgame.setTexture(texture);
        startgame.setScale(sf::Vector2f(scale, scale));
    }
    void draw(sf::RenderWindow &window)
    {
        window.draw(startgame);
    }
};

sf::Texture brickTexture;
sf::Font fontscore;
sf::Text textscore;
sf::Color color(0, 142, 173);

struct Brickblock
{
    sf::Sprite brick;
    float x = 200, y = 0;
    float scale = 0.8f;
    float width = 81 * scale, height = 41 * scale;

    Brickblock()
    {
        if (!brickTexture.loadFromFile("brick.png"))
        {
            cout << "Error" << endl;
        }
        brick.setTexture(brickTexture);
        brick.setOrigin(sf::Vector2f(40.5f, 41.f));
        brick.setScale(sf::Vector2f(scale, scale));
    }
    void setX(float _x)
    {
        x = _x;
    }
    void draw(sf::RenderWindow &window)
    {
        window.draw(brick);
    }
    void update(float window_width, float window_height)
    {
        brick.setPosition(sf::Vector2f(x, y));
        y += 0.1;
    }
    bool collide(float birdx, float birdy, float birdwidth, float birdheight)
    {
        if (y - height <= birdy + birdheight / 2 && y >= birdy - birdheight / 2) // canh tren gach<=canh duoi chim va canh duoi gach>=canh tren chim
        {
            if (x + width / 2 >= birdx - birdwidth / 2 && x - width / 2 <= birdx + birdwidth / 2) // canh phai gach>=canh trai chim va canh trai gach<=canh phai chim
            {
                return true;
            }
        }
        return false;
    }
};
struct Rowbricks
{
    vector<Brickblock> row;
    int brick_number;
    float rand_number, xx;
    Rowbricks()
    {
        rand_number = rand();
        brick_number = (int)rand_number % 3 + 1;
        if (brick_number == 1)
        {
            rand_number = rand();
            xx = (int)rand() % 432;
            Brickblock brick;
            brick.setX(xx);
            row.push_back(brick);
        }
        if (brick_number == 2)
        {
            for (int i = 0; i < 2; i++)
            {
                if (i == 0)
                {
                    Brickblock brick;
                    rand_number = rand();
                    xx = (int)rand_number % 190;
                    brick.setX(xx);
                    row.push_back(brick);
                }
                if (i == 1)
                {
                    Brickblock brick;
                    rand_number = rand();
                    xx = (int)rand_number % 190 + 241;
                    brick.setX(xx);
                    row.push_back(brick);
                }
            }
        }
        if (brick_number == 3)
        {
            for (int i = 0; i < 3; i++)
            {
                if (i == 0)
                {
                    Brickblock brick;
                    rand_number = rand();
                    xx = (int)rand_number % 120;
                    brick.setX(xx);
                    row.push_back(brick);
                }
                if (i == 1)
                {
                    Brickblock brick;
                    rand_number = rand();
                    xx = (int)rand_number % 99 + 165;
                    brick.setX(xx);
                    row.push_back(brick);
                }
                if (i == 2)
                {
                    Brickblock brick;
                    rand_number = rand();
                    xx = (int)rand_number % 31 + 400;
                    brick.setX(xx);
                    row.push_back(brick);
                }
            }
        }
    }
    void draw(sf::RenderWindow &window)
    {
        for (int i = 0; i < brick_number; i++)
        {
            row[i].draw(window);
        }
    }
    void update(float window_width, float window_height)
    {
        for (int i = 0; i < brick_number; i++)
        {
            row[i].update(window_width, window_height);
        }
    }
    bool collide(float birdx, float birdy, float birdwidth, float birdheight)
    {
        for (int i = 0; i < brick_number; i++)
        {
            if (row[i].collide(birdx, birdy, birdwidth, birdheight) == true)
                return true;
        }
        return false;
    }
};
struct Allbricks
{
    vector<Rowbricks> all;
    string yourscore;

    void draw(sf::RenderWindow &window)
    {
        for (unsigned int i = 0; i < all.size(); i++)
        {
            all[i].draw(window);
        }
    }
    void update(long timeloop, float window_width, float window_height)
    {
        if (timeloop % 2250 == 0)
        {
            Rowbricks row;
            all.push_back(row);
            yourscore = to_string(all.size());
            // cout<<"time loop"<<" "<<timeloop<<endl;
            // cout<<"all.size"<<" "<<all.size()<<endl;
        }
        for (unsigned int i = 0; i < all.size(); i++)
        {
            all[i].update(window_width, window_height);
        }
    }
    bool collide(float birdx, float birdy, float birdwidth, float birdheight)
    {
        for (unsigned int i = 0; i < all.size(); i++)
        {
            if (all[i].collide(birdx, birdy, birdwidth, birdheight) == true)
                return true;
        }
        return false;
    }
};
/*struct Soundhit
{
    sf::SoundBuffer buffer;
    sf::Sound sound;
    Soundhit()
    {
        if(!buffer.loadFromFile("Hit.wav"))
            cout<<"Error"<<endl;
        sound.setBuffer(buffer);
    }
    void playSoundhit()
    {
        sound.play();
    }
};*/
struct Status
{

    float window_width = 432, window_height = 768;
    Startgame startgame;
    Background background;
    Endgame endgame;
    Birdblock bird;
    // Brickblock brick;
    // Rowbricks row;
    Allbricks all;
    // Soundhit soundhit;
    string score;
    long timeloop = 0; // 225
    bool start = true;
    ;
    bool gameover = false;
    void displayStatus(sf::RenderWindow &window)
    {
        if (start == true)
        {
            window.clear(sf::Color::Green);
            startgame.draw(window);
        }
        else
        {
            window.clear(sf::Color::Black);
            background.draw(window);
            // brick.draw(window);
            // row.draw(window);
            all.draw(window);
            bird.draw(window);

            // draw score
            score = all.yourscore;
            textscore.setFont(fontscore);
            textscore.setString(score);
            textscore.setCharacterSize(30);
            textscore.setFillColor(color);
            textscore.setStyle(sf::Text::Bold);
            textscore.setPosition(sf::Vector2f(0, 0));
            window.draw(textscore);

            if (bird.y >= window_height)
            {
                window.clear(sf::Color::Black);
                endgame.draw(window);
                textscore.setCharacterSize(30);
                textscore.setFillColor(sf::Color::White);
                textscore.setStyle(sf::Text::Bold);
                textscore.setPosition(sf::Vector2f(210, 370));
                window.draw(textscore);
            }
        }

        window.display();
    }

    void updateStatus()
    {
        if (start == true)
        {
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left) || sf::Mouse::isButtonPressed(sf::Mouse::Right))
                start = false;
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
                start = false;
        }
        else
        {
            if (gameover == false)
            {
                if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
                    bird.moveleft(window_width, window_height);
                else if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
                    bird.moveright(window_width, window_height);
                else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
                    bird.moveleft(window_width, window_height);
                else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
                    bird.moveright(window_width, window_height);
                else
                    bird.fall(window_width, window_height);
            }
            else
            {
                bird.y += -0.5;
                bird.falldown(window_width, window_height);
            }
            if (gameover == false)
            {
                // brick.update(window_width,window_height);
                // row.update(window_width,window_height);
                all.update(timeloop, window_width, window_height);
            }
            bird.update(window_width, window_height);

            if (all.collide(bird.x, bird.y, bird.width, bird.height) == true || bird.y >= window_height)
            {
                // cout<<"cham gach"<<endl;
                // soundhit.playSoundhit();
                gameover = true;
            }

            timeloop++;
        }
    }
};
int main()
{
REPLAY:
    srand(time(0));
    Status status;
    sf::RenderWindow window(sf::VideoMode(status.window_width, status.window_height), "Dump Jump");
    if (!brickTexture.loadFromFile("brick.png"))
    {
        cout << "Error" << endl;
    }
    if (!fontscore.loadFromFile(".VnBahamasB.ttf"))
    {
        cout << "Error loading .VnBahamasB.ttf" << endl;
    }
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        status.updateStatus();
        status.displayStatus(window);
        if (status.gameover == true)
        {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
            {
                goto REPLAY;
            }
        }
    }

    return 0;
}
