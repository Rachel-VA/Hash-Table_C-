#pragma once
#include <iostream>
#include <list>

using namespace std;

class HashTable {
private:
    int numkeys;         // declare number of buckets
    //list<int>* hashT;   
    list<pair<int, int>>* hashT; // Array of lists for chaining key-value pairs, both key and value are int type

    int hashKey(int key); // Hash function to determine bucket index

public:
    HashTable(int numkeys);      // Constructor
    //funcs definitions
    void insertData(int key, int value);  
    void displayHashTable();     
    bool findValue(int key);    
    bool deleteData(int key);   
};
