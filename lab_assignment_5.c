#include <stdio.h>
#include <stdlib.h>

typedef struct node {
	char letter;
	struct node* next;
} node;

// Returns number of nodes in the linkedList.
int length(node* head)
{	int i = 0;
	// while the list has items in it, count it then move to the next node
	while(head != NULL)
	{
		i++;
		head = head->next;
	}
	return i;
}

// parses the string in the linkedList
//  if the linked list is head -> |a|->|b|->|c|
//  then toCString function wil return "abc"
char* toCString(node* head)
{	int len = length(head);

	int i = 0;
	char *str = (char*)malloc((len) * sizeof(char*));
	//while there are items in the list, assign each element to a letter
	//then move to the next element
	//stop once the last character is null, return string
	while(head != NULL)
	{
		str[i++] = head->letter;
		head = head->next;
	}
	str[i] = '\0';
	return str;
}

// inserts character to the linkedlist
// f the linked list is head -> |a|->|b|->|c|
// then insertChar(&head, 'x') will update the linked list as foolows:
// head -> |a|->|b|->|c|->|x|
void insertChar(node** pHead, char c)
{	struct node* Newnode = (node*)malloc(sizeof(node*));
	Newnode ->letter = c;
	Newnode->next = NULL;
	
	if(*pHead == NULL)
	{
		*pHead = Newnode;
		return;
	}
	node* current = *pHead;
	while(current -> next != NULL)
	{
		current = current ->next;
	}
	current ->next = Newnode;
}

// deletes all nodes in the linkedList.
void deleteList(node** pHead)
{	
	node *current = *	pHead;
	while(current != NULL)
	{
		node *next = current->next;
		free(current);
		current = next;
	}
	*pHead = NULL;

}

int main(void)
{
	int i, strLen, numInputs;
	node* head = NULL;
	char* str;
	char c;
	FILE* inFile = fopen("input.txt","r");

	fscanf(inFile, " %d\n", &numInputs);
	
	while (numInputs-- > 0)
	{
		fscanf(inFile, " %d\n", &strLen);
		for (i = 0; i < strLen; i++)
		{
			fscanf(inFile," %c", &c);
			insertChar(&head, c);
		}

		str = toCString(head);
		printf("String is : %s\n", str);

		free(str);
		deleteList(&head);

		if (head != NULL)
		{
			printf("deleteList is not correct!");
			break;
		}
	}

	fclose(inFile);
}