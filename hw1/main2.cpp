#include <string>
#include <cstring>
#include <iostream>
#include <istream>
#include <stdlib.h>
using namespace std;

int main(int argc, char const *argv[])
{
    string a = R"END(Cannot print players. There is no player in the game.

Discard pile is empty.

Draw pile is empty.

Added player Deniz Akin with ID 5.
Added player Lucas Moreau with ID 56.
Added player Emre Yilmaz with ID 25.
Cannot add player. ID 5 already exists.

Players :
Player 5 : Deniz Akin
Player 25 : Emre Yilmaz
Player 56 : Lucas Moreau

Removed player 56.
Cannot remove player. There is no player with ID 99.

Players :
Player 5 : Deniz Akin
Player 25 : Emre Yilmaz

Draw pile has been initialized.
Draw pile: [R1, G3, Y7, B10, B8, G9]

Deniz Akin drew card B10 from the draw pile.
Emre Yilmaz drew card R1 from the draw pile.

Cards of Deniz Akin: [B10]
Cards of Emre Yilmaz: [R1]

Deniz Akin drew card Y7 from the draw pile.
Emre Yilmaz drew card G3 from the draw pile.

Cards of Deniz Akin: [B10, Y7]
Cards of Emre Yilmaz: [R1, G3]

Switched hands between Deniz Akin and Emre Yilmaz.
Cannot switch hands. One or both players do not exist.

Cards of Deniz Akin: [R1, G3]
Cards of Emre Yilmaz: [B10, Y7]

Cannot draw card. The input index is not valid.

Cannot list cards. Player with ID 49 does not exist.

Discard pile is empty.

Player 5 played R1.

Discard pile: [R1]

There is no player with ID 123.
The player does not have Y9 card.

Cards of Deniz Akin: [G3]

Player 25 played B10 then drew B8.

Cards of Emre Yilmaz: [Y7, B8]

Player 25 played B8.

Cards of Emre Yilmaz: [Y7]

The player does not have R1 card.

Discard pile: [R1, B10, B8]

Player 5 played G3 then drew G9.
The game has ended. No cards remain in the draw pile.)END";
    string b = R"END(Cannot print players. There is no player in the game.

Discard pile is empty.

Draw pile is empty.

Added player Deniz Akin with ID 5.
Added player Lucas Moreau with ID 56.
Added player Emre Yilmaz with ID 25.
Cannot add player. ID 5 already exists.

Players :
Player 5 : Deniz Akin
Player 25 : Emre Yilmaz
Player 56 : Lucas Moreau

Removed player 56.
Cannot remove player. There is no player with ID 99.

Players :
Player 5 : Deniz Akin
Player 25 : Emre Yilmaz

Draw pile has been initialized.
Draw pile: [R1, G3, Y7, B10, B8, G9]

Deniz Akin drew card B10 from the draw pile.
Emre Yilmaz drew card R1 from the draw pile.

Cards of Deniz Akin: [B10]
Cards of Emre Yilmaz: [R1]

Deniz Akin drew card Y7 from the draw pile.
Emre Yilmaz drew card G3 from the draw pile.

Cards of Deniz Akin: [B10, Y7]
Cards of Emre Yilmaz: [R1, G3]

Switched hands between Deniz Akin and Emre Yilmaz.
Cannot switch hands. One or both players do not exits.

Cards of Deniz Akin: [R1, G3]
Cards of Emre Yilmaz: [B10, Y7]

Cannot draw card. The input index is not valid.

Cannot list cards. Player with ID 49 does not exits.

Discard pile is empty.

Player 5 played R1.

Discard pile: [R1]

There is no player with ID 123.
The player does not have Y9 card.

Cards of Deniz Akin: [G3]

Player 25 played B10 then drew B8.

Cards of Emre Yilmaz: [Y7, B8]

Player 25 played B8.

Cards of Emre Yilmaz: [Y7]

The player does not have R1 card.

Discard pile: [R1, B10, B8]

Player 5 played G3 then drew G9.
The game has ended. No cards remain in the draw pile.)END";

cout << a.compare(b) << "\n";
    return 0;
}
