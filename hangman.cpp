#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <cctype>

using namespace std;

class HangmanGame {
private:
    string currentWord; // word to guess
    string guessedWord; // current state of guessed word
    vector<char> wrongGuesses; // list of the wrong guesses
    int maxAttempts; // maximum number of incorrect guesses that are allowed

public:
    HangmanGame(const string& word, int attempts)
        : currentWord(word), maxAttempts(attempts) {
        guessedWord = string(currentWord.length(), '_'); // guessed words are filled with underscores
        for (size_t i = 0; i < currentWord.length(); ++i) {
            if (currentWord[i] == ' ') {
                guessedWord[i] = ' ';
            }
        }
    }

    bool guess(char letter) {
        bool found = false;
        letter = tolower(letter);
        for (size_t i = 0; i < currentWord.length(); ++i) {
            if (tolower(currentWord[i]) == letter) {
                guessedWord[i] = currentWord[i];
                found = true;
            }
        }
        if (!found && find(wrongGuesses.begin(), wrongGuesses.end(), letter) == wrongGuesses.end()) {
            wrongGuesses.push_back(letter);
        }
        return found;
    }

    bool isWon() const {
        return guessedWord == currentWord;
    }

    bool isLost() const {
        return wrongGuesses.size() >= maxAttempts;
    }

    string getGuessedWord() const {
        return guessedWord;
    }

    string getWrongGuesses() const {
        return string(wrongGuesses.begin(), wrongGuesses.end());
    }

    string getCurrentWord() const {
        return currentWord;
    }

    int getMaxAttempts() const {
        return maxAttempts;
    }
};

// function to extract a random word from the countries.txt file
string getRandomWord(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Could not open the file: " << filename << endl;
        exit(1);
    }

    vector<string> words;
    string word;
    while (getline(file, word)) {
        if (!word.empty()) {
            words.push_back(word);
        }
    }
    file.close();

    if (words.empty()) {
        cerr << "No words found in the file!" << endl;
        exit(1);
    }

    srand(static_cast<unsigned int>(time(nullptr)));
    return words[rand() % words.size()];
}

// fucntion for rendering the visual aspect of the game
void drawGame(sf::RenderWindow& window, HangmanGame& game, sf::Font& font, sf::CircleShape& head, sf::RectangleShape& body, sf::RectangleShape& leftArm, sf::RectangleShape& rightArm, sf::RectangleShape& leftLeg, sf::RectangleShape& rightLeg) {
    window.clear(sf::Color::White);

    sf::Vector2u windowSize = window.getSize();
    float centerX = windowSize.x / 2.0f;

    // display the guessed word
    sf::Text guessedWordText(game.getGuessedWord(), font, 30);
    guessedWordText.setFillColor(sf::Color::Black);
    guessedWordText.setPosition(centerX - guessedWordText.getLocalBounds().width / 2, 50);
    window.draw(guessedWordText);

    // display the incorrectly guessed alphabets
    sf::Text wrongGuessesText("Wrong guesses: " + game.getWrongGuesses(), font, 20);
    wrongGuessesText.setFillColor(sf::Color::Red);
    wrongGuessesText.setPosition(50, 120);
    window.draw(wrongGuessesText);

    // display the remaining attempts left  
    int attemptsLeft = game.getMaxAttempts() - game.getWrongGuesses().size();
    sf::Text attemptsText("Attempts left: " + to_string(attemptsLeft), font, 20);
    attemptsText.setFillColor(sf::Color::Black);
    attemptsText.setPosition(50, 180);
    window.draw(attemptsText);


    float hangmanBaseX = centerX - 50;
    float hangmanBaseY = 250;

    if (game.getWrongGuesses().size() >= 1) {
        head.setPosition(hangmanBaseX, hangmanBaseY - 50);
        window.draw(head);
    }
    if (game.getWrongGuesses().size() >= 2) {
        body.setPosition(hangmanBaseX + 10, hangmanBaseY - 20);
        window.draw(body);
    }
    if (game.getWrongGuesses().size() >= 3) {
        leftArm.setPosition(hangmanBaseX - 15, hangmanBaseY - 20);
        leftArm.setRotation(45);
        window.draw(leftArm);
    }
    if (game.getWrongGuesses().size() >= 4) {
        rightArm.setPosition(hangmanBaseX + 30, hangmanBaseY - 20);
        rightArm.setRotation(-45);
        window.draw(rightArm);
    }
    if (game.getWrongGuesses().size() >= 5) {
        leftLeg.setPosition(hangmanBaseX + 5, hangmanBaseY + 30);
        leftLeg.setRotation(45);
        window.draw(leftLeg);
    }
    if (game.getWrongGuesses().size() >= 6) {
        rightLeg.setPosition(hangmanBaseX + 15, hangmanBaseY + 30);
        rightLeg.setRotation(-45);
        window.draw(rightLeg);
    }

    window.display();
}

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Hangman Game");
    sf::Font font;
    if (!font.loadFromFile("arial.ttf")) {
        cerr << "Could not load font!" << endl;
        return -1;
    }

    // intialization of shapes for the hangman figure
    sf::CircleShape head(15);
    head.setFillColor(sf::Color::Black);
    head.setOrigin(15, 15);

    sf::RectangleShape body(sf::Vector2f(5, 50));
    body.setFillColor(sf::Color::Black);
    body.setOrigin(2.5, 0);

    sf::RectangleShape leftArm(sf::Vector2f(5, 30));
    leftArm.setFillColor(sf::Color::Black);
    leftArm.setOrigin(2.5, 0);

    sf::RectangleShape rightArm(sf::Vector2f(5, 30));
    rightArm.setFillColor(sf::Color::Black);
    rightArm.setOrigin(2.5, 0);

    sf::RectangleShape leftLeg(sf::Vector2f(5, 30));
    leftLeg.setFillColor(sf::Color::Black);
    leftLeg.setOrigin(2.5, 0);

    sf::RectangleShape rightLeg(sf::Vector2f(5, 30));
    rightLeg.setFillColor(sf::Color::Black);
    rightLeg.setOrigin(2.5, 0);

    // random word extracted from countries.txt file for the game
    string filename = "countries.txt";
    string randomWord = getRandomWord(filename);
    HangmanGame game(randomWord, 6);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::TextEntered) {
                if (event.text.unicode < 128 && isalpha(event.text.unicode)) {
                    char letter = static_cast<char>(event.text.unicode);
                    game.guess(tolower(letter));
                }
            }
        }

        drawGame(window, game, font, head, body, leftArm, rightArm, leftLeg, rightLeg);

        // end the game when it has been either won or lost
        if (game.isWon() || game.isLost()) {
            window.clear(sf::Color::White);
            string resultMessage = game.isWon() ? "You Won!" : "You Lost! The word was: " + game.getCurrentWord();
            sf::Text resultText(resultMessage, font, 30);
            resultText.setFillColor(sf::Color::Black);
            resultText.setPosition(window.getSize().x / 2.0f - resultText.getLocalBounds().width / 2, window.getSize().y / 2.0f - 50);
            window.draw(resultText);
            window.display();
            sf::sleep(sf::seconds(3));
            window.close();
        }
    }

    return 0;
}
