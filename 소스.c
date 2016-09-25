#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "���.h"

void main()
{
	char c;
	int year;
	int month;
	int elec;
	int i = 0;
	int total;
	open_file("data.csv");


	printf("******* Command *******\n");
	printf("1: ���� ��� ���\n2: �⵵ �� ���� ��� �˻�\n3: �� �� ���� ��� �˻�\nQ: ����\n");
	printf("***********************\n");

	while (1)
	{
		printf("\nCommand > ");
		c = getch();
		putch(c);
		c = toupper(c);

		switch (c)
		{
		case '1': //�Էµ� ���� ������ ���
		
			printf("\n�⵵�� ���� �Է��ϼ��� : ");
			scanf("%d %d", &year, &month);
			printf("���� ��뷮�� �Է��ϼ��� : ");
			scanf("%d", &elec);

			if ((year == 2016 && month == 7) || (year == 2016 && month == 8)) {//2016�� 7, 8���� �����ܰ豸���� 50kWh���ϵ� �������� ��� ���
				total = special_cal(year, month, elec);
				printf("���� ��� : %d��\n", total);
				safe(year, month, elec, total);
			}
			else {
				total = elec_cal(year, month, elec);
				printf("���� ��� : %d��\n", total);
				safe(year, month, elec, total);
			}
			break;
		case '2'://�Էµ� �⵵�� ���� ��� �հ�
			printf("\n�⵵�� �Է��ϼ��� : ");
			scanf("%d", &year);
			search_year(year);
			break;
		case '3'://�Էµ� ���� ���� ���� ���
			printf("\n�⵵�� ���� �Է��ϼ��� : ");
			scanf("%d %d", &year, &month);
			search_month(year, month);
			break;

		case 'Q'://���α׷� ����
			printf("\n");
			exit(1);
		default:
			printf("�߸��� ��ɾ��Դϴ�.\n"); 	//�˸��� ���� ���� �Է��� ��� 
			break;
		}
	}

	

}
void open_file(char *fname)
{
	int i;
	FILE *fp;
	if ((fp = fopen(fname, "r")) == NULL)
	{
		printf("File Reading failed! \n");
		exit(1);
	}
	for (i = 0; i<6; i++)
	{
		fscanf(fp, "%d, %lf", &arr[i].basic, &arr[i].add);
		//printf("%d, %.1f\n", arr[i].basic, arr[i].add);
	}
	fclose(fp);
	return;
}
int elec_cal(int year, int month, int elec)
{

	int total;
	int i;
	if (elec <= 100)
		total = arr[0].basic + elec*arr[0].add;
	if (elec > 100 && elec <= 200)
		total = arr[1].basic + 100 * arr[0].add + (elec - 100)*arr[1].add;
	if (elec > 200 && elec <= 300)
		total = arr[2].basic + 100 * arr[0].add + 100 * arr[1].add + (elec - 200)*arr[2].add;
	if (elec > 300 && elec <= 400)
		total = arr[3].basic + 100 * arr[0].add + 100 * arr[1].add + 100 * arr[2].add + (elec - 300)*arr[3].add;
	if (elec > 400 && elec <= 500)
		total = arr[4].basic + 100 * arr[0].add + 100 * arr[1].add + 100 * arr[2].add + 100 * arr[3].add + (elec - 400)*arr[4].add;
	if (elec > 500)
		total = arr[5].basic + 100 * arr[0].add + 100 * arr[1].add + 100 * arr[2].add + 100 * arr[3].add + 100 * arr[4].add + (elec - 500)*arr[5].add;

	return total;
}
int special_cal(int year, int month, int elec)
{
	int total;
	int i;
	if (elec <= 50)
		total = arr[0].basic + elec*arr[0].add;
	if (elec > 50 && elec <= 150)
		total = arr[1].basic + 50 * arr[0].add + (elec - 50)*arr[1].add;
	if (elec > 150 && elec <= 250)
		total = arr[2].basic + 50 * arr[0].add + 50 * arr[1].add + (elec - 150)*arr[2].add;
	if (elec > 250 && elec <= 350)
		total = arr[3].basic + 50 * arr[0].add + 50 * arr[1].add + 50 * arr[2].add + (elec - 250)*arr[3].add;
	if (elec > 350 && elec <= 450)
		total = arr[4].basic + 50 * arr[0].add + 50 * arr[1].add + 50 * arr[2].add + 50 * arr[3].add + (elec - 350)*arr[4].add;
	if (elec > 450)
		total = arr[5].basic + 50 * arr[0].add + 50 * arr[1].add + 50 * arr[2].add + 50 * arr[3].add + 100 * arr[4].add + (elec - 450)*arr[5].add;

	return total;
}
void safe(int year, int month, int elec, int total)
{
	FILE *ofp;
	fopen_s(&ofp, "result.csv", "a");
	fprintf(ofp, "%d, %d, %d, %d\n", year, month, elec, total);

	fclose(ofp);
}
int num_record(char *fname)
{
	int num_record;
	int i = 0;
	int sum = 0;
	FILE *ifp;
	if ((ifp = fopen("result.csv", "r")) == NULL) {
		printf("No such file ! \n");
		exit(1);
	}
	while (fscanf(ifp, "%d, %d, %d, %d\n", &r[i].year, &r[i].month, &r[i].elec, &r[i].pay) == 4) {
		i++;

	}
	num_record = i;

	return num_record;
	fclose(ifp);
}
void search_year(int year)
{
	int sum = 0;
	for (int j = 0; j < num_record("result.csv"); j++) {
		if (r[j].year==year)
		{
			sum += r[j].pay;
		}	
	}

	printf("%d��\n", sum);
	
}
void search_month(int year, int month)
{
	for (int i = 0; i < num_record("result.csv"); i++) {
		if (r[i].year == year && r[i].month == month)
		{
			printf("%d��\n", r[i].pay);
			break;
		}
	
	}
}