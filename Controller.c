#include "Controller.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

//create controller
Controller* create_contoller(CountryRepo* cr)
{

	Controller* c = (Controller*)malloc(sizeof(Controller));
	c->repo = cr;

	return c;

}

//destroy controller
void destroy_controller(Controller* c)
{

	destroy_repo(c->repo);
	free(c);

}

//return repo
CountryRepo* get_repo(Controller* cl)
{
	return cl->repo;
}

/*
Add a country in the repo
Input: Name, continent and population of the country
Output: 0-if not added; 1-if added
*/
int add_country(Controller* cl,char* name, char* continent, double population)
{

	if (strlen(name) == 0 || strlen(continent)==0 || population<=0)
		return 0;

	Country* c = create_country(name, continent, population);

	int ok = add_repo(cl->repo, c);

	if (!ok)
		destroy_country(c);

	return ok;

}


/*
Filter the elements in the repo by continent
Input: A continent
Output: A controller
*/
CountryRepo* filter_continent(Controller* cl,char continent[])
{
	
		fct_pt_f cond = &comp_cont;

		CountryRepo* cr = filter(cl->repo,continent,cond);

		return cr;


}

/*
Filter the elements in the repo by a given string
Input: A string
Output: A controller
*/
CountryRepo* filter_string_controller(Controller* cl, char* str)
{
	fct_pt_f cond = &comp_str;

	CountryRepo* cr = filter(cl->repo, str, cond);

	return cr;
}

/*
Filter the elements in the repo by a given value(greater than)
Input: A value(double)
Output: A controller
*/
CountryRepo* filter_value_controller(Controller* cl, double value)
{

	fct_pt_f cond = &comp_doubs;

	char nr[50];

	sprintf(nr, "%.2lf", value);

	CountryRepo* cr = filter(cl->repo, nr, cond);

	return cr;

}

/*
Filter the elements in the repo by a given value(less than)
Input: A value(double)
Output: A controller
*/
CountryRepo* filter_valuel_controller(Controller* cl, double value)
{
	fct_pt cond = &comp_doubs_i;

	char nr[50];

	sprintf(nr, "%.2lf", value);

	CountryRepo* cr = filter(cl->repo, nr, cond);
}

/*
Sort the elements in the repo ascending by population
Input:-
Output: A controller
*/
CountryRepo* sorta_popl(Controller* cl)
{
	CountryRepo* cr = create_repo();

	for (int i = 0; i < cl->repo->country->lenght; i++)
	{
		Country* aux = create_country(get_name(cl->repo->country->elem[i]), get_continent(cl->repo->country->elem[i]), get_population(cl->repo->country->elem[i]));
		add_repo(cr, aux);
	}


	fct_pt cond = &comp_a;

	sort(cr, cond);

	return cr;
}

/*
Sort the elements in the repo descending by population
Input:-
Output: A controller
*/
CountryRepo* sortd_popl(Controller* cl)
{
	CountryRepo* cr = create_repo();

	for (int i = 0; i < cl->repo->country->lenght; i++)
	{
		Country* aux = create_country(get_name(cl->repo->country->elem[i]), get_continent(cl->repo->country->elem[i]), get_population(cl->repo->country->elem[i]));
		add_repo(cr, aux);
	}


	fct_pt cond = &comp_d;

	sort(cr, cond);

	return cr;
}


/*
Sort the elements in the repo descending by population(without creating another copy of the repo)
Input:A controler
Output: A controller
*/

void sortd_repo(CountryRepo* cr)
{

	fct_pt cond = &comp_d;

	sort(cr, cond);

	return cr;

}

void sorta_repo(CountryRepo* cr)
{

	fct_pt cond = &comp_a;

	sort(cr, cond);

	return cr;
}

CountryRepo* filterg_repo(CountryRepo* cr,double value,char* cont)
{
	CountryRepo* cr_n = create_repo();

	if(value && strlen(cont))
	{
		for (int i = 0; i < cr->country->lenght; i++)
		{
			if (get_population(cr->country->elem[i]) > value && strcmp(get_continent(cr->country->elem[i]),cont)==0)
			{
				Country* aux = create_country(get_name(cr->country->elem[i]), get_continent(cr->country->elem[i]), get_population(cr->country->elem[i]));
				add_repo(cr_n, aux);
			}
		}
	}

	else if (value)
	{
		for (int i = 0; i < cr->country->lenght; i++)
		{
			if (get_population(cr->country->elem[i]) > value)
			{
				Country* aux = create_country(get_name(cr->country->elem[i]), get_continent(cr->country->elem[i]), get_population(cr->country->elem[i]));
				add_repo(cr_n, aux);
			}
		}
	}

	destroy_repo(cr);

	return cr_n;
}

/*
Filter the elements in the repo belonging to a given continent by population
Input: A continent
Output: A controller
*/
CountryRepo* sort_filter_popl_cont(Controller* cl,char* continent)
{

	CountryRepo* cr = create_repo();


	if (strlen(continent))
	{
		for (int i = 0; i < cl->repo->country->lenght;i++)
		{
			if ( strcmp(get_continent(cl->repo->country->elem[i]), continent) == 0)
			{
				Country* aux = create_country(get_name(cl->repo->country->elem[i]), get_continent(cl->repo->country->elem[i]), get_population(cl->repo->country->elem[i]));
				add_repo(cr, aux);
			}
		}
	}

	else
	{
		for (int i = 0; i < cl->repo->country->lenght; i++)
		{
			
			Country* aux = create_country(get_name(cl->repo->country->elem[i]), get_continent(cl->repo->country->elem[i]), get_population(cl->repo->country->elem[i]));
			add_repo(cr, aux);
		}
	}

	fct_pt_f cond = &comp_str_v;


	
		sort_2(cr, cond);


		return cr;
}

/*
Delete a country from the repo
Input: A name
Output: 0-if not deleted; 1-if deleted
*/
int delete_country_controller(Controller* cl, char*name)
{

	return delete_repo(cl->repo, name);
}


/*
Update a country from the repo
Input: A name
Output: 0-if not updated; 1-if updated
*/
int update_all_controller(Controller* cl, char* name, Country* c)
{
	return update_repo(cl->repo, c, name);
}

/*
Change the population of two countries from the repo
Input: A name
Output: 0-if not changed; 1-if changed
*/
int update_migration_controller(Controller* cl, char* update_min, char* to_update, double to_migrate)
{
	return migrate_repo(cl->repo, update_min, to_update, to_migrate);
}


/*
Create a copy of a repo and return in
Input: A name
Output: A (copy) repo
*/
CountryRepo* copy_repo_na(CountryRepo* repo)
{

	CountryRepo *b = create_repo();

	for (int i = 0; i < repo->country->lenght; i++)
	{
		Country* aux = create_country(get_name(repo->country->elem[i]), get_continent(repo->country->elem[i]), get_population(repo->country->elem[i]));
		add_repo(b, aux);
	}

	return b;
}

void undo(Controller* cl, DinamicArray* array)
{
	
	CountryRepo* cr = copy_repo_na(array->elem[array->act-1]);
	destroy_repo(cl->repo);
	cl->repo = cr;
}




