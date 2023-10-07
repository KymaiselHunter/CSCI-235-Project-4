//Name : Kyle
//Instructor : Dr. Tiziana Ligorio
//Project 4

#include<iostream>
using namespace std;

#include "Character.hpp"
#include "Barbarian.hpp"

int main()
{
    //Code within comment block should not work as Character is an abtract class
    /*
    Character * testCharacter = new Character;

    testCharacter->display();
    */
   
    Barbarian *b1 = new Barbarian("BONK", "HUMAN", 11, 5, 5, true, "MACE", "ANOTHERMACE", true);    
    b1->display();

    cout << "\nTainted Barbarian: " << endl;
    b1->eatTaintedStew();
    b1->display();
    b1->eatTaintedStew();
    b1->display();
}
