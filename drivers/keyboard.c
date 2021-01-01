
/*
 * sourced from https://github.com/cfenollosa/os-tutorial/blob/master/20-interrupts-timer/drivers/keyboard.c
 */
#include "keyboard.h"

uint8_t caps = 0;

static void keyboard_callback(isr_reg_t regs){

	uint8_t scancode = port_byte_in(0x60); // get scancode from pic
	char * sc_ascii;
	int_to_ascii(scancode, sc_ascii);
	// prints("Keyboard scancode: ");
	// prints(sc_ascii);
	// prints(", ");
	print_letter(scancode);
	// prints("\n");
}

void init_keyboard(){
	printsln("Intializing keyboard");
	new_handler(0x21, keyboard_callback); // at irq 33
	printsln("done");
}

void print_letter(uint8_t scancode){
	switch (scancode){
		case 0x0:
			prints("ERROR");
			break;
		case 0x1:
			// prints("ESC");
			break;
		case 0x2:
			prints("1");
			break;
		case 0x3:
			prints("2");
			break;
		case 0x4:
			prints("3");
			break;
		case 0x5:
			prints("4");
			break;
		case 0x6:
			prints("5");
			break;
		case 0x7:
			prints("6");
			break;
		case 0x8:
			prints("7");
			break;
		case 0x9:
			prints("8");
			break;
		case 0x0A:
			prints("9");
			break;
		case 0x0B:
			prints("0");
			break;
		case 0x0C:
			prints("-");
			break;
		case 0x0D:
			prints("+");
			break;
		case 0x0E:
			clr_back();
			break;
		case 0x0F:
			prints("Tab");
			break;
		case 0x10:
			prints("q");
			break;
		case 0x11:
			prints("w");
			break;
		case 0x12:
			prints("e");
			break;
		case 0x13:
			prints("r");
			break;
		case 0x14:
			prints("t");
			break;
		case 0x15:
			prints("y");
			break;
		case 0x16:
			prints("u");
			break;
		case 0x17:
			prints("i");
			break;
		case 0x18:
			prints("o");
			break;
		case 0x19:
			prints("p");
			break;
		case 0x1A:
			prints("[");
			break;
		case 0x1B:
			prints("]");
			break;
		case 0x1C:
			prints("\n");
			break;
		case 0x1D:
			prints("LCtrl");
			break;
		case 0x1E:
			prints("a");
			break;
		case 0x1F:
			prints("s");
			break;
		case 0x20:
			prints("d");
			break;
		case 0x21:
			prints("f");
			break;
		case 0x22:
			prints("g");
			break;
		case 0x23:
			prints("h");
			break;
		case 0x24:
			prints("j");
			break;
		case 0x25:
			prints("k");
			break;
		case 0x26:
			prints("l");
			break;
		case 0x27:
			prints(";");
			break;
		case 0x28:
			prints("'");
			break;
		case 0x29:
			prints("`");
			break;
		case 0x2A:
			// prints("LShift");
			caps = 1;
			break;
		case 0x2B:
			prints("\\");
			break;
		case 0x2C:
			prints("z");
			break;
		case 0x2D:
			prints("x");
			break;
		case 0x2E:
			prints("c");
			break;
		case 0x2F:
			prints("v");
			break;
		case 0x30:
			prints("b");
			break;
		case 0x31:
			prints("n");
			break;
		case 0x32:
			prints("m");
			break;
		case 0x33:
			prints(",");
			break;
		case 0x34:
			prints(".");
			break;
		case 0x35:
			prints("/");
			break;
		case 0x36:
			caps = 1;
			break;
		case 0x37:
			prints("Keypad *");
			break;
		case 0x38:
			prints("LAlt");
			break;
		case 0x39:
			prints(" ");
			break;
		default:
			/* 'keuyp' event corresponds to the 'keydown' + 0x80 
			 * it may still be a scancode we haven't implemented yet, or
			 * maybe a control/escape sequence */
			if (scancode <= 0x7f) {
				prints("Unknown key down");
			} else if (scancode <= 0x39 + 0x80) {
				// prints("key up ");
				// print_letter(scancode - 0x80);
				if(scancode - 0x80 == 0x2a) caps = 0;
			} else prints("Unknown key up");
			break;
	}
}
