#include "item.h"

#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <cstring>

using namespace std;

/* Staattisen luokkamuuttujan määrittely. Muuttujan arvoa kasvatetaan
* luokan rakentajissa, minkä ansiosta muuttujassa on tallessa arvo, joka
* kertoo luokasta luotujen instanssien määrän.
*/
size_t Item::count = 0;


/* Oletusrakentaja, jossa asetetaan jäsenmuuttujille oletusarvot ja
* päivitetään staattisen luokkamuuttujan lukema. Lukema päivitetään heti
* rakentajan alussa, koska ajantasaista lukemaa tarvitaan
* generateId-metodissa.
*/
Item::Item()
{
    count++;
    this->id = generateId();
    this->name = "ei nimeä";
    this->category = "muu";
    this->isRented = false;
}


/* Kuormitettu rakentaja, jossa päivitetään staattisen luokkamuuttujan
* lukema ja generoidaan instanssille tunnus. Muiden jäsenmuuttujien arvoiksi
* asetetaan parametrien välityksellä saatavat arvot. category-jäsenmuuttujan
* kohdalla käytetään switch-case-rakennetta, jonka ehtoihin verraten
* category-parametrina saadun kokonaisluvun perusteella asetetaan arvo luokan
* category-jäsenmuuttujalle.
*/
Item::Item(string name, int category, bool isRented)
{
    count++;
    this->id = generateId();
    this->name = name;

    switch (category)
    {
    case 1:
        this->category = "sukset";
        break;

    case 2:
        this->category = "sauvat";
        break;

    case 3:
        this->category = "monot";
        break;

    default:
        this->category = "muu";
        break;
    }

    this->isRented = isRented;
}


// Tuhoaja:
Item::~Item() {}


/* Luokan privaatti jäsenmetodi, joka luo tunnuksen. Funktiossa on useita
* apumuuttujia, joista row- ja rows-muuttujia hyödynnetään tiedoston
* lukemisessa. size_t-tietotyyppiä oleva newId-apumuuttuja alustetaan
* arvoon 0. size_t-tietotyyppiä käytetään tietotyypin int-sijasta, koska
* muualla koodissa hyödynnetään vector<>-tietotyypin size-metodia, joka
* palauttaa size_t-tietotyyppiä olevan luvun.
*
* itemsFileForReading-apumuuttujaan talletetaan ifstream-luokan instanssi,
* jota kuormitetaan luettavan tiedoston nimellä eli
* items_file.txt-merkkijonolla. Jos tiedosto on olemassa eli
* itemsFileForReading-muuttujassa olevan instanssin good-jäsenmetodin kutsu
* palauttaa true-arvon, luetaan tiedoston sisältö rows-muuttujaan siten, että
* yksi rivi vastaa yhtä alkiota. Lopuksi kutsutaan
* itemsFileForReading-muuttujaan talletetun instanssin close-metodia.
*
* Jos items_file.txt-tiedostoa ei ole olemassa, luodaan muualla ohjelmassa
* tämä tiedosto ja lisäksi kolme demotavaraa Item-alkioiseen taulukkoon.
* Koska taulukko on jäsenmuuttuja, ja se esitellään Items.h-tiedostossa
* kolmipaikkaisena, luodaan tästä luokasta siis 3 + 3 eli kuusi instanssia.
*
* Jos instanssien lukumäärä tästä luokasta on kuusi tai vähemmän, ei tiedostoa
* välttämättä ole vielä olemassa, minkä vuoksi kolmelle demomielessä tehdylle
* instanssille generoituisi keskenään sama id, jos se luotaisiin else if
* -haaran toteutusosan perusteella. Siksi if-lauseessa annetaan
* newId-muuttujalle arvo luokasta tehtyjen instanssien lukumäärän perustella.
*
* Instanssien määrästä vähennetään kolme, koska ohjelma luo Items-listan
* alustuksessa kolme merkityksetöntä instanssia, joita ei tuoda näkyviin
* eikä tallenneta tiedostoon. Niiden lukumäärää ei haluta ottaa myöskään
* huomioon muille tavaroille tunnuksia generoitaessa. Siksi
* newId-muuttujaan if-lauseessa asetetaan arvoksi count - 3.
*
* Jos ohjelma on esimerkiksi aloittanut ensimmäisen demoinstanssin luomisen,
* on countin arvo neljä. Silloin newId-muuttujaan tallennetaan arvo 4 - 3 eli
* 1. Näin ensimmäinen demoinstanssi tästä luokasta saa tunnuksen 1. Kun
* ohjelma etenee luomaan toista demoinstanssia, on countin arvo 5, ja
* newId-muuttujan arvo siten 5 - 3 eli 2. Näin toisen demoinstanssin
* tunnukseksi tulee 2.
*
* Jos ensimmäinen ehto ei täyty ja siirrytään else if -haaraan ja jos siis
* rows-muuttajassa olevien alkioiden lukumäärän jakojäännös neljän suhteen on
* 0 eli rivien ollessa kirjoitettuna tiedostoon oikealla tavalla, iteroidaan
* kaikki tavaroiden tunnuksia kuvaavat rivit läpi.
*
* Jokaisella iteraatiolla apumuuttujaan idAsInt tallennetaan kulloisenkin
* iteraatiokierroksen alkion kokonaisluvuksi muutettu arvo. Arvo muutetaan
* kokonaisluvuksi string-kirjaston string to integer -metodia hyödyntämällä.
* Sitten arvoa verrataan silmukan ulkopuolella aiemmin alustettuun
* newId-muuttujan arvoon. Jos idAsInt-muuttujan arvo on suurempi, vaihdetaan
* sen arvo newId-muuttujan arvoksi ja type castataan se samalla vastaamaan
* size_t-tietotyyppiä. Suurimpaa tiedostosta löytyvää id:n arvoa kasvatetaan
* lopuksi newId-muuttujaan tallennettuna yhdellä, ja näin tavaralle saadaan
* generoitua yksilöllinen id, joka ei ole sama muiden tiedostoissa olevien
* tavaroiden tunnusten kanssa ja joka on aina edellisen tavaran tunnusta yhtä
* isompi.
*
* Jos else-haaraan päädytään, tiedoston sisältö on todennäköisesti
* vääränlainen, eikä tiedostonkäsittely tällaisessa tilanteessa toimi enää
* luotettavasti. Niinpä newId:n arvo pysyy 0:na. Lisäksi käyttäjälle
* tulostetaan virheilmoitus.
*/
size_t Item::generateId()
{
    string row;
    vector<string> rows;
    size_t newId = 0;
    ifstream itemsFileForReading = ifstream("items_file.txt");

    if (itemsFileForReading.good())
    {
        while (getline(itemsFileForReading, row))
        {
            rows.push_back(row);
        }
    }

    itemsFileForReading.close();

    if (count <= 6)
    {
        newId = count - 3;
    }
    else if (rows.size() % 4 == 0)
    {
        /* Ensimmäisen tavaran tunnuksesta kertova arvo on rivillä 2 eli
        * rows-muuttujan indeksissä 1. Seuraavan tavaran tunnus on
        * neljän alkion päässä edellisestä.
        */
        for (int i = 1; i < rows.size(); i += 4)
        {
            int idAsInt = stoi(rows[i]);
            if (idAsInt > newId)
            {
                newId = (size_t)idAsInt;
            }
        }
        newId++;
    }
    else
    {
        cout << "Tiedostossa olevat tiedot ovat puutteellisia.\n" << endl;
    }

    return newId;
}


// id-jäsenmuuttujan getter-metodi:
size_t Item::getId()
{
    return this->id;
}


// name-jäsenmuuttujan getter-metodi:
string Item::getName()
{
    return this->name;
}


// category-jäsenmuuttujan getter-metodi:
string Item::getCategory()
{
    return this->category;
}


// isRented-jäsenmuuttujan getter-metodi:
bool Item::getRentalState()
{
    return this->isRented;
}
