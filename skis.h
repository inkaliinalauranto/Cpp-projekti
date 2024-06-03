#ifndef SKIS_H
#define SKIS_H

#include "items.h"

// Luokka perii Items-luokan:
class Skis : public Items
{
private:
    // Privaatin jäsenmuuttujan esittely:
    string categoryName;

public:
    // Oletusrakentajan esittely:
    Skis();

    // Tuhoajan esittely:
    ~Skis();

    // Julkisen jäsenmetodin esittely:
    void listItems();
};

#endif // SKIS_H

