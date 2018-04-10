#include "CountryRepo.h"
#include <stdlib.h>
#include <string.h>


//create repo
CountryRepo* create_repo()
{

	CountryRepo* cr = (CountryRepo*)malloc(sizeof(CountryRepo));
	cr->country = create_dinamic_array(&destroy_country);

	return cr;

}

//destroy repo
void destroy_repo(CountryRepo* cr)
{
	destroy_dinamic_array(cr->country);
	free(cr);
}

/*
Find if a country is in the repo
Input: A name
Output: -1 if the country is not in the repo; the index of the country in the repo
*/
int find(CountryRepo* cr,char *c)
{

	for (int i = 0; i < cr->country->lenght; i++)
		if (strcmp(get_name(cr->country->elem[i]), c) == 0)
			return i;//index in the repo

	return -1;//not found

}

/*
Add a country in the repo
Input: A country
Output: 0 - if not added; 1 - if added
*/
int add_repo(CountryRepo* cr, Country* c)
{
	if (find(cr,get_name(c)) == -1)//if the country exists
	{
		add_dinamic_array(cr->country, c);
		return 1;
	}

	return 0;
}

/*
Delete a country in the repo
Input: A name
Output: 0 - if not deleted; 1 - if deleted
*/
int delete_repo(CountryRepo* cr, char* name)
{
	int in = find(cr,name);

	if (in!=-1)//if the country exists
	{
		delete_from_dinamic_array(cr->country, in);
		return 1;
	}

	return 0;

}

/*
Update a country in the repo
Input: A country
Output: 0 - if not updated; 1 - if updated
*/
int update_repo(CountryRepo* cr, Country* c,char* name)
{
	int in = find(cr,name);
	int inx = find(cr, get_name(c));

	if (in != -1 && inx==-1 && strlen(get_continent(c)) && strlen(get_name(c)))//if what we want to update exists and the country we want to add does not exist
	{
		destroy_country(cr->country->elem[in]);//free the memory 
		cr->country->elem[in] = c;
		return 1;
	}

	return 0;
}

/*
Change the population of two countries in the repo
Input: A country
Output: 0 - if not modified; 1 - if modified
*/
int migrate_repo(CountryRepo* cr, char* c1, char* c2, double pop)
{
	int in_1 = find(cr, c1);
	int in_2 = find(cr, c2);

	if (in_1 != -1 && in_2 != -1)//if the countries exists
	{
		if (get_population(cr->country->elem[in_1]) <= pop)//if population remains >0
			return 0;

		else
		{
			//we create 2 new countries so we can update the population
			Country* C1 = create_country(get_name(cr->country->elem[in_1]), get_continent(cr->country->elem[in_1]), get_population(cr->country->elem[in_1]));
			Country* C2 = create_country(get_name(cr->country->elem[in_2]), get_continent(cr->country->elem[in_2]), get_population(cr->country->elem[in_2]));

			C1->population -= pop;
			C2->population += pop;


			destroy_country(cr->country->elem[in_1]);//free the memory
			destroy_country(cr->country->elem[in_2]);//free the memory

			cr->country->elem[in_1] = C1;
			cr->country->elem[in_2] = C2;

			return 1;
		}
	}
	return 0;
}

/*
Find if a country exists in a list of repos
Input: A name
Output: 0 - if not exists; 1 - if exists
*/
int not_in_repo(DinamicArray* array,char*name)
{
	for (int i = 0; i < array->lenght; i++)
		if (find(array->elem[i],name)!=-1)
			return 0;

	return 1;

}