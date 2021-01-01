#include "vsh.h"

void shell(){
	prints("\n");
	prints("vSOS:/home > ");
	while(1){
		if(get_buffsize()){
			if(peek_buff()[0] == '\n'){
				pop_buff();
				break;
			}
			prints(pop_buff());
		}
	}
	return shell();
}