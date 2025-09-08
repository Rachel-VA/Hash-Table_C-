/*
Rachael Savage
MS549 - Data Structures and Testing
Dr. Jill Coddington
12/08/2024
*/

/*
    This program implements a hash table using chaining and linear probing techniques to handle collisions.

    3 Parts:

    1. Chaining: Uses an array of linked lists to create buckets to store a list of key-value pairs, chaining keys and values in each bucket.

    2. Linear Probing: Using open addressing by probing sequentially to find the next available slot.

    3. Measure performace of the hash tables with insertion, deletion, finding operations with larger datsets
*/



#include "hashTable.h"
#include <iostream>
#include <vector> //container for storing array
#include <utility> //store key-value pairs
#include <stdexcept> //exception handling
#include <string>
#include "linearProbingHashTable.h"
#include <chrono> 


using namespace std::chrono;

using namespace std; //add this line after all other libs


//PART 3: PERFORMANCE TEST FUNC ----------------

void performanceTest() {
    // array data sizes
    int sizes[] = { 100, 1000, 10000 };

    for (int size : sizes) {
        cout << "\n\n =======   Performance Test for Size: " << size << " ========\n\n";
        LinearProbingHashTable<int, int> hashTable(size * 2); // larger table size to give plenty of room to reduce collisions

        // Generate random keys and values
        vector<int> keys(size);
        vector<int> values(size);
        for (int i = 0; i < size; ++i) {
            keys[i] = rand() % (size * 10); // generate keys with a larger range
            values[i] = rand() % 100; // generate values
        }

        // Measure time when inserting
        auto startCount = high_resolution_clock::now();
        for (int i = 0; i < size; ++i) {
            hashTable.insert(keys[i], values[i]);
        }
        auto endCount = high_resolution_clock::now();
        cout << "Insertion Time: " << duration_cast<nanoseconds>(endCount - startCount).count() << " nns\n";

        // time it takes to find and retrieve
        startCount = high_resolution_clock::now();
        for (int i = 0; i < size; ++i) {
            try {
                hashTable.get(keys[i]);
            }
            catch (const exception&) {
                // Handle exception/not found
            }
        }
        endCount = high_resolution_clock::now();
        cout << "Retrieval Time: " << duration_cast<nanoseconds>(endCount - startCount).count() << " nns\n";

        // Measure Deletion Time
        startCount = high_resolution_clock::now();
        for (int i = 0; i < size; ++i) {
            hashTable.remove(keys[i]);
        }
        endCount = high_resolution_clock::now();
        cout << "Deletion Time: " << duration_cast<nanoseconds>(endCount - startCount).count() << " nns\n";
    }
}





int main() {

    //----------------------- PART 1: Chaining technique: using a list to store group values into different buckets. like a filename contains multiple documents in it


  
    cout << "\033[1;35m\n\n*****************************   PART I: HASH TABLE USING CHAINING TECHNIQUE  ************************************* \033[0m" << endl;
    HashTable hashT(20); // Create a hash table with a number of buckets

    // Insert 100 random key-value pairs into the hash table
    cout << "\nInserting random key-value pairs into the hash table...\n";
    for (int i = 0; i < 100; i++) {
        int key = rand() % 100;    // Random keys 0-99
        int value = rand() % 1000; // Random values 0-999
        hashT.insertData(key, value);
        //cout << "Inserted Key: " << key << ", Value: " << value << "\n";
    }

    // Display the hash table
    cout << "\nHash Table after inserting 100 key-value pairs:\n";
    hashT.displayHashTable();

    // Retrieve specific keys
    cout << "\n-------- Retrieving specific keys... \n\n";
    int searchKeys[] = { 34, 75 };
    for (int key : searchKeys) {
        if (hashT.findValue(key)) {
            cout << "Key " << key << " was FOUND.\n";
        }
        else {
            cout << "Key " << key << " was NOT found.\n";
        }
    }

    // Delete specific keys
    cout << "\n------  Deleting specific keys...\n";
    hashT.deleteData(29);
    // hashT.deleteData(4);

    // Display the hash table after deleted 
    cout << "\nHash Table after deletions:\n";
    hashT.displayHashTable();

    
    
    

    //----------PART 2:  Hash Table using Linear Probing Open Address------------------------------------
     
    cout << "\033[1;35m\n\n\n******************************  PART 2: HASH TABLE USING LINEAR PROBING TECHNIQUE  ******************************\n\n\033[0m" << endl;

    // Testing Linear Probing Hash Table with Integers
    cout << "--- Testing Linear Probing with Integers ---\n\n";
    LinearProbingHashTable<int, int> intHashTable(10);

    cout << "Inserting multiple random values...\n";
    for (int i = 0; i < 8; i++) {
        int key = rand() % 20;  // Generate random keys
        int value = rand() % 100; // Generate random values
        intHashTable.insert(key, value);
        cout << "Inserted key " << key << " with value " << value << ".\n";
    }

    cout << "\nHash Table after inserted multiple integer values:\n";
    intHashTable.display();

    int searchKey = 5;
    cout << "\nDeleting key " << searchKey << "...\n";
    if (intHashTable.remove(searchKey)) { // Check if the key was successfully deleted
        cout << "\nHash Table after deleting key " << searchKey << ":\n";
        intHashTable.display();
    }
    else {
        cout << "Key " << searchKey << " was not found for deletion.\n";
    }

    //remove 
    intHashTable.remove(searchKey);
    cout << "\nHash Table after deleting key " << searchKey << ":\n";
    intHashTable.display();

    // Linear probing  with strings
    cout << "\n---------- Linear probing with strings ---------\n\n";
    LinearProbingHashTable<string, string> stringHashTable(10);
    cout << "Inserting strings.....\n\n" << endl;
    stringHashTable.insert("Alice", "Math");
    stringHashTable.insert("Bob", "Science");
    stringHashTable.insert("Charlie", "History");
    stringHashTable.insert("David", "Physics");
    stringHashTable.insert("Eve", "Chemistry");
    stringHashTable.insert("Frank", "Biology");

    cout << "\nHash Table after inserted string data into buckets:\n";
    stringHashTable.display();

    string searchStrKey = "Eve";
    if (stringHashTable.remove(searchStrKey)) { // if the key was successfully deleted
        cout << "\nHash Table after deleting key '" << searchStrKey << "':\n";
        stringHashTable.display();
    }
    else {
        cout << "Key '" << searchStrKey << "' was NOT found for deletition\n";
    }
    

    stringHashTable.remove("Alice");
    cout << "\nHash Table after deleting key 'Alice':\n";
    stringHashTable.display();


    cout << "\033[1;35m\n\n\n**********************  PART 3: PERFORMANCE TESTING ON HASH TABLE  *****************************\n\n\033[0m" << endl;

    // Call performanceTest func above to output
    performanceTest();

    cout << "\n\n\n" << endl;
    return 0;
}//end main

