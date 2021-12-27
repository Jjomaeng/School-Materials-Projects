/* glob.h - global variable for the project
* programmer - ��ȿ��, ��ȿ��
* date - 20/04/2021
*/
#define STsize 1000
#define MAX_ID_LEN 12
#define HTsize 100

typedef struct HTentry* HTpointer;

typedef struct HTentry {
	int index; //hashcode
	HTpointer next; //symbol table
}HTentry;

HTpointer HT[HTsize];

char ST[STsize];

//error ���� ����
enum errorTypes { noerror, illsp, illid, overst };
typedef enum errorTypes ERRORtypes;
ERRORtypes ERR;
