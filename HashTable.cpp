#include "hashTable.h"
//#include <algorithm> //for operations 
#include <iomanip> // For colors

using namespace std;

// Constructor
HashTable::HashTable(int numkeys) {
   
    //hashT = new list<int>[numkeys];
    this->numkeys = numkeys; //numbers of buckets
    hashT = new list<pair<int, int>>[numkeys]; // declare array of lists and each hold key-value pairs
}

// Hash function to determine bucket index
int HashTable::hashKey(int data) {
    return data % this->numkeys;//generate bucket index for keys
}

//insert func
void HashTable::insertData(int key, int value) {
    int dataKey = hashKey(key); //bucket index
    for (auto& p : hashT[dataKey]) {//go over the list 
        if (p.first == key) {//if there is key, 
            p.second = value; // then update its value
            return; //end loop
        }
    }
    hashT[dataKey].emplace_back(key, value); // create  a new key-value pair
}

//display table func
void HashTable::displayHashTable() {
    cout << "\n\n";
    for (int i = 0; i < numkeys; i++) {//go over each bucket index
        cout << "\033[1;34mBucket " << setw(2) << i << ": \033[0m"; // blue

        if (!hashT[i].empty()) { //if buckets occupied
            cout << "  --->  "; 
        }

        for (auto& p : hashT[i]) {//go over all key-pairs in buckets
            cout << "\033[1;32mKey: " << p.first << "\033[0m, "//green for key
                << "\033[1;33mValue: " << p.second << "\033[0m -> "; //yellow for values
        }

        if (hashT[i].empty()) {
            cout << "\033[1;31mEMPTY\033[0m"; // Red for empty buckets
        }

        cout << "\n"; 
    }
}

//find value func
bool HashTable::findValue(int key) {
    int dataKey = hashKey(key); //generate bucket index
    for (auto& p : hashT[dataKey]) { //go over inside the bucket
        if (p.first == key) {//if key is found
            cout << "Key: " << key << ", Value: " << p.second << " found in bucket " << dataKey << ".\n";
            return true; //indicate it
        }
    }
  
    return false;//not found
}

//func for delete 
bool HashTable::deleteData(int key) {
    int dataKey = hashKey(key);//make bucket index
    auto& chain = hashT[dataKey]; //refer to bucket list
    for (auto it = chain.begin(); it != chain.end(); ++it) { //go over the list
        if (it->first == key) {//if key is found, delete the pair
            chain.erase(it);
            cout << "Sucessfully deleted Key: " << key << " from bucket " << dataKey << ".\n";
            return true;//indicate sucess
        }
    }
    cout << "Key " << key << " not found for deletion.\n";
    return false;
}
