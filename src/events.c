#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <poll.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include "events.h"
#include "sound.h"

#define DEBUG 0

struct input_event{
	struct timeval time;
	unsigned short type;
	unsigned short code;
	unsigned int value;
};

void events_listen(const char* event_file){
	const int timeout = -1;
	int ret;

	struct pollfd fds[1];
	fds[0].fd = open(event_file, O_RDONLY | O_NONBLOCK);

	if(fds[0].fd < 0){
		fprintf(stderr, "Failed to open event file(%s)\n", event_file);
		return;
	}

	const int input_size = sizeof(struct input_event);
	struct input_event* input_data = malloc(sizeof(struct input_event));
	memset(input_data, 0, input_size);
	fds[0].events = POLLIN;

	while(1){
		ret = poll(fds, 1, timeout);

		if(ret > 0){
			if(fds[0].revents){
				ssize_t r = read(fds[0].fd, input_data, input_size);
				if(r < 0){
					fprintf(stderr, "Failed to read event file(%s) : %d\n", event_file, (int)r);
					break;
				}else{
					if(DEBUG){
						printf("TIME : %ld.%.06lu\tTYPE : %hu\tCODE : %hu\tVALUE : %u\n", 
								input_data->time.tv_sec,
								input_data->time.tv_usec,
								input_data->type,
								input_data->code,
								input_data->value);
					}
					sound_play();
					memset(input_data, 0, input_size);
				}
			}else{
				fprintf(stderr, "Failed to poll events!!!\n");
			}
		}else{
			fprintf(stderr, "Timeout!!!\n");
		}
	}
	close(fds[0].fd);
}
