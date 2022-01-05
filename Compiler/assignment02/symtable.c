/* symtable.c - symbol table management
* programmer - ¿Ã»ø¡¯
* date - 20/04/2021
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tn.h"
#include "glob.h"

void ReadID();
void ComputeHS(int nid, int leng);
void LookupHS(int nid, int hscode);
void ADDHT(int nid, int hscode);

extern char *yytext;
extern int* yyleng;
extern int idx, nextid, hashcode, found, sameid;

int SymmbolTable(){
	int leng = yyleng;
	nextid = idx;

	ReadID();

	ComputeHS(nextid, idx);
	LookupHS(nextid, hashcode);
	if (!found) {
		ADDHT(nextid, hashcode);
	}
	else {
		nextid = sameid;
		idx -= (leng+1);
	}

  return nextid;
}

void ReadID() {
	for (int i = 0; i < yyleng; i++) {
		ST[idx++] = yytext[i];
	}
	ST[idx++] = '\0';
}

void ComputeHS(int nid, int idx) {
	int key = 0;
	for (int i = nid; i < idx - 1; i++) {
		key += ST[i];
	}
	key %= HTsize;
	hashcode = key;
}

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

void ADDHT(int nid, int hscode) {
	HTpointer ptr;
	ptr = (HTpointer)malloc(sizeof(HTpointer));
	ptr->index = nid;
	ptr->next = HT[hscode];
	HT[hscode] = ptr;
}
