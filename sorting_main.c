#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <memory.h>
#include <ctype.h>
#include <Windows.h>
#include "nhm.h"

double start, end;

movieData data[MAX_SIZE] = { NULL, };    // 구조체 배열을 선언
movieData unsorted[MAX_SIZE] = { NULL, };
element heap_data[MAX_SIZE];
int k = 0;
int i = 0;
int last=0;
int p1 = 0;					//첫번째 파싱 문자열 배열의 인덱스 변수
int p2 = 0;					//두번째 파싱 문자열 배열의 인덱스 변수
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
	if (movie_data == NULL)	//파일스트림생성확인
	{
		printf("파일 읽기 실패!\n");
		return -1;	//비정상적인 종료
	}
	else if (movie_data != NULL)
	{
		char strTemp[255];
		char *str;
		char comparing[255];
		while (!feof(movie_data)) //문자열 한줄씩 읽어옴, 마지막줄이되면 반복문 끝
		{

			fgets(strTemp, sizeof(strTemp), movie_data);
			if (linecnt == 0) {						//첫번째 데이터는 실제 데이터와 무관하므로 체크 후 무시
				linecnt++;
			}
			else {
				strcpy(comparing, strTemp);			//읽어온 데이터 한줄 값 임시 저장
				str = strtok(strTemp, "\"");		//큰따옴표 기준으로 잘라내기 ( 제목에 큰따옴표가 있는 경우에 대한 처리 )

				if (strcmp(str, comparing) != 0) {			//큰따옴표가 존재할 경우, str은 구분자에 의해 잘려 comparing과 다름
					parsing1[p1] = str;
					p1++;

					while (str = strtok(NULL, "\"")) {
						parsing1[p1] = str;
						p1++;
					}


					//쌍따옴표 기준으로 잘렸을 시, 장르 앞 반점이 존재
					//반점 제거
					for (i = 1; parsing1[2][i]; i++)		//buf[i]가 참(널문자가 아님)이면 반복하여라.
					{
						parsing1[2][i - 1] = parsing1[2][i];		//buf[i] 문자를 buf[i-1]로 이동
					}
					parsing1[2][i - 1] = '\0';

					str = strtok(parsing1[0], ",");		//인덱스 우측 반점 제거
					parsing1[0] = str;

					str = strtok(parsing1[1], "()");	//제목과 년도가 합쳐진 값을 괄호 기준으로 분리
					parsing2[p2] = str;
					p2++;
					while (str = strtok(NULL, "()")) {
						parsing2[p2] = str;
						p2++;
					}
					if ((p2 - 1) != 0) {		// 괄호가 한번 이상 존재
						if (!strncmp(parsing2[p2 - 1], "19", 2) || !strncmp(parsing2[p2 - 1], "20", 2)) {
							last = 0;
						}
						else {		//숫자 이외의 것이 섞임, 제목부분
							last = 1;
						}
						if (last == 0) {	//제목과 년도가 함께 있는 상황
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
										if (i % 2 != 0) {				//홀수일 경우 열리는 괄호
											strcat(title, ")");
										}
										else if (i % 2 == 0) {			//짝수일 경우 닫히는 괄호
											strcat(title, "(");
										}
									}
								}
								strcpy(data[linecnt].title, title);
								strcpy(data[linecnt].years, parsing2[p2 - 1]);
							}
						}
						else if (last == 1) {		//제목만 존재하는 상황
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
										if (i % 2 != 0) {				//홀수일 경우 열리는 괄호
											strcat(title, ")");
										}
										else if (i % 2 == 0) {			//짝수일 경우 닫히는 괄호
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

				else if (strcmp(str, comparing) == 0) {					//큰따옴표가 없는 경우
					str = strtok(strTemp, ",");				//반점으로 잘라내기
					parsing1[p1] = str;
					p1++;
					while (str = strtok(NULL, ",")) {
						parsing1[p1] = str;
						p1++;
					}

					str = strtok(parsing1[1], "()");	//제목과 년도 분리
					parsing2[p2] = str;			//p2=1에서 부터 제목과 년도에 대한 분리
					p2++;
					while (str = strtok(NULL, "()")) {
						parsing2[p2] = str;
						p2++;
					}

					if ((p2 - 1) != 0) {		// 괄호가 한번 이상 존재
						if (!strncmp(parsing2[p2 - 1], "19", 2) || !strncmp(parsing2[p2 - 1], "20", 2)) {
							last = 0;
						}
						else {		//숫자 이외의 것이 섞임, 제목부분
							last = 1;
						}
						if (last == 0) {			//년도가 같이 있는 상황
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
										if (i % 2 != 0) {				//홀수일 경우 열리는 괄호
											strcat(title, ")");
										}
										else if (i % 2 == 0) {			//짝수일 경우 닫히는 괄호
											strcat(title, "(");
										}
									}
								}
								strcpy(data[linecnt].title, title);
								strcpy(data[linecnt].years, parsing2[p2 - 1]);
							}
						}
						else if (last == 1) {		//제목만 존재하는 같이 있는 상황
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
										if (i % 2 != 0) {				//홀수일 경우 열리는 괄호
											strcat(title, ")");
										}
										else if (i % 2 == 0) {			//짝수일 경우 닫히는 괄호
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
		printf("  4. 만개(10000개)\n");
		printf("  5. 이만개(20000개)		|");
		printf("  6. 전체\n");
		printf("  0. 종료			\n\n");
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
				printf("잘못 입력하셨습니다. \n");
				continue;
		}
		
		for (int i = 0; i < data_amount; i++) {
			//파일을 열어 구조체 배열에 담은 데이터를 unsorted라는 구조체배열에 담아둠,
			//정렬은 unsorted 구조체 배열에 행해짐, while문이 돌고 다른 정렬을 다시 수행 시 정렬되지 않은 데이터를 정렬하게 하기 위해
			unsorted[i] = data[i];
		}

		printf("++++++++++++++++++정렬 key값 선택++++++++++++++++++\n\n");
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
			printf("다시 입력해주세요.\n");
			continue;
		}
		printf("++++++++++++++++++Movie Data Sorting++++++++++++++++++\n\n");
		printf("  1. 삽입 정렬			|");
		printf("  2. 합병 정렬\n");
		printf("  3. 힙 정렬			|");
		printf("  4. 퀵 정렬\n");
		printf("  5. 기수 정렬			|");
		printf("  0. 종료\n\n");
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
			printf("1. 삽입 정렬 시작 ...\n");
			if(type==0){
				insertion_sort(unsorted, data_amount, "title");
				insertion_sort(unsorted, data_amount, "years");
			}
			else if (type == 1) {
				insertion_sort(unsorted, data_amount, "years");
			}
			break;
		case 2:
			printf("2. 합병 정렬 시작 ...\n");
			if(type==0){
				merge_sort(unsorted, 0, data_amount - 1, "title");
				merge_sort(unsorted, 0, data_amount - 1, "years");
			}
			else if (type == 1) {
				merge_sort(unsorted, 0, data_amount - 1, "years");
			}
			break;
		case 3:
			printf("3. 힙 정렬 시작 ...\n");
			if (type == 0) {
				heap_sort(unsorted, data_amount, "title");
				heap_sort(unsorted, data_amount, "years");
			}
			else if (type == 1) {
				heap_sort(unsorted, data_amount, "years");
			}
			break;
		case 4:
			printf("4. 퀵 정렬 시작 ...\n");
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
				printf("5. 기수 정렬 시작 ...\n");
				radixsort(unsorted, data_amount);
			}
			break;

		default:
			printf("잘못 입력하셨습니다. \n");
			continue;
		}
		end = (double)clock();		//정렬 끝

			if (0 < sel&&sel < 6) {
				if(type==0&&sel==5){		//type이 0이면 제목, 년도가 key 이므로
					printf("기수정렬은 년도만 key값으로 가집니다.\n");
				}
			else{
				
				//정렬된 데이터 출력
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
				printf("*****출력 수행시간 제외*****\n");
				
			}
			if(sel==1){
				printf("삽입 정렬 수행시간 : %lf(sec)\n======================================\n\n", (end - start) / 1000);
			}
			else if (sel == 2) {
				printf("합병 정렬 수행시간 : %lf(sec)\n======================================\n\n", (end - start) / 1000);
			}
			else if (sel == 3) {
				printf("힙 정렬 수행시간 : %lf(sec)\n======================================\n\n", (end - start) / 1000);
			}
			else if (sel == 4) {
				printf("퀵 정렬 수행시간 : %lf(sec)\n======================================\n\n", (end - start) / 1000);
			}
			else if (sel == 5) {
				if(type==1){
					printf("기수 정렬 수행시간 : %lf(sec)\n======================================\n\n", (end - start) / 1000);
				}
			}
		}
	}
	return 0;
}