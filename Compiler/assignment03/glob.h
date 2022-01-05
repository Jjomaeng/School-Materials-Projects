/* glob.h - global variable for the project
* programmer - 이효진, 유효민
* date - 20/04/2021
*/
#define STsize 1000
#define MAX_ID_LEN 12
#define HTsize 100

typedef struct HTentry* HTpointer;

typedef struct HTentry {
	int index; //hashcode
	int type;
	int line_num;
	HTpointer next; //symbol table
}HTentry;

HTpointer HT[HTsize];
char ST[STsize];
int idx;
int nextid;
int hashcode, found, sameid;
int hscode;

typedef enum { type_already, type_function_name, type_function_variable, type_variable, type_array } type_enum;

//error 관련 변수
enum errorTypes { noerror, illsp, illid, overst, nosemi, noclose};
typedef enum errorTypes ERRORtypes;
ERRORtypes ERR;
int cErrors; // error count
int cLine; // line number
