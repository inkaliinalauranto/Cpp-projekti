#ifndef SKIBOOTS_H
#define SKIBOOTS_H

#include "items.h"

// Luokka perii Items-luokan:
class SkiBoots : public Items
{
private:
    // Privaatin jäsenmuuttujan esittely:
    string categoryName;

public:
    // Oletusrakentajan esittely:
    SkiBoots();

    // Tuhoajan esittely:
    ~SkiBoots();

    // Julkisen jäsenmetodin esittely:
    void listItems();
};

#endif // SKIBOOTS_H

