#include <SFML/Graphics.hpp>
#include <time.h>


void Win()//window after win
{
    sf::RenderWindow window(sf::VideoMode(900, 600),"Win");
    sf::Font font;
    font.loadFromFile("Times_New_Roman.ttf");

    sf::Text text;
    text.setFont(font);
    text.setString(" You WIN");
    text.setCharacterSize(24);
    text.setFillColor(sf::Color::White);
    text.setStyle(sf::Text::Bold | sf::Text::Underlined);


    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed)
                window.close();
        }
        window.clear();
        window.draw(text);
        window.display();
    }


}

void Rules()//window to demostrate rules
{
    sf::RenderWindow window(sf::VideoMode(900, 600),"Rules");
    sf::Font font;
    font.loadFromFile("Times_New_Roman.ttf");

    sf::Text text;
    text.setFont(font);
    text.setString("Головне завдання в цiй грi - скласти усi цифри на фiшках у порядку зростання.\n\n Пересувати фiшки можна тiльки на сусiдню вiльну позицiю! \n\n  Для початку гри потрібно спершу закрити правила)");

    text.setCharacterSize(24); // in pixels, not points!
    text.setFillColor(sf::Color::White);
    text.setStyle(sf::Text::Bold | sf::Text::Underlined);


    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed)
                window.close();
        }
        window.clear();
        window.draw(text);
        window.display();
    }


}


class Boolean//class for logical coefficients
{
public:
    bool stop = true, play = false, pusk = false;
    int puskgame = 1000;
};

Boolean boolean;//to work with the boolean class in other classes
sf::RenderWindow app(sf::VideoMode(750, 512), "Estimated Graphic Work");


class Game//class for creating and managing gamme
{
public:
    sf::Sprite s[17];//allocation memory for the array
    int w = 128;//width of one square
    int grid[6][6] = { 0 };//array for each square
    int n = 0;

    int b = 16, x = 0, y = 0;//b - empty square

    Game(sf::Texture& image)
    {
        for(int i = 0; i < 4; i++)
        {
            for(int j = 0; j < 4; j++)
            {
                n++;
                s[n].setTexture(image);
                s[n].setTextureRect(sf::IntRect(i * w, j * w, w, w));
                grid[i + 1][j + 1] = n;
            }
        }

    }

    void update()//changing the position of the squares
    {
        int dx = 0;
        int dy = 0;

        if(grid[x+1][y] == b)
        {
            dx = 1;
            dy = 0;
        }
        if(grid[x-1][y] == b)
        {
            dx = -1;
            dy = 0;
        }
        if(grid[x][y-1] == b)
        {
            dx = 0;
            dy = -1;
        }
        if(grid[x][y+1] == b)
        {
            dx = 0;
            dy = 1;
        }

        n = grid[x][y];
        grid[x][y] = b;
        grid[x + dx][y + dy] = n;

        s[b].move(-dx * w, -dy * w);//animation
        float speed = 16;
        for (int i = 0; i < w; i += speed)
        {
            s[n].move(speed * dx, speed * dy);
            app.draw(s[b]);
            app.draw(s[n]);
            app.display();
        }
        if (boolean.play) {//the requisition under which the win window is displayed
            if (grid[1][1] == 1 && grid[1][2] == 2 && grid[1][3] == 3 && grid[1][4] == 4 &&
                grid[2][1] == 5 && grid[2][2] == 6 && grid[2][3] == 7 && grid[2][4] == 8 &&
                grid[3][1] == 9 && grid[3][2] == 10 && grid[3][3] == 11 && grid[3][4] == 12 &&
                grid[4][1] == 13 && grid[4][2] == 14 && grid[4][3] == 15 && grid[4][4] == 16) {
                boolean.play = false;
                boolean.stop = true;

                boolean.puskgame = 1000;

                app.setFramerateLimit(0);
                Win();//function of Win window


            }
        }
    }
};

class Button//class for start button
{
public:
    sf::Texture t;
    sf::Sprite start;

    Button()
    {
        t.loadFromFile("start.png");

        start.setTexture(t);
        start.setPosition(540, 350);
        start.setTextureRect(sf::IntRect(0, 0, 195, 106));

    }
};

int main()
{

    setlocale(LC_ALL, "");

    Rules();
    srand(time(0));

    sf::Texture t;
    t.loadFromFile("five2.0.png");
    Game game(t);

    Button button;

    while (app.isOpen())
    {
        // Process events
        sf::Event event;
        while (app.pollEvent(event))
        {
            // Close window : exit
            if (event.type == sf::Event::Closed)
                app.close();
            if(event.type == sf::Event::MouseButtonPressed)//mouse control
            {
                if(event.key.code == sf::Mouse::Left)
                {
                    sf::Vector2i pos = sf::Mouse::getPosition(app);
                    if(boolean.play) {
                        if(pos.x <= 512){
                        game.x = pos.x / game.w + 1;
                        game.y = pos.y / game.w + 1;
                        }
                    }
                    else if (boolean.stop)
                    {
                        if(pos.x >= 540 && pos.x <= 736 && pos.y >= 400 && pos.y <= 465)
                        {
                            boolean.stop = false;
                            boolean.pusk = true;

                            app.setFramerateLimit(0);
                        }
                    }
                }

            }
        }

        if(boolean.pusk)//mixing squares
        {
            game.x = rand() % 4 + 1;
            game.y = rand() % 4 + 1;


            boolean.puskgame --;

            if(boolean.puskgame == 0)
            {
                boolean.pusk = false;
                boolean.play = true;
            }
        }

        else if(boolean.play)
        {
            app.setFramerateLimit(60);
        }

        game.update();
        app.clear(sf::Color::White);
        if(boolean.stop)
            app.draw(button.start);
        for(int i = 0; i < 4; i++)
        {
            for(int j = 0; j < 4; j++)
            {
                game.n = game.grid[i + 1][j + 1];
                game.s[game.n].setPosition(i * game.w, j * game.w);
                app.draw(game.s[game.n]);
            }
        }

        app.display();

    }

    return EXIT_SUCCESS;
}
