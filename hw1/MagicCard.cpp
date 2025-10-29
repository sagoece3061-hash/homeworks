#include "MagicCard.h"

MagicCard::MagicCard(): players(nullptr), players_size(0), players_capacity(0), 
draw_pile(nullptr), draw_pile_size(0), draw_pile_capacity(0), 
discard_pile(nullptr), discard_pile_size(0), discard_pile_capacity(0){}

MagicCard::~MagicCard() { delete [] players; delete [] draw_pile; delete [] discard_pile; }

void MagicCard::addPlayer( const int playerID, const string name){
    Player* new_players = new Player[players_size + 1];
    Player new_player = {playerID, name};
    int index = players_size;

    for(int i = 0; i < players_size; i++){
        if(players[i] < new_player)
            new_players[i] = players[i];
        else if(players[i] > new_player){
            index = i;
            break;
        }
        else{
            cout << "Cannot add player. ID " << playerID << " already exists.\n";
            return;
        }
    }
    cout << "Added player " << name << " with ID " << playerID << ".\n";
    new_players[index] = new_player;
    for(int i = index; i < players_size; i++){
        new_players[i + 1] = players[i];
    }

    players_size++;
    players_capacity++;

    delete [] players;
    players = new_players;
}

void MagicCard::removePlayer(const int playerID){//players_capacity???
    int index = findPlayer(playerID, players_size - 1, 0);
    
    if(index == -1){
        cout << "Cannot remove player. There is no player with ID " << playerID << ".\n";
        return;
    }

    Player* new_players = new Player[players_size - 1];

    for(int i = 0; i < index; i++){
        new_players[i] = players[i];
    }
    
    for(int i = index; i < players_size - 1; i++){
        new_players[i] = players[i + 1];
    }

    delete [] players;

    players = new_players;

    players_size--;
    players_capacity--;

    cout << "Removed player " << playerID << ".\n";
}

void MagicCard::printPlayers() const{
    if(players_size == 0){
        cout << "Cannot print players. There is no player in the game.\n";
        return;
    }
    cout << "Players :\n";
    for(int i = 0; i < players_size; i++){
        Player player = players[i];

        cout << "Player " << player.ID << " : " << player.name << "\n";
    }
}

void MagicCard::setDrawPile(const string drawPile[], const int size){
    draw_pile = new Card[size];

    for(int i = 0; i < size; i++){
        draw_pile[i] = drawPile[i];
    }

    draw_pile_capacity = size;
    draw_pile_size = size;

    cout << "Draw pile has been initialized.\n";
}

void MagicCard::drawCardFromDeck( const int playerID, const int n){
    int index = findPlayer(playerID, players_size - 1, 0);
    if(index == -1){
        cout << "";
        return;
    }

    if(n >= draw_pile_size){
        cout << "Cannot draw card. The input index is not valid.\n";
        return;
    }

    Player* player = &players[index];
    Card* new_cards = new Card[player->cards_size + 1];

    for(int i = 0; i < player->cards_size; i++){
        new_cards[i] = player->cards[i];
    }

    new_cards[player->cards_size] = draw_pile[n];

    delete [] player->cards;
    player->cards = new_cards;
    player->cards_capacity = player->cards_size + 1;
    player->cards_size++;

    for(int i = n; i < draw_pile_size - 1; i++){
        draw_pile[i] = draw_pile[i + 1];
    }

    draw_pile_size--;
    cout << player->name << " drew card " << player->cards[player->cards_size - 1] << " from the draw pile.\n";
}

void MagicCard::switchHands( const int player1ID, const int player2ID){
    int index1 = findPlayer(player1ID, players_size - 1, 0);
    int index2 = findPlayer(player2ID, players_size - 1, 0);

    if(index1 == -1 || index2 == -1){
        cout << "Cannot switch hands. One or both players do not exits.\n";
        return;
    }

    Card* temp = players[index1].cards;
    int temp_size = players[index1].cards_size;
    int temp_capacity = players[index1].cards_capacity;

    players[index1].cards = players[index2].cards;
    players[index2].cards = temp;

    players[index1].cards_size = players[index2].cards_size;
    players[index1].cards_capacity = players[index2].cards_capacity;

    players[index2].cards_size = temp_size;
    players[index2].cards_capacity = temp_capacity;

    cout << "Switched hands between " << players[index1].name << " and " << players[index2].name << ".\n";
}

void MagicCard::listDrawPile() const{
    
    if(draw_pile_size == 0) {
        cout << "Draw pile is empty.\n";
        return;
    }

    cout << "Draw pile: [" << draw_pile[0];
    
    for(int i = 1; i < draw_pile_size; i++){
        cout << ", " << draw_pile[i];
    }

    cout << "]\n";
}

void MagicCard::listDiscardPile() const{
    if(discard_pile_size == 0) {
        cout << "Discard pile is empty.\n";
        return;
    }
    
    cout << "Discard pile: [" << discard_pile[0];
    
    for(int i = 1; i < discard_pile_size; i++){
        cout << ", " << discard_pile[i];
    }

    cout << "]\n";
}

void MagicCard::listCardsOfPlayer( const int playerID ) const{
    int index = findPlayer(playerID, players_size - 1, 0);

    if(index == -1){
        cout << "Cannot list cards. Player with ID " << playerID << " does not exits.\n";
        return;
    }
    Player player = players[index];
    
    cout << "Cards of " << player.name << ": [";
    
    if(player.cards_size > 0) cout << player.cards[0];
    
    for(int i = 1; i < player.cards_size; i++){
        cout << ", " << player.cards[i];
    }

    cout << "]\n";
}

void MagicCard::play( const int playerID, const string card ){
    int index = findPlayer(playerID, players_size - 1, 0);
    int card_index = -1;

    if(index == -1){
        cout << "There is no player with ID " << playerID << ".\n";
        return;
    }

    Player* player_ptr = &players[index];
    Card* card_ptr = nullptr;

    for(int i = 0; i < player_ptr->cards_size; i++){
        if(player_ptr->cards[i] == card){
            card_index = i;
            card_ptr = &player_ptr->cards[i];
            break;
        }
    }

    if(!card_ptr){
        cout << "The player does not have " << card << " card.\n";
        return;
    }

    if(!(discard_pile_size == 0 || card_ptr->color == discard_pile[discard_pile_size - 1].color || card_ptr->num == discard_pile[discard_pile_size - 1].num)){
        Card* new_cards = new Card[player_ptr->cards_size + 1];

        for(int i = 0; i < player_ptr->cards_size; i++){
            new_cards[i] = player_ptr->cards[i];
        }

        new_cards[player_ptr->cards_size] = draw_pile[0];

        delete [] player_ptr->cards;
        player_ptr->cards = new_cards;
        player_ptr->cards_capacity = player_ptr->cards_size + 1;
        player_ptr->cards_size++;

        for(int i = 0; i < draw_pile_size - 1; i++){
            draw_pile[i] = draw_pile[i + 1];
        }

        draw_pile_size--;
        cout << "Player " << playerID << " played " << card << " then drew " << player_ptr->cards[player_ptr->cards_size - 1] << ".\n";
    }
    else
        cout << "Player " << playerID << " played " << card << ".\n";

    Card* new_discard_pile = new Card[discard_pile_capacity + 1];

    for(int i = 0; i < discard_pile_size; i++){
        new_discard_pile[i] = discard_pile[i];
    }

    new_discard_pile[discard_pile_size] = card;
    delete [] discard_pile;
    discard_pile = new_discard_pile;
    discard_pile_size++;
    discard_pile_capacity++;

    Card* new_cards = new Card[player_ptr->cards_capacity - 1];

    for(int i = 0; i < card_index; i++){
        new_cards[i] = player_ptr->cards[i];
    }

    for(int i = card_index; i < player_ptr->cards_size - 1; i++){
        new_cards[i] = player_ptr->cards[i + 1];
    }

    delete [] player_ptr->cards;
    player_ptr->cards = new_cards;

    player_ptr->cards_size--;
    player_ptr->cards_capacity--;

    if(player_ptr->cards_size == 0){
        cout << "The game has ended. Player " << playerID << " won.\n";
        exit(0);
    }

    if(draw_pile_size == 0){
        cout << "The game has ended. No cards remain in the draw pile.\n";
        exit(0);
    }
}

int MagicCard::findPlayer(const int playerID, const int upper, const int lower) const{
    if(upper >= lower){
        int mid = lower + (upper - lower) / 2;
        
        if(players[mid].ID < playerID)
            return findPlayer(playerID, upper, mid + 1);
    
        else if(players[mid].ID > playerID)
           return findPlayer(playerID, mid - 1, lower);
    
        else return mid;
    }

    return -1;
}

ostream& operator<<(ostream& os, const Card& card){
    os << card.color << card.num;
    return os;
}
