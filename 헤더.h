#pragma once
#define MAX 10
#define	true	1
#define	false	0

typedef struct {
	int basic; //기본요금
	double add; //전력량 요금
}data;

typedef	struct {
	int		year;	//년
	int		month;  //월
	int		elec;   //전력량
	int		pay;    //전기 요금
} PayRecord;

PayRecord r[MAX];
data arr[6];


int elec_cal(int year, int month, int elec);//입력된 년/월의 전기요금 계산
int special_cal(int year, int month, int elec);//2016년 7, 8월에는 50kWh인하된 조건으로 전기요금 계산
int num_record(char *fname);//저장한 전기요금 데이터 개수를 셈
void search_year(int year);//입력한 년도의 전기 요금합계 계산해서 출력
void search_month(int year, int month);//년/월 검색시 해당 월의 전기요금찾아서 출력
void safe(int year, int month, int elec, int total);//각 월 별 전기요금 csv파일로 저장
void open_file(char *fname);//csv파일 출력