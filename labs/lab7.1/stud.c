#include "stud.h"


const char *logo = 
"  /$$$$$$  /$$                   /$$/$$$$$$          /$$$$$$       \n" 
" /$$__  $$| $$                  | $|_  $$_/         /$$__  $$       \n"
"| $$  \\__/$$$$$$  /$$   /$$ /$$$$$$$ | $$  /$$$$$$$| $$  \\__/$$$$$$ \n"
"|  $$$$$|_  $$_/ | $$  | $$/$$__  $$ | $$ | $$__  $| $$$$  /$$__  $$\n"
" \\____  $$| $$   | $$  | $| $$  | $$ | $$ | $$  \\ $| $$_/ | $$  \\ $$\n"
" /$$  \\ $$| $$ /$| $$  | $| $$  | $$ | $$ | $$  | $| $$   | $$  | $$\n"
"|  $$$$$$/|  $$$$|  $$$$$$|  $$$$$$$/$$$$$| $$  | $| $$   |  $$$$$$/\n"
" \\______/  \\___/  \\______/ \\_______|______|__/  |__|__/    \\______/ \n";
                                                                  

double calc_avg_mark(int *subjs, size_t subj_c)
{
	double avg_sum = 0;
	for(int i = 0; i < subj_c; i++) 
		avg_sum += subjs[i];
	return avg_sum / subj_c;
}

int init_student(student **stud, read_func read_stud, FILE *file)
{
	*stud = malloc(sizeof(struct stud));
	if(!read_stud(*stud, file)) {
		(*stud)->avg = calc_avg_mark((*stud)->subjs, subj_count);
		(*stud)->next = NULL;
		return 0;
	} else {
		if(!file) addstr("READING failed, student cannot be added.");
		free(*stud);
		*stud = NULL;
		return 1;
	}
}

int add_student(student *stud, read_func read_stud, FILE *file)
{
	while(stud->next != NULL) stud = stud->next;
	stud->next = malloc(sizeof(struct stud));
	if(!read_stud(stud->next, file)) {
		stud->next->avg = calc_avg_mark(stud->next->subjs, subj_count);
		stud->next->next = NULL;
		return 0;
	} else {
		if(!file) addstr("READING failed, student cannot be added.");
		free(stud->next);
		stud->next = NULL;
		return 1;
	}
}

int get_count(const student *stud)
{
	int i;
	for(i = 0; stud; i++, stud = stud->next);
	return i;
}

int lenstr(const char *str)
{
    int i;
    for(i = 0; str[i]; i++);
    return i;
}

int edit_student(student *stud, size_t num, read_func read_stud)
{
	if(!stud || num == -1) return 0;
	while(num > 0)
	{
		stud = stud->next;
		if(!stud) return 0;
		num--;
	}
	addstr("Leave blank to keep unchanged.\n");
	read_stud(stud, NULL);
	stud->avg = calc_avg_mark(stud->subjs, subj_count);
	return 1;
}

int rm_student(student **stud_root, size_t num)
{
	student *del_stud = *stud_root, *prev_stud;
	if(num == -1) return 0;
	if(num == 0) *stud_root = del_stud->next;
	else {
		while(del_stud && num > 0)
		{
			prev_stud = del_stud;
			del_stud = del_stud->next;
			num--;
		}
		prev_stud->next = del_stud->next;
	}
	free(del_stud);
	return 1;
}

void rm_all_students(student **stud_root)
{
	student *tmp;
	while(tmp = *stud_root)
	{
		*stud_root = tmp->next;
		free(tmp);
	}	
}

int print_stud(const student *stud, int num, int left, FILE *file)
{
	clear();
	printw("Student #%i metrics\n"
	       " Name: %s\n"
	       " Group: %i\n"
	       " Student marks:\n"
	       "  Phythics %i\n"
	       "  Math %i\n"
	       "  Informathics %i\n"
	       " Average mark: %lf\n\n"
	       "%i students left.", num, stud->name, stud->group, 
	       stud->subjs[phys], stud->subjs[math], stud->subjs[inform], stud->avg, left);
	if(left) {
		addstr("\nPress <0> to return to menu.\n");
		if(getch() == '0') return -1;
	}
	return 0;
}

int save_stud(const student *stud, int num, int left, FILE *file)
{
	return fprintf(file,
		"%s\n%i %i %i %i\n", stud->name, stud->group, 
		stud->subjs[phys], stud->subjs[math], stud->subjs[inform]);
}

int put_studs(const student *stud, out_func put_stud, FILE *file)
{
	int i;
	int stud_left = get_count(stud) - 1;
	noecho();
	for(i = 0; stud; stud = stud->next, i++)
		if(put_stud(stud, i+1, stud_left - i, file) == -1) return i;
	return i;
}

int read_from_term(student *stud, FILE *file)
{
	int error = 0; echo();
	addstr("\nStart reading student's metrics\n\n");
	addstr("Enter name(up to 64 letters): "); error += scanw("\n%64[^\n]s", stud->name) < 1;
	addstr("Enter group: "); error += scanw("%i", &(stud->group)) < 1;
	addstr("Enter marks\n");
	addstr("Enter mark for physics: "); error += scanw("%i", (stud->subjs)+phys) < 1;
	addstr("Enter mark for mathimathics: "); error += scanw("%i", (stud->subjs)+math) < 1;
	addstr("Enter mark for informathics: "); error += scanw("%i", (stud->subjs)+inform) < 1;
	addstr("\nEnd\n");
	return error;
}

int read_from_file(student *stud, FILE *file)
{
	return (fscanf(file, "%64[^\n]s", stud->name) + fscanf(file, "%i%i%i%i\n",
		&(stud->group), (stud->subjs)+phys, (stud->subjs)+math, (stud->subjs)+inform)) < 5;
}

size_t choose_menu(student *stud) 
{
	student *tmp;
	int num = 0, count = 0;

	while(true) {
		clear(); noecho();
		tmp = stud;
		for(count = 0; tmp; count++, tmp = tmp->next)
			printw(" %c %s from %i\n", (count == num) ? '*' : '-', tmp->name, tmp->group);
		
		addstr("\nUse 1(up), 2(down), 3 to select, 0 to cancel.\n");

		switch(getch()) {
			case '1':
				if(num > 0) num--;
				break;
			case '2':
				if(num < count-1) num++;
				break;
			case '3':
				printw("Selected #%i student.\n", num+1);
				return num;
			case '0':
				addstr("Canceling choosing student.\n");
				return -1;
		}
		refresh();
	}
}

void build_menu(student **stud)
{
	int cur_c = 0, count = 0, is_unsaved = 0;
	char path[256] = "stud.db";
	FILE *file;
	
	initscr(); cbreak();

	addstr(logo);
	addstr("\n"
	       " --- Student metrics reading and storing program           ---\n"
	       " --- This program could store, print, find student's data. ---\n"
	       " --- Created by Troshkin Dmitry.			   ---\n"
	       "\n"
	       "Press <anykey> to continue.\n");
	refresh();
	getch();

	while(true) {
		clear();
		printw(" ---------- Menu ----------\n"
		       " - 1. Add student.\n"
		       " - 2. Add students from file.\n"
		       " - 3. Print stored students.\n"
		       " - 4. Edit student's data.\n"
		       " - 5. Remove student's data.\n"
		       	" - 6. Find student's metrics.\n"
		       " %c 7. Save.\n"
		       " - 8. Exit.\n"
		       " - 9. Clear students.\n",
		       is_unsaved ? '*' : '-'
		);
		refresh();

		switch(getch()) {
			case '1':
				clear();
				if(*stud == NULL) init_student(stud, read_from_term, NULL);
				else add_student(*stud, read_from_term, NULL);
				is_unsaved++;
				count++;
				break;
			case '2':
				clear(); echo();
				printw("Enter filename[%s]: ", path);
				scanw("%256[^\n]s", path);
				file = fopen(path, "r");
				if(!file) {
					addstr("File does not exist or you haven't got rights to read it.\n");
					break;
				}
				cur_c = 0;	
				if(*stud == NULL) cur_c += !init_student(stud, read_from_file, file);
				if(count + cur_c) while(!add_student(*stud, read_from_file, file)) cur_c++;
				is_unsaved = (count != 0);
				count += cur_c;
					
				printw("Now %i records readed.\n"
				       "Totally %i students readed.\n", cur_c, count);
				fclose(file);
				break;
			case '3':
				clear();
				if(count == 0) 
					addstr("Nothing here...\n"
					       "Add students before print them.");
				put_studs(*stud, print_stud, NULL);
				break;
			case '4':
				if(count == 0) {
					clear();
					addstr("There is nothing to be edited.\nAdd students first.");
					break;
				}
				is_unsaved = edit_student(*stud, choose_menu(*stud), read_from_term);
                        	break;
			case '5':
				if(count == 0) {
					clear();
					addstr("There are no students to be deleted.\n");
					break;
				}
				if(rm_student(stud, choose_menu(*stud))) {
					addstr("Student removed successfully.\n");
					count--;
					is_unsaved = 1;
				}
				break;
			case '6':
                filtering_menu(stud);

				break;
			case '7':
			    clear();
                printw("Enter filename[%s]: ", path); 
				scanw("%256[^\n]s", path);
				file = fopen(path, "w");
				if(!file) {
					addstr("Can't open file for writing!\n");
					break;		
				}
				put_studs(*stud, save_stud, file);
				addstr("Saving complite.\n");
				is_unsaved = 0;
				fclose(file);
				break;
			case '8':
			        if(is_unsaved) 
				{
					clear();
					addstr("Are you really want to quit?(y/N)");
					refresh();
					if(getch() == 'y') return; 
				}	
				else return;
				break;
			case '9':
				clear();
				rm_all_students(stud);
				addstr("Students cleared...");
				is_unsaved = 0;
				count = 0;
				break;
			default:
				continue;	
		}
		addstr("\nPress <anykey> to go back to menu.\n");
		refresh();
		getch();
		
	}

	endwin();
}

student *stud_filter(stud_cmp cmp_func, const student* stud, const char *name, const int mark, const int subject)
{
    int count;
    student *fstud_root = NULL, *tmp = NULL;

    for(count = 0; stud; count++, stud = stud->next)
    {
        if(cmp_func(stud, name, mark, subject)) {
            if(!fstud_root) {
                fstud_root = malloc(sizeof(student));
                *fstud_root = *stud;
                fstud_root->next = NULL;
                tmp = fstud_root;
            } else {
                tmp->next = malloc(sizeof(student));
                *(tmp->next) = *stud;
                tmp->next->next = NULL;
                tmp = tmp->next;
            }
        }
    }    
    return fstud_root;
}

// Functions for comparing

int isMarkLess(const student * base, const char *name, const int mark, const int subject)
{
    return base->subjs[subject] < mark;
}
int isMarkLessOrEq(const student * base, const char *name, const int mark, const int subject)
{
    return base->subjs[subject] <= mark;
}
int isMarkMore(const student * base, const char *name, const int mark, const int subject)
{
    return base->subjs[subject] > mark;
}
int isMarkMoreOrEq(const student * base, const char *name, const int mark, const int subject)
{
    return base->subjs[subject] >= mark;
}
int isMarkEqual(const student * base, const char *name, const int mark, const int subject)
{
    return base->subjs[subject] == mark;
}

int isContaining(const student * base, const char *name, const int mark, const int subject)
{
    return strstr(base->name, name) != NULL;
}

void filtering_menu(student **stud)
{
    int mode = -1, mark = -1, subject  = -1, to_print = -1, menu = -1;
    char * name = NULL, *path = NULL;
    FILE * file = NULL;
    student *tmp = NULL;
    clear(); echo();
    addstr("Choose output mode(1 - save to file, 2 - print filtred, 3 - remove incorect).\n");
    while(to_print > 3 || to_print < 1) {
        addstr("Input: ");
        scanw("%i", &to_print);
    }

    clear();
    addstr("Choose what to compare:\n");
    addstr(" - 1. Name\n");
    addstr(" - 2. Mark\n");
    addstr(" - 3. Go back\n");
    
    while(menu > 3 || menu < 1) {
        addstr("Input: ");
        scanw("%i", &menu);
    }
    
    switch(menu) {
        case 1:
            name = malloc(64 * sizeof(char));
            clear(); echo();
            addstr("Enter string to search in names: ");
            while(!scanw("%64[^\n]s", name))
                addstr("Try again: "); 
                
            tmp = stud_filter(isContaining, *stud, name, mark, subject);

            break;
        case 2:
            clear(); echo();
            addstr("Choose subject(0 - physics, 1 - informatics, 2 - mathimatics, 3 - exit).\n");
            while(subject > 2 || subject < 0) {
                addstr("Input: ");
                scanw("%i", &subject);  
            }
            addstr("Enter mark.\n");
            while(mark > 10 || mark < 1) {
                addstr("Input: ");
                scanw("%i", &mark);
            }
    
            addstr("Enter mode.\n");
            addstr(" - 1. <\n");
            addstr(" - 2. <=\n");
            addstr(" - 3. >\n");
            addstr(" - 4. >=\n");
            addstr(" - 5. ==\n");
                
            while(mode > 5 || mode < 1) {
                addstr("Input: ");
                scanw("%i", &mode);
            }
            
            switch(mode) {
                case 1: tmp = stud_filter(isMarkLess,*stud, name, mark, subject); break;
                case 2: tmp = stud_filter(isMarkLessOrEq,*stud, name, mark, subject); break;
                case 3: tmp = stud_filter(isMarkMore,*stud, name, mark, subject); break;
                case 4: tmp = stud_filter(isMarkMoreOrEq,*stud, name, mark, subject); break;
                case 5: tmp = stud_filter(isMarkEqual,*stud, name, mark, subject); break;
            }

        break;
        case 3:
            return;

        default:
    }
    
    if(!tmp) {
        clear();
        addstr("No students found!\n");
    }


    if(to_print == 1) {
        path = malloc(256*sizeof(char));
        clear();
        printw("Enter filename[%s]: ", path); 
        scanw("%256[^\n]s", path);
        file = fopen(path, "w");
        if(!file) {
            addstr("Can't open file for writing!\n");
            return;		
        }
        put_studs(tmp, save_stud, file);
        addstr("Saving complite.\n");
        fclose(file);
        rm_all_students(&tmp);
    } else if(to_print == 2) {
        put_studs(tmp, print_stud, NULL);
        rm_all_students(&tmp);
    } else {
        rm_all_students(stud);
        *stud = tmp;
    }
}