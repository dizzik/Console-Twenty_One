#include <iostream>
#include "shuffle.h"
#include "deck.h"

const int DIM = 21;
int isGameOver = 0;

std::vector<std::pair<std::string, std::string>> myCards = {};

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
     std::cout << "\033[2J\033[H"; // Очищення консолі через ANSI-коди
 }

void gameOver(int &isGameOver){
     isGameOver=1;
}

int main(){
     clearConsole();
     // Тасуємо колоду
     shuffle(deck);

     myCards.push_back(deck[0]);
     myCards.push_back(deck[1]);
     int i=1;
     
     char decis;

     while (isGameOver==0){
          if (isGameOver==0) clearConsole();
          
          std::cout << "You have:" << std::endl;
          for (auto x : myCards){
               std::cout << x.first << ' ' << x.second << std::endl;
          } 

          std::cout << "Pick up next card?(Y/n)" << std::endl;
          std::cin >> decis;
          
          if (decis == 'Y') {
               i++;
               myCards.push_back(deck[i]);
          }
          else if (decis == 'n'){
               int sum = mySum();
               if (sum > DIM) {
                    std::cout << "YOU LOSE" << std::endl;
                    return 0;
               }
               else if (sum <= DIM) {
                    std::cout << "YOU WIN" << std::endl;
                    return 0;
               }
          }
          else if (decis == 'e'){
               gameOver(isGameOver);
          }
     }
     return 0;     
}