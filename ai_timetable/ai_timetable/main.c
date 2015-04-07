#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "course.h"
#include "public.h"
#include "person_data.h"

#define CURRENTYEAR 2014
void printTimeTable(struct __course *crs, int *code, int num);

int main() 
{
	struct __course course[NUMCOURSE];
	struct __public public[NUMPUBLIC];
	
	long st_num;
	__p_data *p_data = (__p_data*)malloc(sizeof(__p_data));;
	
	int avrMaj,lib,grade, i, j, k, l, m, n, o, p, q, count;
	int sem, credit;
	int tmp,temp = 0 ,maxp,maxL;
	int tmpTime, tmpTime2;
	// 0 <= courseIndex < 473
	int courseIndex[474], majorIndex[473], libIndex[473];
	int remainLib[7], firstLib = 0;
	int majorSelect[20], libSelect[20];
	int excp[1000], excn=0;
	//the array of cdbn, which user selected finally.
	//and the number of it.
	int userSelect[20], numberOfUserSelect;
	char key[10];
	int flag2 = 0;
	
	//import data from data/*.txt to each struct
	importCourseData(course);
	importPublicData(public);
	
	printf("Enter your student number : ");
	scanf("%ld", &st_num);
	
	printf("Enter how many semester did you finish : ");
	scanf("%d", &sem);

	printf("Enter how many credit in this semester : ");
	scanf("%d", &credit);

	// save User's data on p_data(structure)
	getPersonData(st_num, p_data);
	
	for(i=0;i<sem;i++)
	{
		for(j=0;j<p_data->course[i].cs_num;j++)
		{
			excp[excn++]=atoi(p_data->course[i].cs_code[j]);
		}
		
	}

	////// Calculate some data for recommend our result ////
	tmp=0;
	// Average major (count course, Not credit)
	for(i=0;i<sem;i++)
	{
		tmp+=p_data->course[i].major_num;
	}
	avrMaj=tmp/sem;   
	lib=credit-avrMaj*3;
	grade=sem/2+1;

	// Caculate finished lib
	for(i=0;i<6;i++)
	{
		if(i<5)
			remainLib[i]=2-p_data->complete[i+5];
		else if(i==5)
		{
			// After 2010, policy was changed
			if(st_num/10000>2010)
				remainLib[i]=6-p_data->complete[i+5];
			else if(st_num/10000<=2010)
				remainLib[i]=3-p_data->complete[i+5];
		}
	}
	
	/////////////////////////////////////////////////////////


	j=0,k=0,l=0, n=0;
	// Save all course that can apply in this semester.
	for(i=0;i<NUMCOURSE;i++)
	{
		if(course[i].grade==0 || course[i].grade==grade)
		{
			courseIndex[j]=i;
			j++;
		}
	}
	// Save major course that can apply in this semester.
	for(i=0;i<j;i++)
	{
		if(course[courseIndex[i]].chr==4 || course[courseIndex[i]].chr==1)
		{
			majorIndex[k]=courseIndex[i];
			k++;
		}
	}
	// Save liberal course that can apply in this semester.
	for(i=0;i<j;i++)
	{
		if(course[courseIndex[i]].chr==6 || course[courseIndex[i]].chr==6 || course[courseIndex[i]].chr==7 || course[courseIndex[i]].chr==8 || course[courseIndex[i]].chr==9 || course[courseIndex[i]].chr==10)
		{
			libIndex[n]=courseIndex[i];
			n++;
		}
	}
	/////////// Select Major by using user's own character///////
	maxp=-1,m=0;
	count=0;
	while(avrMaj>0)
	{
		for(l=0;l<k;l++)
		{
			if(majorIndex[l] == -1) continue;
			
			// Select major by preference of professor 
			if(p_data->professor[course[majorIndex[l]].prof]>maxp)
			{
				maxp=p_data->professor[course[majorIndex[l]].prof];
				temp=l;
			}
			// If preference is same, using preference of day
			if(p_data->professor[course[majorIndex[l]].prof]==maxp)
			{
				if(p_data->day[course[majorIndex[l]].class[0].day] > p_data->day[course[majorIndex[temp]].class[0].day])
				{
					temp=l;
				}
				
				for(p = 0; p < 2; p++) {
					for(q = 0; q < 2; q++) {
						// If preference is same, using preference of time
						if(p_data->day[course[majorIndex[l]].class[p].day]==p_data->day[course[majorIndex[temp]].class[q].day])
						{
							if(course[majorIndex[l]].class[p].day == 6 || course[majorIndex[temp]].class[q].day == 6) continue;
							
							if(course[majorIndex[l]].class[p].time[0] >=1 && course[majorIndex[l]].class[p].time[0] <= 7 )
								tmpTime=0;
							else if(course[majorIndex[l]].class[p].time[0] >=8 && course[majorIndex[l]].class[p].time[0] <=13 )
								tmpTime=1;
							else
								tmpTime=2;
							
							if(course[majorIndex[temp]].class[q].time[0] >=1 && course[majorIndex[temp]].class[q].time[0]<=7 )
								tmpTime2=0;
							else if(course[majorIndex[temp]].class[q].time[0] >=8 && course[majorIndex[temp]].class[q].time[0]<=13 )
								tmpTime2=1;
							else
								tmpTime2=2;
							
							if(p_data->time[tmpTime]<p_data->time[tmpTime2])
								temp=l;
						}
					}
				}
				
			}
		}
		if(flag2==0)
		{
			// Finally select the major
			majorSelect[m]=majorIndex[temp]; //courseø°µÈæÓ∞• ¿Œµ¶Ω∫¿˙¿Â
			majorIndex[temp]=-1;
			// reduce count
			avrMaj--;
			flag2++;
			m++;
		}
		else if(flag2!=0)
		{
			for(i=0;i<m;i++)
			{
				int flag = 0;
			
				for(p = 0; p < 2; p++) {
					for(q = 0; q < 2; q++) {
						if(course[majorIndex[temp]].class[p].day==course[majorSelect[i]].class[q].day)
						{
							if(course[majorIndex[temp]].class[p].day == 6 || course[majorSelect[i]].class[q].day == 6) continue;
							
							int st = course[majorIndex[temp]].class[p].time[0];
							int ed = course[majorIndex[temp]].class[p].time[1];
						
							if((st <= course[majorSelect[i]].class[q].time[0] && course[majorSelect[i]].class[q].time[0] <= ed)
							|| (st <= course[majorSelect[i]].class[q].time[1] && course[majorSelect[i]].class[q].time[1] <= ed)
							|| (st >= course[majorSelect[i]].class[q].time[0] && course[majorSelect[i]].class[q].time[1] >= ed))
							{
								// Remove from previous major index
								majorIndex[temp]=-1;
								flag = 1;
							}
						}
					}
				}
			
				if(!flag)
				{
					// Finally select the major
					
					for(p = 0; p < m; p++) {
						if (course[majorSelect[p]].code == course[majorIndex[temp]].code) {
							majorIndex[temp] = -1;
							break;
						}
					}
					
					if(majorIndex[temp] == -1) break;
					majorSelect[m]=majorIndex[temp]; //courseø°µÈæÓ∞• ¿Œµ¶Ω∫¿˙¿Â
					majorIndex[temp]=-1;
					// reduce count
					avrMaj--;
					flag2++;
					m++;
					
					break;
				}
			}
		}
		
		
		
		maxp=0, tmpTime=0, tmpTime2=0,temp=0;

		// If there are no matched major, break
		count++;
		if(count>473)
			break;
	}
	// Because there are no matched major, 
	// so we have to choice more liberal arts
	lib=lib+avrMaj*3;

	///////////////////////////////////Finish selecting major////

	//////////Selecting lib by using public data & individual char //
	maxL=-1,o=0;
	int ttemp=0;
	//Select first liberal arts for using cosign similarity
	//We choice max value from remain liberal arts credit
	for(i=0;i<n;i++)
	{
		if(remainLib[course[libIndex[i]].chr-5]>maxL)
		{
			maxL=remainLib[course[libIndex[i]].chr-5];
			firstLib=libIndex[i]; //courseø°µÈæÓ∞•¿Œµ¶Ω∫
			ttemp=i;
		}
		if(remainLib[course[libIndex[i]].chr-5]==maxL)
		{
			for(p = 0; p < 2; p++) {
				for(q = 0; q < 2; q++) {
					// If preference is same, using preference of time
					if(p_data->day[course[libIndex[l]].class[p].day]==p_data->day[course[libIndex[ttemp]].class[q].day])
					{
						if(course[libIndex[l]].class[p].day == 6 || course[libIndex[ttemp]].class[q].day == 6) continue;
						
						if(course[libIndex[l]].class[p].time[0] >=1 && course[libIndex[l]].class[p].time[0] <= 7 )
							tmpTime=0;
						else if(course[libIndex[l]].class[p].time[0] >=8 && course[libIndex[l]].class[p].time[0] <=13 )
							tmpTime=1;
						else
							tmpTime=2;
					
						if(course[libIndex[ttemp]].class[q].time[0] >=1 && course[libIndex[ttemp]].class[q].time[0]<=7 )
							tmpTime2=0;
						else if(course[libIndex[ttemp]].class[q].time[0] >=8 && course[libIndex[ttemp]].class[q].time[0]<=13 )
							tmpTime2=1;
						else
							tmpTime2=2;
					
						if(p_data->time[tmpTime]<p_data->time[tmpTime2])
							firstLib=libIndex[ttemp];
					}
				}
			}
		}
		
		//Make except array for selecting liberal arts
		if(remainLib[course[libIndex[i]].chr-5]<1 )
		{
			excp[excn++]=course[libIndex[i]].code;
			
		}
		
		
		for(p = 0; p < 2; p++) {
			for(q = 0; q < 2; q++) {
				if(course[libIndex[i]].class[p].day==course[majorSelect[i]].class[q].day) {
					if(course[libIndex[i]].class[p].day == 6 || course[majorSelect[i]].class[q].day == 6) continue;
					
					int st = course[libIndex[i]].class[p].time[0];
					int ed = course[libIndex[i]].class[p].time[1];
					
					if((st <= course[majorSelect[i]].class[q].time[0] && course[majorSelect[i]].class[q].time[0] <= ed)
						|| (st <= course[majorSelect[i]].class[q].time[1] && course[majorSelect[i]].class[q].time[1] <= ed)
						|| (st >= course[majorSelect[i]].class[q].time[0] && course[majorSelect[i]].class[q].time[1] >= ed))
					{
						excp[excn++]=course[libIndex[i]].code;
					}
				}
			}
		}
	}
	libSelect[o++]=firstLib;
	lib -= course[firstLib].score;
	excp[excn++]=course[firstLib].code;
	count=0;
	while(lib>0)
	{
		int cd;
		//get most similar course code (by using cosine similarity).
		cd = getMostSimilar(public, course[firstLib].code, excp,excn);
		
		for(i=0; i< NUMCOURSE; i++)
			if(cd == course[i].code) {
				firstLib = i;
				break;
			}
		
		//Update except array////////////////////////////////
		for(i=0;i<n;i++)
		{
			for(p = 0; p < 2; p++) {
				for(q = 0; q < 2; q++) {
					if(course[libIndex[i]].class[p].day==course[firstLib].class[q].day) {
						if(course[libIndex[i]].class[p].day == 6 || course[firstLib].class[q].day == 6) continue;
						
						int st = course[libIndex[i]].class[p].time[0];
						int ed = course[libIndex[i]].class[p].time[1];
						
						if((st <= course[firstLib].class[q].time[0] && course[firstLib].class[q].time[0] <= ed)
						   || (st <= course[firstLib].class[q].time[1] && course[firstLib].class[q].time[1] <= ed)
						   || (st >= course[firstLib].class[q].time[0] && course[firstLib].class[q].time[1] >= ed))
						{
							excp[excn++]=course[libIndex[i]].code;
						}
					}
				}
			}
		}
		excp[excn++]=course[firstLib].code;
		////////////////////////////////////////////////
		libSelect[o++]=firstLib;
		lib = lib - course[firstLib].score;
		
		count++;
		// If there are no matched liberal arts, break
		if(count>474)
			break;
	}
	/////////////////////////////Finish selecting liberal arts ///////

	// Combine major with liberal arts
	for(i=0;i<m;i++)
		userSelect[i]=majorSelect[i];
	for(i=0;i<o;i++)
		userSelect[m-1+i]=libSelect[i];
	numberOfUserSelect=m+o-1;

	printTimeTable(course,userSelect, numberOfUserSelect);
	
	printf("Do you want select this time table ? [y or n] : ");
	scanf("%s",key);

	if(key[0]=='y')
	{
		//...After finish all routine and when user select a time table.
		p_data->course[sem].enrolled = 1;
      p_data->course[sem].year = grade;
      p_data->course[sem].semester = 2;

      for(i = 0; i < m+o-1; i++) {
         for(j = 0; j < 11; j++) 
            if(course[userSelect[i]].chr == j)
               p_data->complete[j] += course[userSelect[i]].score;

         for(j = 0; j < 16; j++)
            if(course[userSelect[i]].prof == j)
               p_data->professor[j] += 1;

         for(j = 0; j < 6; j++) 
            for(k = 0; k < 2; k++)
               if(course[userSelect[i]].class[k].day == j)
                  p_data->day[j] += 1;
         
         for(j = 0; j < 2; j++) {
            if(course[userSelect[i]].class[j].time[0] <= 7) {
               p_data->time[0] += 1;
               if(course[userSelect[i].class[j].time[1] > 7) {
                  p_data->time[1] += 1;
                  if(course[userSelect[i].class[j].time[1] > 13)
                     p_data->time[2] += 1;
               }
            }
            else if(course[userSelect[i]].class[j].time[0] <= 13) {
               p_data->time[1] += 1;
               if(course[userSelect[i]] > 13)
                  p_data->time[2] += 1;
            }
            else 
               p_data->time[2] += 1;
         }

         if(course[userSelect[i]].chr <= 4)
            p_data->course[sem].major_num += 1;
         else 
            p_data->course[sem].liber_num += 1;

      }

      p_data->course[sem].cs_num = p_data->course[sem].major_num + p_data->course[sem].liber_num;
      for(i = 0; i< p_data->course[sem].cs_num; i++)
         p_data->course[sem].cs_code[j] = itoa(course[userSelect[i]].code);
		updatePersonData(st_num, p_data);
		updatePublicData(public, userSelect, numberOfUserSelect);
		exportPublicData(public);
	}

	free(p_data);
	return 0;
}

void printTimeTable(struct __course *crs, int *code, int num) {
	int i, j;
	
	printf("\n");
	for(i = 0; i < num; i++) {
		printf("%06d : %s %d분반\n         ", crs[code[i]].code, crs[code[i]].name, crs[code[i]].no);
		
		for(j = 0; j < 2; j++) {
			if(crs[code[i]].class[j].day < 6)
				printf("%s %02d - %02d%s",
					   dayweek[crs[code[i]].class[j].day],
					   crs[code[i]].class[j].time[0],
					   crs[code[i]].class[j].time[1],
					   (j == 0 ? " / " : "\n"));
		}
	}
	
	printf("\n");
}