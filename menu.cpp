#include "menu.h"

#include <iostream>
#include <string>
#include "items.h"
#include "skis.h"
#include "skiboots.h"
#include "poles.h"
#include "others.h"

using namespace std;


/* Asetetaan oletusrakentajassa jäsenmuuttujille arvot. items-muuttujalle
* asetetaan arvoksi instanssi Items-luokasta ja choice-muuttujan arvoksi
* asetetaan 7, joka myöhemmässä käytössä indikoi ohjelmasta poistumista.
*/
Menu::Menu()
{
    this->items = Items();
    this->choice = 7;
}



// Tuhoaja:
Menu::~Menu() {}


/* Metodi, jota kutsutaan luokan eri jäsenfunktioissa eri tulostusten
* formatointiin katkoviivalla:
*/
void Menu::printEndLine()
{
    cout << "---------------------------\n" << endl;
}


/* Metodi tulostaa virheviestit ja jatko-ohjeen sekä palauttaa virheestä
* kertovan kokonaisluvun 1.
*/
int Menu::handleError()
{
    cout << "Ohjelmassa tapahtui virhetilanne - vääränlainen syöte." << endl;
    cout << "Jos haluat jatkaa, aja ohjelma uudestaan." << endl;
    cout << "Kiitos ohjelman käytöstä!" << endl;
    return 1;
}


/* Luokan privaatti jäsenmetodi, jossa kysytään käyttäjältä se kategoria,
* jonka tavarat halutaan listata, ja toteutetaan kategorian tavaroiden
* listaus. Käyttäjän antama kategoriasta kertova valinta tallenetaan funktion
* alussa esiteltyyn kokonaislukumuotoiseen category-muuttujaan. Jos syöte on 0
* tai pienempi eli joko vääränlainen kokonaisluku tai kokonaan väärää
* tietotyyppiä oleva merkki, poistutaan funktiosta
* handleError-funktiokutsulla, joka palauttaa virheestä kertovan
* kokonaisluvun.
*
* Muussa tapauksessa luodaan instanssit eri kategorioille tehdyistä luokista,
* jotka kaikki perityvyät Items-luokasta. Sitten switch-case-rakenteella
* tarkastetaan, mitä kategoriaa käyttäjän syöte vastaa, minkä jälkeen
* kutsutaan kategoriaa vastaavan luokan listItems-metodia, joka on
* Items-luokalta perityvä ja lapsiluokan ylikirjoittama metodi. Lopuksi
* eri kategorioita kuvaavat instanssit hävitetään.
*/
int Menu::listItemsByCategory()
{
    int category;

    cout << "Valitse listattava kategoria (1 -> sukset, 2 -> sauvat, 3 -> monot, 4 -> muu): ";
    cin >> category;
    cout << endl;

    if (category <= 0)
    {
        return handleError();
    }
    else
    {
        /* Luodaan instanssit Skis-, Poles-, SkiBoots- ja Others-luokista
        * hyödyntämällä dynaamista kekomuistia:
        */
        Skis* skis = new Skis();
        Poles* poles = new Poles();
        SkiBoots* skiBoots = new SkiBoots();
        Others* others = new Others();

        switch (category)
        {
        case 1:
            /* Jos osoitin on sellainen jonka muistipaikassa oleva arvo on
            * jonkin olion tietotyyppiä ja jos osoittimen avulla halutaan
            * viitata muistipaikassa olevan arvon jäsenmetodiin, tehdään se
            * käyttämällä -> merkkiä:
            */
            skis->listItems();
            break;

        case 2:
            poles->listItems();
            break;

        case 3:
            skiBoots->listItems();
            break;

        default:
            others->listItems();
            break;
        }

        /* Vapautetaan dynaaminen muisti, kun instanssit tulevat
        * elinkaariensa päihin kutsumalla instanssien tuhoajia avainsanalla
        * delete:
        */
        delete skis;
        delete poles;
        delete skiBoots;
        delete others;

        return 0;
    }
}


/* Funktiolle välitetään parametrina instanssi Items-luokasta
* pass by reference -tyylillä eli funktiossa parametrin arvoon tehtävät
* muutokset jäävät voimaan parametrina välitetylle muuttujalle funktiossa
* käynnin jälkeen.
*
* Tässä funktiossa kutsutaan ensin items-instanssin jäsenmetodia listItems,
* jolla listataan tiedostoon kirjatut tavarat. Sen jälkeen käyttäjältä
* kysytään vuokrattavan tavaran tunnus, joka tallennetaan itemId-nimiseen
* merkkijonomuuttujaan.
*
* Sitten kutsutaan items-instanssin rentItem-jäsenmetodia ja parametriksi
* välitetään itemId-muuttujan arvo. Funktiokutsun merkkijonomuotoa oleva
* tulos tallennetaan renting-muuttujaan. Jos tulos on jotakin muuta kuin
* tyhjä merkkijono, tulostetaan viesti onnistuneesta vuokraustapahtumasta.
*/
void Menu::borrowItem(Items& items)
{
    items.listItems();

    string itemId;

    cout << "Syötä vuokrattavan tavaran id: ";
    cin >> itemId;
    cout << endl;

    string renting = items.rentItem(itemId);

    if (renting != "")
    {
        cout << renting << " id:llä " << itemId << " vuokrattu onnistuneesti.\n" << endl;
    }

    printEndLine();
}


/* Funktiolle välitetään parametrina instanssi Items-luokasta
* pass by reference -tyylillä. Funktiossa kutsutaan ensin items-instanssin
* jäsenmetodia listItems, jolla listataan tiedostoon kirjatut tavarat.
* Sen jälkeen käyttäjältä kysytään palautettavan tavaran tunnus, joka
* tallennetaan itemId-nimiseen merkkijonomuuttujaan.
*
* Sitten kutsutaan items-instanssin revertItem-jäsenmetodia ja parametriksi
* välitetään itemId-muuttujan arvo. Funktiokutsun merkkijonomuotoa oleva
* tulos tallennetaan reverting-muuttujaan. Jos tulos on jotakin muuta kuin
* tyhjä merkkijono, tulostetaan viesti onnistuneesta palautustapahtumasta.
*/
void Menu::returnItem(Items& items)
{
    items.listItems();

    string itemId;

    cout << "Syötä palautettavan tavaran id: ";
    cin >> itemId;
    cout << endl;

    string reverting = items.revertItem(itemId);

    if (reverting != "")
    {
        cout << reverting << " id:llä " << itemId << " palautettu onnistuneesti.\n" << endl;
    }

    printEndLine();
}


/* Funktiolle välitetään parametrina instanssi Items-luokasta
* pass by reference -tyylillä. Käyttäjältä kysytään lisättävän tavaran nimi,
* joka tallennetaan itemName-merkkijonomuuttujaan. Käyttäjän syötteen
* käsittelyssä hyödynnetään string-kirjaston ignore- ja getline-metodeja,
* jotta käyttäjä pystyy syöttämään tavaran, jonka nimeen sisältyy
* välilyöntejä.
*
* Jos käyttäjän antama syöte on tyhjä merkkijono, kerrotaan käyttäjälle,
* ettei tavaraa voida lisätä ja poistutaan funktiosta paluuarvolla 2.
* Muussa tapauksessa käyttäjältä kysytään kategoria, ja kokonaislukuna
* annettu syöte tallennetaan category-muuttujaan. Jos syöte on 0 tai
* pienempi eli joko vääränlainen kokonaisluku tai kokonaan väärää muotoa,
* poistutaan funktiosta handleError-jäsenmetodikutsulla, joka palauttaa
* virheestä kertovan kokonaisluvun.
*
* Muussa tapauksessa tallennetaan appendableItem-muuttujaan instanssi
* Item-luokasta, ja instanssille syötetään parametreiksi itemName- ja
* category-muuttujiin talletetut arvot sekä totuusarvo false, jolla
* indikoidaan, että lisätty tavara on oletusarvoisesti vapaa. Sen jälkeen
* size_t-tietotyyppiä olevaan muuttujaan appending tallennetaan
* items-parametrin jäsenmetodin appendItem palauttama arvo. appendItem-metodin
* parametrina välitetään appendableItem.

* Palautettu arvo käsitellään ehtolauseella. Jos se on suurempi kuin nolla,
* tulostetaan viesti tavaran onnistuneesta lisäämisestä. Lopuksi poistutaan
* funktiosta paluuarvolla 0.
*/
int Menu::addItem(Items& items)
{
    printEndLine();

    string itemName;
    int category;

    cout << "Syötä tavaran nimi (vältä skandinaavisia kirjaimia): ";
    cin.ignore();
    getline(cin, itemName);
    cout << endl;

    if (itemName == "")
    {
        cout << "Tavaraa ei voida lisätä, koska sitä ei ole nimetty.\n" << endl;
        printEndLine();
        return 2;
    }

    cout << "Syötä tavaran kategoria (1 -> sukset, 2 -> sauvat, 3 -> monot, 4 -> muu): ";
    cin >> category;
    cout << endl;

    if (category <= 0)
    {
        return handleError();
    }
    else
    {
        Item appendableItem = Item(itemName, category, false);
        size_t appending = items.appendItem(appendableItem);
        if (appending > 0)
        {
            cout << itemName << " lisätty järjestelmään onnistuneesti id:llä " << appending << "\n" << endl;
        }
        printEndLine();
        return 0;
    }
}


/* Funktiolle välitetään parametrina instanssi Items-luokasta
* pass by reference -tyylillä. Funktiossa kutsutaan ensin items-instanssin
* jäsenmetodia listItems, jolla listataan tiedostoon kirjatut tavarat. Sitten
* käyttäjältä kysytään lisättävän tavaran tunnus, joka tallennetaan
* itemId-merkkijonomuuttujaan.
*
* Sen jälkeen kutsutaan items-instanssin removeItem-jäsenmetodia ja
* parametriksi välitetään itemId-muuttujan arvo. Funktiokutsun
* merkkijonomuotoa oleva tulos tallennetaan removing-muuttujaan. Jos tulos
* on jotakin muuta kuin tyhjä merkkijono, tulostetaan viesti onnistuneesta
* poistamistapahtumasta.
*/
void Menu::deleteItem(Items& items)
{
    items.listItems();

    string itemId;

    cout << "Syötä poistettavan tavaran id: ";
    cin >> itemId;
    cout << endl;

    string removing = items.removeItem(itemId);

    if (removing != "")
    {
        cout << removing << " poistettu järjestelmästä onnistuneesti id:llä " << itemId << "\n" << endl;
    }

    printEndLine();
}


/* Funktio, joka käynnistää hiihtotarvikkeiden hallinnointiohjelman.
* Tervehtemistulosteen jälkeen siirrytään while-silmukkaan, joka
* pyörii loppumattomasti (true), kunnes käyttäjä valitsee ehdon, jolla
* kutsutaan break-avainsanaa.
*
* Jokaisella silmukan kierroksella tulostetaan valikko ja pyydetään
* käyttäjää syöttämään valinta. Valinta tallennetaan choice-jäsenmuuttujaan,
* jonka arvoa vertaillaan lukuihin 1-7. Jos valinta täsmää johonkin näistä
* luvuista, toteutetaan ko. ehtoon liittyvät toiminnot tai funktiokutsu.
*
* Muussa tapauksessa palautetaan funktio, joka käsittelee virheellisen
* syötteen ja paluttaa virheestä kertovan kokonaisluvun lopettaen ohjelman.
* Jos ohjelma lopetetaan käyttäjän valinnasta, silmukasta poistumisen jälkeen
* palautetaan kokonaisluku 0 merkkinä ohjelman onnistuneesta ajosta.
*/
int Menu::start()
{
    cout << "Tervetuloa hiihtotarvikkeiden ylläpitojärjestelmään!\n" << endl;

    while (true)
    {
        cout << "Mitä haluat tehdä? " << endl;
        cout << "1 -> Listaa tavarat" << endl;
        cout << "2 -> Listaa yksittäisen kategorian tavarat" << endl;
        cout << "3 -> Vuokraa tavara" << endl;
        cout << "4 -> Palauta tavara" << endl;
        cout << "5 -> Lisää tavara" << endl;
        cout << "6 -> Poista tavara" << endl;
        cout << "7 -> Poistu järjestelmästä\n" << endl;

        cout << "Syötä valintasi: ";
        cin >> this->choice;
        cout << endl;

        if (this->choice == 1)
        {
            // Kutsutaan metodia, joka listaa tavarat:
            this->items.listItems();
        }
        else if (this->choice == 2)
        {
            int categoryListing = listItemsByCategory();
            if (categoryListing != 0)
            {
                return categoryListing;
            }

        }
        else if (this->choice == 3)
        {
            /* Kutsutaan metodia, joka vaihtaa tiedostosta löytyvän
            * vuokrauksen tilasta kertovan arvon arvosta 0 arvoon 1.
            * Funktiossa selvitetään edeltävästi tavaran tunnus, jotta
            * statuksen vaihto voidaan toteuttaa.
            */
            borrowItem(this->items);
        }
        else if (this->choice == 4)
        {
            /* Kutsutaan metodia, joka vaihtaa tiedostosta löytyvän
            * vuokrauksen tilasta kertovan arvon arvosta 1 arvoon 0.
            * Funktiossa selvitetään edeltävästi tavaran tunnus, jotta
            * statuksen vaihto voidaan toteuttaa.
            */
            returnItem(this->items);
        }
        else if (this->choice == 5)
        {
            /* Tallennetaan muuttujaan tavaran lisäävän funktion palauttama
            * arvo, joka voi olla 0-2.
            */
            int additionEvent = addItem(this->items);

            /* Jos addItem-metodin palauttama arvo on 1, poistutaan ohjelmasta
            * virheestä kertovalla kokonaislukuarvolla.
            */
            if (additionEvent == 1)
            {
                return 1;
            }
            /* Jos metodin palauttama arvo on 0 tai 2, jatketaan silmukassa
            * seuraavaalle iteraatiokierrokselle.
            */
            else
            {
                continue;
            }
        }
        else if (this->choice == 6)
        {
            /* Kutsutaan metodia, jolle syötetään parametriksi
            * items-jäsenmuuttujaan talletettu instanssi Items-luokasta.
            * Metodissa kysytään poistettavan tavaran id, jonka perusteella
            * tavara poistetaan tiedostosta.
            */
            deleteItem(this->items);
        }
        else if (this->choice == 7)
        {
            printEndLine();

            cout << "Kiitos ohjelman käytöstä!" << endl;

            // Poistutaan silmukasta break-avainsanan avulla:
            break;
        }
        else
        {
            /* Palautetaan handleError-metodin palauttama kokonaislukuarvo,
            * ja poistutaan ohjelmasta.
            */
            return handleError();
        }
    }

    return 0;
}
