
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include<stdlib.h>
#include<string.h>

#define FILE_NAME "testdata7.txt"
#define STsize 1000
#define HTsize 100

typedef struct HTentry* HTpointer;

typedef struct HTentry {
	int index; //hashcode
	HTpointer next; //symbol table
}HTentry;

HTpointer HT[HTsize];
char ST[STsize];

char seperators[] = " .,;:?!\t\n";
int nextid = 0, nextfree = 0;
int check = 1;
unsigned int idx = 0;
char letter[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789_";

FILE* fp;
char input[1000];
char* i_pt = input;
int hashcode, found, sameid;

enum errorTypes { noerror, illsp, illid, overst };
typedef enum errorTypes ERRORtypes;
ERRORtypes err;

void initialize()
{
	fp = fopen(FILE_NAME, "r");
	if (fp == NULL)
	{
		fprintf(stderr, "File Open Error!\n");
		exit(1);
	}
	char ch;
	while (!feof(fp)) {
		ch = fgetc(fp);
		*(i_pt++) = ch;
	}

	printf("index in ST\tidentifier\n");
	printf("==========================\n");
}

/*Compute the hash code of identifier by summing the ordinal values of its characters and then taking the sum modulo the size of HT.
H(x) = (f(x) mod HTsize) */
void ComputeHS(int nid, int nfree) {
	int key = 0;
	for (int i = nid; i < nfree - 1; i++) {
		key += ST[i];
	}
	key %= HTsize;
	hashcode = key;
}

/*For each identifier, Look it up in the hashtable for previous occurrence of the identifer. If find a match, set the found flag as true.
Otherwise false. If find a match, save the starting index of ST in same id.*/
void LookupHS(int nid, int hscode) {
	int i, j;
	HTpointer node;
	found = 0;
	for (node = HT[hscode]; node && found == 0; node = node->next) {
		found = 1;
		i = nid, j = node->index;
		sameid = j;
		for (; found == 1 && ST[i] != '\0' && ST[j] != '\0'; i++, j++) {
			if (ST[i] != ST[j]) {
				found = 0;
			}
		}
	}
}

/*Add a new identifer to the hash table. If list head ht[hashcode] is null, simply add a list element with starting index of the identifier ST.
IF list head is not a null,it adds a new identifier to the head of the chain.*/
void ADDHT(int nid, int hscode) {
	HTpointer ptr;
	ptr = (HTpointer)malloc(sizeof(HTpointer));
	ptr->index = nid;
	ptr->next = HT[hscode];
	HT[hscode] = ptr;
}

void PrintHStable()
{
	int count = 0;
	printf("[[HASH TABLE]] \n");
	for (int i = 0; i < HTsize; i++) {
		if (HT[i] != NULL) {
			printf("Hash Code %d : ", i);
			HTpointer node = HT[i];
			while (node != NULL) {
				int index = node->index;
				while (ST[index] != '\0')
				{
					printf("%c", ST[index++]);
					count++;
				}
				printf(" ");
				count++;
				node = node->next;
			}
			printf("\n");
		}
	}

	if (count == 0) {
		printf("<%d characters are used in the string table>\n", count);
	}
	else {
		printf("<%d characters are used in the string table>\n", count - 1);
	}
}


void ReadID()
{
	if (strchr("0123456789", input[idx]) != NULL) {	//check start with digit 
		err = illid;
	}

	check = 1;
	while (strchr(seperators, input[idx]) == NULL && input[idx + 1] != '\0' && strchr(letter, input[idx]) != NULL) {
		ST[nextfree++] = input[idx++];
		check = 0;
	}

	if (nextfree - nextid > 12) err = illid;	//check id length

}

void SkipSeperator()
{
	if (strchr(seperators, input[idx]) == NULL) {
		if (check == 1) {
			ST[nextfree++] = input[idx++];
			err = illsp;
		}
	}
	else {
		idx++;
	}
}

void PrintError(ERRORtypes err, char* current)
{
	switch (err)
	{
	case 1:
		printf("ERROR!!\t\t%s\t\tSEPERATOR IS NOT ALLOWED\n", current);
		break;
	case 2:
		if (nextfree - nextid > 12) printf("ERROR!!\t\t%s\t\tTOO LONG ID\n", current);
		else printf("ERROR!!\t\t%s\t\tSTART WITH DIGIT\n", current);
		break;
	case 3:
		printf("ERROR!!\t\tOVERFLOW\n");
		break;
	}
}

int main()
{
	initialize();
	while (input[idx + 1] != '\0')
	{
		err = noerror;
		ReadID();
		SkipSeperator();
		char* current = (char*)malloc(sizeof(char) * (nextfree - nextid));
		for (int i = nextid; i < nextfree; i++) current[i - nextid] = ST[i];
		current[nextfree - nextid] = '\0';
		if (nextfree >= STsize) {
			err = overst;
			PrintError(err, current);
			break;
		}
		else if (err == illid || err == illsp) {
			PrintError(err, current);
			nextfree = nextid;
		}
		else if (nextid != nextfree) {
			ST[nextfree++] = '\0';
			ComputeHS(nextid, nextfree);
			LookupHS(nextid, hashcode);
			if (!found) {
				printf("%d\t\t%s\t\t(entered)\n", nextid, current);
				ADDHT(nextid, hashcode);
				nextid = nextfree;
			}
			else {
				printf("%d\t\t%s\t\t(already existed)\n", sameid, current);
				nextfree = nextid;
			}
		}
	}
	PrintHStable();
	return 0;
}
