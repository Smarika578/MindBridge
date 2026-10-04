#include <SFML/Graphics.hpp>
#include <optional>
#include <string>
#include <fstream>
#include <algorithm>
#include <cctype>

void drawText(
    sf::RenderWindow& window,
    sf::Font& font,
    const std::string& text,
    unsigned int size,
    float x,
    float y,
    sf::Color color)
{
    sf::Text t(font, text, size);
    t.setFillColor(color);
    t.setPosition(sf::Vector2f(x, y));
    window.draw(t);
}

// Convert text to lowercase
std::string lowerCase(std::string text)
{
    std::transform(
        text.begin(),
        text.end(),
        text.begin(),
        [](unsigned char c)
        {
            return static_cast<char>(std::tolower(c));
        });

    return text;
}

// Rule-based MindBridge response
std::string getResponse(const std::string& message)
{
    std::string text = lowerCase(message);

    if (text.find("hello") != std::string::npos ||
        text.find("hi") != std::string::npos ||
        text.find("hey") != std::string::npos)
    {
        return "Hello! I am here to listen.";
    }

    if (text.find("stress") != std::string::npos ||
        text.find("stressed") != std::string::npos ||
        text.find("anxious") != std::string::npos ||
        text.find("anxiety") != std::string::npos)
    {
        return "It sounds difficult. Try taking a slow breath.";
    }

    if (text.find("sad") != std::string::npos ||
        text.find("lonely") != std::string::npos)
    {
        return "I am sorry you are feeling this way. You can share more if you want.";
    }

    if (text.find("happy") != std::string::npos ||
        text.find("good") != std::string::npos)
    {
        return "That is wonderful to hear! What made your day positive?";
    }

    if (text.find("tired") != std::string::npos ||
        text.find("exhausted") != std::string::npos)
    {
        return "You may need a small break. Be kind to yourself.";
    }

    if (text.find("help") != std::string::npos)
    {
        return "I can listen and suggest simple wellness activities.";
    }

    if (text.find("suicid") != std::string::npos ||
        text.find("kill myself") != std::string::npos ||
        text.find("hurt myself") != std::string::npos)
    {
        return "Please contact a trusted person or qualified professional.";
    }

    return "Thank you for sharing. Would you like to tell me more?";
}

int main()
{
    // ------------------------------------------------
    // APPLICATION STATE
    // ------------------------------------------------

    std::string selectedMood = "";
    std::string userMessage = "";
    std::string chatResponse =
        "Hello! I am here to listen.";

    bool chatScreen = false;

    // ------------------------------------------------
    // WINDOW
    // ------------------------------------------------

    sf::RenderWindow window(
        sf::VideoMode({1100, 700}),
        "MindBridge - Offline Wellness Companion"
    );

    // ------------------------------------------------
    // FONT
    // ------------------------------------------------

    sf::Font font;

    if (!font.openFromFile(
        "/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf"))
    {
        return 1;
    }

    // ------------------------------------------------
    // COLORS
    // ------------------------------------------------

    sf::Color darkGreen(25, 70, 60);
    sf::Color green(75, 125, 100);
    sf::Color cream(245, 246, 232);
    sf::Color white(250, 250, 247);
    sf::Color textDark(25, 75, 70);
    sf::Color lightBackground(232, 242, 238);

    // ------------------------------------------------
    // BACKGROUND
    // ------------------------------------------------

    sf::RectangleShape background(
        sf::Vector2f(1100, 700));
    background.setFillColor(cream);

    sf::RectangleShape sky(
        sf::Vector2f(1100, 500));
    sky.setFillColor(sf::Color(220, 239, 235));

    sf::RectangleShape lake(
        sf::Vector2f(1100, 250));
    lake.setFillColor(sf::Color(190, 220, 218));
    lake.setPosition(sf::Vector2f(0, 450));

    // ------------------------------------------------
    // MOUNTAINS
    // ------------------------------------------------

    sf::ConvexShape mountain1;

    mountain1.setPointCount(4);

    mountain1.setPoint(
        0, sf::Vector2f(0, 450));

    mountain1.setPoint(
        1, sf::Vector2f(230, 270));

    mountain1.setPoint(
        2, sf::Vector2f(480, 450));

    mountain1.setPoint(
        3, sf::Vector2f(0, 450));

    mountain1.setFillColor(
        sf::Color(155, 190, 195));

    sf::ConvexShape mountain2;

    mountain2.setPointCount(4);

    mountain2.setPoint(
        0, sf::Vector2f(300, 450));

    mountain2.setPoint(
        1, sf::Vector2f(570, 300));

    mountain2.setPoint(
        2, sf::Vector2f(850, 450));

    mountain2.setPoint(
        3, sf::Vector2f(300, 450));

    mountain2.setFillColor(
        sf::Color(170, 200, 200));

    sf::ConvexShape mountain3;

    mountain3.setPointCount(4);

    mountain3.setPoint(
        0, sf::Vector2f(650, 450));

    mountain3.setPoint(
        1, sf::Vector2f(900, 280));

    mountain3.setPoint(
        2, sf::Vector2f(1100, 450));

    mountain3.setPoint(
        3, sf::Vector2f(650, 450));

    mountain3.setFillColor(
        sf::Color(145, 185, 190));

    // ------------------------------------------------
    // SUN
    // ------------------------------------------------

    sf::CircleShape sun(55);

    sun.setFillColor(
        sf::Color(250, 225, 165));

    sun.setPosition(
        sf::Vector2f(880, 190));

    // ------------------------------------------------
    // SIDEBAR
    // ------------------------------------------------

    sf::RectangleShape sidebar(
        sf::Vector2f(145, 700));

    sidebar.setFillColor(darkGreen);

    sf::CircleShape logo(35);

    logo.setFillColor(
        sf::Color(90, 145, 115));

    logo.setPosition(
        sf::Vector2f(37, 35));

    // ------------------------------------------------
    // MOOD BUTTONS
    // ------------------------------------------------

    sf::RectangleShape happy(
        sf::Vector2f(240, 80));

    happy.setPosition(
        sf::Vector2f(210, 235));

    happy.setFillColor(
        sf::Color(200, 232, 195));

    sf::RectangleShape calm(
        sf::Vector2f(240, 80));

    calm.setPosition(
        sf::Vector2f(470, 235));

    calm.setFillColor(
        sf::Color(195, 225, 238));

    sf::RectangleShape sad(
        sf::Vector2f(240, 80));

    sad.setPosition(
        sf::Vector2f(730, 235));

    sad.setFillColor(
        sf::Color(235, 205, 215));

    // ------------------------------------------------
    // MAIN LOOP
    // ------------------------------------------------

    while (window.isOpen())
    {
        while (const std::optional event =
                   window.pollEvent())
        {
            // ----------------------------------------
            // CLOSE WINDOW
            // ----------------------------------------

            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }

            // ----------------------------------------
            // KEYBOARD
            // ----------------------------------------

            if (const auto* key =
                    event->getIf<sf::Event::KeyPressed>())
            {
                // Escape = return home
                if (key->code ==
                    sf::Keyboard::Key::Escape)
                {
                    chatScreen = false;
                }

                // Enter = send message
                if (chatScreen &&
                    key->code ==
                    sf::Keyboard::Key::Enter)
                {
                    if (!userMessage.empty())
                    {
                        chatResponse =
                            getResponse(userMessage);

                        userMessage.clear();
                    }
                }

                // Backspace
                if (chatScreen &&
                    key->code ==
                    sf::Keyboard::Key::Backspace)
                {
                    if (!userMessage.empty())
                    {
                        userMessage.pop_back();
                    }
                }
            }

            // ----------------------------------------
            // TEXT INPUT
            // ----------------------------------------

            if (chatScreen)
            {
                if (const auto* textEntered =
                        event->getIf<
                            sf::Event::TextEntered>())
                {
                    if (textEntered->unicode >= 32 &&
                        textEntered->unicode < 127)
                    {
                        userMessage +=
                            static_cast<char>(
                                textEntered->unicode);
                    }
                }
            }

            // ----------------------------------------
            // MOUSE CLICK
            // ----------------------------------------

            if (const auto* mouseButton =
                    event->getIf<
                        sf::Event::MouseButtonPressed>())
            {
                if (mouseButton->button ==
                    sf::Mouse::Button::Left)
                {
                    float x =
                        static_cast<float>(
                            mouseButton->position.x);

                    float y =
                        static_cast<float>(
                            mouseButton->position.y);

                    // --------------------------------
                    // CHAT CARD
                    // --------------------------------

                    if (!chatScreen &&
                        x >= 195 && x <= 465 &&
                        y >= 370 && y <= 540)
                    {
                        chatScreen = true;
                    }

                    // --------------------------------
                    // HAPPY
                    // --------------------------------

                    if (!chatScreen &&
                        x >= 210 && x <= 450 &&
                        y >= 235 && y <= 315)
                    {
                        selectedMood = "Happy";

                        std::ofstream file(
                            "data/moods.txt",
                            std::ios::app);

                        if (file)
                        {
                            file << "Happy\n";
                        }
                    }

                    // --------------------------------
                    // CALM
                    // --------------------------------

                    if (!chatScreen &&
                        x >= 470 && x <= 710 &&
                        y >= 235 && y <= 315)
                    {
                        selectedMood = "Calm";

                        std::ofstream file(
                            "data/moods.txt",
                            std::ios::app);

                        if (file)
                        {
                            file << "Calm\n";
                        }
                    }

                    // --------------------------------
                    // SAD
                    // --------------------------------

                    if (!chatScreen &&
                        x >= 730 && x <= 970 &&
                        y >= 235 && y <= 315)
                    {
                        selectedMood = "Sad";

                        std::ofstream file(
                            "data/moods.txt",
                            std::ios::app);

                        if (file)
                        {
                            file << "Sad\n";
                        }
                    }
                }
            }
        }

        // ==================================================
        // DRAW
        // ==================================================

        window.clear();

        // ==================================================
        // CHAT SCREEN
        // ==================================================

        if (chatScreen)
        {
            sf::RectangleShape chatBackground(
                sf::Vector2f(1100, 700));

            chatBackground.setFillColor(
                lightBackground);

            window.draw(chatBackground);

            // Header
            sf::RectangleShape chatHeader(
                sf::Vector2f(1100, 100));

            chatHeader.setFillColor(
                darkGreen);

            window.draw(chatHeader);

            drawText(
                window,
                font,
                "MindBridge Chat",
                34,
                190,
                30,
                sf::Color::White);

            drawText(
                window,
                font,
                "Offline Supportive Companion",
                17,
                193,
                70,
                sf::Color(215, 235, 225));

            drawText(
                window,
                font,
                "Press ESC to return home",
                15,
                850,
                42,
                sf::Color(220, 235, 228));

            // Chat area
            sf::RectangleShape responseBox(
                sf::Vector2f(760, 170));

            responseBox.setPosition(
                sf::Vector2f(180, 160));

            responseBox.setFillColor(
                sf::Color::White);

            window.draw(responseBox);

            drawText(
                window,
                font,
                "MindBridge",
                20,
                205,
                185,
                darkGreen);

            drawText(
                window,
                font,
                chatResponse,
                19,
                205,
                230,
                sf::Color(70, 85, 80));

            // Input box
            sf::RectangleShape inputBox(
                sf::Vector2f(760, 80));

            inputBox.setPosition(
                sf::Vector2f(180, 380));

            inputBox.setFillColor(
                sf::Color::White);

            inputBox.setOutlineThickness(2);

            inputBox.setOutlineColor(
                sf::Color(150, 180, 165));

            window.draw(inputBox);

            drawText(
                window,
                font,
                userMessage.empty()
                    ? "Type your message..."
                    : userMessage,
                18,
                205,
                407,
                userMessage.empty()
                    ? sf::Color(150, 160, 155)
                    : sf::Color(50, 70, 65));

            drawText(
                window,
                font,
                "Press ENTER to send",
                15,
                205,
                490,
                green);

            // Example prompts
            drawText(
                window,
                font,
                "Try: hello | I feel stressed | I feel sad | I feel happy",
                16,
                260,
                570,
                sf::Color(80, 100, 90));

            drawText(
                window,
                font,
                "MindBridge provides supportive responses and is not a medical diagnosis tool.",
                13,
                300,
                630,
                sf::Color(110, 120, 115));
        }

        // ==================================================
        // HOME SCREEN
        // ==================================================

        else
        {
            window.draw(background);
            window.draw(sky);

            window.draw(mountain1);
            window.draw(mountain2);
            window.draw(mountain3);

            window.draw(lake);
            window.draw(sun);

            window.draw(sidebar);
            window.draw(logo);

            // Sidebar
            drawText(
                window,
                font,
                "M",
                35,
                58,
                36,
                sf::Color::White);

            drawText(
                window,
                font,
                "HOME",
                18,
                43,
                150,
                sf::Color::White);

            drawText(
                window,
                font,
                "CHAT",
                18,
                48,
                220,
                sf::Color::White);

            drawText(
                window,
                font,
                "MOOD",
                18,
                45,
                290,
                sf::Color::White);

            drawText(
                window,
                font,
                "JOURNAL",
                18,
                35,
                360,
                sf::Color::White);

            drawText(
                window,
                font,
                "BREATHING",
                16,
                28,
                430,
                sf::Color::White);

            drawText(
                window,
                font,
                "SETTINGS",
                16,
                30,
                625,
                sf::Color(220, 235, 228));

            // Header
            drawText(
                window,
                font,
                "MindBridge",
                42,
                190,
                50,
                textDark);

            drawText(
                window,
                font,
                "Your Offline Wellness Companion",
                22,
                193,
                105,
                sf::Color(65, 110, 100));

            drawText(
                window,
                font,
                "A calmer mind builds a brighter tomorrow.",
                18,
                745,
                75,
                textDark);

            // Question
            drawText(
                window,
                font,
                "How are you feeling today?",
                34,
                405,
                170,
                textDark);

            // Mood buttons
            window.draw(happy);
            window.draw(calm);
            window.draw(sad);

            drawText(
                window,
                font,
                "HAPPY",
                23,
                300,
                262,
                sf::Color(40, 90, 50));

            drawText(
                window,
                font,
                "CALM",
                23,
                565,
                262,
                sf::Color(40, 80, 115));

            drawText(
                window,
                font,
                "SAD",
                23,
                825,
                262,
                sf::Color(110, 55, 75));

            // Selected mood
            if (!selectedMood.empty())
            {
                drawText(
                    window,
                    font,
                    "Mood saved: " + selectedMood,
                    18,
                    465,
                    205,
                    darkGreen);
            }

            // Chat card
            sf::RectangleShape chatCard(
                sf::Vector2f(270, 170));

            chatCard.setPosition(
                sf::Vector2f(195, 370));

            chatCard.setFillColor(white);

            window.draw(chatCard);

            drawText(
                window,
                font,
                "CHAT COMPANION",
                20,
                220,
                395,
                textDark);

            drawText(
                window,
                font,
                "Talk with an offline",
                16,
                220,
                435,
                sf::Color(80, 95, 90));

            drawText(
                window,
                font,
                "supportive companion.",
                16,
                220,
                460,
                sf::Color(80, 95, 90));

            drawText(
                window,
                font,
                "->",
                25,
                425,
                480,
                green);

            // Journal card
            sf::RectangleShape journalCard(
                sf::Vector2f(270, 170));

            journalCard.setPosition(
                sf::Vector2f(490, 370));

            journalCard.setFillColor(white);

            window.draw(journalCard);

            drawText(
                window,
                font,
                "JOURNAL",
                20,
                515,
                395,
                textDark);

            drawText(
                window,
                font,
                "Write your thoughts",
                16,
                515,
                435,
                sf::Color(80, 95, 90));

            drawText(
                window,
                font,
                "and save them locally.",
                16,
                515,
                460,
                sf::Color(80, 95, 90));

            drawText(
                window,
                font,
                "->",
                25,
                720,
                480,
                green);

            // Breathing card
            sf::RectangleShape breathingCard(
                sf::Vector2f(270, 170));

            breathingCard.setPosition(
                sf::Vector2f(785, 370));

            breathingCard.setFillColor(white);

            window.draw(breathingCard);

            drawText(
                window,
                font,
                "BREATHING",
                20,
                810,
                395,
                textDark);

            drawText(
                window,
                font,
                "Follow a simple",
                16,
                810,
                435,
                sf::Color(80, 95, 90));

            drawText(
                window,
                font,
                "guided breathing exercise.",
                16,
                810,
                460,
                sf::Color(80, 95, 90));

            drawText(
                window,
                font,
                "->",
                25,
                1015,
                480,
                green);

            // Privacy
            drawText(
                window,
                font,
                "OFFLINE & LOCAL",
                18,
                440,
                575,
                darkGreen);

            drawText(
                window,
                font,
                "| Your data stays on this system",
                16,
                600,
                577,
                sf::Color(70, 95, 90));

            // Footer
            drawText(
                window,
                font,
                "MindBridge is a wellness companion, not a medical diagnosis tool.",
                14,
                330,
                650,
                sf::Color(100, 110, 105));
        }

        window.display();
    }

    return 0;
}
