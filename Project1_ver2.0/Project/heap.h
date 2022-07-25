#pragma once

#define HMAXLEN 200
#define datatype double
typedef struct metag {
	int t;
	int pow2;
	int pow3;
	int father;
}Etag;
#define tagtype Etag
typedef struct mynode {
	tagtype tag;
	//int val;
	datatype val;
}Node, * node;
typedef struct myheapbig
{
	Node arr[HMAXLEN];
	int len;
}*heap,Myheap;

void heap_init(heap H); 
void swap(node a, node b);
void heap_down(heap H, int x);
void heap_up(heap H, int x);
void heap_push(heap H, tagtype tag, datatype val);
void heap_clear(heap H);
Node heap_top(heap H);
Node heap_pop(heap H);
void heap_print(heap H);
