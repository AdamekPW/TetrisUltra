#include "Menu.h"


Menu::Menu() {
 
    ShowShadowContest = false;
    Volume = 100;
}

sf::RectangleShape Menu::Button(int Width, int Height, int x, int y) {
    sf::RectangleShape button(sf::Vector2f(Width, Height)); // Rozmiar przycisku
    button.setFillColor(sf::Color::White); // Kolor przycisku
    button.setPosition(y, x); // Pozycja przycisku

    return button;
}

void Menu::MenuLoop(int* GameOrMenu, sf::RenderWindow &window) {
    sf::RectangleShape square(sf::Vector2f(30*0.9, 30*0.9));
    
    sf::Color Orange(255, 165, 0);
    sf::Color Pink(255, 105, 180);
    std::random_device rd;
    std::mt19937 generator(rd());
    std::uniform_int_distribution<int> distribution(1, 11);
    for (int i = 0; i < 4; i++) {
        
        int Number = distribution(generator);
        Shapes* Shape = RandomShape();
        Shape->RandRotation();
        Shape->SetX(-i * 10000 * 30);
        Shape->SetY(Number);
        ListOfShapes.push_back(Shape);
    }

    //wczytywanie obrazkow ---------------------------------------------
    sf::Texture PlayImage;
    if (!PlayImage.loadFromFile("MenuImages/PlayButton.png")) {}
    sf::Sprite Play;
    Play.setTexture(PlayImage);
    Play.setPosition(85, 300);

    sf::Texture SettingsImage;
    if (!SettingsImage.loadFromFile("MenuImages/SettingsButton.png")) {}
    sf::Sprite Settings;
    Settings.setTexture(SettingsImage);
    Settings.setPosition(85, 380);

    sf::Texture ExitImage;
    if (!ExitImage.loadFromFile("MenuImages/ExitButton.png")) {}
    sf::Sprite Exit;
    Exit.setTexture(ExitImage);
    Exit.setPosition(85, 460);

    sf::Texture MusicVolumeImage;
    if (!MusicVolumeImage.loadFromFile("MenuImages/MusicVolumeButton.png")) {}
    sf::Sprite MusicVolume;
    MusicVolume.setTexture(MusicVolumeImage);
    MusicVolume.setPosition(80, 320);

    sf::Texture ShapeShadowRedImage;
    if (!ShapeShadowRedImage.loadFromFile("MenuImages/ShapeShadowRed.png")) {}
    sf::Sprite ShapeShadowRed;
    ShapeShadowRed.setTexture(ShapeShadowRedImage);
    ShapeShadowRed.setPosition(80, 410);

    sf::Texture ShapeShadowGreenImage;
    if (!ShapeShadowGreenImage.loadFromFile("MenuImages/ShapeShadowGreen.png")) {}
    sf::Sprite ShapeShadowGreen;
    ShapeShadowGreen.setTexture(ShapeShadowGreenImage);
    ShapeShadowGreen.setPosition(80, 410);

    sf::Texture LeftArrowImage;
    if (!LeftArrowImage.loadFromFile("MenuImages/LeftArrowButton.png")) {}
    sf::Sprite LeftArrow;
    LeftArrow.setTexture(LeftArrowImage);
    LeftArrow.setScale(0.3f, 0.3f);
    LeftArrow.setPosition(20, 850);

    sf::Texture VolumeArrowImage;
    if (!VolumeArrowImage.loadFromFile("MenuImages/VolumeArrow.png")) {}
    sf::Sprite VolumeArrow;
    VolumeArrow.setTexture(VolumeArrowImage);
    VolumeArrow.setScale(0.08f, 0.08f);
    VolumeArrow.setPosition(330, 280);

    


    sf::Sprite VolumeArrowDown;
    VolumeArrowDown.setTexture(VolumeArrowImage);
    VolumeArrowDown.setScale(0.08f, 0.08f);
    VolumeArrowDown.rotate(180);
    VolumeArrowDown.setPosition(378, 420);

    sf::Text Pkt;
    sf::Font font;
    font.loadFromFile("ARIAL.ttf");
    Pkt.setFont(font);
    Pkt.setFillColor(sf::Color::White);
    Pkt.setCharacterSize(40);
    std::stringstream ss;
    ss << this->Volume;
    std::string PunktyStr = ss.str();
    Pkt.setString(PunktyStr);
    Pkt.setPosition(320, 324);
    

    bool IsSettings = false;
    bool ShowShadow = false;

    while (*GameOrMenu == 0) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
                *GameOrMenu = 3;
            }
     
            if (event.type == sf::Event::MouseButtonPressed) {
                sf::Vector2i mousePosition = sf::Mouse::getPosition(window);

                if (IsSettings == false) {
                   
                    sf::FloatRect PlayButton = Play.getGlobalBounds();
                    sf::FloatRect SettingsButton = Settings.getGlobalBounds();
                    sf::FloatRect ExitButton = Exit.getGlobalBounds();

                    if (PlayButton.contains(static_cast<sf::Vector2f>(mousePosition))) {
                        std::cout << "Play!\n";
                        *GameOrMenu = 1;
                        window.clear();
                    }
                    if (SettingsButton.contains(static_cast<sf::Vector2f>(mousePosition))) {
                        std::cout << "Settings!\n";
                        IsSettings = true;
                        window.clear();

                    }
                    if (ExitButton.contains(static_cast<sf::Vector2f>(mousePosition))) {
                        window.close();
                        *GameOrMenu = 1;

                    }
                }
                else {
                    sf::FloatRect ShapeShadowButton = ShapeShadowRed.getGlobalBounds();
                    sf::FloatRect BackButton = LeftArrow.getGlobalBounds();
                    sf::FloatRect VolumeArrowButton = VolumeArrow.getGlobalBounds();
                    sf::FloatRect VolumeArrowDownButton = VolumeArrowDown.getGlobalBounds();

                    if (ShapeShadowButton.contains(static_cast<sf::Vector2f>(mousePosition)))
                        ShowShadow = !ShowShadow;
        
                    else if (BackButton.contains(static_cast<sf::Vector2f>(mousePosition))) 
                        IsSettings = false;
                    else if (VolumeArrowButton.contains(static_cast<sf::Vector2f>(mousePosition))) {
                        
                        this->Volume += 4;
                        if (this->Volume > 100) this->Volume = 100;
                        std::stringstream ss;
                        ss << this->Volume;
                        std::string PunktyStr = ss.str();
                        Pkt.setString(PunktyStr);
                        float textWidth = Pkt.getLocalBounds().width;

                        // Wyœrodkuj tekst na osi X wzglêdem punktu referencyjnego
                        float xPosition = 348 - (textWidth / 2);

                        // Ustaw pozycjê tekstu
                        Pkt.setPosition(xPosition, 324);
                        
                    }
                    else if (VolumeArrowDownButton.contains(static_cast<sf::Vector2f>(mousePosition))) {
                        
                        this->Volume -= 4;
                        if (this->Volume < 0) this->Volume = 0;
                        std::stringstream ss;
                        ss << this->Volume;
                        std::string PunktyStr = ss.str();
                        Pkt.setString(PunktyStr);
                        float textWidth = Pkt.getLocalBounds().width;

                        // Wyœrodkuj tekst na osi X wzglêdem punktu referencyjnego
                        float xPosition = 348 - (textWidth / 2);

                        // Ustaw pozycjê tekstu
                        Pkt.setPosition(xPosition, 324);
                    }

                }
            }
        }
        window.clear();
        if (IsSettings == false) {
            for (int i = 0; i < ListOfShapes.size(); i++) {
                Shapes* CurrentShape = ListOfShapes[i];
                CurrentShape->Move(30, 0);
                int id = CurrentShape->GetId();
                int x = CurrentShape->GetX() * 0.001;
                int y = CurrentShape->GetY() *30;
                for (int j = 0; j < CurrentShape->Points.size(); j++) {
                    int Px = x + CurrentShape->Points[j][0] * 30;
                    int Py = y + CurrentShape->Points[j][1] * 30;
                    if (id == 2) square.setFillColor(sf::Color::Yellow);
                    else if (id == 3) square.setFillColor(sf::Color::Magenta);
                    else if (id == 4) square.setFillColor(Pink);
                    else if (id == 5) square.setFillColor(Orange);
                    else if (id == 6) square.setFillColor(sf::Color::Red);
                    else if (id == 7) square.setFillColor(sf::Color::Green);
                    else if (id == 8) square.setFillColor(sf::Color::Cyan);
                    square.setPosition(Py, Px);
                    window.draw(square);

                }
                if (x > 1000) {
                   
                    delete CurrentShape;
                    int Number = distribution(generator);
                    Shapes* Shape = RandomShape();
                    Shape->RandRotation();
                    Shape->SetX(-100000);
                    Shape->SetY(Number);
                    ListOfShapes[i] = Shape;
                }
            }
            window.draw(Play);
            window.draw(Settings);
            window.draw(Exit);
            
        }
        else {
            


            window.draw(MusicVolume);
            window.draw(LeftArrow);
            window.draw(VolumeArrow);
            window.draw(VolumeArrowDown);
            window.draw(Pkt);
            if (ShowShadow) {
                window.draw(ShapeShadowGreen);
                this->ShowShadowContest = true;
            }
            else {
                window.draw(ShapeShadowRed);
                this->ShowShadowContest = false;
            }
        }
        
        window.display();
    }
    window.clear();
    for (int i = 0; i < ListOfShapes.size(); i++) {
        delete ListOfShapes[i];
    }
}