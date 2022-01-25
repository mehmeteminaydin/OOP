#include "HashTable.h"

#include <cassert>
#include <iostream>
#include <iomanip>

const int KeyedHashTable::PRIME_LIST[PRIME_TABLE_COUNT] =
{
     2,    3,   5,   7,  11,  13,  17,  19,
     23,  29,  31,  37,  41,  43,  47,  53,
     59,  61,  67,  71,  73,  79,  83,  89,
     97, 101, 103, 107, 109, 113, 127, 131,
    137, 139, 149, 151, 157, 163, 167, 173,
    179, 181, 191, 193, 197, 199, 211, 223,
    227, 229, 233, 239, 241, 251, 257, 263,
    269, 271, 277, 281, 283, 293, 307, 311,
    313, 317, 331, 337, 347, 349, 353, 359,
    367, 373, 379, 383, 389, 397, 401, 409,
    419, 421, 431, 433, 439, 443, 449, 457,
    461, 463, 467, 479, 487, 491, 499, 503,
    509, 521, 523, 541
};

int KeyedHashTable::Hash(const std::string& key) const
{
    // TODO
    int len = key.size();
    int sum = 0;
    int temp;
    for(int i = 0; i < len; i++){
        temp = key[i]*PRIME_LIST[i];
        sum += temp;
    }
    sum %= tableSize;
    return sum;
}

void KeyedHashTable::ReHash()
{
    // TODO
    int old_table_size = tableSize;
    tableSize = FindNearestLargerPrime(tableSize*2);
    HashData* new_table = new HashData[tableSize];
    int rehashed_index; 
    int prob;
    for(int i = 0 ; i < old_table_size; i++){
        rehashed_index = Hash(table[i].key);
        // if there is no collision
        if(new_table[rehashed_index].key == ""){
            new_table[rehashed_index].key = table[i].key;
            new_table[rehashed_index].intArray = table[i].intArray;
        }
        // apply quadratic probing
        else{
            prob = 1;
            while(new_table[rehashed_index].key != ""){
                rehashed_index += (prob*prob);
                if(new_table[rehashed_index].key == ""){
                    new_table[rehashed_index].key = table[i].key;
                    new_table[rehashed_index].intArray = table[i].intArray;
                    break;
                }
                rehashed_index -= (prob*prob);
                prob++;
            }
        }
    }
    delete[] table;
    table = NULL;
    table = new_table;
}

int KeyedHashTable::FindNearestLargerPrime(int requestedCapacity)
{
    // TODO
    for(int i = 0; i < PRIME_TABLE_COUNT; i++){
        if(PRIME_LIST[i] > requestedCapacity){
            return PRIME_LIST[i];
        }
    }
}

KeyedHashTable::KeyedHashTable()
{
    // TODO
    tableSize = 2;
    occupiedElementCount = 0;
    table = new HashData[tableSize];
}

KeyedHashTable::KeyedHashTable(int requestedCapacity)
{
    // TODO
    tableSize = FindNearestLargerPrime(requestedCapacity);
    occupiedElementCount = 0;
    table = new HashData[tableSize];
}

KeyedHashTable::KeyedHashTable(const KeyedHashTable& other)
{
    // TODO
    tableSize = other.tableSize;
    table = new HashData[tableSize];
    occupiedElementCount = other.occupiedElementCount;
    
    for(int i = 0; i < tableSize; i++){
            table[i].key= other.table[i].key;
            table[i].intArray = other.table[i].intArray;
    }
}

KeyedHashTable& KeyedHashTable::operator=(const KeyedHashTable& other)
{
    // TODO
    // check whether they are the same or not
    if(&other != this){
        // delete this;
        for(int i = 0; i < tableSize; i++){
            // clear strings and data
            table[i].key.clear();
            table[i].intArray.clear();
        }
        // delete table array
        delete[] table;
        table = NULL;
        occupiedElementCount = 0;
        tableSize = 0;
        
        // assign necessary variables;
        tableSize = other.tableSize;
        table = new HashData[tableSize];
        occupiedElementCount = other.occupiedElementCount;
        for(int i = 0; i < tableSize; i++){
            table[i].key= other.table[i].key;
            table[i].intArray = other.table[i].intArray;
        }
    }
    return *this;
}

KeyedHashTable::~KeyedHashTable()
{
    // TODO
    for(int i = 0; i < tableSize; i++){
        // clear strings and data
        table[i].key.clear();
        table[i].intArray.clear();
    }
    // delete table array
    delete[] table;
    table = NULL;
    occupiedElementCount = 0;
    tableSize = 0;
}

bool KeyedHashTable::Insert(const std::string& key,
                            const std::vector<int>& intArray)
{
    // TODO
    int prob = 1;
    // find hashed index
    int new_index = Hash(key);

    // check if there exists already a same key;
    for(int i = 0; i < tableSize; i++){
        if(table[i].key == key){
            return false;
        }
    }

    // if there is no collision
    if(table[new_index].key == ""){
        table[new_index].key = key;
        table[new_index].intArray =intArray;
    }

    // otherwise, apply quadratic probing
    else{
        while(table[new_index].key != ""){
            new_index += (prob*prob);
            if(table[new_index].key == ""){
                table[new_index].key = key;
                table[new_index].intArray = intArray;
                break;
            }
            new_index -= (prob*prob);
            prob++;
        }
    }
    // increment occupiedElementCount;
    occupiedElementCount++;
    if(occupiedElementCount * EXPAND_THRESHOLD >= tableSize){
        ReHash();
    }
    return true;
}

bool KeyedHashTable::Remove(const std::string& key)
{
    // TODO
    for(int i = 0; i < tableSize; i++){
        if(table[i].key == key){
            table[i].key = "";
            table[i].intArray.clear();
            occupiedElementCount--;
            return true;
        }
    }
    return false;
}

void KeyedHashTable::ClearTable()
{
   // TODO
   for(int i = 0; i < tableSize; i++){
        // clear strings and data
        table[i].key = "";
        table[i].intArray.clear();
    }
    occupiedElementCount = 0;
}

bool KeyedHashTable::Find(std::vector<int>& valueOut,
                          const std::string& key) const
{
    // TODO
    for(int i = 0; i < tableSize; i++){
        if(table[i].key == key){
            valueOut = table[i].intArray;
            return true;
        }
    }
    return false;
}

void KeyedHashTable::Print() const
{
    // ============================= //
    // This function is implemented  //
    // Do not edit this function !   //
    // ============================= //
    std::cout << "HT:";
    if(occupiedElementCount == 0)
    {
        std::cout << " Empty";
    }
    std::cout << "\n";
    for(int i = 0; i < tableSize; i++)
    {
        if(table[i].key == "") continue;

        std::cout << "[" << std::setw(3) << i << "] ";
        std::cout << "[" << table[i].key << "] ";
        std::cout << "[";
        for(size_t j = 0; j < table[i].intArray.size(); j++)
        {
            std::cout << table[i].intArray[j];
            if((j + 1) != table[i].intArray.size())
                std::cout << ", ";
        }
        std::cout << "]\n";
    }
    std::cout.flush();
}