#ifndef HERBIVORE_H
#define HERBIVORE_H
#include <string>
#include "Animal.h"
using namespace std;

class Herbivore:public Animal{
private:
	// New variable for override function
	string Training;
	string Feeding;
public:
	Herbivore();
	void setTraining(string str);
	string getTraining() const;
	virtual void printTraining() const;
	void setFeeding(string str);
	string getFeeding() const;
	virtual void printFeeding() const;
	virtual void getInfo() const;
};

#endif