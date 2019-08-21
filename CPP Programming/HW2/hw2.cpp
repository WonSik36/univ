#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <string>
using namespace std; // Or you can use std::

//Number of menu
#define OPTIONNUM 5

#define ORDER1 "MC Donalds Hamburger"
#define ORDER2 "Lotteria Hamburger"
#define ORDER3 "Burger King Hamburger"
#define ORDER4 "Popeyes Hamburger"
#define ORDER5 "Mister Pizza"

#define PRICE1 3000
#define PRICE2 4000
#define PRICE3 3500
#define PRICE4 4700
#define PRICE5 5000

// Initialize array of order and price
const char* order[OPTIONNUM] = {ORDER1, ORDER2, ORDER3, ORDER4, ORDER5};
const int price[OPTIONNUM] = {PRICE1, PRICE2, PRICE3, PRICE4, PRICE5};


void printMenu(); //print menu
void printLine(string str); //print line
void printOrdMenu(); // print menu board
void printWhiteSpace(); // print white space
int orderMenu(); // return order
void showPrice(int ord); // return price of user choose

int main(){

  //print menu
  printMenu();

  while(1){
    int ord = orderMenu();
    if(ord == 0){
      cout<<"Good bye~~"<<endl;
      break;
    }
    else
      showPrice(ord);
  }
  return 0;
}

//print menu show main menu board
void printMenu(){
  cout<<"*--------------------------------------*"<<endl;
  printWhiteSpace();
  cout<<"|"<<setw(27)<<"Choose Hamburger"; cout<<setw(12)<<"|"<<endl;
  printWhiteSpace();
  printOrdMenu();
  printWhiteSpace();
  cout<<"*--------------------------------------*"<<endl;
}

void printOrdMenu(){
  for(int i=0; i<OPTIONNUM; i++){
      //make number to string
      char intStr[10];
      itoa(i+1, intStr, 10);
      string numstr = intStr;

      //make price to string
      itoa(price[i], intStr, 10);
      string pristr = intStr;

      //call printLine function that made by cout
      printLine(numstr + ". " + order[i]+"    "+pristr+"won");
  }
}

void printLine(string str){
    cout<<"|"<<str<<setw(39-str.length())<<"|"<<endl;
}

void printWhiteSpace(){
  cout<<"|"<<setw(39)<<"|"<<endl;
}

int orderMenu(){
  int ord = -1;

  while(1){
    cout<<endl<<"Select Number(0 to exit): ";
    cin>>ord;
    cout<<endl;

    if(ord>=0 && ord<=OPTIONNUM)
      break;
    else
      cout<<"WARNING: Wrong Input"<<endl;
  }
  return ord;
}

void showPrice(int ord){
  cout<<"You order "<<order[ord-1]<<" : "<<price[ord-1]<<" won"<<endl;
}
