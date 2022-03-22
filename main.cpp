// sample main file, replace this with your own code
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include "module/item.hpp"
#include "module/recipe.hpp"
#include "module/menu.hpp"

using namespace std;

vector<string> split(string str, char delimiter = ' ') {
  vector<string> res;
  stringstream ss(str);
  string temp;

  while(getline(ss, temp, delimiter)) {
    res.push_back(temp);
  }

  return res;
}

int main() {
  vector<string> readItem;
  ListItem listItem = ListItem();
  Inventory invent = Inventory();
  Crafting craft = Crafting();
  ListRecipe *listRecipe = new ListRecipe();
  Recipe *tempRecipe;
  Item *tempItem;
  string tempId, tName, tType, tTool;
  string configPath = "./config";
  string itemConfigPath = configPath + "/item.txt";

  // Baca semua item dari item.txt
  ifstream itemConfigFile(itemConfigPath);
  for (string line; getline(itemConfigFile, line);) {
    readItem = split(line);
    if (readItem[3] == "TOOL") {
      tempItem = new Tool(readItem[0], readItem[1], readItem[2], readItem[3], 0);
    } else {
      tempItem = new NonTool(readItem[0], readItem[1], readItem[2], readItem[3], 0);
    }
    listItem << *tempItem;
  }

  // read recipes
  for (const auto &entry : filesystem::directory_iterator(configPath + "/recipe")) {
    ifstream recipeConfigFile(entry.path());
    string line;
    int idx = 0;

    getline(recipeConfigFile, line);
    tempRecipe = new Recipe((int)line[0]-48, (int)line[2]-48);
    string *tempMat = new string[tempRecipe->getN()];

    for (int i = 0; i < tempRecipe->getRow(); i++) {
      getline(recipeConfigFile, line);
      readItem = split(line);
      for (int j = 0; j < readItem.size(); j++) {
        tempRecipe->setMaterial(idx, readItem[j]);
        idx++;
      }
    }

    getline(recipeConfigFile, line);
    readItem = split(line);
    tempRecipe->setOutput(readItem[0], stoi(readItem[1]));
    
    listRecipe->addRecipe(*tempRecipe);
  };

  string command;
  while (cin >> command) {
    if (command == "EXPORT") {
      string outputPath;
      cin >> outputPath;
      ofstream outputFile(outputPath);
      for (int i = 0; i < SIZEI; i++) {
        outputFile << invent.getSlot(i)->getId() << ":" << invent.getSlot(i)->getSide() << endl;
      }
      cout << "Exported" << endl;
    } else if (command == "CRAFT") {
      cout << "TODO" << endl;
    } else if (command == "GIVE") {
      string itemName;
      int itemQty;
      cin >> itemName >> itemQty;
      cout << "TODO" << endl;
    } else if (command == "MOVE") {
      string slotSrc;
      int slotQty;
      string slotDest;
      // need to handle multiple destinations
      cin >> slotSrc >> slotQty >> slotDest;

      char srcType = slotSrc[0];
      char destType = slotDest[0];
      int srcDest = slotSrc[1];
      int destDest = slotDest[1];
      cout << "TODO" << endl;
    } else if (command == "SHOW") {
      craft.display();
      invent.display();
    } else if (command == "DISCARD") {

    } else if (command == "USE") {

    } else {
      // todo
      cout << "Invalid command" << endl;
    }
  }
  return 0;
}
