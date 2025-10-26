#pragma once

#include "frame.h"

#define PAGE_SIZE 4096

typedef struct frame_list_node {
	frame* frame;
	frame_list_node* next;
}

typedef struct frame_control_t {
	frame_list_node* head;
	frame_list_node* tail;
	int total_frames;
}

frame_control_t frame_control_block;
