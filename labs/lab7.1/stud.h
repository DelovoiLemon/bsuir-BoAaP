#pragma once
#ifndef STUD
#define STUD

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ncurses.h>

enum subjects { phys = 0, inform = 1, math = 2, subj_count = 3 };

typedef struct stud {
	char name[64];
	int group;
	int subjs[subj_count];
	double avg;
	struct stud *next;
} student;

typedef int (*read_func)(student *, FILE *);
typedef int (*out_func)(const student *, int, int, FILE *);
typedef int (*stud_cmp)(const student *, const char *name, const int mark, const int subject);


double calc_avg_mark(int *subjs, size_t subj_c);
int init_student(student **stud, read_func read_stud, FILE *file);
int add_student(student *stud, read_func read_stud, FILE *file);
int get_count(const student *stud);
int edit_student(student *stud, size_t num, read_func read_stud);
int rm_student(student **stud_root, size_t num);
void rm_all_students(student **stud_root);
int print_stud(const student *stud, int num, int left, FILE *file);
int save_stud(const student *stud, int num, int left, FILE *file);
int put_studs(const student *stud, out_func put_stud, FILE *file);
int read_from_term(student *stud, FILE *file);
int read_from_file(student *stud, FILE *file);
size_t choose_menu(student *stud);
void build_menu(student **stud);
void filtering_menu(student **stud);


#endif