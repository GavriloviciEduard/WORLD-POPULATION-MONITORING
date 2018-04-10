#include "stdlib.h"
#include "DataStruct.h"
#include <string.h>

//create dinamic array
DinamicArray* create_dinamic_array(void* cond)
{
	DinamicArray* array = (DinamicArray*)malloc(sizeof(DinamicArray));
	array->elem = (auto_elem*)malloc(10 * sizeof(auto_elem));
	array->lenght = 0;
	array->destroy = cond;//a pointer to a function
	array->capacity = 10;
	array->act = 0;

	return array;
}


//destroy dinamic array
void destroy_dinamic_array(DinamicArray* array)
{
	for (int i = 0; i < array->lenght; i++)
	{
		array->destroy(array->elem[i]);
	}

	free(array->elem);

	free(array);
}


//resize the dinamic array
int resize(DinamicArray* array)
{

	array->capacity *= 2;

	auto_elem* aux = (auto_elem*)realloc(array->elem, array->capacity * sizeof(auto_elem));

	if (aux == NULL)//if can't be resized anymore
		return 0;

	array->elem = aux;


	return 1;
}


//add in the dinamic array
int add_dinamic_array(DinamicArray* array, auto_elem* c)
{

	int ok = 1;

	if (array->lenght == array->capacity)//if no more space, then we have to resize the array
		ok = resize(array);

	if (ok)
	{
		array->elem[array->lenght++] = c;
		return 1;
	}

	return 0;
}

//delete an element from the dinamic array
void delete_from_dinamic_array(DinamicArray* array, int index)
{

	array->destroy(array->elem[index]);//destroy the element 

	for (int i = index; i < array->lenght-1; i++)
		array->elem[i] = array->elem[i + 1];

	array->lenght--;

}
