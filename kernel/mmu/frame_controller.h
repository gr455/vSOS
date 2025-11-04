#pragma once

#include "frame.h"
#include "../panic.h"
#include "../../libc/math.h"

#define PAGE_SIZE 4096

typedef struct frame_list_node {
	frame* frame;
	struct frame_list_node* next;
} frame_list_node;

typedef struct frame_control_t {
	frame_list_node* head;
	frame_list_node* tail;
	int total_frames;
} frame_control_t;

void fctl_init(char * start_phys, uint32_t size);
frame* fctl_get_free_frame();
void fctl_free_frame(frame* f);
