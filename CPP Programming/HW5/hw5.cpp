#include<iostream>
#include <string>
#include <cstdlib>
using namespace std;
//Complete the code
class People {
private:
	string name;
	string stuNo;
public:
	People(){ }
	People(string name, string stuNo){
		this->name = name;
		this->stuNo = stuNo;
	}
	void setName(string name){
		this->name = name;
	}
	void setStuNo(string stuNo) {
		this->stuNo = stuNo;	
	}
	string getName() {
		return name;
	}
	string getStuNo() {
		return stuNo;
	}
	void print() {
		cout<<"My name is "<<name<<" stu no is "<<stuNo<<endl;
	}
};

class Team {
private:
	string name;
	People member[30];
	int cnt = 0;
public:
	Team(){ }
	Team(string _name){
		this->name = _name;
	}
	void addMember(People people) {
		if(cnt > 29) {
			cout <<"full";
		}
		else {
			// include people to member and add 1 to count
			member[cnt] = people;
			cnt++;
		}
	}
	void printMember() {
		//looping print to all member
		for(int i=0; i<cnt; i++){
			cout<<"RC_Team's Member name is "<<member[i].getName()<<endl;
		}
	}
};

int main()
{
	Team* team1 = new Team("RC_Team");
	People p1("Gildong", "21800123");
	People p2("Professor", "29500123");
	p1.print();
	// print : My name is Gildong stu no is 21800123
	p1.setName("Won Sik"); //your name
	p1.setStuNo("21300691"); //your student number
	p1.print();
	// change to your name Gildong -> (your name), (21800123 -> 21x00xxx)
	// print : My name is (Your name) Stu no is 21x00xxx
	team1 ->addMember(p1);
	team1->addMember(p2);
	team1 -> printMember();
	// print : RC_Team's Member name is (Your name)

	system("pause");
}