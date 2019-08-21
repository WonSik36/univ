#ifndef CARNIVORE_H
#define CARNIVORE_H
#include <string>
#include "Animal.h"
using namespace std;

class Carnivore:public Animal{
private:
	// New variable for override function
	string Training;
	string Feeding;
public:
	Carnivore();
	void setTraining(string str);
	string getTraining() const;
	virtual void printTraining() const;
	void setFeeding(string str);
	string getFeeding() const;
	virtual void printFeeding() const;
	virtual void getInfo() const;
};

#endif