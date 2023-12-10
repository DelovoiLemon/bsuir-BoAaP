#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>

const char *logo = 
"  /$$$$$$  /$$                   /$$/$$$$$$          /$$$$$$       \n" 
" /$$__  $$| $$                  | $|_  $$_/         /$$__  $$       \n"
"| $$  \\__/$$$$$$  /$$   /$$ /$$$$$$$ | $$  /$$$$$$$| $$  \\__/$$$$$$ \n"
"|  $$$$$|_  $$_/ | $$  | $$/$$__  $$ | $$ | $$__  $| $$$$  /$$__  $$\n"
" \\____  $$| $$   | $$  | $| $$  | $$ | $$ | $$  \\ $| $$_/ | $$  \\ $$\n"
" /$$  \\ $$| $$ /$| $$  | $| $$  | $$ | $$ | $$  | $| $$   | $$  | $$\n"
"|  $$$$$$/|  $$$$|  $$$$$$|  $$$$$$$/$$$$$| $$  | $| $$   |  $$$$$$/\n"
" \\______/  \\___/  \\______/ \\_______|______|__/  |__|__/    \\______/ \n";
                                                                  

enum subjects { phys = 0, inform = 1, math = 2, subj_count = 3 };

typedef struct stud {
	char name[64];
	int group;
	int subjs[subj_count];
	double avg;
	struct stud *next;
} student;

typedef int (read_func)(student *, FILE *);
typedef void (out_func)(const student *, int, FILE *);

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

void print_stud(const student *stud, int num, FILE *file)
{
	int stud_left = get_count(stud) - 1;
	clear();
	printw("Student #%i metrics\n"
	       " Name: %s\n"
	       " Group: %i\n"
	       " Student marks:\n"
	       "  Phythics %i\n"
	       "  Math %i\n"
	       "  Informathics %i\n"
	       " Average mark: %lf\n\n"
	       "%i students left.\n", num, stud->name, stud->group, 
	       stud->subjs[phys], stud->subjs[math], stud->subjs[inform], stud->avg, stud_left);
	if(stud_left) getch();
}

void save_stud(const student *stud, int num, FILE *file)
{
	fprintf(file,
		"%s\n%i %i %i %i\n", stud->name, stud->group, 
		stud->subjs[phys], stud->subjs[math], stud->subjs[inform]);
}

int put_studs(const student *stud, out_func put_stud, FILE *file)
{
	int i;
	for(i = 0; stud; stud = stud->next, i++)
		put_stud(stud, i+1, file);
	return i;
}

int read_from_term(student *stud, FILE *file)
{
	int error = 0;
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
                        	break;
			case '5':
				if(rm_student(stud, choose_menu(*stud))) {
					addstr("Student removed successfully.\n");
					count--;
					is_unsaved = 1;
				}
				break;
			case '6':

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
		}
		refresh();
		getch();
		
	}

	endwin();
}

int main()
{
	student *root_stud = NULL;

	build_menu(&root_stud); 

	rm_all_students(&root_stud); // Clean up
}
