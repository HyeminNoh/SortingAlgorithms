#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <memory.h>
#include <ctype.h>
#include <Windows.h>
#include "sorting.h"

double start, end;

movieData data[MAX_SIZE] = { NULL, };
movieData unsorted[MAX_SIZE] = { NULL, };
element heap_data[MAX_SIZE];
int k = 0;
int i = 0;
int last=0;
int p1 = 0;
int p2 = 0;
int linecnt = 0;
char title[100];
int sel = 0;
int data_amount = 0;
int type = 0;

int main() {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 8);

	char *parsing1[10] = { NULL, };
	char *parsing2[10] = { NULL, };

	FILE *movie_data = fopen("C://Users/Hyemin/Algorithm/movies.txt", "rt");
	if (movie_data == NULL)
	{
		printf("���� �б� ����!\n");
		return -1;
	}
	else if (movie_data != NULL)
	{
		char strTemp[255];
		char *str;
		char comparing[255];
		while (!feof(movie_data))
		{

			fgets(strTemp, sizeof(strTemp), movie_data);
			if (linecnt == 0) {						
				linecnt++;
			}
			else {
				strcpy(comparing, strTemp);			
				str = strtok(strTemp, "\"");		

				if (strcmp(str, comparing) != 0) {			
					parsing1[p1] = str;
					p1++;

					while (str = strtok(NULL, "\"")) {
						parsing1[p1] = str;
						p1++;
					}

					for (i = 1; parsing1[2][i]; i++)
					{
						parsing1[2][i - 1] = parsing1[2][i];		
					}
					parsing1[2][i - 1] = '\0';

					str = strtok(parsing1[0], ",");
					parsing1[0] = str;

					str = strtok(parsing1[1], "()");
					parsing2[p2] = str;
					p2++;
					while (str = strtok(NULL, "()")) {
						parsing2[p2] = str;
						p2++;
					}
					if ((p2 - 1) != 0) {
						if (!strncmp(parsing2[p2 - 1], "19", 2) || !strncmp(parsing2[p2 - 1], "20", 2)) {
							last = 0;
						}
						else {
							last = 1;
						}
						if (last == 0) {
							if (p2 == 2) {
								strcpy(data[linecnt].title, parsing2[0]);
								strcpy(data[linecnt].years, parsing2[1]);
							}
							else {
								for (i = 0; i < p2 - 2; i++) {
									strcat(title, parsing2[i]);
									if (i == 0) {
										strcat(title, "(");
									}
									else {
										if (i % 2 != 0) {
											strcat(title, ")");
										}
										else if (i % 2 == 0) {
											strcat(title, "(");
										}
									}
								}
								strcpy(data[linecnt].title, title);
								strcpy(data[linecnt].years, parsing2[p2 - 1]);
							}
						}
						else if (last == 1) {
							if (p2 == 1) {
								strcpy(data[linecnt].title, parsing2[0]);
								strcpy(data[linecnt].years, "\0");
							}
							else {
								for (i = 0; i < p2 - 1; i++) {
									strcat(title, parsing2[i]);
									if (i == 0) {
										strcat(title, "(");
									}
									else {
										if (i % 2 != 0) {
											strcat(title, ")");
										}
										else if (i % 2 == 0) {
											strcat(title, "(");
										}
									}
								}
								strcpy(data[linecnt].title, title);
								strcpy(data[linecnt].years, "\0");
							}
						}
					}
					else {
						strcpy(data[linecnt].title, parsing2[0]);
					}
				}

				else if (strcmp(str, comparing) == 0) {
					str = strtok(strTemp, ",");
					parsing1[p1] = str;
					p1++;
					while (str = strtok(NULL, ",")) {
						parsing1[p1] = str;
						p1++;
					}

					str = strtok(parsing1[1], "()");
					parsing2[p2] = str;
					p2++;
					while (str = strtok(NULL, "()")) {
						parsing2[p2] = str;
						p2++;
					}

					if ((p2 - 1) != 0) {
						if (!strncmp(parsing2[p2 - 1], "19", 2) || !strncmp(parsing2[p2 - 1], "20", 2)) {
							last = 0;
						}
						else {
							last = 1;
						}
						if (last == 0) {
							if (p2 == 2) {
								strcpy(data[linecnt].title, parsing2[0]);
								strcpy(data[linecnt].years, parsing2[1]);
							}
							else {
								for (i = 0; i < p2 - 2; i++) {
									strcat(title, parsing2[i]);
									if (i == 0) {
										strcat(title, "(");
									}
									else {
										if (i % 2 != 0) {				
											strcat(title, ")");
										}
										else if (i % 2 == 0) {			
											strcat(title, "(");
										}
									}
								}
								strcpy(data[linecnt].title, title);
								strcpy(data[linecnt].years, parsing2[p2 - 1]);
							}
						}
						else if (last == 1) {
							if (p2 == 1) {
								strcpy(data[linecnt].title, parsing2[0]);
								strcpy(data[linecnt].years, "\0");
							}
							else {
								for (i = 0; i < p2 - 1; i++) {
									strcat(title, parsing2[i]);
									if (i == 0) {
										strcat(title, "(");
									}
									else {
										if (i % 2 != 0) {				
											strcat(title, ")");
										}
										else if (i % 2 == 0) {			
											strcat(title, "(");
										}
									}
								}
								strcpy(data[linecnt].title, title);
								strcpy(data[linecnt].years, "\0");
							}
						}
					}
					else {
						strcpy(data[linecnt].title, parsing2[0]);
					}
				}

				strcpy(data[linecnt].no, parsing1[0]);
				strcpy(data[linecnt].genre, parsing1[p1 - 1]);

				p1 = 0;
				p2 = 0;
				*title = NULL;
				linecnt++;
			}
		}
		fclose(movie_data);
	}

	while (1)
	{
		
		printf("++++++++++++++++++++++++++++++++++++++++++++++++++++++\n\n");
		printf("정렬할 데이터 개수를 선택해주세요\n");
		printf("  1. 500개			|");
		printf("  2. 1000개\n");
		printf("  3. 5000개			|");
		printf("  4. 10000개\n");
		printf("  5. 20000개		|");
		printf("  6. 전체\n");
		printf("  0. 끝내기			\n\n");
		printf("=====================================================\n");
		printf("->");
		scanf("%d", &data_amount);
		if (!data_amount) break;

		if (0 < sel&&sel < 7)
			printf("=====================================================\n");

		switch (data_amount) {
			case 1:
				data_amount = 500;
				break;
			case 2:
				data_amount = 1000;
				break;
			case 3:
				data_amount = 5000;
				break;
			case 4:
				data_amount = 10000;
				break;
			case 5:
				data_amount = 20000;
				break;
			case 6:
				data_amount = linecnt;
				break;
			default:
				printf("다시 선택해주세요. \n");
				continue;
		}
		
		for (int i = 0; i < data_amount; i++) {
			unsorted[i] = data[i];
		}

		printf("++++++++++++++++++기수정렬은 key가 년도일때만 가능++++++++++++++++++\n\n");
		printf("  1. 제목, 년도			|");
		printf("  2. 년도\n\n");
		printf("=====================================================\n");
		printf("->");
		scanf("%d", &type);

		switch (type) {
		case 1:
			type = 0;
			break;
		case 2:
			type = 1;
			break;
		default:
			type = 0;
			printf("다시 선택해주세요.\n");
			continue;
		}
		printf("++++++++++++++++++Movie Data Sorting++++++++++++++++++\n\n");
		printf("  1. 삽입 정렬			|");
		printf("  2. 합병 정렬\n");
		printf("  3. 힙 정렬			|");
		printf("  4. 퀵 정렬\n");
		printf("  5. 기수 정렬			|");
		printf("  0. 끝내기\n\n");
		printf("=====================================================\n");
		printf("->");
		scanf("%d", &sel);

		if (!sel) break;

		if (0 < sel&&sel < 6)
			printf("=====================================================\n");
		start = (double)clock();
		switch (sel)
		{
		case 1:
			printf("1. 삽입정렬 진행 중 ...\n");
			if(type==0){
				insertion_sort(unsorted, data_amount, "title");
				insertion_sort(unsorted, data_amount, "years");
			}
			else if (type == 1) {
				insertion_sort(unsorted, data_amount, "years");
			}
			break;
		case 2:
			printf("2. 합병정렬 진행 중 ...\n");
			if(type==0){
				merge_sort(unsorted, 0, data_amount - 1, "title");
				merge_sort(unsorted, 0, data_amount - 1, "years");
			}
			else if (type == 1) {
				merge_sort(unsorted, 0, data_amount - 1, "years");
			}
			break;
		case 3:
			printf("3. 힙 정렬 진행 중 ...\n");
			if (type == 0) {
				heap_sort(unsorted, data_amount, "title");
				heap_sort(unsorted, data_amount, "years");
			}
			else if (type == 1) {
				heap_sort(unsorted, data_amount, "years");
			}
			break;
		case 4:
			printf("4. 퀵 정렬 진행 중 ...\n");
			if (type == 0) {
				quick_sort(unsorted, 0, data_amount - 1, "title");
				quick_sort(unsorted, 0, data_amount - 1, "years");
			}
			else if (type == 1) {
				quick_sort(unsorted, 0, data_amount - 1, "years");
			}
			break;
		case 5:
			if (type == 0) {
				break;
			}
			else if (type == 1) {
				printf("5. 기수 정렬 진행 중 ...\n");
				radixsort(unsorted, data_amount);
			}
			break;

		default:
			printf("다시 입력해주세요. \n");
			continue;
		}
		end = (double)clock();

			if (0 < sel&&sel < 6) {
				if(type==0&&sel==5){
					printf("기수정렬은 년도가 키일때만 정렬이 가능합니다.\n");
				}
			else{
				printf(" No	|				   T i t l e				| Years |		Genre\n");
				for (i = 0; i < 5; i++) {
					printf("===========================");
				}
				printf("\n");

				for (i = 1; i < data_amount; i++) {
					printf("%-10s%-70s%-10s%-10s\n", unsorted[i].no, unsorted[i].title, unsorted[i].years, unsorted[i].genre);
				}
				for (i = 0; i < 5; i++) {
					printf("===========================");
				}
				printf("\n\n");
				printf("*****정렬 완료*****\n");
				
			}
			if(sel==1){
				printf("삽입정렬 수행시간 : %lf(sec)\n======================================\n\n", (end - start) / 1000);
			}
			else if (sel == 2) {
				printf("합병정렬 수행시간 : %lf(sec)\n======================================\n\n", (end - start) / 1000);
			}
			else if (sel == 3) {
				printf("힙정렬 수행시간 : %lf(sec)\n======================================\n\n", (end - start) / 1000);
			}
			else if (sel == 4) {
				printf("퀵정렬 수행시간 : %lf(sec)\n======================================\n\n", (end - start) / 1000);
			}
			else if (sel == 5) {
				if(type==1){
					printf("기수정렬 수행시간 : %lf(sec)\n======================================\n\n", (end - start) / 1000);
				}
			}
		}
	}
	return 0;
}