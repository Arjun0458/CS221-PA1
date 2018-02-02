#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <string>
#include <vector>

#include "kebab.h"

// Constructor
Kebab::Kebab(){
    
}

// Adds item to the pointy end of the skewer
// and returns true if skewer has space to add
// and item is a valid ingredient
// Returns false if skewer is full or ingredient is invalid
bool Kebab::addIngredient(char item){
    if (isValidIngredient(item) == true && (skewer.size() < maxlength)){
        skewer.push_back(item);
        return true;
    } else return false;
}

// Adds the ingredients specified by s using addIngredient
// up to the capacity of the skewer
void Kebab::buildKebab(std::string s){
    std::vector<char> ingredients(s.c_str(), s.c_str() + s.size());
    for (unsigned long i=0; i < ingredients.size(); i++){
        addIngredient(ingredients.at(i));

        if(skewer.size() >= maxlength){
            return;
        } 
    } 
    return;
}

// returns the number of meat items on this kebab
unsigned int Kebab::numMeats() const{
    int num_ingredient = skewer.size();
    int count = 0;
    for (int i = 0; i < num_ingredient; i++){
        if (skewer.at(i) == 'B' || skewer.at(i) == 'b'){
            count++;
        }
    }
    return count;
}
  
// Returns true iff this kebab contains at least the same collection
// of ingredients as k, in any order
// Note that this kebab may contain more total ingredients than k,
// but will return true as long as this kebab's ingredients is
// a super-multiset of k's ingredients
bool Kebab::hasSameIngredients(Kebab& k) const{
    std::vector<char> skewer_copy = skewer;
    std::sort(skewer_copy.begin(), skewer_copy.end());
    std::sort(k.skewer.begin(), k.skewer.end());
    if(std::includes(skewer_copy.begin(), skewer_copy.end(),k.skewer.begin(), k.skewer.end())){
        return true;
    }
    if(std::includes(k.skewer.begin(), k.skewer.end(),skewer_copy.begin(), skewer_copy.end())){
        return true;
    }
    return false;

}
  
// Returns a string representing the ingredients on this kebab
// in the order in which they are skewered
std::string Kebab::listIngredients() const{
    std::string ingredients;

    int num_ingredient = skewer.size();

    for (int i = num_ingredient - 1; i >= 0; i--){
        ingredients.push_back( skewer.at(i) );
    }
    return ingredients;

}