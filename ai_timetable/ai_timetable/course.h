#include <stdbool.h>

#define MINI(a,b) (((a) < (b)) ? (a) : (b))
#define MAXI(a,b) (((a) > (b)) ? (a) : (b))

//number of each data
#define NUMCOURSE		473
#define NUMCHARACTER	11
#define NUMDAYWEEK		6
#define NUMBUILDING		16
#define NUMCSPROF		16

#define NUMMAJOR		5

//etc types
//#define TABLE			0
//#define TDISABLE		1
//
//struct __etc {
//	int type;
//	int major;
//	int grade;
//};

struct __class {
	int day, time[2];
	int dept;
	char room[20];
};

struct __course {
	short grade, chr, score;
	bool abeek;
	int code, no, prof;
	char name[60], etc[200];
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

static const char *csprof[16] = {
	"이상환", "강승식", "김상철", "김영만", "김준호", "김혁만", "우종우", "윤명근", "윤상민",
	"윤성혜", "임성수", "임은진", "최준수", "한광수", "한재일", "황선택"
};

void importCourseData(struct __course *crs);