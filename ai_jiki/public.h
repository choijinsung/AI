#include <stdbool.h>

//number of each data
#define NUMPUBLIC		214

struct __public {
	int cdbn; //course db number
	short vector[NUMPUBLIC];
	short length;
	bool available;
};

void importPublicData(struct __public *pub);
int getMostSimilar(struct __public *pub, int cdbn);
void updatePublicData(struct __public *pub, int *cdbn, int num);

//jiki's memo
//
//calculate the length of a vector only when
//one or more element(s) (of the vector) got changed.