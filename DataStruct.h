#pragma once

typedef void(*Destroy)(void*);
typedef void(*auto_elem);


typedef struct
{
	auto_elem* elem;//any kind of element
	int lenght;
	int capacity;
	int act;
	Destroy destroy;//any kind of destroy

}DinamicArray;

//create dinamic array
DinamicArray* create_dinamic_array(void* cond);

//destroy dinamic array
void destroy_dinamic_array(DinamicArray* array);

//add an element in the dinamic array
int add_dinamic_array(DinamicArray* array, auto_elem* c);

//delete an element from the dinamic array
void delete_from_dinamic_array(DinamicArray* array, int index);

//destroy the dinamic array
void destroy_dinamic_array(DinamicArray* array);




