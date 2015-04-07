#include <stdio.h>

#include "course.h"
#include "public.h"

int main() {
	struct __course course[NUMCOURSE];
	struct __public public[NUMPUBLIC];
	
	// 0<= cdbn < 473
	int cdbn1 = 3, cdbn2;
	
	//the array of cdbn, which user selected finally.
	int userSelect[20];
	
	//and the number of it.
	int numberOfUserSelect;
	
	//!!!!!NOTE!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!//
	//																		//
	//		Use struct __course element number, not real course code.		//
	//		for example, in case of 'course[3].code : 573'					//
	//		use 3, not 573 (and i'm calling it, cdbn)						//
	//																		//
	//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!END!!!!!//
	
	//import data from data/*.txt to each struct
	importCourseData(course);
	importPublicData(public);
	
	//get the cdbn of a course which is most similar with the course with cdbn1.
	cdbn2 = getMostSimilar(public, cdbn1);
	
	
	//...After finish all routine and when user select a time table.
	updatePublicData(public, userSelect, numberOfUserSelect);
	
	
	return 0;
}