#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "public.h"

void importPublicData(struct __public *pub) {
	FILE *file;
	int i, j;
	
	file = fopen("data/public.txt", "r");
	
	for(i = 0; i < NUMPUBLIC; i++) {
		fscanf(file, "%d", &pub[i].cdbn);
		
		for(j = 0; j < NUMPUBLIC; j++)
			fscanf(file, "%hd", &pub[i].vector[j]);
	}
	
	fclose(file);
}

int getMostSimilar(struct __public *pub, int cdbn) {
	int src = 0, ret = -1;
	double sim = 0.0;
	
	int i, j;
	
	while(pub[src].cdbn != cdbn || src < NUMPUBLIC) src++;
	if(src == NUMPUBLIC) return -1;
	
	for(i = 0; i < NUMPUBLIC; i++) {
		double temp;
		int num = 0;
		
		if(i == src) continue;
		if(pub[src].length * pub[i].length == 0) continue;
		
		for(j = 0; j < NUMPUBLIC; j++)
			if(pub[src].vector[j] == 1 && pub[i].vector[j] == 1) num++;
		
		temp = num/sqrt(pub[src].length * pub[i].length);
		if(temp > sim) { sim = temp; ret = i; }
	}
	
	return pub[ret].cdbn;
}

void updatePublicData(struct __public *pub, int *cdbn, int num) {
	int *ptr = (int *) malloc(sizeof(int *) * num);
	int i, j;
	
	for(i = 0; i < num; i++)
		for(j = 0; j < NUMPUBLIC; j++)
			if(pub[j].cdbn == cdbn[i]) { ptr[i] = j; break; }
	
	for(i = 0; i < num-1; i++)
		for(j = i+1; j < num; j++)
			pub[ptr[i]].vector[ptr[j]] = pub[ptr[j]].vector[ptr[i]] = 1;
}