#define MAX_SIZE 28000
#define SWAP(x, y, t) ( (t)=(x), (x)=(y), (y)=(t) )

typedef struct
{
	char no[100];
	char title[500];
	char years[100];
	char genre[100];
}movieData;

typedef movieData* element;

typedef struct
{
	element heap[MAX_SIZE+1];
	int heap_size;
}HeapType;

void merge_years(movieData list[], int left, int mid, int right);
void merge_title(movieData list[], int left, int mid, int right);
void merge_sort(movieData list[], int left, int right, char* type);

void insertion_sort(movieData list[], int n, char* type);

int partition(movieData list[], int left, int right, char* type);
void quick_sort(movieData list[], int left, int right, char* type);

void heap_sort(movieData list[], int n, char *type);
element delete_max_heap(HeapType *h);
void insert_max_heap(HeapType *h, element item);
void init(HeapType *h);

void radixsort(movieData list[], int n);
void countSort(movieData list[], int n, int exp);
int getMax(movieData list[], int n);