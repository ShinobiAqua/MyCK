#include <stdio.h>
#include <stdlib.h>
#include "heap.h"
#include "miracl.h"

void heap_init(heap H)
{
	H->len = 0;
}
void swap(node a, node b)
{
	Node tmp;
	tmp.val = a->val;
	tmp.tag = a->tag;
	a->val = b->val;
	a->tag = b->tag;
	b->val = tmp.val;
	b->tag = tmp.tag;
}
void heap_down(heap H, int x)
{
	while (x*2 <= H->len)
	{
		if (H->arr[x].val < H->arr[x * 2].val)
		{
			if (x * 2 + 1 <= H->len)
			{
				if (H->arr[x * 2 + 1].val > H->arr[x * 2].val)
				{
					swap(&H->arr[x], &H->arr[x * 2 + 1]);
					x = x * 2 + 1;
					continue;
				}
			}
			swap(&H->arr[x], &H->arr[x * 2]);
			x = x * 2;
		}
		else
			break;
	}
	return;
}
void heap_up(heap H, int x)
{
	while (x >1)
	{
		if (H->arr[x / 2].val < H->arr[x].val)
		{
			swap(&H->arr[x], &H->arr[x / 2]);
			x = x / 2;
		}
		else
			break;
		
	}
	return;
}
void heap_push(heap H,tagtype tag,datatype val)
{
	if (H->len >= HMAXLEN - 1)
	{
		printf("error1 !\n");
		return;
	}
	H->len++;
	H->arr[H->len].val = val;
	H->arr[H->len].tag = tag;
	heap_up(H, H->len);
}
void heap_clear(heap H)
{
	H->len = 0;
	return;
}
Node heap_top(heap H)
{
	if (H->len <= 0)
	{
		printf("error2 !\n");
		return;
	}
	return H->arr[1];
}
Node heap_pop(heap H)
{
	if (H->len <= 0)
	{
		printf("error3 !\n");
		return;
	}
	Node tmp = H->arr[1];
	swap(&H->arr[1], &H->arr[H->len]);
	H->len--;
	heap_down(H, 1);
	return tmp;
}
void heap_print(heap H)
{
	for (int i = 1; i <= H->len; i++)
	{
		Node t = H->arr[i];
		printf("%d:%lf %d %d %d       ", i, t.val,t.tag.t,t.tag.pow2,t.tag.pow3);
	}
	printf("\n");
}