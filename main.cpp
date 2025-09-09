#include <iostream>
#include "shuffle.h"
#include "deck.h"
#include "dealer.h"

const int DIM = 21;
int isGameOver = 0;

std::vector<std::pair<std::string, std::string>> myCards = {};
std::vector<std::pair<std::string, std::string>> dealerCards = {};

void drawCards(bool revealAll){
     std::cout << "Dealer have: \n";
     for (size_t i = 0; i < dealerCards.size(); i++) {
        if (i == 0 && !revealAll) {
            std::cout << "[Hidden] \n"; // first card is hidden
        } 
        else {
            std::cout << dealerCards[i].first << " " << dealerCards[i].second << " " << std::endl;
        }
     }
     std::cout << std::endl;
    
     std::cout << "You have: \n";
     for (auto x : myCards){ 
          std::cout << x.first << ' ' << x.second << std::endl;
     }
}

int mySum(){
     int pSum=0;
     for (auto x : myCards){
          if (x.first == "2") pSum+=2;
          if (x.first == "3") pSum+=3;
          if (x.first == "4") pSum+=4;
          if (x.first == "5") pSum+=5;
          if (x.first == "6") pSum+=6;
          if (x.first == "7") pSum+=7;
          if (x.first == "8") pSum+=8;
          if (x.first == "9") pSum+=9;
          if (x.first == "10" || x.first == "Jack" || x.first == "Queen" || x.first == "King") pSum+=10;
          if (x.first == "Ace"){
               std::cout << "choose your Ace value: (1/10)" << std::endl;
               int val;
               std::cin>> val;
               if (val == 1) pSum+=1;
               else pSum+=10;
          }
     }
     return pSum;
}

void clearConsole() {
     std::cout << "\033[2J\033[H"; // clear console by ANSI-codes
}

void gameOver(int &isGameOver){
     isGameOver=1;
}

int main(){
     clearConsole();

     shuffle(deck); // shuffle deck

     dealer Dealer; // make a Dealer

     myCards.push_back(deck[0]); // take 2 cards from deck
     myCards.push_back(deck[2]);
     dealerCards.push_back(deck[1]); // dealer takes 2 cards from deck
     dealerCards.push_back(deck[3]);

     int i=3;
     
     char decis;

     while (isGameOver==0){
          if (isGameOver==0) clearConsole();
          drawCards(false);
          std::cout << "Pick up next card?(Y/n)" << std::endl;
          std::cin >> decis;
          
          if (decis == 'Y') {
               i++;
               myCards.push_back(deck[i]);
               Dealer.decision();
          }

          else if (decis == 'n'){
               int sum = mySum();
                  
               Dealer.decision();
          }

          else if (decis == 'e'){
               gameOver(isGameOver);
               drawCards(true);
          }
     }
     return 0;     
}