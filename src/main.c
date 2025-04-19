#include "events.h"

#define INPUT_DEV "/dev/input/event2"


int main(int argc, char** argv){
	events_listen(INPUT_DEV);
	return 0;
}
