#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "public.h"

void importPublicData(struct __public *pub) {
	FILE *file;
	int i, j;
	
	file = fopen("data/public.txt", "r");
	
	for(i = 0; i < NUMPUBLIC; i++) {
		fscanf(file, "%d", &pub[i].code);
		fscanf(file, "%hd", &pub[i].length);
		
		for(j = 0; j < NUMPUBLIC; j++)
			fscanf(file, "%hd", &pub[i].vector[j]);
	}
	
	fclose(file);
}

int getMostSimilar(struct __public *pub, int code, int *excp, int excn) {
	int src = 0, ret = -1;
	double sim = 0.0;
	
	int *excpdbn = (int *) malloc(sizeof(int) * excn);
	
	int i, j;
	
	while(pub[src].code != code && src < NUMPUBLIC) src++;
	if(src == NUMPUBLIC) return -1;
	
	for(i = 0; i < excn; i++) {
		for(j = 0; j < NUMPUBLIC; j++) {
			if(excp[i] == pub[j].code) {
				excpdbn[i] = j;
				break;
			}
		}
		
		excpdbn[i] = -1;
	}
	
	for(i = 0; i < NUMPUBLIC; i++) {
		double temp;
		int num = 0;
		
		if(i == src) continue;
		
		for(j = 0; j < excn; j++)
			if(i == excpdbn[j]) continue;
		
		if(pub[src].length * pub[i].length == 0) continue;
		
		for(j = 0; j < NUMPUBLIC; j++)
			if(pub[src].vector[j] == 1 && pub[i].vector[j] == 1) num++;
		
		temp = num/sqrt(pub[src].length * pub[i].length);
		if(temp > sim) { sim = temp; ret = i; }
	}
	
	if(ret == -1) return 0;
	return pub[ret].code;
}

void updatePublicData(struct __public *pub, int *code, int num) {
	int *ptr = (int *) malloc(sizeof(int) * num);
	int i, j;
	
	for(i = 0; i < num; i++) {
		for(j = 0; j < NUMPUBLIC; j++)
			if(pub[j].code == code[i]) { ptr[i] = j; break; }
		
		if(j == NUMPUBLIC) ptr[i] = -1;
	}
	
	for(i = 0; i < num-1; i++) {
		if(ptr[i] == -1) continue;
		for(j = i+1; j < num; j++) {
			if(ptr[j] == -1) continue;
			pub[ptr[i]].vector[ptr[j]] = pub[ptr[j]].vector[ptr[i]] = 1;
		}
	}
	
	for(i = 0; i < num; i++) {
		short len = 0;
		
		if(ptr[i] == -1) continue;
		for(j = 0; j < NUMPUBLIC; j++)
			if(pub[ptr[i]].vector[j] == 1) len++;
		
		pub[ptr[i]].length = len;
	}
}

void exportPublicData(struct __public *pub) {
	FILE *file;
	int i, j;
	
	file = fopen("data/public.txt", "w");
	
	for(i = 0; i < NUMPUBLIC; i++) {
		fprintf(file, "%06d ", pub[i].code);
		fprintf(file, "%03hd ", pub[i].length);
		
		for(j = 0; j < NUMPUBLIC; j++)
			fprintf(file, "%hd%c", pub[i].vector[j], (j == NUMPUBLIC-1 ? '\n' : ' '));
	}
	
	fclose(file);
}