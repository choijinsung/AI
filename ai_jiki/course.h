#include <stdbool.h>

#define MINI(a,b) (((a) < (b)) ? (a) : (b))
#define MAXI(a,b) (((a) > (b)) ? (a) : (b))

//number of each data
#define NUMCOURSE		473
#define NUMCHARACTER	11
#define NUMDAYWEEK		6
#define NUMBUILDING		16

#define NUMMAJOR		5

struct __class {
	int day, time[2];
	int dept;
	char room[20];
};

struct __course {
	short grade, chr, score;
	bool abeek;
	int code, no;
	char name[60], prof[60], etc[200];
	struct __class class[2];
};

static const char *crsCharacter[11] = {
	"교양기초",			"학부(과)기초",		"계열교양",
	"교양선택",			"전공선택",
	
	"교양(문학언어)",		"교양(역사철학)",		"교양(정경사세)",
	"교양(과학기술자연)",	"교양(예체능계)",		"교양(인성교육)"
};

static const char *dayweek[6] = {
	"월", "화", "수", "목", "금", "토"
};

static const char *building[16] = {
	"7호관", "예술관", "종합복지관", "테니스장", "공학관", "경상관", "국제관B동", "국제관A동",
	"체육관", "과학관", "법학관", "본부관", "형설관", "조형관", "북악관", "명원민속관"
};

void importCourseData(struct __course *crs);

//WARNING : FOR DEVELOPER ONLY BELOW. DON'T USE IT!!!
//void exportPublicData(struct __course *crs);