#include <iostream>
#include <SFML/Graphics.hpp>


using namespace std;
using namespace sf;

Font f;


class node
{
private:
    static int curent_number_node;
    int number_node;
    int array_connection;
public:
    node(/* args */);
    ~node();
};

node::node(/* args */)
{
}

node::~node()
{
}



struct Shape_Button
{
    RectangleShape button_bar;
    Text text_button;

    Shape_Button(RectangleShape s, Text t)
    {
        button_bar = s;
        text_button = t;
    }
};


class button
{
private:
    int pos_x;
    int pos_y;
    string text;
    Color col;

    int size_h;
    int size_v;
    Color text_col;
public:
    button();
    button(int x, int y, string t, Color c);

    Shape_Button create_button();
    int get_pos_x();
    int get_pos_y();
    int get_size_h();
    int get_size_v();
    ~button();
};

button::button()
{
    pos_x = 0;
    pos_y = 0;
    text = "TEXT";
    col = Color::Red;

    size_h = 4 * 20;
    size_v = 25;
    text_col = Color::Black;
}

button::button(int x, int y, string t, Color c)
{
    pos_x = x;
    pos_y = y;
    text = t;
    col = c;

    size_h = t.size() * 19;
    size_v = 25;
    text_col = Color::Black;
}

button::~button()
{
}

Shape_Button button::create_button()
{
    RectangleShape square;

    square.setSize(Vector2f(size_h, size_v));
    square.setPosition(pos_x, pos_y);
    square.setFillColor(col);



    Text text_b;

    text_b.setFillColor(text_col);
    text_b.setFont(f);
    text_b.setCharacterSize(20);
    text_b.setPosition(pos_x, pos_y);
    text_b.setString(text);

    return Shape_Button(square, text_b);
}

int button::get_pos_x()
{
    return pos_x;
}

int button::get_pos_y()
{
    return pos_y;
}

int button::get_size_h()
{
    return size_h;
}

int button::get_size_v()
{
    return size_v;
}


int main()
{
    f.loadFromFile("Fonts/arial.ttf");
    
    button b(100, 100, "PLAY", Color::Green);
    Shape_Button My_button(b.create_button());

    int poser = 0;
    bool allow_move = false;

    CircleShape circle, circle2;

    circle.setFillColor(sf::Color::Green);
    circle.setPosition(800, 200);
    circle.setRadius(50);

    circle2.setFillColor(Color::Green);
    circle2.setPosition(500, 500);
    circle2.setRadius(50);

    RenderWindow window(VideoMode(1200, 680), "Chess");

    while (window.isOpen())
    {
        Event event;

        window.clear();

        while (window.pollEvent(event))
        {

            if ((event.type == Event::Closed) || (Keyboard::isKeyPressed(Keyboard::Escape)))
            {
                window.close();
            }
            
            if (event.type == Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == Mouse::Left)
                {
                    poser = ((Mouse::getPosition(window).x - circle.getPosition().x - 50) * (Mouse::getPosition(window).x - circle.getPosition().x - 50)) + ((Mouse::getPosition(window).y - circle.getPosition().y - 50) * (Mouse::getPosition(window).y - circle.getPosition().y - 50));
                    if (2500 >= poser)
                    {
                        allow_move = true;
                    }
                }
                
            }

            if (event.type == Event::MouseButtonReleased)
            {
                if (event.mouseButton.button == Mouse::Left)
                {
                    if (My_button.button_bar.getFillColor() == Color::White)
                    {
                        circle.setPosition(Mouse::getPosition(window).x - 50, Mouse::getPosition(window).y - 50);
                        //circle.setRadius(50.f);
                        My_button.button_bar.setFillColor(Color::Green);
                    }

                    if (My_button.button_bar.getFillColor() == Color::Green)
                    {
                        if (IntRect(b.get_pos_x(), b.get_pos_y(), b.get_size_h(), b.get_size_v()).contains(Mouse::getPosition(window)))
                        {
                            My_button.button_bar.setFillColor(Color::White);
                            break;
                        }
                    }
                    
                    allow_move = false;
                }
                
            }
            
            
            
        }

        if (allow_move == true)
        {
            circle.setPosition(Mouse::getPosition(window).x - 50, Mouse::getPosition(window).y - 50);
        }

        Vertex line[] =
        {
            Vertex(Vector2f(circle.getPosition().x + 50, circle.getPosition().y + 50), Color::Red),
            Vertex(Vector2f(circle2.getPosition().x + 50, circle2.getPosition().y + 50), Color::Red)
        };
        

        window.draw(My_button.button_bar);
        window.draw(My_button.text_button);
        window.draw(line, 2, Lines);
        window.draw(circle);
        window.draw(circle2);
        window.display();
    }
    
    return 0;
}