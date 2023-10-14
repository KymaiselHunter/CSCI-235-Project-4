/*
CSCI235 Fall 2023
Project 3 - Tavern Class
Georgina Woo
June 20 2023
Tavern.cpp declares the Tavern class along with its private and public members
*/
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
Tavern::Tavern(std::string pFileName)
{
  //get access to file
  std::ifstream tavernParameters;
  
  //if file name wrong or file does not exist, file not found
  try
  {
    tavernParameters.open(pFileName);

    if(!tavernParameters.is_open()) throw 404;
  }
  catch(int x)
  {
    std::cout << "File Not Found";
  }

  //now loop through the file to get information for characters
  //use exception if the information in the file is formated wrong
  //get information and put it into a 2d matrix
  //if not enough info throw error
  std::vector<std::vector<std::string>> fileToMatrix;

  try
  {
    std::string line;
    bool first = true;

    while(getline(tavernParameters, line))
    {
      //
      if(first)
      {
        first = false;
        continue;
      }
      
      //std::cout << "line : "<< line << std::endl;
      //loop to get info from line
      std::vector<std::string> lineInformation;
      //std::cout << line << std::endl;

      while(line.find(",") != -1)
      {
        lineInformation.push_back(line.substr(0, line.find(",")));
        line = line.substr(line.find(",") + 1);
      }
      lineInformation.push_back(line);

      if(lineInformation.size() != 14) throw 14;
      
      //send vector of info to matrix
      fileToMatrix.push_back(lineInformation);
    }
  }
  catch(int x)
  {
    std::cout << "Incorrect amount of information in line";
  }
  catch(...)
  {
    std::cout << "Unknown File to character error";
  }

  tavernParameters.close();
  
  //dynamic allocation
  //for dynamic allocation, get size
  int amountOfCharacters = fileToMatrix.size();
  //std::cout << amountOfCharacters << std::endl;

  //dynamically allocated array
  //array of pointers
  Character** c = new Character*[amountOfCharacters];

  //create characters
  //exception if input is off
  try 
  {
    //do for each line to get each char info
    for(int i = 0; i < amountOfCharacters; i++)
    {
      std::vector<std::string> lineInformation = fileToMatrix[i];
      //std::cout << i << " " <<lineInformation[0] << std::endl;
      if(lineInformation[2] == "BARBARIAN")
      {
        c[i] = new Barbarian(lineInformation[0], lineInformation[1], 
        std::stoi(lineInformation[3]), std::stoi(lineInformation[4]), std::stoi(lineInformation[5]),
        std::stoi(lineInformation[6]), lineInformation[7], lineInformation[8],
        std::stoi(lineInformation[13]));
        //c[i]->display();
        //Character *b1 = new Barbarian("BONK", "HUMAN", 11, 5, 5, true, "MACE", "ANOTHERMACE", true);  
      }
      else if(lineInformation[2] == "MAGE")
      {
        c[i] = new Mage(lineInformation[0], lineInformation[1], 
        std::stoi(lineInformation[3]), std::stoi(lineInformation[4]), std::stoi(lineInformation[5]),
        std::stoi(lineInformation[6]), lineInformation[9], lineInformation[7],
        std::stoi(lineInformation[10]));
        //c[i]->display();
      }
      else if(lineInformation[2] == "SCOUNDREL")
      {
        c[i] = new Scoundrel(lineInformation[0], lineInformation[1], 
        std::stoi(lineInformation[3]), std::stoi(lineInformation[4]), std::stoi(lineInformation[5]),
        std::stoi(lineInformation[6]), lineInformation[7], lineInformation[9],
        std::stoi(lineInformation[12]));
        //c[i]->display();
      }
      else if(lineInformation[2] == "RANGER")
      {
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
            //std::cout << "issue here? : " << lineInformation[9]<<std::endl;
          }
          //add last affinity after semi colon
          affinities.push_back(lineInformation[11]);
        }

        std::vector<Arrows> arrows;

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
            //std::cout << "issue here? : " << lineInformation[5]<<std::endl;
          }
          //add last arrow after semi colon
          Arrows a;
          a.type_ = lineInformation[7].substr(0,lineInformation[7].find(" "));
          a.quantity_ = std::stoi(lineInformation[7].substr(lineInformation[7].find(" ") + 1, 
          lineInformation[7].find(";") - lineInformation[7].find(" ") + 1));

          arrows.push_back(a);
          lineInformation[7] = lineInformation[7].substr(lineInformation[7].find(";")+1);
        }

        //test to find where error
        // std::cout << i << " " <<lineInformation[0] << std::endl;
        // std::cout << i << " " <<lineInformation[1] <<
        // " " << lineInformation[1] <<
        // " " << lineInformation[3] <<
        // " " << lineInformation[4] <<
        // " " << lineInformation[5] <<
        // " " << lineInformation[6] <<
        // std::endl;

        // std::cout << i << " " << lineInformation[10] << std::endl;

        // for(int i = 0; i < affinities.size(); i++)
        // {
        //   std::cout << affinities[i] << std::endl;
        // }

        // for(int i = 0; i < arrows.size(); i++)
        // {
        //   std::cout << arrows[i].type_ << " " << arrows[i].quantity_ << std::endl;
        // }

        c[i] = new Ranger(lineInformation[0], lineInformation[1], 
        std::stoi(lineInformation[3]), std::stoi(lineInformation[4]), std::stoi(lineInformation[5]),
        std::stoi(lineInformation[6]), arrows, affinities,
        std::stoi(lineInformation[10]));

        c[i]->display();
      }
      else throw "Invalid Input";
      //std::cout << i << " " << "what the actual fuck" << std::endl;
      //c[i]->display();
    }
  }
  catch(...)
  {
    std::cout << "Unknown Error when constructing characters";
  }
  
  //have the characters enter the tavern
  for(int i = 0; i < amountOfCharacters; i++)
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
void Tavern::taintedStew() const
{
  for(int i = 0; i < this->getCurrentSize(); i++)
  {
    this->items_[i]->eatTaintedStew();
  }
}