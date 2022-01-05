/* symtable.c - symbol table management
* programmer - ¿Ã»ø¡¯
* date - 22/04/2021
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tn.h"
#include "glob.h"

void ReadID();
int ComputeHS(int nid, int leng);
void LookupHS(int nid, int hscode);
void ADDHT(int nid, int hscode);

extern char *yytext;
extern int* yyleng;

//Return the ST-index of the matching identifier.
void SymbolTable() {
	int leng = yyleng;
	nextid = idx;

	ReadID();

	ComputeHS(nextid, idx);
	LookupHS(nextid, hashcode);

	//Find no match, add a new element to the list, pointing to the new identifier.
	if (!found) {
		ADDHT(nextid, hashcode);
	}
	//Find a match, delete the new identifier from ST and return the ST-index of the matching identifier.
	else {
		nextid = sameid;
		idx -= (leng + 1);
	}
}

//Read the identifier directly into ST. Each identifier is terminated with the null character.
void ReadID() {
	for (int i = 0; i < yyleng; i++) {
		ST[idx++] = yytext[i];
	}
	ST[idx++] = '\0';
}

/*Compute the hash code of identifier by summing the ordinal values of its characters and then taking the sum modulo the size of HT.
H(x) = (f(x) mod HTsize) */
int ComputeHS(int nid, int idx) {
	int key = 0;
	for (int i = nid; i < idx - 1; i++) {
		key += ST[i];
	}
	key %= HTsize;
	hashcode = key;

	return hashcode;
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
	ptr = (HTpointer*)malloc(sizeof(HTentry));
	ptr->index = nid;
	ptr->type = 0;
	ptr->line_num = cLine;
	ptr->next = HT[hscode];
	HT[hscode] = ptr;
}

void printHT()
{
	printf("[[HASH TABLE]] \n");
	for (int i = 0; i < HTsize; i++) {
		if (HT[i] != NULL) {
			printf("Hash Code %d : ", i);
			HTpointer node = HT[i];
			while (node != NULL) {
				int index = node->index;
				printf("\t(");
				while (ST[index] != '\0')
				{
					printf("%c", ST[index++]);
				}
				printf(": ");
				switch (node->type) {
					case 1: printf("function name, return type = integer, "); break;
					case 2: printf("function name, return type = void, "); break;
					case 3: printf("function name, return type = float, "); break;
					case 4: printf("function parameter, return type = integer, "); break;
					case 5: printf("function parameter, return type = void, "); break;
					case 6: printf("function parameter, return type = float, "); break;
					case 7: printf("variable, type int, "); break;
					case 8: printf("variable, type void, "); break;
					case 9: printf("variable, type float, "); break;
					case 10: printf("array, type int, "); break;
					case 11: printf("array, type void, "); break;
					case 12: printf("array, type float, "); break;
					default: printf("parse error identifier, "); break;
				}
				printf("line %d)", node->line_num);
				node = node->next;
			}
			printf("\n");
		}
	}
}
