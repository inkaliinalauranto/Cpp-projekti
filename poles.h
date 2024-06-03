#ifndef POLES_H
#define POLES_H

#include "items.h"

// Luokka perii Items-luokan:
class Poles : public Items
{
private:
    // Privaatin jäsenmuuttujan esittely:
    string categoryName;

public:
    // Oletusrakentajan esittely:
    Poles();

    // Tuhoajan esittely:
    ~Poles();

    // Julkisen jäsenmetodin esittely:
    void listItems();
};

#endif // POLES_H

