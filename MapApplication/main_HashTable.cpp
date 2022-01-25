#include "HashTable.h"

int main()
{
    KeyedHashTable ht;
    ht.Insert("A", std::vector<int>());
    ht.Insert("X", std::vector<int>());
    ht.Insert("U", std::vector<int>());

    ht.Print();
}