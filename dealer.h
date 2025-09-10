#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <iomanip> 

class dealer 
{
private:
    int playerSum(std::vector<std::pair<std::string,int>>& myCard){
        int res = 0; int aces = 0;
        bool first = true;
        for (auto x : myCard){
            if (first) first = false;
            else{
                res+=x.second;
                if (x.second == 0){
                    aces++;
                    res+=11;
                }
            }
        }
        while (res > 21 && aces > 0){
            res-=10;
            aces--;
        }
        return res;
    }

    int dealerSum(std::vector<std::pair<std::string,int>>& dealerCards){
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

    double successChances(int currentIndex, int _dealerSum){
        int goodCards = 0;
        int totalCards = deck.size() - (currentIndex + 1);

        for (int j = currentIndex + 1; j < deck.size(); j++) {
            int value = deck[j].second;

            if (value == 0) {
                if (_dealerSum + 11 <= 21) value = 11;
                else value = 1;
            }

            if (_dealerSum + value <= 21) {
                goodCards++;
            }
        }
        return (double)goodCards / totalCards;
    }
    double playerChance(int currentIndex, int _playerSum){
        int goodCards = 0;
        int totalCards = deck.size() - (currentIndex + 1);
        if (_playerSum + deck[0].second <= 21) goodCards++;
        for (int j = currentIndex + 1; j < deck.size(); j++) {
            int value = deck[j].second;

            if (value == 0) {
                if (_playerSum + 11 <= 21) value = 11;
                else value = 1;
            }

            if (_playerSum + value <= 21) {
                goodCards++;
            }
        }
        return (double)goodCards / totalCards;
    }
public:
    bool decision(int& i,std::vector<std::pair<std::string,int>>& myCards, std::vector<std::pair<std::string,int>>& dealerCards, int& sum, bool playerDecis){
        int _dealerSum = dealerSum(dealerCards);
        int _playerSum = playerSum(myCards);

        double chance = successChances(i, _dealerSum);
        double _playerChance = playerChance(i, _playerSum);
        
        if (_dealerSum >= 21) return false;
        else if (_playerSum >= 21) return false;

        else if (_playerSum >= 19 && !playerDecis && _playerChance <= 0.22) return false;

        else if (_dealerSum < 12){
            i++;
            dealerCards.push_back(deck[i]);
            return true;
        }
        else if (13 <= _dealerSum && _dealerSum <= 16){
            if (chance >= 0.55){
                i++;
                dealerCards.push_back(deck[i]);
                return true;
            }
            else if (chance >= 0.32 && sum == 21){
                i++;
                dealerCards.push_back(deck[i]);
                return true;
            }
            else if (chance >= 0.45 && _playerChance <= 0.14 && _playerSum >= 19){
                return false;
            }
            else if (_playerChance >= 0.75 && _playerSum >= 19 && chance >= 0.55){
                i++;
                dealerCards.push_back(deck[i]);
                return true;
            }
        }
        else if (17 <= _dealerSum && _dealerSum <= 19){
            if (chance >= 0.65 && _dealerSum == 17){
                if (_playerChance <= 0.20){
                    i++;
                    dealerCards.push_back(deck[i]);
                    return true;
                }
                else if (chance >= 0.7){
                    i++;
                    dealerCards.push_back(deck[i]);
                    return true;
                }
            }
            else if (_dealerSum <= 19 && chance >= 0.78){
                if (chance >= 0.70 && _playerChance <= 0.3){
                    i++;
                    dealerCards.push_back(deck[i]);
                    return true;
                }else if (chance >= 0.9){
                    i++;
                    dealerCards.push_back(deck[i]);
                    return true;
                }
            }
        }
        else if (20 <= _dealerSum && _dealerSum <= 21 && chance >= 0.9){
            i++;
            dealerCards.push_back(deck[i]);
            return true;
        }

        return false;
    }
};
