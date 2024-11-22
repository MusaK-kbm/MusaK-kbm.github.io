
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <vector>
#include <string>
#include <random>
#include <ctime>
#include <iostream>

// Hangman variables
const int MAX_TRIES = 5;
std::string getRandomWord();
int letterFill(char guess, std::string& maskedWord, const std::string& secretWord);

int main() {
    // Initialize SFML window
    sf::RenderWindow window(sf::VideoMode(600, 400), "Hangman Game");

    // Choose a word
    std::string secretWord = getRandomWord();
    std::string maskedWord(secretWord.size(), '*');
    int wrongGuesses = 0;

    // Set up font
    sf::Font font;
    if (!font.loadFromFile("arial.ttf")) {
        std::cerr << "Font loading failed\n";
        return 1;
    }

    // Text elements
    sf::Text displayWord(maskedWord, font, 30);
    displayWord.setPosition(50, 50);
    sf::Text message("Guess a letter:", font, 20);
    message.setPosition(50, 150);
    sf::Text triesLeft("Tries left: " + std::to_string(MAX_TRIES - wrongGuesses), font, 20);
    triesLeft.setPosition(50, 200);

    // Main game loop
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            } else if (event.type == sf::Event::TextEntered) {
                if (isalpha(event.text.unicode)) {
                    char guess = tolower(static_cast<char>(event.text.unicode));
                    
                    // Process the guess
                    if (letterFill(guess, maskedWord, secretWord) == 0) {
                        wrongGuesses++;
                        message.setString("Incorrect guess!");
                    } else {
                        message.setString("Correct guess!");
                    }

                    // Update display
                    displayWord.setString(maskedWord);
                    triesLeft.setString("Tries left: " + std::to_string(MAX_TRIES - wrongGuesses));

                    // Check for win or lose
                    if (maskedWord == secretWord) {
                        message.setString("You won! The word was: " + secretWord);
                        window.clear();
                        window.draw(displayWord);
                        window.draw(message);
                        window.draw(triesLeft);
                        window.display();
                        sf::sleep(sf::seconds(3)); // Pause to show win message
                        window.close();
                    } else if (wrongGuesses >= MAX_TRIES) {
                        message.setString("Game over! The word was: " + secretWord);
                        window.clear();
                        window.draw(displayWord);
                        window.draw(message);
                        window.draw(triesLeft);
                        window.display();
                        sf::sleep(sf::seconds(3)); // Pause to show lose message
                        window.close();
                    }
                }
            }
        }

        // Draw everything
        window.clear();
        window.draw(displayWord);
        window.draw(message);
        window.draw(triesLeft);
        window.display();
    }

    return 0;
}

std::string getRandomWord() {
    std::vector<std::string> words = {
        "Afghanistan", "Albania", "Algeria", "America", "Andorra",
        "Angola", "Antigua", "Argentina", "Armenia", "Australia",
        "Austria", "Azerbaijan", "Bahamas", "Bahrain", "Bangladesh",
        "Barbados", "Belarus", "Belgium", "Belize", "Benin",
        "Bhutan", "Bissau", "Bolivia", "Bosnia", "Botswana",
        "Brazil", "British", "Brunei", "Bulgaria", "Burkina",
        "Burma", "Burundi", "Cambodia", "Cameroon", "Canada",
        "Cape Verde", "Central African Republic", "Chad", "Chile", "China",
        "Colombia", "Comoros", "Congo", "Costa Rica", "Croatia",
        "Cuba", "Cyprus", "Czech", "Denmark", "Djibouti",
        "Dominica", "East Timor", "Ecuador", "Egypt", "El Salvador",
        "Emirates", "England", "Eritrea", "Estonia", "Ethiopia",
        "Fiji", "Finland", "France", "Gabon", "Gambia",
        "Georgia", "Germany", "Ghana", "Great Britain", "Greece",
        "Grenada", "Grenadines", "Guatemala", "Guinea", "Guyana",
        "Haiti", "Herzegovina", "Honduras", "Hungary", "Iceland",
        "India", "Indonesia", "Iran", "Iraq", "Ireland",
        "Israel", "Italy", "Ivory Coast", "Jamaica", "Japan",
        "Jordan", "Kazakhstan", "Kenya", "Kiribati", "Korea",
        "Kosovo", "Kuwait", "Kyrgyzstan", "Laos", "Latvia",
        "Lebanon", "Lesotho", "Liberia", "Libya", "Liechtenstein",
        "Lithuania", "Luxembourg", "Macedonia", "Madagascar", "Malawi",
        "Malaysia", "Maldives", "Mali", "Malta", "Marshall",
        "Mauritania", "Mauritius", "Mexico", "Micronesia", "Moldova",
        "Monaco", "Mongolia", "Montenegro", "Morocco", "Mozambique",
        "Myanmar", "Namibia", "Nauru", "Nepal", "Netherlands",
        "New Zealand", "Nicaragua", "Niger", "Nigeria", "Norway",
        "Oman", "Pakistan", "Palau", "Panama", "Papua",
        "Paraguay", "Peru", "Philippines", "Poland", "Portugal",
        "Qatar", "Romania", "Russia", "Rwanda", "Samoa",
        "San Marino", "Sao Tome", "Saudi Arabia", "Scotland", "Senegal",
        "Serbia", "Seychelles", "Sierra Leone", "Singapore", "Slovakia",
        "Slovenia", "Solomon", "Somalia", "South Africa", "South Sudan",
        "Spain", "Sri Lanka", "St. Kitts", "St. Lucia", "Sudan",
        "Suriname", "Swaziland", "Sweden", "Switzerland", "Syria",
        "Taiwan", "Tajikistan", "Tanzania", "Thailand", "Tobago",
        "Togo", "Tonga", "Trinidad", "Tunisia", "Turkey",
        "Turkmenistan", "Tuvalu", "Uganda", "Ukraine", "United Kingdom",
        "United States", "Uruguay", "USA", "Uzbekistan", "Vanuatu",
        "Vatican", "Venezuela", "Vietnam", "Wales", "Yemen",
        "Zambia", "Zimbabwe"
    };
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(0, words.size() - 1);
    return words[dist(gen)];
}

int letterFill(char guess, std::string& maskedWord, const std::string& secretWord) {
    int matches = 0;
    for (size_t i = 0; i < secretWord.size(); i++) {
        if (tolower(secretWord[i]) == guess && maskedWord[i] == '*') {
            maskedWord[i] = secretWord[i];
            matches++;
        }
    }
    return matches;
}