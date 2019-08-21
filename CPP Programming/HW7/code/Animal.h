#ifndef ANIMAL_H
#define ANIMAL_H
#include <string>
using namespace std;

class Animal{
private:
	string Species;
	string Habitat;
	string Food;
	string Type;
	int Weight;

public:
	Animal();
	string getSpecies() const;
	void setSpecies(string str);
	string getHabitat() const;
	void setHabitat(string str);
	string getFood() const;
	void setFood(string str);
	string getType() const;
	void setType(string str);
	int getWeight() const;
	void setWeight(int w);

	// Pure Virtual Function which will be overrided
	virtual void printTraining() const = 0;
	virtual void printFeeding() const = 0;
	// Virtual Function which will be overrided
	virtual void getInfo() const;
};

#endif