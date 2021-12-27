#include <stdio.h>
#include <stdlib.h>

typedef int ElementType;
typedef struct Node* PtrToNode;
typedef PtrToNode List;
typedef PtrToNode Position;
struct Node {
	ElementType Element;
	Position Next;
};

List Read() {
	List L = (List)malloc(sizeof(struct Node));
	List ptr = L;
	int num = 0;
	scanf_s("%d", &num);
	ElementType value;
	for (int i = 0; i < num; i++) {
		scanf_s("%d", &value);
		List tmp = (List)malloc(sizeof(struct Node));
		tmp->Element = value;
		ptr->Next = tmp;
		ptr = ptr->Next;
	}
	ptr->Next = NULL;
	return L;
}
void Print(List L) {
	List ptr = L;
	while (ptr->Next != NULL) {
		printf("%d ", ptr->Next->Element);
		ptr = ptr->Next;
	}
	printf("\n");
}
List Reverse(List L);

int main()
{
	List L1, L2;
	L1 = Read();
	L2 = Reverse(L1);
	Print(L1);
	Print(L2);
	return 0;
}

List Reverse(List L) {
	List ptr = L;
	List L2 = (List)malloc(sizeof(struct Node));
	List ptr2 = L2;
	List tem = L2;
	while (ptr->Next != NULL) {
		List tem2 = (List)malloc(sizeof(struct Node));
		tem2->Element = ptr->Next->Element;
		if (ptr2 != L2)
			tem2->Next = ptr2;
		ptr2 = tem2;
		ptr = ptr->Next;
	}
	List Head = (List)malloc(sizeof(struct Node));
	Head->Next = ptr2;
	return Head;
}