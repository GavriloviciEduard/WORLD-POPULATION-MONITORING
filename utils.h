#pragma once
#include "Controller.h"

//compare two values
int comp_a(double a, double b);

//compare two values
int comp_d(double a, double b);

//sort
void sort(CountryRepo* cr, int(*fct_pt)(double, double));

//compare two strings
int comp_cont(char a[], Country* c);

//filter
CountryRepo* filter(CountryRepo* cro, char str[], int(*fct_pt)(char*, Country*));

//compare two strings
int comp_str(char a[], Country* c);

//compare two values
int comp_doubs(char a[], Country* c);

//compare two values
int comp_doubs_i(char a[], Country* c);

//verifies if the continent is valid
int valid_cont(char cont[]);

//sort
void sort_2(CountryRepo * cr, int(*fct_pt_f)(char*, Country*));

//compare two strings
int comp_str_v(char* a, Country* c);