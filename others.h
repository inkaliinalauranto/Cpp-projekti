#ifndef OTHERS_H
#define OTHERS_H

#include "items.h"

// Luokka perii Items-luokan
class Others : public Items
{
private:
    // Privaatin jäsenmuuttujan esittely:
    string categoryName;

public:
    // Oletusrakentajan esittely:
    Others();

    // Tuhoajan esittely:
    ~Others();

    // Julkisen jäsenmetodin esittely:
    void listItems();
};

#endif // OTHERS_H

