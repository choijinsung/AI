#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "person_data.h"

void getPersonData(long, __p_data *p_data);
void updatePersonData(long, __p_data *p_data);

void getPersonData(long st_num, __p_data *p_data) {
	FILE *file;
	char loc[100] = "data/\0";
	char stnum_buf[20];
	char str[20];
	int element, elem_num;
	int i = 0;

	sprintf(stnum_buf, "%ld", st_num);
	strcat(stnum_buf, ".txt");
	strcat(loc, stnum_buf);
	
	if((file = fopen(loc, "r")) == NULL) {
		printf("File opening failed.\n");
		exit(1);
	}

	fscanf(file, "%s", str);
	if(!strcmp(str, "<complete>")) {
		elem_num = 11;
		while(elem_num--) {
			fscanf(file, "%d", &element);
			fscanf(file, "%d", &p_data->complete[element]);
		}
	}
	
	fscanf(file, "%s", str);
	if(!strcmp(str, "<professor>")) {
		elem_num = 16;
		while(elem_num--) {
			fscanf(file, "%d", &element);
			fscanf(file, "%d", &p_data->professor[element]);
		}
	}
	
	fscanf(file, "%s", str);
	if(!strcmp(str, "<day>")) {
		elem_num = 6;
		while(elem_num--) {
			fscanf(file, "%d", &element);
			fscanf(file, "%d", &p_data->day[element]);
		}
	}

	fscanf(file, "%s", str);
	if(!strcmp(str, "<time>")) {
		elem_num = 3;
		while(elem_num--) {
			fscanf(file, "%d", &element);
			fscanf(file, "%d", &p_data->time[element]);
		}
	}
	
	fscanf(file, "%s", str);
	if(!strcmp(str, "<course>")) {
		elem_num = 10;
		
		while(elem_num--) {
			fscanf(file, "%d", &element);
			fscanf(file, "%d", &p_data->course[element].year);
			
			if(p_data->course[element].year == 0) {
				p_data->course[element].enrolled = 0;
				continue;
			}
			
			p_data->course[element].enrolled = 1;

			fscanf(file, "%d", &p_data->course[element].semester);
			fscanf(file, "%d", &p_data->course[element].major_num);
			fscanf(file, "%d", &p_data->course[element].liber_num);
			fscanf(file, "%d", &p_data->course[element].cs_num);

			for(i = 0; i < p_data->course[element].cs_num; i++)
				fscanf(file, "%s", p_data->course[element].cs_code[i]);
		}
	}

	fclose(file);
}

void updatePersonData(long st_num, __p_data *p_data) {
	FILE *file;
	char loc[100] = "data/\0";
	char stnum_buf[20];
	int i = 0, j = 0;

	sprintf(stnum_buf, "%ld", st_num);
	strcat(stnum_buf, ".txt");
	strcat(loc, stnum_buf);

	if((file = fopen(loc, "w")) == NULL) {
		printf("File opening failed.\n");
		exit(1);
	}

	fprintf(file, "<complete>\n");
	for(i = 0; i < 11; i++)
		fprintf(file, "%d %d\n", i, p_data->complete[i]);
	
	fprintf(file, "<professor>\n");
	for(i = 0; i < 16; i++)
		fprintf(file, "%d %d\n", i, p_data->professor[i]);
	
	fprintf(file, "<day>\n");
	for(i = 0; i < 6; i++)
		fprintf(file, "%d %d\n", i, p_data->day[i]);

	fprintf(file, "<time>\n");
	for(i = 0; i < 3; i++)
		fprintf(file, "%d %d\n", i, p_data->time[i]);

	fprintf(file, "<course>\n");
	for(i = 0; i < 10; i++) {
		if(p_data->course[i].enrolled == 0) {
			fprintf(file, "%d 0\n", i);
			continue;
		}
		fprintf(file, "%d %d %d ", i, p_data->course[i].year, p_data->course[i].semester);
		fprintf(file, "%d %d %d ", p_data->course[i].major_num, p_data->course[i].liber_num, p_data->course[i].cs_num);
		for(j = 0; j < p_data->course[i].cs_num; j++)
			fprintf(file, "%s ", p_data->course[i].cs_code[j]);
		fprintf(file, "\n");
	}
	fprintf(file, "<EOF>");
	fclose(file);
}