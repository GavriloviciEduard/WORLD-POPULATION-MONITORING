#pragma once
#include "DataStruct.h"
#include "Country.h"

typedef struct
{
	DinamicArray* country;

}CountryRepo;

//create repo
CountryRepo* create_repo();

//destroy repo
void destroy_repo(CountryRepo* cr);

//find a country
int find(CountryRepo* cr, char *c);

//add a country
int add_repo(CountryRepo* cr, Country* c);

//delete a country
int delete_repo(CountryRepo* cr, char* name);

//update a country
int update_repo(CountryRepo* cr, Country* c, char* name);

//change the population of two countries
int migrate_repo(CountryRepo* cr, char* c1, char* c2, double pop);

//search if a country exists in a list of repos
int not_in_repo(DinamicArray* array, char*name);