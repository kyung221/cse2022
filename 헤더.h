#pragma once
#define MAX 10
#define	true	1
#define	false	0

typedef struct {
	int basic; //�⺻���
	double add; //���·� ���
}data;

typedef	struct {
	int		year;	//��
	int		month;  //��
	int		elec;   //���·�
	int		pay;    //���� ���
} PayRecord;

PayRecord r[MAX];
data arr[6];


int elec_cal(int year, int month, int elec);//�Էµ� ��/���� ������ ���
int special_cal(int year, int month, int elec);//2016�� 7, 8������ 50kWh���ϵ� �������� ������ ���
int num_record(char *fname);//������ ������ ������ ������ ��
void search_year(int year);//�Է��� �⵵�� ���� ����հ� ����ؼ� ���
void search_month(int year, int month);//��/�� �˻��� �ش� ���� ������ã�Ƽ� ���
void safe(int year, int month, int elec, int total);//�� �� �� ������ csv���Ϸ� ����
void open_file(char *fname);//csv���� ���