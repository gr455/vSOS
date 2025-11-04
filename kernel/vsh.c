#include "vsh.h"

char valid_c[128][10] = {"add"};

// debug
void __dbg_printespbsp() {
	unsigned int ebp, esp;
	char esps[32], ebps[32];

	__asm__ volatile (
		"mov %%ebp, %0\n\t"
		"mov %%esp, %1\n\t"
		: "=r"(ebp), "=r"(esp)
	);
	int_to_ascii(ebp, ebps);
	int_to_ascii(esp, esps);

	printinfs("-------------\n");
	prints("ebp: ");
	printsln(ebps);
	prints("esp: ");
	printsln(esps);
	printinfs("-------------\n");
}

void shell(){
	char q[80];
	int p = 0;
	__dbg_printespbsp();
	prints("root@vSOS># ");
	while(1){
		if(get_buffsize() > 0) {
			char ch = pop_buff();
			if(ch == '\n'){
				q[p] = '\0';  // Terminate current comm
				prints("\n");
				handler(q);
				return;
			}

			if(ch == '\b'){
				if(p > 0){
					p--;
					clr_back();
				}
			}
			else{
				q[p++] = ch;
				char tmp[2] = {ch, '\0'};
				prints(tmp);
			}
		}
	}

	printe("uncaught shell error");
}

void handler(char q[]){
	prints("\n");
	char word[128];
	split(q, word, 0);
	if(strcmp(word, "add") == 0){
		char a[10];
		char b[10];
		char re[10];
		split(q, a, 1);
		split(q, b, 2);
		int_to_ascii(add(stoi(a), stoi(b)), re);
		printsln(re);
		return;
	}
	if(word[0] == '\0') return;

	prints(word);
	printsln(": command not found");
	return;
}

// uint8_t isvalidc(char c[]){
// 	uint8_t i;
// 	for(i; i < sizeof(valid_c))
// }

int add(int a, int b){
	return a+b;
}
