void main(){

	char * vid_mem = (char*) 0xb8000;
	// *vid_mem = 'v';
	*(vid_mem + 0x1) = 'v';
	*(vid_mem + 0x2) = 0x0f;
	*(vid_mem + 0x3) = 'S';
	*(vid_mem + 0x4) = 0x0f;
	*(vid_mem + 0x5) = 'O';
	*(vid_mem + 0x6) = 0x0f;
	*(vid_mem + 0x7) = 'S';
	*(vid_mem + 0x8) = 0x0f;
}