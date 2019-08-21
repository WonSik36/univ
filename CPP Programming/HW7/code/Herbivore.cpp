#include <iostream>
#include <cstdlib>
#include <string>
#include "Herbivore.h"
using namespace std;

// Constructor
Herbivore::Herbivore(){
	setType("Herbivore");

	cout<<"This is Herbivore Constructor"<<endl;
}
// New Function for help printTraining() which overrides virtual function
void Herbivore::setTraining(string str){
	Training = str;
}
string Herbivore::getTraining() const{
	return Training;
}
// Override Function
void Herbivore::printTraining() const{
	cout<<getType()<<" was trained in "<<Training<<endl;
}
// New Function for help printFeeding() which overrides virtual function
void Herbivore::setFeeding(string str){
	Feeding = str;
}
string Herbivore::getFeeding() const{
	return Feeding;
}
// Override Function
void Herbivore::printFeeding() const{
	cout<<getType()<<" was fed well with "<<Feeding<<endl;
}
// Override Function
void Herbivore::getInfo() const{
	cout<<"I am a "<<getSpecies()<<endl;
	cout<<"I eat "<<getFood()<<endl;
	cout<<"I am a "<<getType()<<"!"<<endl;
	cout<<"I weigh "<<getWeight()<<"kg"<<endl;
	cout<<"I live in the "<<getHabitat()<<endl;
	printFeeding();
	printTraining();
}