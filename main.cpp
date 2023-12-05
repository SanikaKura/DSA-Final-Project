
#include <iostream>
#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <cstring>
#include <fstream>
#include <sstream>
#include <chrono>
#include "trie.h"
#include "hashMap.h"
using namespace std;
using namespace sf;
using namespace std::chrono;

void setText(sf::Text &text, float x, float y){

    sf::FloatRect textRect = text.getLocalBounds();
    text.setOrigin(textRect.left + textRect.width/2.0f,
                   textRect.top + textRect.height/2.0f);
    text.setPosition(sf::Vector2f(x, y));
}


int main(){
    string nameInput = "name" ;

    int x =700; int y = 700;

    ///objects for first window
    sf::RenderWindow window(sf::VideoMode(x, y), "SFML works!");
    sf::Text title;
    sf::Font fontType;
    fontType.loadFromFile("font.ttf");

    title.setFont(fontType);
    title.setString("WELCOME TO DOG RANK!");
    title.setCharacterSize(24);
    title.setStyle(sf::Text::Bold | sf::Text::Underlined);
    setText(title, x / 2.0f, (y / 2.0f) - 160);

    sf::Text name_input;
    name_input.setString("Enter your dogs name: ");name_input.setCharacterSize(20);name_input.setFont(fontType);
    setText(name_input, x / 2.0f, (y / 2.0f) - 75);
    name_input.setStyle(sf::Text::Bold);

    Sprite dog;
    Texture tdog;
    tdog.loadFromFile("dogImage.png");
    dog.setTexture(tdog);
    dog.setPosition(110, 400);

    string cursor = "|";
    sf::Text inputText;
    //inputText.setString("Enter your name: ");
    inputText.setFont(fontType);
    inputText.setCharacterSize(20);
    //setText(inputText, 800/2.0f, (600/2.0f)-75);
    inputText.setStyle(sf::Text::Bold);
    inputText.setFillColor(sf::Color::Yellow);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {

            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::TextEntered && event.key.code != sf::Keyboard::Backspace) {
                if (cursor.size() <= 10 && isdigit(event.text.unicode) == false &&
                    event.text.unicode > 31 && event.text.unicode <= 127) {
                    cursor.pop_back();
                    cursor += event.text.unicode;
                    cursor += "|";
                    inputText.setString(cursor);
                }
                nameInput = cursor ;
            }
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Backspace) {
                    if (!cursor.empty()) {
                        cursor.pop_back();
                        inputText.setString(cursor);
                    }
                }

                if (event.type == sf::Event::KeyPressed) {
                    if (event.key.code == sf::Keyboard::Enter) {
                        window.close();
                    }
                }
            }
            if (event.type == Event::MouseButtonPressed) {
                if (Mouse::isButtonPressed(Mouse::Left)) {
                    if (0 < event.mouseButton.x && event.mouseButton.x < 200 ) {

                        window.close();
                    }
                    else if (201 < event.mouseButton.x && event.mouseButton.x < 400 &&
                             0 < event.mouseButton.y && event.mouseButton.y < 400) {
                        window.close();
                    }
                }
            }
        }
        setText(inputText, 350, 300);
        window.clear(sf::Color::Blue);
        window.draw(title);
        window.draw(inputText);
        window.draw(name_input);
        window.draw(dog);
        window.display();
    }
    ///////////////////////////////////////

    string upper; //this is our user input
    for (char c : nameInput){
        upper += toupper(c);
    }

    set <string> names;
    ifstream dog_file("NYC_Dog_Licensing_Dataset.csv");
    string line;
    trie tree_26; //initializing tree
    int total;
    auto start = high_resolution_clock::now();
    while (getline(dog_file, line)){
        istringstream string_stream(line);
        string name;
        if (getline(string_stream, name, ',')){
            if (name != "UNKNOWN" && name != "AnimalName" && name != "NAME" && name != "NAME NOT PROVIDED" && name != "NAMENOTPROVIDED" && name != "Unknown"){
                string final;

                for(char c : name){
                    if (isalpha(c)){
                        final+=c;
                    }
                }
                if (final == "true"){
                    final = "TRUE";
                }
                names.insert(final);
                tree_26.insert(final);
            }
        }
    }
    dog_file.close();
    //cout << "26-ary tree results: " << tree_26.get_count(upper) << endl;
    tree_26.get_rank(tree_26.root, upper);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<std::chrono::milliseconds>(stop - start);    ///timer for 26 ary tree
    //cout << "time taken: " << duration.count() << " milliseconds" << endl << endl;


    ifstream dog_file2("NYC_Dog_Licensing_Dataset.csv");
    string line2;
    hashMap dog_hash;
    auto start2 = high_resolution_clock::now();

    ///                                                                          reading dog file!
    while (getline(dog_file2, line2)){
        istringstream string_stream(line2);
        string name;
        if (getline(string_stream, name, ',')){
            if (name != "UNKNOWN" && name != "AnimalName" && name != "NAME" && name != "NAME NOT PROVIDED" && name != "NAMENOTPROVIDED" && name != "Unknown"){
                string final;
                for(char c : name){
                    if (isalpha(c)){
                        final+=c;
                    }
                }
                if (final == "true"){
                    final = "TRUE";
                }
                dog_hash.insert((string)(final));
            }
        }
    }
    dog_file2.close();
    //cout << "hash map results: " << dog_hash.get_count(upper) << endl;
    //cout << "hash map rank: " << dog_hash.ranking(upper) << endl;
    auto stop2 = high_resolution_clock::now();
    auto duration2 = duration_cast<std::chrono::milliseconds>(stop2 - start2);           ///timer for hashmap!
    //cout << "time taken: " << duration2.count()  << " milliseconds" << endl;
    ////////////////////////////////////////////////////

    int tree_count = tree_26.get_count(upper.substr(0, upper.length()-1));
    //cout << upper.substr(0, upper.length()-1);
    string theDog = upper.substr(0, upper.length()-1);
    int tree_rank = tree_26.get_rank(tree_26.root, upper.substr(0, upper.length()-1));

    sf::RenderWindow window2(sf::VideoMode(x, y), "Results: ");

    sf::Text title1;
    title1.setFont(fontType);
    title1.setString("Results:");
    title1.setCharacterSize(24);
    title1.setStyle(sf::Text::Bold | sf::Text::Underlined);
    setText(title1, x / 2.0f, (y / 2.0f) - 225);

    sf::Text dogCount;
    dogCount.setFont(fontType);
    string dCount = to_string(tree_26.get_count(theDog)); ///uses get count  function
    dogCount.setString(dCount);
    dogCount.setCharacterSize(24);
    dogCount.setStyle(sf::Text::Bold);
    setText(dogCount, x / 2.0f +200, (y / 2.0f) - 170);

    sf::Text countText;
    countText.setFont(fontType);
    countText.setString("Number of dogs with that name: ");
    countText.setCharacterSize(24);
    countText.setStyle(sf::Text::Bold);
    setText(countText, x / 2.0f -75, (y / 2.0f) - 170);


    sf::Text dogRank;
    dogRank.setFont(fontType);
    string dRank = to_string(tree_26.get_rank(tree_26.root,theDog)); ///uses get rank function
    dogRank.setString(dRank);
    dogRank.setCharacterSize(24);
    dogRank.setStyle(sf::Text::Bold);
    setText(dogRank, x / 2.0f +200, (y / 2.0f) - 140);

    sf::Text rankText;
    rankText.setFont(fontType);
    rankText.setString("             Rank of dog name: ");
    rankText.setCharacterSize(24);
    rankText.setStyle(sf::Text::Bold);
    setText(rankText, x / 2.0f -75, (y / 2.0f) - 140);


    sf::Text trieText;
    trieText.setFont(fontType);
    trieText.setString("Time taken by trie: ");
    trieText.setCharacterSize(20);
    trieText.setStyle(sf::Text::Bold);
    setText(trieText, x / 2.0f -100, (y / 2.0f));

    sf::Text trieTime;
    trieTime.setFont(fontType);
    string tt = to_string(duration.count()); ///the 26 ary run time
    trieTime.setString(tt + " milliseconds");
    trieTime.setCharacterSize(20);
    trieTime.setStyle(sf::Text::Bold);
    setText(trieTime, x / 2.0f +150, (y / 2.0f));

    sf::Text hashText;
    hashText.setFont(fontType);
    hashText.setString("Time taken by hash: ");
    hashText.setCharacterSize(20);
    hashText.setStyle(sf::Text::Bold);
    setText(hashText, x / 2.0f -100, (y / 2.0f)+30 );

    sf::Text hashTime;
    hashTime.setFont(fontType);
    string time_ = to_string(duration2.count()); ///hashmap run time
    hashTime.setString(time_ + " milliseconds");
    hashTime.setCharacterSize(20);
    hashTime.setStyle(sf::Text::Bold);
    setText(hashTime, x / 2.0f +150, (y / 2.0f)+30);


    tree_26.getTenHelper(tree_26.root, tree_26.root, "");
    for (int i = 0; i < 10; i++){
        //cout << tree_26.top[i] << endl;
        }


    sf::Text topTitle;
    topTitle.setFont(fontType);
    topTitle.setString("Top ten dog names:");
    topTitle.setCharacterSize(24);
    topTitle.setStyle(sf::Text::Bold | sf::Text::Underlined);
    setText(topTitle, x / 2.0f, (y / 2.0f)+100);

    sf::Text topTen;
    topTen.setFont(fontType);
    topTen.setString("1. " + tree_26.top[0] + "\n" + "2. " + tree_26.top[1] + "\n" + "3. " + tree_26.top[2] + "\n" + "4. " + tree_26.top[3] + "\n" + "5. " + tree_26.top[4]);
    topTen.setCharacterSize(24);
    topTen.setStyle(sf::Text::Bold);
    setText(topTen, x / 2.0f-100, (y / 2.0f)+200);

    sf::Text topTen2;
    topTen2.setFont(fontType);
    topTen2.setString("     6. " + tree_26.top[5] + "\n" + "     7. " + tree_26.top[6] + "\n" + "     8. " + tree_26.top[7] + "\n" + "     9. " + tree_26.top[8] + "\n" + "     10." + tree_26.top[9]);
    topTen2.setCharacterSize(24);
    topTen2.setStyle(sf::Text::Bold);
    setText(topTen2, x / 2.0f+100, (y / 2.0f)+200);

    sf::Text top20;
    top20.setFont(fontType);
    top20.setString("We've definitely heard that before!");
    top20.setCharacterSize(24);
    top20.setStyle(sf::Text::Bold);
    setText(top20, 350, 275);

    sf::Text top10;
    top10.setFont(fontType);
    top10.setString("Its a classic!");
    top10.setCharacterSize(24);
    top10.setStyle(sf::Text::Bold);
    setText(top10, 350, 275);

    sf::Text top100;
    top100.setFont(fontType);
    top100.setString("Pretty common dog name!");
    top100.setCharacterSize(24);
    top100.setStyle(sf::Text::Bold);
    setText(top100, 350, 275);

    sf::Text _100plus;
    _100plus.setFont(fontType);
    _100plus.setString("So unique!");
    _100plus.setCharacterSize(24);
    _100plus.setStyle(sf::Text::Bold);
    setText(_100plus, 350, 275);


    setText(name_input, x / 2.0f, (y / 2.0f) - 75);
    name_input.setStyle(sf::Text::Bold);
    while (window2.isOpen()) {
        sf::Event event;
        while (window2.pollEvent(event)) {

            if (event.type == sf::Event::Closed) {
                window2.close();
            }

            if (event.type == sf::Event::KeyPressed) {


                if (event.type == sf::Event::KeyPressed) {
                    if (event.key.code == sf::Keyboard::Enter) {
                        window2.close();
                    }
                }
            }
            if (event.type == Event::MouseButtonPressed) {
                if (Mouse::isButtonPressed(Mouse::Left)) {
                    if (0 < event.mouseButton.x && event.mouseButton.x < 200 ) {
                        window2.close();
                    }
                    else if (201 < event.mouseButton.x && event.mouseButton.x < 400 &&
                             0 < event.mouseButton.y && event.mouseButton.y < 400) {
                        window2.close();
                    }
                }
            }
        }
        setText(inputText, 350, 300);
        window2.clear(sf::Color::Magenta);
        window2.draw(title1);
        window2.draw(dogCount);
        window2.draw(countText);
        window2.draw(dogRank);
        window2.draw(rankText);
        window2.draw(trieTime);
        window2.draw(trieText);
        window2.draw(hashText);
        window2.draw(hashTime);
        window2.draw(topTen);
        window2.draw(topTen2);
        window2.draw(topTitle);
        if (tree_26.get_rank(tree_26.root,theDog) <= 10){
            window2.draw(top10);
        }
        else if (tree_26.get_rank(tree_26.root,theDog) <= 20){
            window2.draw(top20);
        }
        else if (tree_26.get_rank(tree_26.root,theDog) <= 100){
            window2.draw(top100);
        }
        else if (tree_26.get_rank(tree_26.root,theDog) > 100){
            window2.draw(_100plus);
        }

        window2.display();
    }


}