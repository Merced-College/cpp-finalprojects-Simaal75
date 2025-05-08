//Simaal Belgaumi
// Johnathan Cortez
//Make a Card Game - CPSC 25

#include <string>
#include <iostream>
using namespace std;

// your job is to fix this object
class Card { // Keeps a card object
public:
   // Constructor to initialize the card
   Card() {}  // Default constructor
   Card(string suit, string rank, int value): suit(suit), rank(rank), value(value) {}

   // Getters
   string get_suit() { return suit; }
   string get_rank() { return rank; }
   int get_value() { return value; }

   // Print the card details
   void print_card() { cout << rank << " of " << suit << endl; }

private:
   // Data variables for the card
   string suit;
   string rank;
   int value;
};

// define the constants for suits, ranks, and values
const string SUITS[] = {"Hearts", "Diamonds", "Clubs", "Spades"};
const string RANKS[] = {"2", "3",  "4",    "5",     "6",    "7",  "8",
                        "9", "10", "Jack", "Queen", "King", "Ace"};
const int VALUES[] = {2, 3, 4, 5, 6, 7, 8, 9, 10, 10, 10, 10, 11};

// int DECK[52];  // Array to store deck of cards
Card deck[52]; // Array to store 52 cards in deck
int currentCardIndex = 0;
/*
defines the arrays and variables related to a deck of playing cards through the
suits, ranks, the current card index, and the deck itself.
*/

void initializeDeck() {
  int deckIndex = 0;
  for (int suitIndex = 0; suitIndex < 4; suitIndex++) {
    for (int rankIndex = 0; rankIndex < 13; rankIndex++) {
      // Card(string suit, string rank, int value);
      deck[deckIndex++] = Card(SUITS[suitIndex], RANKS[rankIndex], VALUES[rankIndex]);
    }
  }
}

void shuffleDeck() {
  for (int i = 0; i < 52; i++) {
    int index = rand() % 52;
    Card temp = deck[i]; // these next three lines are a swap function
    deck[i] = deck[index];
    deck[index] = temp;
  }
}

Card dealCard() { 
  return deck[currentCardIndex++]; 
}

int dealInitialPlayerCards() {
  Card card1 = dealCard();
  Card card2 = dealCard();
  cout << "Your cards: ";
  card1.print_card();
  card2.print_card();
  return card1.get_value() + card2.get_value();
}

int playerTurn(int playerTotal) {
  while (true) {
    cout << "Your total is " << playerTotal << ". Do you want to hit or stand?" << endl;
    string action;
    getline(cin, action); // get the player's action (hit or stand)
    if (action == "hit") {
      Card newCard = dealCard();
      playerTotal += newCard.get_value();
      cout << "You drew a ";
      newCard.print_card();
      if (playerTotal > 21) {
        break;
      }
    } else if (action == "stand") {
      break;
    } else {
      cout << "Invalid action. Please type 'hit' or 'stand'." << endl;
    }
  }
  return playerTotal;
}

int main() {
  int playerWins = 0, dealerWins = 0, ties = 0;
  string playAgain;

  do {
    initializeDeck();    // Initialize the deck
    shuffleDeck();       // Shuffle the deck

    int playerTotal = dealInitialPlayerCards();  // Deal initial cards to player
    cout << "The playerTotal is " << playerTotal << endl;

    playerTotal = playerTurn(playerTotal);  // Player's turn to hit or stand

    if (playerTotal > 21) {
      cout << "You busted! Dealer wins." << endl;
      dealerWins++;
    } else {
      int dealerTotal = 17; // Simple dealer rule (can be expanded)
      cout << "The dealer's total is " << dealerTotal << endl;

      if (dealerTotal > 21) {
        cout << "Dealer busted! You win!" << endl;
        playerWins++;
      } else if (playerTotal > dealerTotal) {
        cout << "You win!" << endl;
        playerWins++;
      } else if (playerTotal < dealerTotal) {
        cout << "Dealer wins." << endl;
        dealerWins++;
      } else {
        cout << "It's a tie!" << endl;
        ties++;
      }
    }

    cout << "\nScoreboard: " << endl;
    cout << "Player Wins: " << playerWins << endl;
    cout << "Dealer Wins: " << dealerWins << endl;
    cout << "Ties: " << ties << endl;

    cout << "\nDo you want to play another round? (y/n): ";
    getline(cin, playAgain);

  } while (playAgain == "y" || playAgain == "Y");

  cout << "\nFinal Scoreboard: " << endl;
  cout << "Player Wins: " << playerWins << endl;
  cout << "Dealer Wins: " << dealerWins << endl;
  cout << "Ties: " << ties << endl;

  return 0;
}
