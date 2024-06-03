#include "others.h"

#include "items.h"


/* Oletusrakentaja, joka kutsuu isäntäluokan oletusrakentajaa. Luokan
* rakentajassa categoryName-jäsenmuuttujalle asetetaan arvoksi luokan
* nimi eli "muu".
*/
Others::Others() : Items()
{
    this->categoryName = "muu";
}


// Tuhoaja:
Others::~Others() {}


/* Isäntäluokalta perittävä jäsenmetodi, jonka toteutus ylikirjoitetaan
* tässä luokan käyttötarkoitusta palvelevaksi. Metodin ylikirjoitettavassa
* versiossa esitetään kaksi string-alkioista koostuvaa vectoria. Sen
* jälkeen kutsutaan isäntäluokan readFileToRows-metodia, jolle parametrina
* välitetään ensimmäinen vector-muuttuja. Metodissa rows-muuttujaan luetaan
* items_file.txt-tiedoston rivit.
*
* Sen jälkeen kutsutaan isäntäluokan filterByCategory-metodia, jossa haetaan
* ja tulostetaan kategorian tavarat rows-muuttujaan talletetuista alkioista.
* Metodille välitetään siis parametreiksi molemmat vector-apumuuttujat sekä
* luokan jäsenmuuttuja categoryName.
*/
void Others::listItems()
{
    vector<string> rows;
    vector<string> categoryRows;

    Items::readFileToRows(rows);

    Items::filterByCategory(rows, this->categoryName, categoryRows);
}
