#pragma once
#include "CountryRepo.h"
#include "utils.h"

typedef struct
{

	CountryRepo* repo;

}Controller;

typedef int(*fct_pt)(double, double);//pointer to a function
typedef int(*fct_pt_f)(char*,Country*);//pointer to a function

//create controller
Controller* create_contoller(CountryRepo* cr);

//destroy controller
void destroy_controller(Controller* c);

//add country in the repo
int add_country(Controller* cl, char* name, char* continent, double population);

//filter countries by continent
CountryRepo* filter_continent(Controller* cl, char continent[]);

//filter countries by a values
CountryRepo* filter_value_controller(Controller* cl, double value);

//sort countries ascending by population 
CountryRepo* sorta_popl(Controller* cl);

//sort countries descending by population
CountryRepo* sortd_popl(Controller* cl);

//delete a country form the repo
int delete_country_controller(Controller* cl, char*name);

//update a country from the repo
int update_all_controller(Controller* cl, char* name, Country* c);

//change the population of two countries from the repo
int update_migration_controller(Controller* cl, char* update_min, char* to_update, double to_migrate);

//filter countries by a given string
CountryRepo* filter_string_controller(Controller* cl, char* str);

//return repo
CountryRepo* get_repo(Controller* cl);

//sort the the countries from a given continent by population(asc.)
CountryRepo* sort_filter_popl_cont(Controller* cl, char* continent);

//create a copy of a repo
CountryRepo* copy_repo_na(CountryRepo* repo);

//sort countries whose names contain a given string, sorted descending by population(without creating a copy of the repo)
void sortd_repo(CountryRepo* cr);

void sorta_repo(CountryRepo* cr);

CountryRepo* filterg_repo(CountryRepo* cr, double value, char* cont);

void undo(Controller* cl, DinamicArray* array);