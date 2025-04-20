#include "events.h"
#include "sound.h"

#define INPUT_DEV "/dev/input/event2"


int main(int argc, char** argv){
	if(sound_init() == 0){
		events_listen(INPUT_DEV);
	}
	return 0;
}
