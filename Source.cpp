#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <iostream>
using namespace std;
using namespace sf;

class rompecabezas {
public:
    RenderWindow window;
    Event event;

    rompecabezas() {
        window.create(VideoMode(1800, 900), "My window", Style::Default);

    }
    void createTexture( ) {
        Image Img;
        if (!Img.loadFromFile("imagenes/si.png")) {
            cout << "Epa hermano, hay un peo aqui";
        }
        else {
            Texture texture;
            texture.loadFromImage(Img);
            cout << "Imagen cargada...";
            texture.setSmooth(true);
            Vector2u size = texture.getSize();
            Sprite sprite;
            sprite.setTexture(texture);
            sprite.setOrigin(texture.getSize().x / 2.0f, texture.getSize().y / 2.f);
            sprite.setPosition(window.getSize().x / 2.f, window.getSize().y / 2.f);

            sprite.setScale(1400.f / texture.getSize().x, 500.f / texture.getSize().y);

            window.draw(sprite);
        }
    }


    void text( string s, int x, int y, int size, int fontName = 1) {
        Font font;
        string path = "fonts/";
        switch (fontName) {
        case 0: {
            path.append("eva.otf");
            break;
        }case 1: {
            path.append("arial.ttf");
            break;
        }
        }
        if (!font.loadFromFile(path)) {
            cout << "La fuente no fue encontrada";
        }
        else {
            Text text;
            text.setFont(font);
            text.setString(s);
            text.setCharacterSize(size);
            text.setFillColor(Color::White);
            text.setOrigin(text.getLocalBounds().width / 2, text.getLocalBounds().height / 2);
            text.setPosition(x, y);
            window.draw(text);
        }
    }

    RectangleShape boton( string s, int x, int y) {
        RectangleShape boton(Vector2f(200, 80));
        boton.setFillColor(Color::Magenta);
        boton.setOrigin(boton.getSize().x / 2, boton.getSize().y / 2);
        boton.setPosition(x, y);
        Text texto;
        texto.setString(s);
        Font font;
        font.loadFromFile("fonts/arial.ttf");
        texto.setFont(font);
        texto.setOrigin(texto.getLocalBounds().width / 2, texto.getLocalBounds().height / 2);

        texto.setPosition(x, y - 10);
        window.draw(boton);
        window.draw(texto);
        return boton;
    }



    int lectorDeEventos( Event& event) {
        switch (event.type)
        {
        case Event::Closed: {
            return 0;
            break;
        }
                          //En caso que haya presionado una tecla:
        case Event::KeyPressed: {
            if (event.key.scancode == sf::Keyboard::Scan::Escape)
            {
                return 0;
            }
            else if (event.key.scancode == Keyboard::Scan::Enter) {

                return 1;
            }

            break;
        }
        case Event::Resized: {
            window.setSize(window.getSize());
            break;
        }
        case Event::MouseButtonPressed: {
            if (Mouse::isButtonPressed(sf::Mouse::Left)) {
                return 2;
            }
            break;
        }
        case Event::TextEntered: {
            return 3;
            break;
        }
        default: {
            break;
        }

        }
    }

    void  puzzleStart() {
        bool t = true;
        bool enter = false;
        string name;
        while (t) {

            window.clear(Color::Black);
            text( "rompecabezas", 900, 50, 100, 0);
            text( "Ingrese su nombre!", 900, 150, 40);
            text( name, 900, 200, 40);
            RectangleShape bSi;
            RectangleShape bNo;


            if (enter) {
                text("¿Esta correcto tu nombre?", 900, 300, 40);

                bSi = boton("Si", 450, 350);
                bNo = boton("No", 1350, 350);

            }

            RectangleShape botonT = boton("listo", 900, 750);



            while (window.pollEvent(event)) {

                int ev = lectorDeEventos(event);

                switch (ev) {
                case 0: {
                    t = false;
                    break;
                }
                case 1: {
                    enter = true;
                    cout << "enter";
                    break;
                }
                case 2: {
                    if (Mouse::isButtonPressed(sf::Mouse::Left)) {
                        Vector2f pR = window.mapPixelToCoords(Vector2i(event.mouseButton.x, event.mouseButton.y));
                        if (name.size() > 0) {

                            if (bSi.getGlobalBounds().contains(pR)) {
                                cout << "Iniciamos juego";
                            }
                            else if (bNo.getGlobalBounds().contains(pR)) {
                                name = "";
                                enter = false;
                                break;
                            }
                        }
                        else if (botonT.getGlobalBounds().contains(pR)) {
                            //cout << "Presionado";
                            t = false;
                            break;
                        }
                    }
                    break;

                }
                case 3: {
                    if (event.text.unicode < 128) {
                        name.push_back(event.text.unicode);


                    }
                    break;
                }

                }
            }

            window.display();
        }

    }


    void menu()
    {
        

        //main loop
        while (window.isOpen()) {
            window.clear(Color::Black);
            text("rompecabezas", 900, 200, 150, 0);
            text( "v.25", 900, 310, 150, 0);
            RectangleShape botonStart = boton( "START", 900, 510);
            RectangleShape botonSalir = boton( "SALIR", 900, 610);

            while (window.pollEvent(event)) {
                int ev = lectorDeEventos(event);
                switch (ev) {
                case 0: {
                    window.close();
                    break;
                }
                case 2: {
                    if (Mouse::isButtonPressed(sf::Mouse::Left)) {
                        Vector2f pR = window.mapPixelToCoords(Vector2i(event.mouseButton.x, event.mouseButton.y));
                        if (botonStart.getGlobalBounds().contains(pR)) {

                            puzzleStart();
                        }
                        else if (botonSalir.getGlobalBounds().contains(pR)) {
                            window.close();
                        }
                    }
                    break;
                }
                }
            }

            window.display();


        }
    }



};



int main()
{
    rompecabezas r;
    r.menu();
    return 0;
} 