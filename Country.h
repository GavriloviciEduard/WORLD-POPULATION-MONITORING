#pragma once

typedef struct
{
	char* name;
	char* continent;
	double population;
}Country;

//create country
Country* create_country(char* name, char* continent, double population);

//destroy country 
void destroy_country(Country* c);

//get name of a country
char* get_name(Country *c);

//get name of a continent
char* get_continent(Country *c);

//get population of a country
double get_population(Country *c);

//"overloading" print
void to_string(Country *c,char str[]);

