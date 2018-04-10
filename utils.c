#include "Controller.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>




//compare two values
int comp_a(double a, double b)
{
	return a > b;
}

//compare two values
int comp_d(double a, double b)
{
	return a < b;
}

//compare two strings
int comp_cont(char a[], Country* c)
{

	return strcmp(a, c->continent) == 0;
}

//find if 'a' is in the name of the country 
int comp_str(char a[], Country* c)
{
	return strstr(c->name, a);
}

//compare two doubles
int comp_doubs(char a[], Country* c)
{
	double nr;

	sscanf(a, "%lf", &nr);//char to double

	return c->population > nr;
}

//compare two doubles
int comp_doubs_i(char a[], Country* c)
{
	double nr;

	sscanf(a, "%lf", &nr);//char to double

	return c->population < nr;
}

//generic bubble sort (functions with 2 doubles)
void sort(CountryRepo * cr, int(*fct_pt)(double, double))
{
	for (int i = 0; i < cr->country->lenght-1; i++)
		for (int j = i + 1; j < cr->country->lenght; j++)
			if (fct_pt(get_population(cr->country->elem[i]),get_population(cr->country->elem[j])))
			{
				
				Country* aux = create_country( get_name(cr->country->elem[i]), get_continent(cr->country->elem[j]), get_population(cr->country->elem[i]) );
				destroy_country(cr->country->elem[i]);
				cr->country->elem[i] = cr->country->elem[j];
				cr->country->elem[j] = aux;
				
			}
}

//generic filter
CountryRepo* filter(CountryRepo* cr,char str[],int(*fct_pt)(char*,Country*))
{
	

	CountryRepo* cr_n = create_repo();

	if (strlen(str) == 0)
	{
		for (int i = 0; i < cr->country->lenght; i++)
		{
			Country* aux = create_country(get_name(cr->country->elem[i]), get_continent(cr->country->elem[i]), get_population(cr->country->elem[i]));
			add_repo(cr_n, aux);
		}
	}

	else
	{
		for(int i=0;i< cr->country->lenght;i++)
			if (fct_pt(str, cr->country->elem[i]))
			{
				Country* aux = create_country(get_name(cr->country->elem[i]), get_continent(cr->country->elem[i]), get_population(cr->country->elem[i]));
				add_repo(cr_n, aux);
			}
	}


	return cr_n;

}

//if a continet is valid
int valid_cont(char cont[])
{
	return (strcmp(cont, "Europe") == 0) || (strcmp(cont, "America") == 0) ||
		(strcmp(cont, "Africa") == 0) || (strcmp(cont, "Australia") == 0) ||
		(strcmp(cont, "Asia") == 0) || strlen(cont) == 0;
}

//generic bubble sort (functions with char and Country)
void sort_2(CountryRepo * cr, int(*fct_pt_f)(char*, Country*))
{
	for (int i = 0; i < cr->country->lenght - 1; i++)
		for (int j = i + 1; j < cr->country->lenght; j++)
			if (fct_pt_f(get_name(cr->country->elem[i]),cr->country->elem[j]))
			{
				Country* aux = create_country(get_name(cr->country->elem[i]), get_continent(cr->country->elem[i]), get_population(cr->country->elem[i]));
				destroy_country(cr->country->elem[i]);
				cr->country->elem[i] = cr->country->elem[j];
				cr->country->elem[j] = aux;

			}
}
//compare two strings
int comp_str_v(char* a, Country* c)
{

	return strcmp(a, c->name) > 0;

}
