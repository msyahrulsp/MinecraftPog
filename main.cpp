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
  ListRecipe listRecipe = ListRecipe();
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

    int itemIdx = listItem.findItem(readItem[0]);
    if (itemIdx != -1) {
      tempId = listItem.getId(itemIdx);
      tType = listItem.getType(itemIdx);
      tTool = listItem.getCat(itemIdx);

      if (tTool == "TOOL") {
        tempItem = new Tool(tempId, readItem[0], tType, tTool, 10);
      } else {
        tempItem = new NonTool(tempId, readItem[0], tType, tTool, stoi(readItem[1]));
      }

      tempRecipe->setOutput(tempItem);
    } else {
      cout << "Nama Item di File Input salah" << endl;
      exit(0);
    }
    
    listRecipe.addRecipe(*tempRecipe);
  }

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
      string craftType;
      cin >> craftType;

      if (craftType == "ONCE") {
        craft.craft(&listRecipe, &invent, false);
      } else if (craftType == "ALL") {
        craft.craft(&listRecipe, &invent, true);
      } else {
        cout << "Invalid craft type" << endl;
      }
    } else if (command == "GIVE") {
      string itemName;
      int itemQty;
      cin >> itemName >> itemQty;

      int itemIdx = listItem.findItem(itemName);
      if (itemIdx != -1) {
        tempId = listItem.getId(itemIdx);
        tName = listItem.getName(itemIdx);
        tType = listItem.getType(itemIdx);
        tTool = listItem.getCat(itemIdx);

        if (tTool == "TOOL") {
          for (int i = 0; i < itemQty; i++) {
            tempItem = new Tool(tempId, tName, tType, tTool, 10);
            invent.addItem(tempItem);
          }
        } else {
          while (itemQty > 0) {
            int qt = (itemQty >= 64 ? 64 : itemQty);
            tempItem = new NonTool(tempId, tName, tType, tTool, qt);
            craft.addItem(tempItem);
            itemQty -= qt;
          }
        }
      } else {
        cout << "Item tidak terdaftar" << endl;
      }
    } else if (command == "MOVE") {
      string slotSrc;
      int slotQty;
      string slotDest;
      
      cin >> slotSrc >> slotQty >> slotDest;

      // bisa ada n tujuan

      char srcType = slotSrc[0];
      char destType = slotDest[0];
      int srcDest = slotSrc[1];
      int destDest = slotDest[1];
      cout << "TODO" << endl;
    } else if (command == "SHOW") {
      craft.display();
      invent.display();
    } else if (command == "DISCARD") {
      string slotSrc;
      int slotQty;
      
      cin >> slotSrc >> slotQty;
      char srcType = slotSrc[0];
      int destType = (int)slotSrc[1]-48;

      if (srcType == 'I') {
        if (destType >= 0 && destType < 36) {
          invent.discard(destType, slotQty);
        } else {
          cout << "Index tujuan invalid" << endl;
        }
      } else if (srcType == 'C') {
        if (destType >= 0 && destType < 9) {
          craft.discard(destType, slotQty);
        } else {
          cout << "Index tujuan invalid" << endl;
        }
      } else {
        cout << "Tujuan invalid" << endl;
      }
    } else if (command == "USE") {
      string slotSrc;

      cin >> slotSrc;
      char srcType = slotSrc[0];
      int destType = (int)slotSrc[1]-48;

      if (srcType == 'I') {
        if (destType >= 0 && destType < 36) {
          invent.use(destType);
        } else {
          cout << "Index tujuan invalid" << endl;
        }
      } else if (srcType == 'C') {
        if (destType >= 0 && destType < 9) {
          craft.use(destType);
        } else {
          cout << "Index tujuan invalid" << endl;
        }
      } else {
        cout << "Tujuan invalid" << endl;
      }
    } else {
      cout << "Invalid command" << endl;
    }
  }
  return 0;
}
