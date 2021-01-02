#include "vsh.h"

char valid_c[128][10] = {"add"};


void shell(){
	char q[80];
	q[0] = '\0'; // reference 
	int p = 0;
	prints("vSOS:/home > ");
	while(1){
		if(peek_buff()[0] == '\n'){
			pop_buff();
			q[p++] = '\0';
			return handler(q);
		}

		if(get_buffsize() > 0){
			char ch[2];
			ch[0] = pop_buff()[0];
			ch[1] = '\0';
			if(ch[0] == '\b'){
				if(p > 0){
					p--;
					q[p] = '\0'; // in case user doesnt add another character
					clr_back();
				}
			}
			else{
				q[p++] = ch[0];
				prints(ch);
			}
		}
	}

	printe("uncaught shell error");
}

void handler(char q[]){
	prints("\n");
	char word[128];
	split(q, word, 0);
	if(!strcmp(word, "add")){
		char a[4];
		char b[4];
		split(q, a, 1);
		split(q, b, 2);
		printsln(a);
		printsln(b);
		return shell();
	}
	if(word[0] == '\0') return shell();

	prints(word);
	printsln(": command not found");
	return shell();
}

// uint8_t isvalidc(char c[]){
// 	uint8_t i;
// 	for(i; i < sizeof(valid_c))
// }

uint32_t add(uint32_t a, uint32_t b){
	return a+b;
}