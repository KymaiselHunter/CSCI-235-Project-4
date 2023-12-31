/*
CSCI235 Fall 2023
Project 3 - Tavern Class
Georgina Woo
June 20 2023
Tavern.cpp declares the Tavern class along with its private and public members
*/

//Name : Kyle
//Instructor : Dr. Tiziana Ligorio
//Project 4

#include "Tavern.hpp"

/** Default Constructor **/
Tavern::Tavern() : ArrayBag<Character*>(), level_sum_{0}, num_enemies_{0}
{
}

//include for taking a file
#include <fstream>
//include for storing info
#include <vector>

//Paremeterized Constructor
/**
    @param: the name of an input file
    @pre: Formatting of the csv file is as follows (each numbered item appears separated by comma, only one value for each numbered item):
1. Name: An uppercase string
2. Race: An uppercase string [HUMAN, ELF, DWARF, LIZARD, UNDEAD]
3. Subclass: An uppercase string [BARBARIAN, MAGE, SCOUNDREL, RANGER]
4. Level/Vitality/Armor: A positive integer
5. Enemy: 0 (False) or 1 (True)
6. Main: Uppercase string or strings representing the main weapon (Barbarian and Mage), Dagger type (Scoundrel), or arrows (Ranger). A ranger's arrows are of the form [TYPE] [QUANTITY];[TYPE] [QUANTITY], where each arrow type is separated by a semicolon, and the type and its quantity are separated with a space.
7. Offhand: An uppercase string that is only applicable to Barbarians, and may be NONE if the Barbarian does not have an offhand weapon, or if the character is of a different subclass.
8. School/Faction: Uppercase strings that represent a Mage's school of magic: [ELEMENTAL, NECROMANCY, ILLUSION] or a Scoundrel's faction: [CUTPURSE, SHADOWBLADE, SILVERTONGUE], and NONE where not applicable
9. Summoning: 0 (False) or 1 (True), only applicable to Mages (summoning an Incarnate) and Rangers (Having an Animal Companion)
10. Affinity: Only applicable to Rangers. Affinities are of the form [AFFINITY1];[AFFINITY2] where multiple affinities are separated by a semicolon. Th value may be NONE for a Ranger with no affinities, or characters of other subclasses.
11. Disguise: 0 (False) or 1 (True), only applicable to Scoundrels, representing if they have a disguise.
12. Enraged: 0 (False) or 1 (True), only applicable to Barbarians, representing if they are enraged.
    @post: Each line of the input file corresponds to a Character subclass and dynamically allocates Character derived objects, adding them to the Tavern.
*/
Tavern::Tavern(const std::string pFileName)
{
  //get access to file
  std::ifstream tavernParameters(pFileName);
  
  //check for failure to open file
  if(tavernParameters.fail())
  {
    std::cerr << "File cannot be opened for reading." << std::endl;
    exit(1);//exit if failed to open
  }

  //remove first line
  std::string line;
  getline(tavernParameters,line);

  //dynamically allocated array
  //array of pointers
  Character** c = new Character*[100];//size is 100 as that is the max that an array bag may hold
  //size here is more like capacity in this situation
  int size = 0;//size used for iteration in for loops 


  while(getline(tavernParameters, line))
  {
    //NAME,RACE,SUBCLASS,LEVEL,VITALITY,ARMOR,ENEMY,MAIN,OFFHAND,SCHOOL/FACTION,SUMMONING,AFFINITY,DISGUISE,ENRAGED
    
    //loop to get info from line
    std::vector<std::string> lineInformation;

    while(line.find(",") != -1)
    {
      lineInformation.push_back(line.substr(0, line.find(",")));
      line = line.substr(line.find(",") + 1);
    }
    lineInformation.push_back(line);
    
    //if statement depending on what class to instantiate this object as
    if(lineInformation[2] == "BARBARIAN")
    {
      c[size] = new Barbarian(lineInformation[0], lineInformation[1], 
      std::stoi(lineInformation[4]), std::stoi(lineInformation[5]), std::stoi(lineInformation[3]),
      std::stoi(lineInformation[6]), lineInformation[7], lineInformation[8],
      std::stoi(lineInformation[13]));
    }
    else if(lineInformation[2] == "MAGE")
    {
      c[size] = new Mage(lineInformation[0], lineInformation[1], 
      std::stoi(lineInformation[4]), std::stoi(lineInformation[5]), std::stoi(lineInformation[3]),
      std::stoi(lineInformation[6]), lineInformation[9], lineInformation[7],
      std::stoi(lineInformation[10]));
    }
    else if(lineInformation[2] == "SCOUNDREL")
    {
      c[size] = new Scoundrel(lineInformation[0], lineInformation[1], 
      std::stoi(lineInformation[4]), std::stoi(lineInformation[5]), std::stoi(lineInformation[3]),
      std::stoi(lineInformation[6]), lineInformation[7], lineInformation[9],
      std::stoi(lineInformation[12]));
    }
    else if(lineInformation[2] == "RANGER")
    {
      //create a vector of affinities for the affinity parameter
      std::vector<std::string> affinities;
      
      //if they have affinities, if not, the vect will be empty
      if(lineInformation[11] != "NONE")
      {
        //while loop to go through the affinities list and add them to vect
        //substr to remove added affinities
        while(lineInformation[11].find(";")!=-1)
        {
          affinities.push_back(lineInformation[11].substr(0,lineInformation[11].find(";")));
          lineInformation[11] = lineInformation[11].substr(lineInformation[11].find(";")+1);
        }
        //add last affinity after semi colon
        affinities.push_back(lineInformation[11]);
      }

      std::vector<Arrows> arrows;

      //if this ranger has arrows get that data, if not give an empty arrow vector
      if(lineInformation[7] != "NONE")
      {
        //while loop to go through the arrow list and add them to vect
        //substr to remove added arrow
        //use the space to differ between type and quantity
        while(lineInformation[7].find(";")!=-1)
        {
          Arrows a;
          a.type_ = lineInformation[7].substr(0,lineInformation[7].find(" "));
          a.quantity_ = std::stoi(lineInformation[7].substr(lineInformation[7].find(" ") + 1, 
          lineInformation[7].find(";") - lineInformation[7].find(" ") + 1));

          arrows.push_back(a);
          lineInformation[7] = lineInformation[7].substr(lineInformation[7].find(";")+1);
        }
        //add last arrow after semi colon
        //this code does the same thing as the previous block but this will not be going through the for loop
        //as the last arrow will not have a semicololn after it
        Arrows a;
        a.type_ = lineInformation[7].substr(0,lineInformation[7].find(" "));
        a.quantity_ = std::stoi(lineInformation[7].substr(lineInformation[7].find(" ") + 1));

        arrows.push_back(a);
      }
      c[size] = new Ranger(lineInformation[0], lineInformation[1], 
      std::stoi(lineInformation[4]), std::stoi(lineInformation[5]), std::stoi(lineInformation[3]),
      std::stoi(lineInformation[6]), arrows, affinities,
      std::stoi(lineInformation[10]));
    }
    size++;
  }
  //close cuz file is no longer needed;
  tavernParameters.close();

  //have the characters enter the tavern
  for(int i = 0; i < size; i++)
  {
    this->enterTavern(c[i]);
  }

  //now that they entered, deal with array to avoid memory leak
  delete [] c;
  c = nullptr;
}

/** 
    @param:   A reference to a Character(changed to pointer)  entering the Tavern
    @return:  returns true if a Character was successfully added to items_, false otherwise
    @post:    adds Character(changed to pointer)  to the Tavern and updates the level sum and the enemy count if the character is an enemy.
**/
bool Tavern::enterTavern(Character* a_character)
{
  if(add(a_character))
  {
    level_sum_ += a_character->getLevel();
    if(a_character->isEnemy())
      num_enemies_++;
     
    return true;
  }
  else
  {
    return false;
  }
}

/** @param:   A reference(changed to pointer)  to a Character leaving the Tavern  
    @return:  returns true if a character was successfully removed from items_, false otherwise
    @post:    removes the character(pointer)  from the Tavern and updates the level sum and the enemy count if the character is an enemy.
**/
bool Tavern::exitTavern(Character* a_character)
{
  if(remove(a_character))
  {
    level_sum_ -= a_character->getLevel();
    if(a_character->isEnemy())
      num_enemies_--;
      
    return true;
  }
  return false;
}



/** 
    @return:  The integer level count of all the characters currently in the Tavern
    **/
    int Tavern::getLevelSum()
    {
      return level_sum_;
    }



/** 
    @return:  The average level of all the characters in the Tavern
    @post:    Considers every character currently in the Tavern, updates the average level of the Tavern rounded to the NEAREST integer, and returns the integer value.
**/
int Tavern::calculateAvgLevel()
{
   return (level_sum_>0) ? round(double(level_sum_) / item_count_) : 0.0;

}



/** 
    @return:  The integer enemy count of the Tavern
    **/
    int Tavern::getEnemyCount()
    {
      return num_enemies_;
    }



/** 
    @return:  The percentage (double) of all the enemy characters in the Tavern
    @post:    Considers every character currently in the Tavern, updates the enemy percentage of the Tavern rounded to 2 decimal places, and returns the double value.
**/
double Tavern::calculateEnemyPercentage()
{
  double enemy_percent = (num_enemies_>0) ?  (double(num_enemies_) / item_count_) * 100: 0.0;
  return std::ceil(enemy_percent*100.0) / 100.0; //round up to to decimal places
 
}


/** 
    @param:   A string reference to a race 
    @return:  An integer tally of the number of characters in the Tavern of the given race
**/
int Tavern::tallyRace(const std::string &race)
{
  int frequency = 0;
  int curr_index = 0;   
  while (curr_index < item_count_)
  {
    if (items_[curr_index]->getRace() == race)
    {
      frequency++;
    } 

    curr_index++; 
  }

  return frequency;
}


/**
  @post:    Outputs a report of the characters currently in the tavern in the form:
  "Humans: [x] \nElves: [x] \nDwarves: [x] \nLizards: [x] \nUndead: [x] \n\nThe average level is: [x] \n[x]% are enemies.\n\n"

  Example output: 
  Humans: 5
  Elves: 8
  Dwarves: 3
  Lizards: 7
  Undead: 2

  The average level is: 16
  24% are enemies.
*/
void Tavern::tavernReport()
{
  int humans = tallyRace("HUMAN");
  int elves = tallyRace("ELF");
  int dwarves = tallyRace("DWARF");
  int lizards = tallyRace("LIZARD");
  int undead = tallyRace("UNDEAD");
  
  std::cout << "Humans: " << humans << std::endl;
  std::cout << "Elves: " << elves << std::endl;
  std::cout << "Dwarves: " << dwarves << std::endl;
  std::cout << "Lizards: " << lizards << std::endl;
  std::cout << "Undead: " << undead << std::endl;
  std::cout << "\nThe average level is: " << calculateAvgLevel() << std::endl;
  std::cout << std::fixed << std::setprecision(2) << calculateEnemyPercentage() << "% are enemies.\n\n";
}

/**
    @post: For every character in the tavern, displays each character's information
*/
void Tavern::displayCharacters() const
{
  for(int i = 0; i < this->getCurrentSize(); i++)
  {
    this->items_[i]->display();
  }
}


/**
@param: a string reference to a race
@post: For every character in the tavern of the given race (only exact matches to the input string), displays each character's information
*/
void Tavern::displayRace(const std::string &pRace) const
{
  for(int i = 0; i < this->getCurrentSize(); i++)
  {
    if(items_[i]->getRace() == pRace)items_[i]->display();
  }
}

/**
@post: Every character in the tavern eats a tainted stew.
*/
void Tavern::taintedStew()
{
  for(int i = 0; i < this->getCurrentSize(); i++)
  {
    this->items_[i]->eatTaintedStew();
  }
}