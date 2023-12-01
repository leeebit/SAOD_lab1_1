//#define _CRT_SECURE_NO_WARNINGS

#define NUMBER 60
#define FIO_LENGTH 15

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct StudentData {
	int ID;
	char name[FIO_LENGTH];
	char surname[FIO_LENGTH];
	char patronymic[FIO_LENGTH];
	int book_number;
	int mark_first;
	int mark_second;
	int mark_third;
	int mark_fourth;
	int mark_fifth;

};

int read_file(const char filename[], StudentData Student[], int& number) {
	FILE* f = 0;

	if (fopen_s(&f, filename, "r") != 0)
		return -1;
	while (number < 10)//feof(f) == 0)
	{
		number++;

		fscanf_s(f, "%d %s %s %s %d %d %d %d %d %d\n", &Student[number].ID, Student[number].surname, FIO_LENGTH, Student[number].name, FIO_LENGTH,
			Student[number].patronymic, FIO_LENGTH, &Student[number].book_number, &Student[number].mark_first,
			&Student[number].mark_second, &Student[number].mark_third, &Student[number].mark_fourth,
			&Student[number].mark_fifth);

	}

	number++;

	fclose(f);

	return 0;
}

void print_table(StudentData Student[], int& number) {
	printf("-----------------------------------------------------------------------------\n");
	printf("|%-2s|", "N");
	printf("%-15s|", "SURNAME");
	printf("%-10s|", "NAME");
	printf("%-15s|", "MIDDLENAME");
	printf("%-10s|", "RECORDBOOK");
	printf("%-2s|", "IT");
	printf("%-4s|", "MATH");
	printf("%-2s|", "PE");
	printf("%-3s|", "RUS");
	printf("%-3s|\n", "ENG");

	for (int i = 0; i < number - 1; i++)
	{
		printf("-----------------------------------------------------------------------------\n");
		printf("|%2d|", i);
		printf("%15s|", Student[i].surname);
		printf("%10s|", Student[i].name);
		printf("%15s|", Student[i].patronymic);
		printf("%10d|", Student[i].book_number);
		printf("%2d|%4d|%2d|%3d|%3d|\n", Student[i].mark_first, Student[i].mark_second, Student[i].mark_third, Student[i].mark_fourth, Student[i].mark_fifth);
	}
	printf("-----------------------------------------------------------------------------\n");

}

void change(StudentData Student[], int i, int j)
{
	StudentData temp = Student[i];
	Student[i] = Student[j];
	Student[j] = temp;
}

void sort_surname(StudentData Student[], int& number) {
	bool flag = true;
	while (flag)
	{
		flag = false;
		for (int i = 0; i < number - 1; i++)
			if (strcmp(Student[i].surname, Student[i + 1].surname) > 0)
			{
				change(Student, i, i + 1);
				flag = true;
			}
	}
}

void sort_subject(StudentData Student[], int& number) {
	int choice = 0;
	bool flag = true;
	do {
		printf_s("1 - IT\n 2 - MATH\n 3-PE\n 4-RUS\n 5-ENG");
		printf_s("Enter your choice:");
		scanf_s("%d", &choice);
	} while (choice == 1 && choice == 2 && choice == 3 && choice == 4 && choice == 5);

	switch (choice) {
	case 1:
		while (flag)
		{
			flag = false;
			for (int i = 0; i < number - 1; i++)
				if (Student[i].mark_first < Student[i + 1].mark_first)
				{
					change(Student, i, i + 1);
					flag = true;
				}
		}
		break;
	case 2:
		while (flag)
		{
			flag = false;
			for (int i = 0; i < number - 1; i++)
				if (Student[i].mark_second < Student[i + 1].mark_second)
				{
					change(Student, i, i + 1);
					flag = true;
				}
		}
		break;
	case 3:
		while (flag)
		{
			flag = false;
			for (int i = 0; i < number - 1; i++)
				if (Student[i].mark_third < Student[i + 1].mark_third)
				{
					change(Student, i, i + 1);
					flag = true;
				}
		}
	case 4:
		while (flag)
		{
			flag = false;
			for (int i = 0; i < number - 1; i++)
				if (Student[i].mark_fourth < Student[i + 1].mark_fourth)
				{
					change(Student, i, i + 1);
					flag = true;
				}
		}
	case 5:
		while (flag)
		{
			flag = false;
			for (int i = 0; i < number - 1; i++)
				if (Student[i].mark_fifth < Student[i + 1].mark_fifth)
				{
					change(Student, i, i + 1);
					flag = true;
				}
		}
	}
}

void find_surname(StudentData Student[], int number, char buffer[])
{
	StudentData dopStudentList[NUMBER / 5];
	int dopStudentCount = 0;

	for (int i = 0; i < number; i++)
		if (strcmp(Student[i].surname, buffer) == 0)
			dopStudentList[dopStudentCount++] = Student[i];
	dopStudentCount++;

	if (dopStudentCount > 1)
		print_table(dopStudentList, dopStudentCount);

	else
		printf_s("There is no such surname.\n");

	system("pause");
}

void get_surname(char buffer[])
{
	printf_s("Enter surname: ");

	scanf_s("%s", buffer, NUMBER);
}

void average_mark(StudentData Student[], int number, int &sum, double &max) {

	double average_mark[5] = {0};
	for (int i = 0; i < 5; i++) {
		sum = 0;
		for (int j = 0; j < number-1; j++) {
			if (i == 0) 
			sum += Student[j].mark_first;
			
			if(i==1)sum += Student[j].mark_second;
				
			if(i== 2) sum += Student[j].mark_third;
				
			if(i==3) sum += Student[j].mark_fourth;
			
			if(i== 4) sum += Student[j].mark_fifth;
			
			
		}average_mark[i] = (double)sum / 10;
		if (average_mark[i] > max)
			max = average_mark[i];
	}
	printf("IT - %lf\n", average_mark[0]);
	printf("MATH - %lf\n", average_mark[1]);
	printf("PE - %lf\n", average_mark[2]);
	printf("RUS - %lf\n", average_mark[3]);
	printf("ENG - %lf\n", average_mark[4]);
	printf("Max average ball - %lf\n", max);
}

int main()
{

	StudentData Student[NUMBER];
	int number = -1;
	int choice = 0;
	char buffer[NUMBER];
	int sum = 0;
	double max = 0;

	if (read_file("Date.txt", Student, number) == -1)
	{
		printf_s("Error opening file!\n");
		return -1;
	}

	system("cls");

	print_table(Student, number);

	bool flag = true;
	while (flag)
	{
		do {
			printf_s("Sort by:\n");
			printf_s("1 - surname\n");
			printf_s("2 - mark\n");
			printf_s("3 - Find surname\n");
			printf_s("4 - Average mark\n");
			printf_s("5 - Exit\n");
			printf_s("Enter your choice: ");
			scanf_s("%d", &choice);
		} while (choice == 1 && choice == 2 && choice == 3 && choice == 4 && choice == 5);


		switch (choice)
		{

		case 1:
			sort_surname(Student, number);
			print_table(Student, number);
			break;

		case 2:
			sort_surname(Student, number);
			sort_subject(Student, number);
			print_table(Student, number);
			break;

		case 3:
			get_surname(buffer);
			find_surname(Student, number, buffer);
			break;
		case 4: average_mark(Student, number, sum, max);
			break;
		case 5:
			flag = false;
			break;
		default:
			printf_s("Invalid value! Try again.\n");

		}
	}

	return 0;
}

 