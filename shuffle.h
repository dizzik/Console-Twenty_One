#pragma once
#include <algorithm>  // for shuffle()
#include <random> 

std::random_device rd;
std::mt19937 g(rd());

void shuffle(std::vector<std::pair<std::string, std::string>>& deck){
    std::shuffle(deck.begin(), deck.end(), g);
}
