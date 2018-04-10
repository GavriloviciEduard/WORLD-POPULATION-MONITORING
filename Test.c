#include "Test.h"
#include <assert.h>
#include <string.h>

void test_model()
{

	Country* c=create_country("South Africa", "Africa", 55.91);
	assert(strcmp(get_name(c), "South Africa") == 0);
	assert(strcmp(get_continent(c), "Africa") == 0);
	assert(get_population(c) == 55.91);

	destroy_country(c);

	c = create_country("Greece", "Europe", 9.91);
	assert(strcmp(get_name(c), "Greece") == 0);
	assert(strcmp(get_continent(c), "Europe") == 0);
	assert(get_population(c) == 9.91);

	destroy_country(c);

	c = create_country("Japan", "Asia", 99.91);
	assert(strcmp(get_name(c), "Japan") == 0);
	assert(strcmp(get_continent(c), "Asia") == 0);
	assert(get_population(c) == 99.91);

	destroy_country(c);
}

void test_repo()
{
	CountryRepo* cr = create_repo();
	Country* c1 = create_country("South Africa", "Africa", 55.91);
	Country* c2 = create_country("Greece", "Europe", 5.91);
	Country* c3 = create_country("Japan", "Asia", 99.91);
	Country* c4 = create_country("Estonia", "Europe", 11.21);
	Country* c5 = create_country("Malta", "Europe", 1.21);

	assert(cr != NULL);
	assert(add_repo(cr, c1) == 1);
	assert(add_repo(cr, c2) == 1);
	assert(add_repo(cr, c3) == 1);
	assert(add_repo(cr, c5) == 1);
	assert(add_repo(cr, c1) == 0);
	assert(add_repo(cr, c3) == 0);
	assert(delete_repo(cr, get_name(c1)) == 1);
	assert(delete_repo(cr,"Asia") == 0);
	assert(update_repo(cr, c4, "Greece") == 1);
	assert(update_repo(cr, c4, "Greece") == 0);
	assert(migrate_repo(cr, get_name(c4), get_name(c3), 10) == 1);
	assert(migrate_repo(cr, get_name(c5), get_continent(c5), 10) == 0);
	
	destroy_repo(cr);

}

void test_controller()
{
	CountryRepo* cr = create_repo();
	Controller* cn = create_contoller(cr);
	Country* c3 = create_country("Japan", "Asia", 99.91);

	assert(cn != NULL);

	
	assert(add_country(cn, "Romania", "Europe", 19.71)==1);
	assert(add_country(cn, "Greece", "Europe", 10.75)==1);
	assert(add_country(cn, "USA", "America", 323.1)==1);
	assert(add_country(cn, "Uruguay", "America", 3.44)==1);
	assert(add_country(cn, "", "America", 3.44) == 0);
	assert(add_country(cn, "Uruguay", "", 3.44) == 0);
	assert(add_country(cn, "Uruguay", "America", 0) == 0);
	assert(add_country(cn, "Uruguay", "America", -3.44) == 0);

	assert(delete_country_controller(cn, "Romania") == 1);
	assert(delete_country_controller(cn, "Uruguay") == 1);
	assert(delete_country_controller(cn, "Romania") == 0);
	assert(delete_country_controller(cn, "Uruguay") == 0);
	assert(delete_country_controller(cn, "") == 0);

	assert(update_all_controller(cn, "Greece", c3) == 1);
	assert(update_all_controller(cn, "", c3) == 0);
	assert(update_all_controller(cn, "USA", c3) == 0);

	assert(update_migration_controller(cn, "USA", "Japan", 10) == 1);
	assert(update_migration_controller(cn, "USA", "Romania", 10) == 0);
	assert(update_migration_controller(cn, "Uruguay", "Romania", 10) == 0);

	destroy_controller(cn);
}

void test_dinamic_array()
{
	DinamicArray* array = create_dinamic_array(&destroy_country);
	Country* c1 = create_country("South Africa", "Africa", 55.91);
	Country* c2 = create_country("Greece", "Europe", 5.91);
	Country* c3 = create_country("Japan", "Asia", 99.91);
	Country* c4 = create_country("Estonia", "Europe", 11.21);
	Country* c5 = create_country("Malta", "Europe", 1.21);
	Country* c6 = create_country("South Africa", "Africa", 55.91);
	Country* c7 = create_country("Greece", "Europe", 5.91);
	Country* c8 = create_country("Japan", "Asia", 99.91);
	Country* c9 = create_country("Estonia", "Europe", 11.21);
	Country* c10 = create_country("Malta", "Europe", 1.21);
	Country* c11 = create_country("South Africa", "Africa", 55.91);
	Country* c12 = create_country("Greece", "Europe", 5.91);
	Country* c13 = create_country("Japan", "Asia", 99.91);
	Country* c14 = create_country("Estonia", "Europe", 11.21);
	Country* c15 = create_country("Malta", "Europe", 1.21);

	assert(add_dinamic_array(array,c1) == 1);
	assert(add_dinamic_array(array, c2) == 1);
	assert(add_dinamic_array(array, c3) == 1);
	assert(add_dinamic_array(array, c4) == 1);
	assert(add_dinamic_array(array, c5) == 1);
	assert(add_dinamic_array(array, c6) == 1);
	assert(add_dinamic_array(array, c7) == 1);
	assert(add_dinamic_array(array, c8) == 1);
	assert(add_dinamic_array(array, c9) == 1);
	assert(add_dinamic_array(array, c10) == 1);
	assert(add_dinamic_array(array, c11) == 1);
	assert(add_dinamic_array(array, c12) == 1);
	assert(add_dinamic_array(array, c13) == 1);
	assert(add_dinamic_array(array, c14) == 1);
	assert(add_dinamic_array(array, c15) == 1);

	destroy_dinamic_array(array);
}

void start_tests()
{
	test_model();
	test_repo();
	test_controller();
	test_dinamic_array();
}
