#include "frame_controller.h"

frame_control_t frame_control_block;
frame all_frames[1024]; // support up to 4MiB of frames for now
frame_list_node all_frame_nodes[1024];

void fctl_init(char* start_phys, uint32_t size) {
	printsucs("Initializing frame controller with heap starting at physical address: ");
	uint32_t frames = min((uint32_t)(size) / PAGE_SIZE, 8192);
	char* phys = start_phys;
	for (uint32_t i = 0; i < frames; i++) {
		frame f = {
			.phys = phys,
			.mapped = false
		};
		all_frames[i] = f;
		phys += PAGE_SIZE;
	}

	if (frames < 8192) {
		panic("Could not allocate 32 MiB of heap space for kernel frames");
		return;
	}

	for (int i = 0; i < frames; i++) {
		frame_list_node node = {
			.frame = &all_frames[i],
			.next = NULL
		};
		all_frame_nodes[i] = node;
	}

	for (int i = 0; i < frames - 1; i++) {
		all_frame_nodes[i].next = &all_frame_nodes[i + 1];
	}
	frame_control_block.head = &all_frame_nodes[0];
	frame_control_block.tail = &all_frame_nodes[frames - 1];
}

frame* fctl_get_free_frame() {
	if (frame_control_block.head == NULL) {
		panic("Out of frames");
		return NULL;
	}
	frame_list_node* node = frame_control_block.head;
	frame* f = node->frame;
	f->mapped = true;
	frame_control_block.head = node->next;
	if (frame_control_block.head == NULL) {
		frame_control_block.tail = NULL;
	}
	return f;
}

void fctl_free_frame(frame* f) {
	f->mapped = false;
	frame_list_node* node = &all_frame_nodes[(f->phys - all_frames[0].phys) / PAGE_SIZE];
	node->next = NULL;
	if (frame_control_block.tail == NULL) {
		frame_control_block.head = node;
		frame_control_block.tail = node;
	} else {
		frame_control_block.tail->next = node;
		frame_control_block.tail = node;
	}
}
