#pragma once
#include <iostream>
#include <string>
#include <vector> //container to store array
#include <stdexcept>//exception ahndling
#include <utility>//store key0value pairs

using namespace std;


//template class for a hash table
template <typename K, typename V>
class LinearProbingHashTable {
private:
    struct Entry {
        //key and values 
        K key;
        V value;
        bool occupied;

        // Default constructor
        Entry() : occupied(false) {}

        // Constructor to start 
        Entry(const K& k, const V& v, bool o) : key(k), value(v), occupied(o) {}
    };

    //vector to store hash table
    vector<Entry> table;
    size_t capacity; //slots of hash table
    size_t size; //current elements

    size_t hashFunction(const K& key) const; //hash index for a key
    size_t probe(size_t index) const; //prob for next index if collisions

public:  
    //constructor to start hash table with 10 slots
    LinearProbingHashTable(size_t initialCapacity = 10);

    void insert(const K& key, const V& value); //insert key-valaue pairs
    V get(const K& key) const; //find key-value pairs
    bool remove(const K& key); //remove
    void display() const;//output
};


// Implement the Constructor and all funcs
template <typename K, typename V>
LinearProbingHashTable<K, V>::LinearProbingHashTable(size_t initialCapacity)
    : table(initialCapacity), capacity(initialCapacity), size(0) {
}

// Hash func
template <typename K, typename V>
size_t LinearProbingHashTable<K, V>::hashFunction(const K& key) const {
    return std::hash<K>{}(key) % capacity; //use buit-in hash to hash and applied modulor operation for table
}

// Linear probing func to handle collisions
template <typename K, typename V>
size_t LinearProbingHashTable<K, V>::probe(size_t index) const {
    return (index + 1) % capacity; //keep moving to the next slo
}

// Insert a key-value pair into table
template <typename K, typename V>
void LinearProbingHashTable<K, V>::insert(const K& key, const V& value) {
    if (size == capacity) {//if table is full,
        throw overflow_error("Hash table is full"); //then show message
    }

    size_t index = hashFunction(key); //compute index key

    for (size_t i = 0; i < capacity; ++i) { //keep moving to find a slot
        if (!table[index].occupied || table[index].key == key) { //if slot is empty or match key
            table[index] = Entry(key, value, true);//then  drop it in
            ++size; //incre table size
            return; //end loop
        }
        index = probe(index);//move to next slot
    }
}

// Retrieve a value by key similar to the above func
template <typename K, typename V>
V LinearProbingHashTable<K, V>::get(const K& key) const {
    size_t index = hashFunction(key); //make index for key

    for (size_t i = 0; i < capacity; ++i) {//keep moving to find the key
        if (table[index].occupied && table[index].key == key) {//if slot is in used and key match
            return table[index].value; //take it and display
        }
        index = probe(index);//keep moving to next slot
    }
    throw out_of_range("Key not found"); //end of hash table and NOT found
}

// Remove a key-value pair similar to funcs above
template <typename K, typename V>
bool LinearProbingHashTable<K, V>::remove(const K& key) {
    size_t index = hashFunction(key); //compute indx for key

    for (size_t i = 0; i < capacity; ++i) {//keep moving to find slot and match key
        if (table[index].occupied && table[index].key == key) {//if slot is in used and ket macth
            table[index].occupied = false;//take it and empty it
            --size; //reduce table
            return true; //end loop and indicate ssucessfully removed
        }
        index = probe(index);//keep moving
    }
    return false;//indicate not foud
}

// Display table with colors coded
template <typename K, typename V>
void LinearProbingHashTable<K, V>::display() const {
    // ANSI escape codes for colors
    const string bucketColor = "\033[1;34m";//blue
    const string keyColor = "\033[1;32m";//gree
    const string valueColor = "\033[1;33m";//yellow
    const string emptyColor = "\033[1;31m"; //red
    const string resetColor = "\033[0m";  //reset color to default

    cout << bucketColor << "Hash Table:\n" << resetColor;
    //go over each bucket
    for (size_t i = 0; i < capacity; ++i) {
        cout << bucketColor << "Bucket " << i << ": " << resetColor; // show bucket index
        if (table[i].occupied) {//if bucket is taken, display them
            cout << keyColor << "Key: " << table[i].key << resetColor
                << " " << valueColor << "Value: " << table[i].value << resetColor << "\n";
        }
        else {
            cout << emptyColor << "EMPTY" << resetColor << "\n"; //show empty bucket in red
        }
    }
}






//reference source
//https://www.google.com/search?q=how+to+create+a+sha+table+using+template+and+linear+probing+in+C%2B%2B%0D%0A&sca_esv=face10566ce46e9f&sxsrf=ADLYWIL5Xl3uBsJrcfwJDY5pA-PWXy1ANA%3A1733696277635&source=hp&ei=FRtWZ92TJK2p5NoPxcWQiQQ&iflsig=AL9hbdgAAAAAZ1YpJbJ2NpkQWyMlqYQ2stD5-BZeJSYY&ved=0ahUKEwid8pj2mZmKAxWtFFkFHcUiJEEQ4dUDCBo&uact=5&oq=how+to+create+a+sha+table+using+template+and+linear+probing+in+C%2B%2B%0D%0A&gs_lp=Egdnd3Mtd2l6IkNob3cgdG8gY3JlYXRlIGEgc2hhIHRhYmxlIHVzaW5nIHRlbXBsYXRlIGFuZCBsaW5lYXIgcHJvYmluZyBpbiBDKysKMgcQIRigARgKMgcQIRigARgKMgcQIRigARgKMgcQIRigARgKMgcQIRigARgKMgUQIRirAkj5wAFQywpYkpsBcAJ4AJABAJgBnAGgAeMgqgEENDguNbgBA8gBAPgBAZgCN6ACnyKoAgvCAgYQswEYhQTCAgoQABgDGOoCGI8BwgIKEC4YAxjqAhiPAcICDhAuGIAEGLEDGNEDGMcBwgILEC4YgAQY0QMYxwHCAg4QABiABBixAxiDARiKBcICCBAAGIAEGLEDwgIUEC4YgAQYsQMY0QMYgwEYxwEYigXCAgUQABiABMICERAuGIAEGLEDGIMBGNQCGIoFwgIREC4YgAQYsQMY0QMYgwEYxwHCAg4QLhiABBixAxiDARjUAsICCxAAGIAEGLEDGIMBwgIFEC4YgATCAg4QLhiABBixAxiDARiKBcICBhAAGBYYHsICCBAAGIAEGKIEwgILEAAYgAQYhgMYigXCAgUQIRigAcICBRAAGO8FmAMJ8QXjmVDhNdByZ5IHBDQ4LjegB5eFAw&sclient=gws-wiz
//https://www.geeksforgeeks.org/implementing-hash-table-open-addressing-linear-probing-cpp/
//https://www.tutorialspoint.com/cplusplus-program-to-implement-hash-tables-with-linear-probing
//https://www.google.com/search?q=how+to+display+colors+output++in+C%2B%2B&sca_esv=face10566ce46e9f&sxsrf=ADLYWIJVXJwLkBBSZCka14tnkCREcAI-0Q%3A1733698538352&ei=6iNWZ-mOFcej5NoPgYDHoAY&ved=0ahUKEwjpq5qsopmKAxXHEVkFHQHAEWQQ4dUDCA8&uact=5&oq=how+to+display+colors+output++in+C%2B%2B&gs_lp=Egxnd3Mtd2l6LXNlcnAiJGhvdyB0byBkaXNwbGF5IGNvbG9ycyBvdXRwdXQgIGluIEMrKzIIECEYoAEYwwQyCBAhGKABGMMEMggQIRigARjDBEj6OlD6EViTMXACeAGQAQCYAWOgAYIPqgECMjW4AQPIAQD4AQGYAhOgArcKwgIKEAAYsAMY1gQYR8ICBBAhGArCAggQABiABBiiBMICBRAAGO8FwgIIEAAYogQYiQWYAwCIBgGQBgiSBwIxOaAH_HY&sclient=gws-wiz-serp
//https://gist.github.com/Kielx/2917687bc30f567d45e15a4577772b02