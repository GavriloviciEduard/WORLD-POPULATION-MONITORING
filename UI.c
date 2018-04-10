#include "UI.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


//create ui
UI* create_UI(Controller* cl)
{

	UI* ui = (UI*)malloc(sizeof(UI));
	ui->contr = cl;

	return ui;

}


//destroy ui
void destroy_UI(UI* ui)
{

	destroy_controller(ui->contr);
	free(ui);
}


/*
Prints the available menu for the problem
Input: -
Output: The menu is printed in the console
*/
void menu()
{
	printf("\n**********************************************************\n");
	printf("A - Add country.\n");
	printf("B - Delete country(by name).\n");
	printf("C - Update country(by name).\n");
	printf("D - Migrate from a country to another.\n");
	printf("E - Display all the countries.\n");
	printf("F - Display all the countries whose names contain a given string.\n");
	printf("G - Display all the countries belonging to a given continent.\n");
	printf("H - Display all the countries whose populations are greater than a given value.\n");
	printf("I - Display all the countries whose populations are less than a given value.\n");
	printf("J - Display all the countries sorted ascending by population.\n");
	printf("K - Display all the countries sorted descending by population.\n");
	printf("L - Display all countries on a given continent, sorted ascending by country name.\n");
	printf("M - Display all the countries whose names contain a given string, sorted descending by population.\n");
	printf("N - Display all the countries on a given continent , whose populations are greater than a given value, sorted ascending by population.\n");
	printf("O - Undo\n");
	printf("P - Redo\n");
	printf("X - Exit.\n");
	printf("\**********************************************************\n");
}



/*
Clean the buffer
Input: -
Output: -
*/
void clear()
{

	while ((getchar()) != '\n');
}

/*
Read a string
Input: A string 'str'
Output: A modified string 'str' (might be empty)
*/
void read_str(char str[])
{
	gets(str);
}


/*
Read a double and return it
Input: -
Output: A double 'nr'
*/
double read_doub()
{

	double nr=0;

	scanf("%lf", &nr);

	while (nr<=0)//while the number is not positive
	{
		clear();
		printf("\nThe population is not valid!Try again!");
		printf("\nGive the population of the country(in millions(>0)):");
		scanf("%lf", &nr);
		
	}

	return nr;
}

/*
Read a continent
Input: A char cont[]
Output: A continent saved in cont[]
*/
void read_cont(char cont[])
{
	gets(cont);
	int ok = valid_cont(cont);

	while (!ok)
	{
		printf("\nThe continent is not valid!Try again!");
		printf("\nGive the continent of the country(may be Europe, America, Africa, Australia and Asia) : ");

		clear();
		gets(cont);
		ok = valid_cont(cont);
	}

	
}

/*
Add a country in the repo and (if it's the case) save the previous repo for undo/redo
Input: Array(for undo/redo) and okk to know if we should add in the array
Output: A country was added in the repo and the previous repo was saved
*/
void add_country_ui(UI* ui, DinamicArray* array)
{

	char name[51];
	char continent[11];
	double population=0;

	printf("Give the name of the country:");
	read_str(name);
	printf("\nGive the continent of the country(may be Europe, America, Africa, Australia or Asia): ");
	read_cont(continent);
	printf("\nGive the population of the country(in millions(>0)):");
	population = read_doub();

	if (array->act != array->lenght && array->lenght && array->act)
		delete_from_dinamic_array(array, array->act);

	if (strlen(name) != 0 && strlen(continent) != 0 && population && find(ui->contr->repo, name) == -1 && not_in_repo(array,name)) //if we should save the current repo for undo/redo
	{
		CountryRepo* cr = copy_repo_na(ui->contr->repo);
		add_dinamic_array(array,cr);
		array->act++;
	}

	int ok=add_country(ui->contr, name, continent, population);

	if (ok)
	{
		printf("\nThe country was added.");
	}
		
	

	else
		printf("\nThe country could not be added.");

	printf("\n");
	system("pause");

}

/*
Delete a country from the repo and (if it's the case) save the previous repo for undo/redo
Input: Array(for undo/redo) and okk to know if we should add in the array
Output: A country was deletede from the repo and the previous repo was saved
*/
void delete_country_ui(UI* ui, DinamicArray* array)
{

	char name[51];

	printf("\nGive the name of the country:");
	read_str(name);

	if (array->act != array->lenght && array->lenght && array->act)
		delete_from_dinamic_array(array, array->act);

	if (find(ui->contr->repo, name) != -1)//if we should save the current repo for undo/redo
	{
		CountryRepo* cr = copy_repo_na(ui->contr->repo);
		add_dinamic_array(array, cr);
		array->act++;
	}

	int ok = delete_country_controller(ui->contr, name);


	if (ok)
	{
		printf("\nThe country was deleted.");
	}
	

	else
		printf("\nNothing to delete.");

	printf("\n");
	system("pause");

}
/*
Update a country from the repo and (if it's the case) save the previous repo for undo/redo
Input: Array(for undo/redo) and okk to know if we should add in the array
Output: A country was update from the repo and the previous repo was saved
*/
void update_country_ui(UI* ui, DinamicArray* array)
{


	char name[51];
	char namen[51];
	char continentn[11];
	double populationn = 0;

	printf("\nGive the name of the country:");
	read_str(name);

	printf("Give the  new name of the country:");
	read_str(namen);
	printf("\nGive the new continent of the country(may be Europe, America, Africa, Australia or Asia): ");
	read_cont(continentn);
	printf("\nGive the new population of the country(in millions(>0)):");
	populationn = read_doub();

	if (array->act != array->lenght && array->lenght && array->act)
		delete_from_dinamic_array(array, array->act);

	if (find(ui->contr->repo, name) != -1 && find(ui->contr->repo, namen) == -1 && not_in_repo(array, namen))//if we should save the current repo for undo/redo
	{
		CountryRepo* cr = copy_repo_na(ui->contr->repo);
		add_dinamic_array(array, cr);
		array->act++;
	}

	Country* c = create_country(namen, continentn, populationn);

	int ok = update_all_controller(ui->contr, name, c);

	if (ok)
	{
		printf("\nThe country was updated.");
	}
		
	

	else
		printf("\nNothing to update.");

	printf("\n");
	system("pause");


	
}
/*
Change the population of two countries from the repo and (if it's the case) save the previous repo for undo/redo
Input: Array(for undo/redo) and okk to know if we should add in the array
Output: The population of two countries from the repo was modified and the previous repo was saved
*/
void migrate_ui(UI* ui, DinamicArray* array)
{

	char name_1[51];
	char name_2[51];
	double pop = 0;
	int in;

	printf("\nGive the name of the country from which the population migrates:");
	read_str(name_1);
	printf("\nGive the name of the country to which the population migrates:");
	read_str(name_2);
	printf("\nGive the population(in millions(>0) which migrates):");
	pop = read_doub();


	if (array->act != array->lenght && array->lenght && array->act)
		delete_from_dinamic_array(array, array->act);

	in = find(ui->contr->repo, name_1);

	if (in != -1 && find(ui->contr->repo, name_2) != -1 && get_population(ui->contr->repo->country->elem[in]) > pop)//if we should save the current repo for undo/redo
	{
		CountryRepo* cr = copy_repo_na(ui->contr->repo);
		add_dinamic_array(array, cr);
		array->act++;
	}

	int ok = update_migration_controller(ui->contr, name_1, name_2, pop);

	if (ok)
	{
		printf("\nThe population migrated.");
	}
		
	

	else
		printf("\nThe update of population failed.");

	printf("\n");
	system("pause");
	


}

/*
Display the elements from the repo
Input: A controller
Output: The countries are display on the console
*/
void display(CountryRepo* cr)
{
	char str[101];

	if (cr->country->lenght)
		for (int i = 0; i < cr->country->lenght; i++)
		{
			to_string(cr->country->elem[i], str);
			printf("%d. -> %s \n", i+1, str);
		}
			
		

	else
		printf("\nNothing to print.");

	printf("\n");
	system("pause");
}

/*
Display all the elements from the repo
Input: -
Output: The countries are display on the console
*/

void display_all_ui(UI* ui)
{
	CountryRepo* cr = get_repo(ui->contr);

	display(cr);	
}


/*
Display the elements(containing a given string) from the repo
Input: A controller
Output: The countries are display on the console
*/
void display_str_ui(UI* ui)
{

	char str[51];
	printf("\nGive a string:");
	read_str(str);

	CountryRepo* cr = filter_string_controller(ui->contr, str);

	display(cr);
	destroy_repo(cr);

}

/*
Display the elements(belonging to a givent continent) from the repo
Input: A controller
Output: The countries are display on the console
*/
void display_cont_ui(UI* ui)
{
	char continent[51];
	printf("\nGive the continent of the country(may be Europe, America, Africa, Australia or Asia): ");
	read_cont(continent);

	CountryRepo* cr = filter_continent(ui->contr, continent);

	display(cr);
	destroy_repo(cr);
}

/*
Display the elements(with a population greater than a given value) from the repo
Input: A controller
Output: The countries are display on the console
*/
void display_value_ui(UI* ui)
{
	double nr = 0;
	printf("\nGive a value >0:");
	nr=read_doub();

	CountryRepo* cr=  filter_value_controller(ui->contr, nr);

	display(cr);
	destroy_repo(cr);

}


/*
Display the elements(with a population less than a given value) from the repo
Input: A controller
Output: The countries are display on the console
*/
void display_valuel_ui(UI* ui)
{

	double nr = 0;
	printf("\nGive a value >0:");
	nr = read_doub();


	CountryRepo* cr = filter_valuel_controller(ui->contr, nr);

	display(cr);
	destroy_repo(cr);

}

/*
Display the elements(sorted ascending by population) from the repo
Input: A controller
Output: The countries are display on the console
*/
void sorta_ui(UI* ui)
{
	CountryRepo* cr = sorta_popl(ui->contr);

	display(cr);
	destroy_repo(cr);

}

/*
Display the elements(sorted descdending by population) from the repo
Input: A controller
Output: The countries are display on the console
*/
void sortd_ui(UI* ui)
{
	CountryRepo* cr = sortd_popl(ui->contr);
	
	display(cr);
	destroy_repo(cr);
}


/*
Undo the last operation. The current repo becomes the previous repo which was saved in an dinamic array.
Input: An Array
Output: A modified repo
*/
void undo_ui(UI* ui, DinamicArray* array)
{

	if(array->act)
		array->act--;


	if (array->act)
	{

		display(ui->contr->repo);
		printf("\n\n\n");
		printf("****************UNDO****************");
		printf("\n\n\n");
		undo(ui->contr, array);
		display(ui->contr->repo);
	}

	else
	{
		printf("Nothing to undo.");
		printf("\n");
		system("pause");
	}
}


/*
Redo the last operation.The op array shows which was the last operation.Because we are redoing the last operation we don't want to save again the current repo so okk==''
Input: An Array
Output: A modified repo
*/
void redo_ui(UI* ui, DinamicArray* array)
{

	if (array->act<array->lenght)
	{

		if (array->act == 0)
			array->act++;

		display(ui->contr->repo);
		printf("\n\n\n");
		printf("****************REDO****************");
		printf("\n\n\n");
		array->act++;
		undo(ui->contr, array);
		display(ui->contr->repo);
		
	}

	else
	{
		printf("Nothing to redo.");
		printf("\n");
		system("pause");
	}
	
}


/*
Display all countries on a given continent, sorted ascending by country name
Input: -
Output:The countries are display on the console 
*/
void sf_cont_pop_ui(UI* ui)
{
	char continent[51];
	printf("\nGive the continent of the country(may be Europe, America, Africa, Australia or Asia): ");
	read_cont(continent);

	CountryRepo* cr = sort_filter_popl_cont(ui->contr, continent);

	display(cr);
	destroy_repo(cr);
}

/*
Display all the countries whose names contain a given string, sorted descending by population
Input: -
Output:The countries are display on the console
*/
void sortd_str(UI* ui)
{
	char str[51];
	printf("\nGive a string:");
	read_str(str);

	CountryRepo* cr =  (filter_string_controller(ui->contr, str));
	sortd_repo(cr);
	display(cr);
	destroy_repo(cr);
}

void sort_c_ui(UI* ui)
{
	char continent[51];
	printf("\nGive the continent of the country(may be Europe, America, Africa, Australia or Asia): ");
	read_cont(continent);
	double nr = 0;
	printf("\nGive a value >0:");
	nr = read_doub();

	CountryRepo* cr = copy_repo_na(ui->contr->repo);
	cr = filterg_repo(cr, nr, continent);
	sorta_repo(cr);
	

	display(cr);
	destroy_repo(cr);

}

void add_last(UI* ui, DinamicArray* array)
{

	if(array->lenght)
	{
		CountryRepo* cr;
		cr = copy_repo_na(ui->contr->repo);
		add_dinamic_array(array, cr);
		array->act++;
	}

}

//start app
void start(UI* ui)
{
	DinamicArray* array = create_dinamic_array(&destroy_repo);
	int ok = 0;

	while (1)
	{
		
		system("cls");
		menu();
		printf("\nEnter an option:");
		char opt = toupper(getch());
		system("cls");

		if (opt == 'X')
		{
			destroy_dinamic_array(array);
			break;
		}

		else
		{
			switch (opt)
			{

				case 'A' :
					add_country_ui(ui,array);
					break;

				case 'B':
					delete_country_ui(ui,array);
					break;


				case 'C':
					update_country_ui(ui,array);
					break;

				case 'D':
					migrate_ui(ui,array);
					break;

				case 'E':
					display_all_ui(ui);
					break;

				case 'F':
					display_str_ui(ui);
					break;

				case 'G':
					display_cont_ui(ui);
					break;

				case 'H':
					display_value_ui(ui);
					break;

				case 'I':
					display_valuel_ui(ui);
					break;

				case 'J':
					sorta_ui(ui);
					break;

				case 'K':
					sortd_ui(ui);
					break;

				case 'L':
					sf_cont_pop_ui(ui);
					break;

				case 'M':
					sortd_str(ui);
					break;

				case 'N':
					sort_c_ui(ui);
					break;

				case 'O':

					if (ok < array->act)
					{
						add_last(ui, array);
						ok = array->act;
					}

					undo_ui(ui,array);
					break;

				case 'P':
					redo_ui(ui, array);

				default:
					printf("The option does not exist!Try again!");
					printf("\n");
					system("pause");
					break;
			}
		}

		
		
		clear();

	}

}