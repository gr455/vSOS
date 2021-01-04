
/*
 * sourced from https://github.com/cfenollosa/os-tutorial/blob/master/20-interrupts-timer/drivers/keyboard.c
 */
#include "keyboard.h"

uint8_t caps = 0;
char keybuff[MAX_KEYBUFF_S][2] = {'\0','\0'};
uint8_t pusher = 0;
uint8_t popper = 0;
uint8_t buff_size = 0;

static void keyboard_callback(isr_reg_t regs){

	uint8_t scancode = port_byte_in(0x60); // get scancode from pic
	char * sc_ascii;
	int_to_ascii(scancode, sc_ascii);
	if(scancode == 0x1c){
		push_buff("\n");
		return;
	}
	handle_stroke(scancode);
	// prints("G");
	// push_buff("\n");
}

void init_keyboard(){
	new_handler(0x21, keyboard_callback); // at irq 1, isr 33
}

void push_buff(char k[]){
	keybuff[pusher][0] = k[0];
	pusher++;
	pusher = pusher % MAX_KEYBUFF_S;
	buff_size++;
}

char * pop_buff(){
	char * re = keybuff[popper];
	popper++;
	popper = popper % MAX_KEYBUFF_S;
	buff_size--;
	return re;
}

char * peek_buff(){
	return keybuff[popper];
}

uint8_t get_buffsize(){
	return buff_size;
}

void handle_stroke(uint8_t scancode){
	switch (scancode){
		case 0x0:
			push_buff("ERROR");
			break;
		case 0x1:
			// push_buff("ESC");
			break;
		case 0x2:
			push_buff("1");
			break;
		case 0x3:
			push_buff("2");
			break;
		case 0x4:
			push_buff("3");
			break;
		case 0x5:
			push_buff("4");
			break;
		case 0x6:
			push_buff("5");
			break;
		case 0x7:
			push_buff("6");
			break;
		case 0x8:
			push_buff("7");
			break;
		case 0x9:
			push_buff("8");
			break;
		case 0x0A:
			push_buff("9");
			break;
		case 0x0B:
			push_buff("0");
			break;
		case 0x0C:
			push_buff("-");
			break;
		case 0x0D:
			push_buff("+");
			break;
		case 0x0E:
			push_buff("\b");
			break;
		case 0x0F:
			push_buff("Tab");
			break;
		case 0x10:
			push_buff("q");
			break;
		case 0x11:
			push_buff("w");
			break;
		case 0x12:
			push_buff("e");
			break;
		case 0x13:
			push_buff("r");
			break;
		case 0x14:
			push_buff("t");
			break;
		case 0x15:
			push_buff("y");
			break;
		case 0x16:
			push_buff("u");
			break;
		case 0x17:
			push_buff("i");
			break;
		case 0x18:
			push_buff("o");
			break;
		case 0x19:
			push_buff("p");
			break;
		case 0x1A:
			push_buff("[");
			break;
		case 0x1B:
			push_buff("]");
			break;
		case 0x1C:
			break;
		case 0x1D:
			push_buff("LCtrl");
			break;
		case 0x1E:
			push_buff("a");
			break;
		case 0x1F:
			push_buff("s");
			break;
		case 0x20:
			push_buff("d");
			break;
		case 0x21:
			push_buff("f");
			break;
		case 0x22:
			push_buff("g");
			break;
		case 0x23:
			push_buff("h");
			break;
		case 0x24:
			push_buff("j");
			break;
		case 0x25:
			push_buff("k");
			break;
		case 0x26:
			push_buff("l");
			break;
		case 0x27:
			push_buff(";");
			break;
		case 0x28:
			push_buff("'");
			break;
		case 0x29:
			push_buff("`");
			break;
		case 0x2A:
			// push_buff("LShift");
			caps = 1;
			break;
		case 0x2B:
			push_buff("\\");
			break;
		case 0x2C:
			push_buff("z");
			break;
		case 0x2D:
			push_buff("x");
			break;
		case 0x2E:
			push_buff("c");
			break;
		case 0x2F:
			push_buff("v");
			break;
		case 0x30:
			push_buff("b");
			break;
		case 0x31:
			push_buff("n");
			break;
		case 0x32:
			push_buff("m");
			break;
		case 0x33:
			push_buff(",");
			break;
		case 0x34:
			push_buff(".");
			break;
		case 0x35:
			push_buff("/");
			break;
		case 0x36:
			caps = 1;
			break;
		case 0x37:
			push_buff("Keypad *");
			break;
		case 0x38:
			push_buff("LAlt");
			break;
		case 0x39:
			push_buff(" ");
			break;
		default:
			/* 'keuyp' event corresponds to the 'keydown' + 0x80 
			 * it may still be a scancode we haven't implemented yet, or
			 * maybe a control/escape sequence */
			if (scancode <= 0x7f) {
				// push_buff("Unknown key down");
			} else if (scancode <= 0x39 + 0x80) {
				// push_buff("key up ");
				// handle_stroke(scancode - 0x80);
				if(scancode - 0x80 == 0x2a) caps = 0;
			} //else push_buff("Unknown key up");
			break;
	}
}

void mask_keybr_intr(){
	/*
		in al,0x21
		or al,0x02
		out 0x21,al
	*/
	uint8_t flags = port_byte_in(0x21);
	flags |= 0x2;
	port_byte_out(0x21, flags);  
}

void unmask_keybr_intr(){
	/*
		in al,0x21
		and al,11111101b
		out 0x21,al
	*/
	uint8_t flags = port_byte_in(0x21);
	flags &= 0xfd;
	port_byte_out(0x21, flags); 
}