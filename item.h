#ifndef ITEM_H
#define ITEM_H

#include <iostream>

using namespace std;

class Item
{
private:
    // Luokan privaattien jäsenmuuttujien esittely:
    size_t id;
    string name;
    string category;
    bool isRented;

    // Luokan privaatin jäsenmetodin esittely:
    size_t generateId();

public:
    // Julkisen staattisen luokkamuuttujan esittely:
    static size_t count;

    // Julkisen oletusrakentajan esittely:
    Item();

    // Julkisen kuormitetun rakentajan esittely:
    Item(string name, int category, bool isRented);

    // Tuhoajan esittely:
    ~Item();

    // Julkisten getter-metodien esittely:
    size_t getId();
    string getName();
    string getCategory();
    bool getRentalState();
};

#endif // ITEM_H

