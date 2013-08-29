#include <stdio.h>
#include <stdlib.h>
#include <ringlist.h>

int main() {
	
	RingList *list = ringlist_new();
	ringlist_fill(list, 50);
	ringlist_print(list);

	return 0;
}