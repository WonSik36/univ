#include <iostream>
#include <cstdlib>
#include <string>
#include "Animal.h"
using namespace std;

// Animal Object Constructor
Animal::Animal(){
	Species = "";
	Habitat = "";
	Food = "";
	Type = "";
	Weight = 0;

	cout<<"This is Animal Class Constructor"<<endl;
}

// Mutator & Accessor
string Animal::getSpecies() const{
	return Species;
}
void Animal::setSpecies(string str){
	Species = str;
}
string Animal::getHabitat() const{
	return Habitat;
}
void Animal::setHabitat(string str){
	Habitat = str;
}
string Animal::getFood() const{
	return Food;
}
void Animal::setFood(string str){
	Food = str;
}
string Animal::getType() const{
	return Type;
}
void Animal::setType(string str){
	Type = str;
}
int Animal::getWeight() const{
	return Weight;
}
void Animal::setWeight(int w){
	Weight = w;
}
// Virtual Function getInfo
void Animal::getInfo() const{
	cout<<"I am a "<<Species<<endl;
	cout<<"I eat "<<Food<<endl;
	cout<<"I am a "<<Type<<"!"<<endl;
	cout<<"I weigh "<<Weight<<"kg"<<endl;
	cout<<"I live in the "<<Habitat<<endl;
}
