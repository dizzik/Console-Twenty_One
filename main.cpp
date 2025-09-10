#include <iostream>
#include "shuffle.h"
#include "deck.h"
#include "dealer.h"

const int DIM = 21;
int isGameOver = 0;

std::vector<std::pair<std::string, int>> myCards = {};
std::vector<std::pair<std::string, int>> dealerCards = {};

void drawCards(bool revealAll){
     std::cout << "///////////////////////////////////////////\n";
     std::cout << "Dealer have: \n";
     for (size_t i = 0; i < dealerCards.size(); i++) {
        if (i == 0 && !revealAll) {
            std::cout << "[Hidden] \n"; // first card is hidden
        } 
        else {
            std::cout << dealerCards[i].first << " " << std::endl;
        }
     }
     std::cout << std::endl;
    
     std::cout << "You have: \n";
     for (auto x : myCards){ 
          std::cout << x.first << std::endl;
     }
}

int mySum(){
     int playerSum=0;
     for (auto x : myCards){
          playerSum+=x.second;
          if (x.second == 0){
               std::cout << "choose your Ace value: (1/11)" << std::endl;
               int val;
               std::cin>> val;
               if (val == 1) playerSum+=1;
               else playerSum+=11;
          }
     }
     return playerSum;
}
int botSum(){
     int res = 0; int aces = 0;
     for (auto x : dealerCards){
          res+=x.second;
          if (x.second == 0){
               aces++;
               res+=11;
          }
     }
     while (res > 21 && aces > 0){
          res-=10;
          aces--;
     }
     return res;
}

void clearConsole() {
     std::cout << "\033[2J\033[H"; // clear console by ANSI-codes
}

void gameOver(int &isGameOver){
     isGameOver=1;
}

void winner(int& playerSum, int& dealerSum){
     clearConsole();
     gameOver(isGameOver);
     if (playerSum <= 21 && dealerSum <= 21){
          if (playerSum > dealerSum) std::cout << "YOU WIN!\n";
          else if (dealerSum > playerSum) std::cout << "YOU LOSE\n";
          else if (dealerSum == playerSum) std::cout << "DRAW\n";
     }
     else if (playerSum > 21 && dealerSum <= 21) std::cout << "YOU LOSE\n";
     else if (playerSum <= 21 && dealerSum > 21) std::cout << "YOU WIN!\n";
     else{
          if (playerSum < dealerSum) std::cout << "YOU WIN!\n";
          else if (playerSum > dealerSum) std::cout << "YOU LOSE\n";
          else std::cout << "DRAW\n";
     }    
}

int main(){
     clearConsole();

     dealer Dealer; // make a Dealer
     
     shuffle(deck); // shuffle deck

     myCards.push_back(deck[0]); // take 2 cards from deck
     myCards.push_back(deck[2]);
     dealerCards.push_back(deck[1]); // dealer takes 2 cards from deck
     dealerCards.push_back(deck[3]);

     int i=3;
     
     char decis;

     while (isGameOver==0){
          int playerSum = mySum();
          int dealerSum = botSum();
          drawCards(false);

          std::cout << "Pick up next card?(y/n)" << std::endl;
          std::cin >> decis;

          if (decis == 'y') {
               i++;
               myCards.push_back(deck[i]);
               Dealer.decision(i, myCards, dealerCards, playerSum, true);
          }

          else if (decis == 'n'){
               if (!Dealer.decision(i, myCards, dealerCards, playerSum, false)){
                    winner(playerSum, dealerSum);
               }
          }

          else if (decis == 'e'){
               gameOver(isGameOver);
               drawCards(true);
          }
          if (isGameOver==0) clearConsole();
     }
     return 0;     
}