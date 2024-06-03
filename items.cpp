#include "items.h"

#include "item.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;


/* Määritellään oletusrakentajassa fileName-jäsenmuuttujan arvoksi
* merkkijonomuotoinen tiedostonimi items_file.txt. Tallennetaan
* itemsFileForReading-muuttujaan instanssi ifstream-luokasta, jolle
* välitetään parametrina fileName-muuttujaan tallennettu merkkijono.
*
* Ehtolausella tarkistetaan, onko itemsFileForReading-muuttuja luettavissa.
* Jos ei, tiedostoa ei ole olemassa, jolloin asetetaan demotarkoituksessa
* itsemääritellyt arvot items-taulukon kullekin alkiolle. Alkiot luetaan
* fileName-muuttujan arvon nimiseen tekstitiedostoon silmukassa, jos
* kirjoittaminen tiedostoon onnistuu. Muussa tapauksessa tulostetaan viesti
* virhetilanteesta.
*
* Lopuksi kutsutaan sekä tiedostoon kirjoittamiseen liittyvän
* ofstream-instanssin että tiedostosta lukemiseen liittyvän
* ifstream-instanssin close-metodeja.
*/
Items::Items()
{
    this->fileName = "items_file.txt";

    // Avataan lukuyhteys:
    ifstream fileReading = ifstream(this->fileName);

    /* Jos items_file.txt-tiedostoa ei vielä ole olemassa eli jos ohjelma
    * ajetaan ensimmäisen kerran, luodaan tiedosto ja lisätään siihen
    * silmukassa items-taulukon alkioiden tiedot.
    */
    if (!fileReading.good())
    {
        this->items[0] = Item("Rossignol Xium", 1, false);
        this->items[1] = Item("Leki HRC", 2, false);
        this->items[2] = Item("Ficher Speedmax Skate", 3, false);

        // Avataan kirjoitusyhteys:
        ofstream fileWriting = ofstream(this->fileName);

        if (fileWriting.fail())
        {
            cout << "Ohjelmassa tapahtui virhetilanne - tiedostoon ei voi kirjoittaa.\n" << endl;
        }
        else
        {
            for (int i = 0; i < 3; i++)
            {
                int id = i + 1;
                fileWriting
                    << items[i].getName() << "\n"
                    << items[i].getId() << "\n"
                    << items[i].getCategory() << "\n"
                    << items[i].getRentalState() << "\n";
            }
        }


        // Suljetaan kirjoitusyhteys:
        fileWriting.close();
    }

    // Suljetaan lukuyhteys:
    fileReading.close();
}


// Tuhoaja:
Items::~Items() {}


/* Määritellään privaatti jäsenmetodi, joka ottaa parametrina
* merkkijonoalkioista koostuvan vector-listan. Tässä funktiossa parametrina
* välitetystä muuttujasta tehdään kopio, eivätkä funktion parametriin tekemät
* muutokset tapahdu itse muuttujalle.
*
* Alustetaan kokonaislukumuuttuja size arvoon 0. Jos parametrinä välitetyssä
* muuttujassa on alkioita eli jos se ei ole tyhjä, asetetaan size-muuttujan
* arvoksi alkioiden määrä hyödyntämällä parametrin size-jäsenmetodia. Koska
* metodi palauttaa size_t-tietotyyppiä olevan arvon, tehdään sille type
* castaus. Lopuksi palautetaan size-muutujan arvo.
*/
int Items::setSize(vector<string> rows)
{
    int size = 0;

    if (!rows.empty())
    {
        size = (int)rows.size();
    }

    return size;
}


/* Määritellään privaatti jäsenmetodi, joka ottaa parametreina
* merkkijonoalkioista koostuvan vector-listan pass by reference -tyylillä sekä
* vakioarvoisina tunnuksesta kertovan merkkijonon, tilanteesta kertovan
* totuusarvon ja virheestä kertovan merkkijonon.
*
* Määritetään ensin funktiossa useita apumuuttujia alustusarvoilla. Sen
* jälkeen tallennetaan muuttujaan fileWriting ofstream-luokan instanssi,
* jolle parametriksi annetaan fileName-jäsenmuuttujan arvo. Jos muuttujan
* jäsenmetodi fail palauttaa arvon true eli tiedostoon kirjoittaminen ei
* onnistu, tulostetaan siitä viesti.
*
* Jos taas parametrina välitetyn vector-listan alkioiden lukumäärä on
* neljä tai suurempi, eli tiedostossa on rivejä, ja jos lukumäärän
* jakojäännös on 0 eli rivit on kirjoitettu tiedostoon oikealla tavalla,
* iteroidaan kaikki vuokrauksen tilasta kertova rivit läpi. Jos parametrina
* välitetyn tunnuksen arvo vastaa iteraatiokierroksen arvoa, asetetaan
* arvot myös muihin apumuuttujiin ja poistutaan silmukasta.
*
* Sen jälkeen iteroidaan parametrina välitetyn rows-muuttujan kaikki alkiot
* läpi. Jos iteraation indeksi vastaa apumuuttujaan indexOfValueToBeChanged
* tallennettua indeksiä ja jos indeksiä vastaavan alkion arvo ei ole sama kuin
* parametrinä välitetyn propertyState-muttujan arvo eli vuokraustilaa ei
* koiteta muuttaa jo olemassa olevaksi, asetetaan arvoksi
* propertyState-parametrissä välitetty totuusarvo merkkijonoksi muutettuna.
* Muussa tapauksessa isAlreadyInAction-apumuuttujan arvo vaihdetaan todeksi
* ja tulostetaan parametrina saatu virheviesti.
*
* Jos sen sijaan indeksi vastaa indexOfItemName-apumuuttujaan talletettua
* indeksiä, annetaan itemName-apumuuttujan arvoksi alkion arvo
* rows-vectorissa ko. indeksin kohdalta. Silmukan lopuksi kirjoitetaan
* iteroitava rivi fileWriting-muuttujaan.
*
* Uloimmassa else-haarassa tulostetaan virheviesti, ja lopuksi kutsutaan
* fileWriting-muuttujaan talletetun instanssin close-metodia. Sen jälkeen
* tarkastetaan, onko isIdInFile-apumuuttujan arvo muuttunut funktion aikana
* todeksi. Jos ei, tulostetaan siitä tieto ja poistutaan funktiosta tyhjän
* merkkijonon muotoa olevalla paluuarvolla. Jos isAlreadyInAction-muuttujan
* arvo on funktiossa muutettu todeksi, poistutaan funktiosta niin ikään
* tyhjällä merkkijonolla. Muussa tapauksessa poistutaan funktiossa
* itemName-apumuuttujaan talletetuulla arvolla.
*/
string Items::changeRentalState(vector<string>& rows, const string id, const bool propertyState, const string emsg)
{
    // Haetaan rows-vectorissa olevien alkioiden lukumäärä:
    int rowsSize = setSize(rows);
    /* Alustetaan tavaran nimen osoittavan indeksin arvoksi indeksi, jota ei
    * varmasti löydy rows-muuttujasta antamalla arvoksi alkioiden lukumäärä.
    * rows-muuttujassa viimeisen alkion indeksi on aina lukumäärä - 1.
    */
    int indexOfItemName = rowsSize;
    /* Alustetaan myös muutettavan arvon osoittavan indeksin arvoksi indeksi,
    * jota ei varmasti löydy rows-muuttujasta.
    */
    int indexOfValueToBeChanged = rowsSize;
    bool isIdInFile = false;
    bool isAlreadyInAction = false;
    string itemName = "";

    ofstream fileWriting = ofstream(this->fileName);

    if (fileWriting.fail())
    {
        cout << "Ohjelmassa tapahtui virhetilanne - tiedostoon ei voi kirjoittaa.\n" << endl;
    }
    else if (rows.size() >= 4 && rows.size() % 4 == 0)
    {
        /* Ensimmäisen tavaran tunnuksesta kertova arvo on rivillä 2 eli
        * rows-muuttujan indeksissä 1. Seuraavan tavaran vastaava arvo on
        * edellisestä neljän alkion päässä.
        */
        for (int i = 1; i < rows.size(); i += 4)
        {
            if (rows[i] == id)
            {
                // Tavaran nimi on tunnuksen indeksiä edeltävässä indeksissä:
                indexOfItemName = i - 1;
                /* Tavaran vuokrauksesta kertovan tilan indeksi on kahden
                indeksin päässä tunnuksen indeksistä:
                */
                indexOfValueToBeChanged = i + 2;
                /* Jos parametrinä välitetty id löytyy, vaihdetaan siitä
                kertovan totuusarvomuuttujan arvo todeksi:
                */
                isIdInFile = true;
                break;
            }
        }

        for (int i = 0; i < rows.size(); i++)
        {
            if (i == indexOfValueToBeChanged)
            {
                /* Hyödynnetään vertailussa string-kirjaston
                string to integer -metodia, ja lisäksi type castataan
                kokonaisluvuksi muutettu arvo totuusarvoksi:
                */
                if ((bool)stoi(rows[i]) == propertyState)
                {
                    isAlreadyInAction = true;
                    cout << emsg << endl;
                }
                else
                {
                    rows[i] = to_string(propertyState);
                }
            }
            else if (i == indexOfItemName)
            {
                itemName = rows[indexOfItemName];
            }
            fileWriting << rows[i] << endl;
        }
    }
    else
    {
        cout << "Tiedosto on tyhjä tai siinä olevat tiedot ovat puutteellisia.\n" << endl;
    }

    fileWriting.close();

    if (!isIdInFile)
    {
        cout << "Tavaraa syöttämälläsi tunnuksella ei löydy järjestelmästä.\n" << endl;
        return "";
    }
    else if (isAlreadyInAction)
    {
        return "";
    }
    else
    {
        return itemName;
    }
}


/* Määritellään privaatti jäsenmetodi, joka ottaa vastaan kategorian nimeä
* indikoivan vakiomerkkijonon ja merkkijonoalkioista koostuvan
* vector-listan pass by reference -tyylillä. Metodissa määritellään
* apumuuttuja index, jonka avulla ja arvoa silmukassa muuttamalla
* määritellään, minkälainen teksti tulostetaan ennen iteraatiokierroksella
* käsiteltävän alkion arvon tulostamista. For-silmukassa käydään siis läpi
* parametrina välitetyn vectorin alkiot, jotka switch-rakenteen ja
* index-apumuuttujan avulla tulostetaan formatoituun muotoon.
*/
void Items::printByCategory(const string categoryName, vector<string>& categoryRows)
{
    int index = 0;

    cout << "-- Tavarat kategoriassa " << categoryName << " --\n " << endl;
    for (int i = 0; i < categoryRows.size(); i++)
    {
        switch (index)
        {
        case 0:
            cout << "Tavaran nimi: " << categoryRows[i] << endl;
            break;

        case 1:
            cout << "Tavaran id: " << categoryRows[i] << endl;
            break;

        case 2:
            cout << "Tavaran kategoria: " << categoryRows[i] << endl;
            break;

        case 3:
            cout << "Tavaran vuokraustilanne: ";
            if (stoi(categoryRows[i]) == 1)
            {
                cout << "varattu\n" << endl;
            }
            else
            {
                cout << "vapaa\n" << endl;
            }
            index = -1;
            break;
        }
        index++;
    }

    cout << "---------------------------------\n" << endl;
}


/* Funktiolle välitetään parametrina merkkijonoalkioista koostuva dynaaminen
* vector-lista pass by reference -tyylillä eli funktiossa parametrin arvoon
* tehtävät muutokset jäävät voimaan parametrina välitetylle muuttujalle
* funktiossa käynnin jälkeen. Funktiossa ei siis käsitellä parametrina
* välitetystä muuttujasta tehtyä kopiota vaan muuttujaa itse.
*
* Tässä funktiossa esitellään merkkijonomuotoa oleva muuttuja row ja
* alustetaan fileReading-niminen instanssi ifstream-luokasta. Instanssille
* välitetään parametriksi fileName-jäsenmuuttujan arvo. Jos tiedoston
* lukeminen onnistuu eli fileReading-instanssin good-jäsenmetodi palauttaa
* arvon true, luetaan while-silmukassa tiedoston rivit parametrina välitetyn
* rows-vectorin alkioiksi.
*
* Muussa tapauksessa tulostetaan virheilmoitus. Lopuksi kutsutaan
* fileReading-muuttujaan talletetun ifstream-instanssin close-metodia.
*/
void Items::readFileToRows(vector<string>& rows)
{
    string row;
    ifstream fileReading = ifstream(this->fileName);

    if (fileReading.good())
    {
        while (getline(fileReading, row))
        {
            rows.push_back(row);
        }
    }
    else
    {
        cout << "Ohjelmassa tapahtui virhetilanne: tiedostoa ei ole olemassa.\n" << endl;
    }

    fileReading.close();
}


/* Määritellään periytyvä jäsenmetodi, joka ottaa parametreina vastaan
* kaksi eri merkkijonoalkioista koostuvaa vectoria pass by reference -tyylillä
* sekä kategorian nimeä kuvaavan vakiomerkkijonon. Jos parametrinä välitetyn
* rows-vektorin alkioiden lukumäärä on neljä tai suurempi ja jos lukumäärän
* jakojäännös on 0 eli rivit on lisätty vectoriin oikealla logiikalla,
* iteroidaan kaikki kategorian kertovat rivit läpi.
*
* Jos parametrina välitetyn kategorian nimi vastaa iteraatiokierroksen alkion
* arvoa, lisätään parametrina välitettyyn categoryRows-vectoriin tiedot siitä
* tavarasetistä, jonka kategoriakohta on kyseessä. Sitten kutsutaan metodia,
* jossa categoryRows-vectoriin tallennetut tiedot tulostetaan formatoidussa
* muodossa ja jolle sen vuoksi välitetään parametrit categoryName ja
* categoryRows.

* Jos rows-parametrin alkioiden lukumäärä ei vastaa ensimmäisiin ehtoihin,
* siirrytään else-haaraan, jossa käyttäjälle tulostetaan virheviesti.
*/
void Items::filterByCategory(vector<string>& rows, const string categoryName, vector<string>& categoryRows)
{
    if (rows.size() >= 4 && rows.size() % 4 == 0)
    {
        /* Ensimmäisen tavaran kategorian kertova arvo on kolmannessa alkiossa
        * eli indeksissä 2. Seuraavan tavaran vastaava arvo on edellisestä
        * neljän alkion päässä.
        */
        for (int i = 2; i < rows.size(); i += 4)
        {
            if (rows[i] == categoryName)
            {
                /* Tavaran nimen kertova alkio löytyy kategorian kertovan
                 * alkion edellistä alkiota edeltävästä alkiosta:
                 */
                string name = rows[i - 2];
                categoryRows.push_back(name);

                /* Tavaran tunnuksen kertova alkio löytyy kategorian kertovaa
                 * alkiota edeltävästä alkiosta:
                 */
                string id = rows[i - 1];
                categoryRows.push_back(id);

                string category1 = rows[i];
                categoryRows.push_back(category1);

                /* Tavaran varaustilanteen kertova alkio löytyy kategorian
                 * kertovaa alkiota seuraavasta alkiosta:
                 */
                string isRented = rows[i + 1];
                categoryRows.push_back(isRented);
            }
        }

        printByCategory(categoryName, categoryRows);
    }
    else
    {
        cout << "Tiedosto on tyhjä tai siinä olevat tiedot ovat puutteellisia.\n" << endl;
    }
}


/* Luokan julkinen jäsenmetodi, jonka aluksi alustetaan useampia apumuuttujia.
* fileReading-muuttujaan alustetaan luokasta ifstream instanssi, jolle
* välitetään parametriksi fileName-jäsenmuuttuja. Sen jälkeen while-silmukassa
* luetaan funktion alussa alustettuun row-merkkijonoapumuuttujaan
* fileReading-muuttujaan määritellyn tiedoston rivi iteraatiokierroksen
* mukaan. Switch-rakenteella valitaan tulostettava teksti, jonka perään
* tulostetaan row-muuttujaan kyseisellä iteraatiolla tallennettu rivi.
* Switch-rakenteessa vertailtavaa index-apumuuttujan arvoa kasvatetaan
* while-silmukan eri iteraatioilla, kunnes sen arvo on 3.
*
* Indeksin arvon ollessa kolme, vertaillaan row-muuttujaan talletettua arvoa.
* Arvon mukaan tulostetaan tavaran vuokraustilanteeksi joko varattu tai vapaa.
* Sitten index-muuttujan arvo "nollataan" arvoon -1. Yksi neljän iteraation
* yhdistelmä vastaa yhden tavaran tietojen läpikäyntiä. Lisäksi käytössä on
* apumuuttuja itemOrdinary, jota kasvatetaan joka neljännen rivin eli jokaisen
* tavaratietosetin välein. Muuttuja kertoo listatun tavaran järjestysnumeron,
* joka tulostetaan. Lopuksi kutsutaan fileReading-muuttujaan talletun
* instanssin close-metodia.
*/
void Items::listItems()
{
    cout << "----- Kaikki tavarat ------\n" << endl;

    string row;

    ifstream fileReading = ifstream(this->fileName);

    int index = 0;
    int itemOrdinary = 1;

    while (getline(fileReading, row))
    {
        switch (index)
        {
        case 0:
            cout << itemOrdinary << ". --\n" << "Tavaran nimi: " << row << endl;
            itemOrdinary++;
            break;

        case 1:
            cout << "Tavaran id: " << row << endl;
            break;

        case 2:
            cout << "Tavaran kategoria: " << row << endl;
            break;

        case 3:
            cout << "Tavaran vuokraustilanne: ";
            if (row[0] == '1')
            {
                cout << "varattu\n" << endl;
            }
            else
            {
                cout << "vapaa\n" << endl;
            }
            index = -1;
            break;
        }
        index++;
    }

    fileReading.close();

    cout << "---------------------------\n" << endl;
}


/* Luokan julkinen jäsenmetodi, joka ottaa vastaan merkkijonomuotoa olevan
* vakioparametrin. Funktion alussa esitellään apumuuttuja rows, joka
* välitetään parametrina readFileToRows-funktiokutsuun. Sen jälkeen alustetaan
* totuusarvoapumuuttuja propertyState arvoon true, koska vuokratessa halutaan
* vaihtaa tavaran isRented-arvo epätodesta todeksi.
*
* Alustetaan myös errorMessage-niminen apumuuttuja virheviestin kertovalla
* merkkijonolla. Palautetaan funktiosta arvo, joka saadaan kutsumalla
* changeRentalState-jäsenmetodia. Parametreiksi funktiokutsuun asetetaan
* tämän funktion id-vakioparametri sekä apumuuttujien arvot. Paluuarvona
* changeRentalState-funktiosta saadaan merkkijono.
*/
string Items::rentItem(const string id)
{
    vector<string> rows;

    /* Luetaan tiedoston sisältö rows-muuttujaan hyödyntämällä
    * pass by reference -tekniikkaa:
    */
    readFileToRows(rows);

    bool propertyState = true;
    string errorMessage = "Tavara on jo varattu, ei vuokrattavissa.\n";

    // Varsinainen varaaminen:
    return changeRentalState(rows, id, propertyState, errorMessage);
}


/* Luokan julkinen jäsenmetodi, joka ottaa vastaan merkkijonomuotoa olevan
* vakioparametrin. Funktion alussa esitellään apumuuttuja rows, joka
* välitetään parametrina readFileToRows-funktiokutsuun. Sen jälkeen alustetaan
* totuusarvoapumuuttuja propertyState arvoon false, koska palautettaessa
* halutaan vaihtaa tavaran isRented-arvo todesta epätodeksi.
*
* Alustetaan myös errorMessage-niminen apumuuttuja virheviestin kertovalla
* merkkijonolla. Palautetaan funktiosta arvo, joka saadaan kutsumalla
* changeRentalState-jäsenmetodia. Parametreiksi funktiokutsuun asetetaan
* tämän funktion id-vakioparametri sekä apumuuttujien arvot. Paluuarvona
* changeRentalState-funktiosta saadaan merkkijono.
*/
string Items::revertItem(string id)
{
    vector<string> rows;

    /* Luetaan tiedoston sisältö rows-muuttujaan hyödyntämällä
    * pass by reference -tekniikkaa:
    */
    readFileToRows(rows);

    bool propertyState = false;
    string errorMessage = "Tavara on jo palautettu.\n";

    // Varsinainen palauttaminen:
    return changeRentalState(rows, id, propertyState, errorMessage);
}


/* Luokan julkinen jäsenmetodi, joka ottaa vastaan Item-luokan muotoa
* olevan parametrin. itemsFile-apumuuttujaan tallennetaan luokasta ofstream
* luotu instanssi, jota kuormitetaan tämän luokan fileName-jäsenmuuttujalla
* sekä ios_base-nimiavaruuteen kuuluvilla app- ja out-parametreillä.
* Parametrin ios_base::app | ios_base::out avulla tiedoston loppuun pystytään
* lisäämään tekstiä.
*
* Jos fileReading-muuttujaan talletetun instanssin fail-metodin palauttama
* arvo ei ole tosi, lisätään tiedostoon neljä uutta riviä eli uuden tavaran
* tiedot, jotka saadaan välitetyn item-parametrin getter-metodeilla. Lisäksi
* kutsutaan fileReading-muuttujassa olevan instanssin close-metodia ja
* poistutaan funktiosta siten, että paluuarvoksi asetetaan itemin tunnus.
* Muussa tapauksessa tulostetaan virheviesti ja palautetaan -1 merkkinä siitä,
* ettei tavaran lisääminen onnistu.
*/
size_t Items::appendItem(Item item)
{
    /* Lisätään items_file.txt-tiedoston loppuun tekstiä antamalla
    * ofstream-instanssille toiseksi parametriksi
    * ios_base::app | ios_base::out. Tekstiksi lisätään uuden tavaran
    * tiedot, jotka saadaan välitetyn item-parametrin getter-metodeilla.
    */
    ofstream fileReading = ofstream(fileName, ios_base::app | ios_base::out);

    if (fileReading.fail())
    {
        cout << "Ohjelmassa tapahtui virhetilanne - tiedostoon ei voi kirjoittaa.\n" << endl;
        return -1;
    }
    else
    {
        fileReading
            << item.getName() << "\n"
            << item.getId() << "\n"
            << item.getCategory() << "\n"
            << item.getRentalState() << "\n";

        fileReading.close();

        return item.getId();
    }
}


/* Määritellään julkinen jäsenmetodi, joka ottaa vastaan merkkijonomuotoa
* olevan tavaran tunnusta indikoivan vakioparametrin. Funktion alussa
* esitellään apumuuttuja rows, joka välitetään parametrina
* readFileToRows-funktiokutsuun. Sen jälkeen alustetaan useita apumuuttujia
* alustusarvoilla.
*
* Sen jälkeen tallennetaan muuttujaan fileWriting ofstream-luokan instanssi,
* jolle parametriksi annetaan fileName-jäsenmuuttujan arvo. Jos muuttujan
* jäsenmetodi fail palauttaa arvon true eli tiedostoon kirjoittaminen ei
* onnistu, tulostetaan siitä viesti.
*
* Jos taas parametrina välitetyn vector-listan alkioiden lukumäärä on
* neljä tai suurempi, eli tiedostossa on rivejä ja jos lukumäärän
* jakojäännös on 0 eli rivit on kirjoitettu tiedostoon oikealla tavalla,
* iteroidaan kaikki tunnuksen kertovat rivit läpi. Jos parametrina välitetyn
* tunnuksen arvo vastaa iteraatiokierroksen arvoa, asetetaan arvot
* tilanteeseen liittyviin apumuuttujiin ja poistutaan silmukasta.
*
* Sen jälkeen iteroidaan parametrina välitetyn rows-muuttujan kaikki alkiot
* läpi. Kirjoitetaan iteroitava alkio tiedostoon, jos iteraatiokierros ei
* vastaa yhteenkään edellisessä silmukassa päivitetyistä muuttujien arvoista.
* Jos iteraatiokierroksen numero sen sijaan vastaa aiemmassa silmukassa
* firstRemovableIndex-apumuuttujaan talletettua indeksiä, annetaan
* itemName-apumuuttujan arvoksi alkion arvo rows-vectorissa ko. indeksin
* kohdalta.
*
* Uloimmassa else-haarassa tulostetaan virheviesti, ja lopuksi kutsutaan
* fileWriting-muuttujaan talletetun instanssin close-metodia. Sen jälkeen
* tarkastetaan, onko isIdInFile-apumuuttujan arvo muuttunut funktion aikana
* todeksi. Jos ei, tulostetaan siitä tieto ja poistutaan funktiosta tyhjän
* merkkijonon muotoa olevalla paluuarvolla. Muussa tapauksessa poistutaan
* funktiossa itemName-apumuuttujaan talletetulla arvolla.
*/
string Items::removeItem(const string id)
{
    vector<string> rows;

    // Välitetään rows-muuttuja pass by reference -tekniikalla:
    readFileToRows(rows);

    // Haetaan rows-vectorissa olevien alkioiden lukumäärä:
    int rowsSize = setSize(rows);
    string itemName = "";
    /* Alustetaan ensimmäisen poistettavan indeksin arvoksi indeksi, jota ei
    * varmasti löydy rows-muuttujasta asettamalla
    * firstRemovableIndex-muuttujan arvoksi alkioiden lukumäärä.
    * rows-muuttujassa viimeisen alkion indeksi on aina lukumäärä - 1.
    */
    int firstRemovableIndex = rowsSize;
    /* Alustetaan myös kolmea muuta poistettavaa arvoa osoittavan indeksin
    * arvoiksi indeksit, joita ei varmasti löydy rows-muuttujasta.
    */
    int secondRemovableIndex = rowsSize + 1;
    int thirdRemovableIndex = rowsSize + 2;
    int fourthRemovableIndex = rowsSize + 3;
    bool isIdInFile = false;

    ofstream fileWriting = ofstream(this->fileName);

    if (fileWriting.fail())
    {
        cout << "Ohjelmassa tapahtui virhetilanne - tiedostoon ei voi kirjoittaa.\n" << endl;
    }
    else if (rows.size() >= 4 && rows.size() % 4 == 0)
    {
        for (int i = 1; i < rows.size(); i += 4)
        {
            if (rows[i] == id)
            {
                firstRemovableIndex = i - 1;
                secondRemovableIndex = i;
                thirdRemovableIndex = i + 1;
                fourthRemovableIndex = i + 2;
                isIdInFile = true;
                break;
            }
        }

        for (int i = 0; i < rows.size(); i++)
        {
            if (i != firstRemovableIndex && i != secondRemovableIndex && i != thirdRemovableIndex && i != fourthRemovableIndex)
            {
                fileWriting << rows[i] << endl;
            }
            else if (i == firstRemovableIndex)
            {
                itemName = rows[firstRemovableIndex];
            }
        }
    }
    else
    {
        cout << "Tiedosto on tyhjä tai siinä olevat tiedot ovat puutteellisia.\n" << endl;
    }

    fileWriting.close();

    if (!isIdInFile)
    {
        cout << "Tavaraa syöttämälläsi tunnuksella ei löydy järjestelmästä.\n" << endl;
        return "";
    }
    else
    {
        return itemName;
    }
}
