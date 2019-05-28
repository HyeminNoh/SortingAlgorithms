#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <memory.h>
#include <ctype.h>
#include "sorting.h"

double start, end;

movieData result[MAX_SIZE] = { NULL, };

void merge_title(movieData list[], int left, int mid, int right)
{
	int i, j, k, l;
	static movieData sorted[MAX_SIZE];

	i = left; j = mid + 1; k = left;

	while (i <= mid && j <= right) {
		if (strcmp(list[i].title, list[j].title) > 0)
			sorted[k++] = list[i++];
		else
			sorted[k++] = list[j++];
	}
	if (i > mid)
		for (l = j; l <= right; l++)
			sorted[k++] = list[l];
	else
		for (l = i; l <= mid; l++)
			sorted[k++] = list[l];
	for (l = left; l <= right; l++)
		list[l] = sorted[l];
}

void merge_years(movieData list[], int left, int mid, int right)
{
	int i, j, k, l;
	static movieData sorted[MAX_SIZE];

	i = left; j = mid + 1; k = left;

	while (i <= mid && j <= right) {
		if (strcmp(list[i].years, list[j].years) < 0)
			sorted[k++] = list[i++];
		else
			sorted[k++] = list[j++];
	}
	if (i > mid)
		for (l = j; l <= right; l++)
			sorted[k++] = list[l];
	else
		for (l = i; l <= mid; l++)
			sorted[k++] = list[l];
	for (l = left; l <= right; l++)
		list[l] = sorted[l];
}

void merge_sort(movieData list[], int left, int right, char* type)
{
	int mid;
	if (left < right)
	{
		mid = (left + right) / 2;
		merge_sort(list, left, mid, type);
		merge_sort(list, mid + 1, right, type);
		if (strcmp(type, "title") == 0) {
			merge_title(list, left, mid, right);
		}
		else if (strcmp(type, "years") == 0) {
			merge_years(list, left, mid, right);
		}
	}
}


void insertion_sort(movieData list[], int n, char *type)
{
	int unsorted;
	int sorted;
	movieData unsortedItem;
	
	if (strcmp(type, "title") == 0) {
		for (unsorted = 1; unsorted < n; unsorted++)
		{
			unsortedItem = list[unsorted];

			for (sorted = unsorted - 1; (sorted >= 0) && strcmp(list[sorted].title, unsortedItem.title) > 0; sorted--)
				list[sorted + 1] = list[sorted];

			list[sorted + 1] = unsortedItem;
		}
	}
	else if (strcmp(type, "years") == 0) {
		for (unsorted = 1; unsorted < n; unsorted++)
		{
			unsortedItem = list[unsorted];

			for (sorted = unsorted - 1; (sorted >= 0) && strcmp(list[sorted].years, unsortedItem.years) > 0; sorted--)
				list[sorted + 1] = list[sorted];

			list[sorted + 1] = unsortedItem;
		}
	}
}


int partition(movieData list[], int left, int right, char* type)
{
	char pivot[200];
	movieData temp[1];
	int low, high;

	low = left;
	high = right + 1;
	if (strcmp(type, "title") == 0) {
		strcpy(pivot, list[left].title); 	
		do {
			do
				low++;
			while (low <= right && strcmp(list[low].title, pivot) < 0);
			do
				high--;
			while (high >= left && strcmp(list[high].title, pivot) > 0);
			if (low < high) SWAP(list[low], list[high], temp[0]);
		} while (low < high);

		SWAP(list[left], list[high], temp[0]);
		return high;
	}
	else if (strcmp(type, "years") == 0) {
		strcpy(pivot, list[left].years);
		do {
			do
				low++;
			while (low <= right && strcmp(list[low].years, pivot) < 0);
			do
				high--;
			while (high >= left && strcmp(list[high].years, pivot) > 0);
			if (low < high) SWAP(list[low], list[high], temp[0]);
		} while (low < high);

		SWAP(list[left], list[high], temp[0]);
		return high;
	}
}

void quick_sort(movieData list[], int left, int right, char* type)
{
	if (left < right) {
		if (strcmp(type, "title") == 0) {
			int q = partition(list, left, right, type);
			quick_sort(list, left, q - 1, type);
			quick_sort(list, q + 1, right, type);
		}
		else if (strcmp(type, "years") == 0) {
			int q = partition(list, left, right, type);
			quick_sort(list, left, q - 1, type);
			quick_sort(list, q + 1, right, type);
		}
	}
}


void heap_sort(movieData list[], int n, char *type)
{
	int i;
	HeapType h;
	movieData *input;
	movieData *output;
	input = list;
	int k = 0;

	init(&h);
	
	if (strcmp(type, "title") == 0) {
		for (i = 0; i < n; i++) {
			insert_max_heap(&h, input, "title");
			input++;
		}
		for (i = 0; i < n; i++) {
			output = delete_max_heap(&h, "title");
			strcpy(result[i].no, output->no);
			strcpy(result[i].title, output->title);
			strcpy(result[i].years, output->years);
			strcpy(result[i].genre, output->genre);
			//printf("%-10s %-70s %-10s %-10s\n", output->no, output->title, output->years, output->genre);
			//printf("------------------------------------------\n");
		}
	}
	else if (strcmp(type, "years") == 0) {
		for (i = 0; i < n; i++) {
			insert_max_heap(&h, input, "years");
			input++;
		}
		for (i = 0; i<n; i++) {
			output = delete_max_heap(&h, "years");
			strcpy(result[i].no, output->no);
			strcpy(result[i].title, output->title);
			strcpy(result[i].years, output->years);
			strcpy(result[i].genre, output->genre);
			//printf("%-10s %-70s %-10s %-10s\n", output->no, output->title, output->years, output->genre);
			//printf("------------------------------------------\n");
		}
	}
	for (int i = 0; i < n; i++) {
		strcpy(list[i].no, result[i].no);
		strcpy(list[i].title, result[i].title);
		strcpy(list[i].years, result[i].years);
		strcpy(list[i].genre, result[i].genre);
	}

}
element delete_max_heap(HeapType *h, char *type)
{
	int parent, child;
	element item, temp;

	item = h->heap[1];
	temp = h->heap[(h->heap_size)--];
	parent = 1;
	child = 2;
	if (strcmp(type, "title") == 0) {
		while (child <= h->heap_size) {
			
			if ((child < h->heap_size) &&
				(strcmp(h->heap[child]->title, h->heap[child + 1]->title) > 0))
				child++;
			if (strcmp(temp->title, h->heap[child]->title) <= 0) break;
			
			h->heap[parent] = h->heap[child];
			parent = child;
			child *= 2;
		}
	}
	else if (strcmp(type, "years")==0) {
		while (child <= h->heap_size) {
			
			if ((child < h->heap_size) &&
				(strcmp(h->heap[child]->years, h->heap[child + 1]->years) > 0))
				child++;
			if (strcmp(temp->years, h->heap[child]->years) <= 0) break;
			
			h->heap[parent] = h->heap[child];
			parent = child;
			child *= 2;
		}
	}
	h->heap[parent] = temp;
	return item;
}


void insert_max_heap(HeapType *h, element item, char *type)
{
	int i;
	i = ++(h->heap_size);
	if (strcmp(type, "title")==0) {
		
		while ((i != 1) && (strcmp(item->title, h->heap[i / 2]->title) < 0)) {
			h->heap[i] = h->heap[i / 2];
			i /= 2;
		}
	}
	else if(strcmp(type,"years")==0){
		
		while ((i != 1) && (strcmp(item->years, h->heap[i / 2]->years) < 0)) {
			h->heap[i] = h->heap[i / 2];
			i/=2;
		}
	}
	h->heap[i] = item;
	//printf("%-10s %-70s %-10s %-10s\n",h->heap[i]->no, h->heap[i]->title, h->heap[i]->years, h->heap[i]->genre);
}


void init(HeapType *h)
{
	h->heap_size = 0;
}


int getMax(movieData list[], int n)
{
	int max = atoi(list[0].years);
	for (int i = 1; i < n; i++)
		if (atoi(list[i].years) > max)
			max = atoi(list[i].years);
	return max;
}

void countSort(movieData list[], int n, int exp)
{
	int i = 0;
	int count[100] = { 0 };

	for (i = 0; i < n; i++)
		count[(atoi(list[i].years) / exp) % 10]++;

	for (i = 1; i < 10; i++)
		count[i] += count[i - 1];

	for (i = n - 1; i >= 0; i--)
	{
		result[count[(atoi(list[i].years) / exp) % 10] - 1] = list[i];
		count[(atoi(list[i].years) / exp) % 10]--;
	}

	for (i = 0; i < n; i++)
		list[i] = result[i];
}

void radixsort(movieData list[], int n)
{
	int m = getMax(list, n);
	for (int exp = 1; m / exp > 0; exp *= 10)
		countSort(list, n, exp);
}