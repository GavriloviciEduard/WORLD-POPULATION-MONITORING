#include "UI.h"
#include <crtdbg.h>

int main()
{
	system("color 02");
	//start tests
	start_tests();

	//create repo and controller
	CountryRepo* cr = create_repo();
	Controller* cl = create_contoller(cr);
	
	//add countries in the repo
	add_country(cl, "Romania", "Europe", 19.71);
	add_country(cl, "Greece", "Europe", 10.75);
	add_country(cl, "USA", "America", 323.1);
	add_country(cl, "Uruguay", "America", 3.44);
	add_country(cl, "Egypt", "Africa", 95.69);
	add_country(cl, "South Africa", "Africa", 55.91);
	add_country(cl, "Japan", "Asia", 127);
	add_country(cl, "Philippines", "Asia", 103.3);
	add_country(cl, "Australia", "Australia", 24.13);
	add_country(cl, "Tasmania", "Australia", 1.51);

	//create ui and start
	UI* ui = create_UI(cl);
	start(ui);
	destroy_UI(ui);

	_CrtDumpMemoryLeaks();

    return 0;
}

