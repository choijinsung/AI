typedef struct {
	int enrolled;
	int year;
	int semester;
	int major_num;
	int liber_num;
	int cs_num;
	char cs_code[20][10];
} __course;

typedef struct {
	int complete[11];
	int professor[16];
	int day[7];
	int time[3];
	__course course[10];
} __p_data;

void getPersonData(long, __p_data *p_data);
void updatePersonData(long, __p_data *p_data);