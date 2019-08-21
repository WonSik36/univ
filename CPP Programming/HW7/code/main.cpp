#include "Carnivore.h"
#include "Herbivore.h"
#include <iostream>
#include <cstdlib>
#include <string>
using namespace std;

int main(){
	// 7 functions
	Carnivore animalOne = Carnivore();
	animalOne.setSpecies("Tiger");
	animalOne.setHabitat("Mountain");
	animalOne.setFood("meat");
	animalOne.setWeight(80);
	animalOne.setTraining("axe throwing");
	animalOne.setFeeding("meat");
	animalOne.getInfo();

	cout<<endl;
	// 7 functions
	Herbivore animalTwo = Herbivore();
	animalTwo.setSpecies("Deer");
	animalTwo.setHabitat("Savana");
	animalTwo.setFood("grass");
	animalTwo.setWeight(40);
	animalTwo.setTraining("Juggling");
	animalTwo.setFeeding("grass");
	animalTwo.getInfo();

	system("pause");
	return 0;
}