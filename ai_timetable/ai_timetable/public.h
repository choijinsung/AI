#include <stdbool.h>

//number of each data
#define NUMPUBLIC		214

struct __public {
	int code;
	short vector[NUMPUBLIC];
	short length;
	bool available;
};

void importPublicData(struct __public *pub);
int getMostSimilar(struct __public *pub, int code, int *excp, int excn);
void updatePublicData(struct __public *pub, int *code, int num);
void exportPublicData(struct __public *pub);