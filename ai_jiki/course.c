#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "course.h"

void parseCourse(struct __course *crs, char *str);
void parseClass(struct __class *cls, char *str);

void importCourseData(struct __course *crs) {
	FILE *file;
	char str[2000], dump;
	int i = 0;
	
	file = fopen("data/courses.txt", "r");
	
	for(i = 0; i < NUMCOURSE; i++) {
		fscanf(file, "%[^\n]s", str);
		fscanf(file, "%c", &dump);
		
		parseCourse(&crs[i], str);
	}
	
	fclose(file);
}

void parseCourse(struct __course *crs, char *str) {
	char *tok, temp[200];
	int i;
	
	crs->abeek = false;
	
	tok = strtok(str, "/");
	
	for(i = 0; i < 9; i++) {
		switch (i) {
			case 0 : crs->grade = atoi(tok);	break;
			case 1 : crs->chr = atoi(tok);		break;
			case 2 : crs->code = atoi(tok);		break;
			case 3 : strcpy(crs->name, tok);	break;
			case 4 : crs->no = atoi(tok);		break;
			case 5 : strcpy(crs->prof, tok);	break;
			case 6 : crs->score = atoi(tok);	break;
			case 7 : strcpy(temp, tok);			break;
			case 8 : strcpy(crs->etc, tok);
		}
		
		tok = strtok(NULL, "/");
	}
	
	if(strstr(crs->name, "공학인증")) crs->abeek = true;
	parseClass(crs->class, temp);
	if(crs->etc[0] == '\r') crs->etc[0] = '\0'; //for windows only.
}

void parseClass(struct __class *cls, char *str) {
	char tok[4][50], *temp;
	int i, j;
	
	cls[0].day = cls[1].day = -1;
	if(str[0] == 'x') return;
	
	strcpy(tok[0], strtok(str, " \0"));
	
	for(i = 1; i < 4; i++) {
		if(!(temp = strtok(NULL, " \0"))) tok[i][0] = '\0';
		else strcpy(tok[i], temp);
	}
	
	for(i = 0; i < 2; i++) {
		if(tok[i*2][0] == '\0') continue;
		
		for(j = 0; j < 6; j++) {
			if(strstr(tok[i*2], dayweek[j])) {
				char *time = tok[i*2] + strlen(dayweek[j]);
				int st = 0, ed = 0, t;
				
				cls[i].day = j;
				cls[i].time[0] = 30;
				cls[i].time[1] = -1;
				
				for(t = 0; time[t] != '\0'; t++) {
					if(time[t] == ',') continue;
					
					if('0' <= time[t] && time[t] <= '9') {
						st = (time[t]-'0') * 2;
						ed = st+1;
					}
					else if('A' <= time[t] && time[t] <= 'I') {
						st = (time[t]-'A') * 3 + 2;
						ed = st+2;
					}
					
					cls[i].time[0] = MINI(cls[i].time[0], st);
					cls[i].time[1] = MAXI(cls[i].time[1], ed);
				}
				
				break;
			}
		}
		
		for(j = 0; j < 16; j++) {
			if(strstr(tok[i*2+1], building[j])) {
				cls[i].dept = j;
				strcpy(cls[i].room, tok[i*2+1]);
				break;
			}
		}
	}
}

//WARNING : FOR DEVELOPER ONLY BELOW. DON'T USE IT!!!
//void exportPublicData(struct __course *crs) {
//	FILE *file;
//	int i = 0, dump = -1, j = 0;
//	
//	file = fopen("data/public.txt", "w");
//	
//	for(i = 0; i < NUMCOURSE; i++) {
//		if(crs[i].chr < NUMMAJOR) continue;
//		if(crs[i].code != dump) {
//			dump = crs[i].code;
//			
//			fprintf(file, "%3d ", i);
//			
//			for(j = 0; j < 214; j++)
//				fprintf(file, "%d%c", 0, (j == 213 ? '\n' : ' '));
//		}
//	}
//	
//	fclose(file);
//}