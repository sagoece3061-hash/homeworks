#ifndef _MAGIC_CARD
#define _MAGIC_CARD

#include <string>
#include <cstring>
#include <iostream>
#include <istream>
#include <stdlib.h>
#include <math.h>
#include <cmath>

using namespace std;

class Card {
public:
    int num;
    char color;

    Card(): color(0), num(0){}

    Card(const string st){
        color = st.at(0);
        num = 0;

        for(int i = 1; i < st.length(); i++){
            num += (st.at(i) - '0') * pow(10, (st.length() - i - 1));
        }
    }

    friend ostream& operator<<(ostream& os, const Card& card);

    bool operator==(const std::string& a) const {
        std::string card_str;
        card_str += color;
        card_str += std::to_string(num);

        return card_str == a;
    }
};

class Player {
public:
    int ID;
    string name;
    Card* cards;
    size_t cards_capacity;
    size_t cards_size;

    Player()
    : ID(0), name(""), cards(nullptr), cards_capacity(0), cards_size(0){}

    Player(int ID, string name)
    : ID(ID), name(name), cards(nullptr), cards_capacity(0), cards_size(0 ){}
    
    Player(int ID, string name, Card* cards, size_t cards_capacity, size_t cards_size)
    : ID(ID), name(name), cards(cards), cards_capacity(cards_capacity), cards_size(cards_size){}

    Player(const Player& other){
        ID = other.ID;
        name = other.name;

        cards = new Card[other.cards_capacity];
        cards_size = other.cards_size;
        cards_capacity = other.cards_capacity;

        for(int i = 0; i < other.cards_size; i++){
            cards[i] = other.cards[i];
        }
    }

    Player& operator=(const Player& other){
        if(this == &other){
            return *this;
        }

        ID = other.ID;
        name = other.name;

        delete [] cards;
        cards = new Card[other.cards_capacity];
        cards_size = other.cards_size;
        cards_capacity = other.cards_capacity;

        for(int i = 0; i < other.cards_size; i++){
            cards[i] = other.cards[i];
        }

        return *this;
    }

    Player(Player&& other) noexcept : 
    ID(other.ID), name(std::move(other.name)), cards(other.cards), 
    cards_size(other.cards_size), cards_capacity(other.cards_capacity){

        other.cards = nullptr;
        other.cards_size = 0;
        other.cards_capacity = 0;
    }

    Player& operator=(Player&& other) noexcept {
        if(this == &other){
            return *this;
        }
        
        ID = other.ID;
        name = std::move(other.name);

        delete [] cards;
        
        cards_size = other.cards_size;
        cards_capacity = other.cards_capacity;
        cards = other.cards;
        
        other.cards = nullptr;
        other.cards_size = 0;
        other.cards_capacity = 0;

        return *this;
    }

    ~Player(){
        delete [] cards;
    }

    bool operator<(const Player& a){
        if(this->ID < a.ID) return true;
        return false;
    }

    bool operator>(const Player& a){
        if(this->ID > a.ID) return true;
        return false;
    }

    bool operator==(const Player& a){
        if(this->ID == a.ID) return true;
        return false;
    }
};

class MagicCard {
public:
    MagicCard();
    ~MagicCard();

    void addPlayer( const int playerID, const string name);
    void removePlayer(const int playerID);
    void printPlayers() const;

    void setDrawPile(const string drawPile[], const int size);
    void drawCardFromDeck( const int playerID, const int n);
    void switchHands( const int player1ID, const int player2ID);
    void listDrawPile() const;
    void listDiscardPile() const;
    void listCardsOfPlayer( const int playerID ) const;
    
    void play( const int playerID, const string card );

    int findPlayer(const int playerID, const int upper, const int lower) const;

    Player* players;
    size_t players_size;
    size_t players_capacity;
    
    Card* draw_pile;
    size_t draw_pile_size;
    size_t draw_pile_capacity;

    Card* discard_pile;
    size_t discard_pile_size;
    size_t discard_pile_capacity;
private:
};
#endif