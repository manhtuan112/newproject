#include <SFML/Graphics.hpp>
#include <time.h>
using namespace sf;

int main()
{
    srand(time(0));

    RenderWindow app(VideoMode(710, 450), "hung bong");
    app.setFramerateLimit(60);
    Texture t2;
    t2.loadFromFile("images/background.jpg");

    Sprite bgSprite;
    bgSprite.setTexture(t2);
    bgSprite.setScale(static_cast<float>(app.getSize().x) / t2.getSize().x,
        static_cast<float>(app.getSize().y) / t2.getSize().y);


    Texture t1, t3, t4;
    t1.loadFromFile("images/block03.png");
    t3.loadFromFile("images/ball.png");
    t4.loadFromFile("images/paddle.png");

    Sprite sBackground(t2), sBall(t3), sPaddle(t4);
    sPaddle.setPosition(710, 440);

    Sprite block[1000];

    int n = 0;
    for (int i = 1; i <= 15; i++)
        for (int j = 1; j <= 10; j++)
        {
            block[n].setTexture(t1);
            block[n].setPosition(i * 45, j * 20);
            n++;
        }

    float dx = 6, dy = 5;
    float x = 300, y = 300;

    while (app.isOpen())
    {
        Event e;
        while (app.pollEvent(e))
        {
            if (e.type == Event::Closed)
                app.close();
        }

        x += dx;
        for (int i = 0; i < n; i++)
            if (FloatRect(x + 2, y + 2, 6, 6).intersects(block[i].getGlobalBounds()))
            {
                block[i].setPosition(-100, 0); dx = -dx;
            }

        y += dy;
        for (int i = 0; i < n; i++)
            if (FloatRect(x + 3, y + 3, 6, 6).intersects(block[i].getGlobalBounds()))
            {
                block[i].setPosition(-100, 0); dy = -dy;
            }

        if (x < 0 || x>700)  dx = -dx;
        if (y < 0 || y>440)  dy = -dy;

        if (Keyboard::isKeyPressed(Keyboard::Right)) sPaddle.move(6, 0);
        if (Keyboard::isKeyPressed(Keyboard::Left)) sPaddle.move(-6, 0);

        if (FloatRect(x, y, 12, 12).intersects(sPaddle.getGlobalBounds())) dy = -(rand() % 1 + 2);

        sBall.setPosition(x, y);

        app.clear();
        app.draw(sBackground);
        app.draw(sBall);
        app.draw(sPaddle);

        for (int i = 0; i < n; i++)
            app.draw(block[i]);

        app.display();
    }

    return 0;
}