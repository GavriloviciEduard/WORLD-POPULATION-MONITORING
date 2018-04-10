#pragma once
#include "Test.h"
#include "Windows.h"

typedef struct 
{

	Controller* contr;

}UI;

//create ui
UI* create_UI(Controller* cl);

//destroy ui
void destroy_UI(UI* ui);

//start app
void start(UI* ui);

