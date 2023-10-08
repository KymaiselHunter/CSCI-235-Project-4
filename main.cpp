//Name : Kyle
//Instructor : Dr. Tiziana Ligorio
//Project 4

#include<iostream>
using namespace std;

#include "Character.hpp"
#include "Barbarian.hpp"
#include "Mage.hpp"
#include "Ranger.hpp"
#include "Scoundrel.hpp"

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

    //test ranger
    cout << "======================================" << endl;
    Arrows testArrow1;
    testArrow1.type_ = "Wood";
    testArrow1.quantity_ = 30;

    Arrows testArrow2;
    testArrow2.type_ = "Fire";
    testArrow2.quantity_ = 5;

    vector<Arrows> testQuiver;
    testQuiver.push_back(testArrow1);
    testQuiver.push_back(testArrow2);

    vector<string> testAffinities;
    testAffinities.push_back("FIRE");
    testAffinities.push_back("Poison");

    cout << "UNDEAD Ranger" << endl;
    Character *r1 = new Ranger("MARROW", "UNDEAD", 9, 4, 6, false, testQuiver, testAffinities, true);
    r1->display();

    cout << "tainted UNDEAD Ranger" << endl;
    r1->eatTaintedStew();
    r1->display();
    
    cout << "Normal ranger with poision affininity" << endl;
    Character *r2 = new Ranger("NUSY", "DWARF", 9, 4, 6, false, testQuiver, testAffinities, true);
    r2->display();

    cout << "Tainted Normal ranger" << endl;
    r2->eatTaintedStew();
    r2->display();

    //test Scoundrel
    cout << "======================================" << endl;
    cout << "Test given Scoundrel(Cutpurse)" << endl;
    Character * s1 = new Scoundrel("FLEA", "DWARF", 6, 4, 4, true, "ADAMANT", "Cutpurse", true);
    s1->display();

    cout << "Test tainted given Scoundrel(Cutpurse)" << endl;
    s1->eatTaintedStew();
    s1->display();

    cout << "Test Scoundrel(SIlver tongue)" << endl;
    Character * s2 = new Scoundrel("DAKOTA", "LIZARD", 6, 4, 4, true, "ADAMANT", "SILVERTONGUE", true);
    s2->display();

    cout << "Test tainted Scoundrel(SIlver tongue)" << endl;
    s2->eatTaintedStew();
    s2->display();
}
