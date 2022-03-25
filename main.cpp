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
  ArmorSlot armor = ArmorSlot();
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
    // Bikin pointer ke class baru, pertipe
    if (readItem[3] == "TOOL") {
      tempItem = new Tool(readItem[0], readItem[1], readItem[2], readItem[3], 0);
    } else if (readItem[3] == "ARMOR") {
      tempItem = new Armor(readItem[0], readItem[1], readItem[2], readItem[3], 0);
    } else {
      tempItem = new NonTool(readItem[0], readItem[1], readItem[2], readItem[3], 0);
    }

    // Masukin item ke list item
    listItem << *tempItem;
  }

  // Baca recipe semua item
  for (const auto &entry : filesystem::directory_iterator(configPath + "/recipe")) {
    ifstream recipeConfigFile(entry.path());
    string line;
    int idx = 0;

    getline(recipeConfigFile, line);
    tempRecipe = new Recipe((int)line[0]-48, (int)line[2]-48);
    string *tempMat = new string[tempRecipe->getN()];

    // Ambil tiap char, dinamis ukurannya
    for (int i = 0; i < tempRecipe->getRow(); i++) {
      getline(recipeConfigFile, line);
      readItem = split(line);
      for (int j = 0; j < readItem.size(); j++) {
        // Set recipe, perindex
        tempRecipe->setMaterial(idx, readItem[j]);
        idx++;
      }
    }

    getline(recipeConfigFile, line);
    readItem = split(line);
    int itemIdx = listItem.findItem(readItem[0], "nama");

    // Bikin pointer ke class baru buat dimasukin ke list recipe
    if (itemIdx != -1) {
      tempId = listItem.getId(itemIdx);
      tType = listItem.getType(itemIdx);
      tTool = listItem.getCat(itemIdx);

      if (tTool == "TOOL") {
        tempItem = new Tool(tempId, readItem[0], tType, tTool, 10);
      } else if (tTool == "ARMOR") {
        tempItem = new Armor(tempId, readItem[0], tType, tTool, 20);
      } else {
        tempItem = new NonTool(tempId, readItem[0], tType, tTool, stoi(readItem[1]));
      }

      tempRecipe->setOutput(tempItem);
    } else {
      cout << "Nama Item di File Input salah" << endl;
      exit(1);
    }
    
    listRecipe.addRecipe(*tempRecipe);
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
      string craftType;
      cin >> craftType;

      // Craft per jenis, sekali atau semua
      if (craftType == "ONCE") {
        craft.craft(&listRecipe, &invent, false, &listItem);
      } else if (craftType == "ALL") {
        craft.craft(&listRecipe, &invent, true, &listItem);
      } else {
        cout << "Invalid craft type" << endl;
      }
    } else if (command == "GIVE") {
      string itemName;
      int itemQty;
      cin >> itemName >> itemQty;

      int itemIdx = listItem.findItem(itemName, "nama"); // Nyari index item input di list
      if (itemIdx != -1) { // Item gk ditemuin

        // Bikin class baru buat masukin ke inventory
        tempId = listItem.getId(itemIdx);
        tName = listItem.getName(itemIdx);
        tType = listItem.getType(itemIdx);
        tTool = listItem.getCat(itemIdx);

        if ((tTool == "TOOL") || (tTool == "ARMOR")) {
          for (int i = 0; i < itemQty; i++) {
            if (tTool == "TOOL") {
              tempItem = new Tool(tempId, tName, tType, tTool, 10);
            } else {
              tempItem = new Armor(tempId, tName, tType, tTool, 20);
            }
            invent.addItem(tempItem);
          }
        } else {
          // Case give item > 64, biar gk kesimpen di 1 slot dan tetep jalan
          while (itemQty > 0) { 
            int qt = (itemQty >= 64 ? 64 : itemQty);
            tempItem = new NonTool(tempId, tName, tType, tTool, qt);
            invent.addItem(tempItem);
            itemQty -= qt;
          }
        }
      } else {
        cout << "Item tidak terdaftar" << endl;
        exit(1);
      }
    } else if (command == "MOVE") {
      string slotSrc;
      int slotQty;
      string slotDest;
      
      cin >> slotSrc >> slotQty;
      for (int i = 0; i < slotQty; i++) {
        cin >> slotDest;

        char srcType = slotSrc[0];
        char destType = slotDest[0];
        int srcDest = 0;
        int destDest = 0;

        // Change masukan tujuan biar bisa puluhan
        for (int i = 1; i < slotSrc.size(); i++) {
          srcDest = srcDest * 10 + (int)slotSrc[i]-48;
        }

        for (int i = 1; i< slotDest.size(); i++) {
          destDest = destDest * 10 + (int)slotDest[i]-48;
        }

        if (srcType == 'I') {
          if (destType == 'I') {
            invent.move(srcDest, destDest);
          } else if (destType == 'C') {
            invent.move(srcDest, destDest, &craft);
          } else {
            cout << "Tujuan invalid" << endl;
          }
        } else if (srcType == 'C') {
          if (destType == 'I') {
            craft.move(srcDest, destDest, &invent);
          } else if (destType == 'C') {
            craft.move(srcDest, destDest);
          } else {
            cout << "Tujuan invalid" << endl;
          }
        } else {
          cout << "Tujuan invalid" << endl;
        }
      }
    } else if (command == "SHOW") {
      cout << "\t\t\t-- INVENTORY MENU --" << endl << endl;
      craft.display();
      cout << endl;
      invent.display();
      cout << endl;

      cout << "\t-- Armor Slot --" << endl;
      armor.displayArmor();
      cout << endl;
    } else if (command == "DISCARD") {
      string slotSrc;
      int slotQty;
      
      cin >> slotSrc >> slotQty;
      char srcType = slotSrc[0];
      int destType = 0;

      // Change masukan tujuan biar bisa puluhan
      for (int i = 1; i < slotSrc.size(); i++) {
        destType = destType * 10 + (int)slotSrc[i]-48;
      }

      if (srcType == 'I') {
        if (destType >= 0 && destType < 27) {
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
      int destType = 0;

      // Change masukan tujuan biar bisa puluhan
      for (int i = 1; i < slotSrc.size(); i++) {
        destType = destType * 10 + (int)slotSrc[i]-48;
      }

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
    } else if (command == "EQUIP") {
      string slotSrc;

      cin >> slotSrc;
      char srcType = slotSrc[0];
      int destType = 0;

      // Change masukan tujuan biar bisa puluhan
      for (int i = 1; i < slotSrc.size(); i++) {
        destType = destType * 10 + (int)slotSrc[i]-48;
      }

      if (srcType == 'I') {
        tempItem = invent.getSlot(destType);
        armor.equip(tempItem, &invent, destType);
      } else if (srcType == 'C') {
        cout << "Armor hanya bisa diequip dari Inventory" << endl;
      } else {
        cout << "Tujuan invalid" << endl;
      }
    } else if (command == "EXIT") {
      break;
    } else {
      cout << "Invalid command" << endl;
    }
  }
  return 0;
}