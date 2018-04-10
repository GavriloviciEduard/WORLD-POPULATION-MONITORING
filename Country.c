#include "Country.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

//create country
Country* create_country(char* name, char* continent, double population)
{

	Country* c = (Country *)malloc(sizeof(Country));
	c->name = (char *)malloc(sizeof(char) * (strlen(name) + 1));
	strcpy(c->name, name);
	c->continent = (char *)malloc(sizeof(char) * (strlen(continent)+1));
	strcpy(c->continent, continent);
	c->population = population;

	return c;

}

//destroy country
void destroy_country(Country* c)
{

	free(c->name);
	free(c->continent);
	free(c);

}

//getter
char* get_name(Country *c)
{

	return c->name;
}

//getter
char* get_continent(Country *c)
{

	return c->continent;

}

//getter
double get_population(Country *c)
{

	return c->population;

}

//"overloading" print
void to_string(Country *c,char str[])
{

	sprintf(str, "%s is in %s and has a population of %.2lf milions.", c->name, c->continent, c->population);

}