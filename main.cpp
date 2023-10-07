//Name : Kyle
//Instructor : Dr. Tiziana Ligorio
//Project 4

#include<iostream>
using namespace std;

#include "Character.hpp"
#include "Barbarian.hpp"
#include "Mage.hpp"

int main()
{
    //Code within comment block should not work as Character is an abtract class
    /*
    Character * testCharacter = new Character;

    testCharacter->display();
    */

    //test barbarian
    cout << "======================================" << endl;
    Character *b1 = new Barbarian("BONK", "HUMAN", 11, 5, 5, true, "MACE", "ANOTHERMACE", true);    
    b1->display();

    cout << "Tainted Barbarian: " << endl;
    b1->eatTaintedStew();
    b1->display();
    b1->eatTaintedStew();
    b1->display();

    //test mage
    cout << "======================================" << endl;
    Character *m1 = new Mage("SPYNACH", "ELF", 6, 4, 4, false, "ILLUSION", "WAND", true);
    m1->display();

    cout << "Tainted Barbarian: " << endl;
    m1->eatTaintedStew();
    m1->display();
}
