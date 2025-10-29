#include "MagicCard.h"


int main(int argc, char const *argv[])
{
    MagicCard game;

    game.printPlayers();
    cout << endl;

    game.listDiscardPile();
    cout << endl;

    game.listDrawPile();
    cout << endl;

    game.addPlayer(5, "Deniz Akin");
    game.addPlayer(56, "Lucas Moreau");
    game.addPlayer(25, "Emre Yilmaz");
    game.addPlayer(5, "Derya Yildirim");
    cout << endl;

    game.printPlayers();
    cout << endl;

    game.removePlayer(56);
    game.removePlayer(99);
    cout << endl;

    game.printPlayers();
    cout << endl;

    string cards[] = {"R1", "G3", "Y7", "B10", "B8", "G9"};
    game.setDrawPile(cards, 6);

    game.listDrawPile();
    cout << endl;

    game.drawCardFromDeck(5, 3);
    game.drawCardFromDeck(25, 0);
    cout << endl;

    game.listCardsOfPlayer(5);
    game.listCardsOfPlayer(25);
    cout << endl;

    game.drawCardFromDeck(5, 1);
    game.drawCardFromDeck(25, 0);
    cout << endl;

    game.listCardsOfPlayer(5);
    game.listCardsOfPlayer(25);
    cout << endl;

    game.switchHands(5, 25);
    game.switchHands(5, 99);
    cout << endl;

    game.listCardsOfPlayer(5);
    game.listCardsOfPlayer(25);
    cout << endl;

    game.drawCardFromDeck(25, 10);
    cout << endl;

    game.listCardsOfPlayer(49);
    cout << endl;

    game.listDiscardPile();
    cout << endl;

    game.play(5, "R1");
    cout << endl;

    game.listDiscardPile();
    cout << endl;


    game.play(123, "G3");
    game.play(25, "Y9");
    cout << endl;

    game.listCardsOfPlayer(5);
    cout << endl;

    game.play(25, "B10");
    cout << endl;

    game.listCardsOfPlayer(25);
    cout << endl;

    game.play(25, "B8");
    cout << endl;

    game.listCardsOfPlayer(25);
    cout << endl;

    game.play(5, "R1");
    cout << endl;
    
    game.listDiscardPile();
    cout << endl;

    game.play(5, "G3");
    cout << endl;

    return 0;
}