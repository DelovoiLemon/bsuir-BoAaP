#include "stud.h"

int main()
{
	student *root_stud = NULL;

	build_menu(&root_stud); 

	rm_all_students(&root_stud); // Clean up
}
