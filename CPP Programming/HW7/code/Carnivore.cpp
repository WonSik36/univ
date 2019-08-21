#include <iostream>
#include <cstdlib>
#include <string>
#include "Carnivore.h"
using namespace std;

// Constructor
Carnivore::Carnivore(){
	setType("Carnivore");

	cout<<"This is Carnivore Constructor"<<endl;
}
// New Function for help printTraining() which overrides virtual function
void Carnivore::setTraining(string str){
	Training = str;
}
string Carnivore::getTraining() const{
	return Training;
}
// Override Function
void Carnivore::printTraining() const{
	cout<<getType()<<" was trained in "<<Training<<endl;
}
// New Function for help printFeeding() which overrides virtual function
void Carnivore::setFeeding(string str){
	Feeding = str;
}
string Carnivore::getFeeding() const{
	return Feeding;
}
// Override Function
void Carnivore::printFeeding() const{
	cout<<getType()<<" was fed well with "<<Feeding<<endl;
}
// Override Function
void Carnivore::getInfo() const{
	cout<<"I am a "<<getSpecies()<<endl;
	cout<<"I eat "<<getFood()<<endl;
	cout<<"I am a "<<getType()<<"!"<<endl;
	cout<<"I weigh "<<getWeight()<<"kg"<<endl;
	cout<<"I live in the "<<getHabitat()<<endl;
	printFeeding();
	printTraining();
}