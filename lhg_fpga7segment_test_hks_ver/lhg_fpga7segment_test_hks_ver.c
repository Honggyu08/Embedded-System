#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <time.h>
#include <termio.h>

static struct termios initial_settings, new_settings;
static int peek_character = -1;

void init_keyboard() {
	tcgetattr(0, &initial_settings);
	new_settings = initial_settings;
	new_settings.c_lflag = ~ICANON;
	new_settings.c_lflag = ~ECHO;
	new_settings.c_cc[VMIN] = 1;
	new_settings.c_cc[VTIME] = 0;
	tcsetattr(0, TCSANOW, &new_settings);
}

void close_keyboard() {
	tcsetattr(0, TCSANOW, &initial_settings);
}

int kbhit() {
	char ch;
	int nread;

	if(peek_character != -1)
		return 1;
	new_settings.c_cc[VMIN] = 0;
	tcsetattr(0, TCSANOW, &new_settings);
	nread = read(0, &ch, 1);
	new_settings.c_cc[VMIN] = 1;
	tcsetattr(0, TCSANOW, &new_settings);
	if(nread == 1) {
		peek_character = ch;
		return 1;
	}
	return 0;
}

int readch() {
	char ch;

	if(peek_character != -1) {
		ch = peek_character;
		peek_character = -1;
		return ch;
	}
	read(0, &ch, 1);
	return ch;
}

int main(int argc, char * argv[]) {
int fd, value = 1, count, clock, ch, i;
unsigned short input, dir = 0;

if ((fd = open("/dev/lhg_fpga7segment", O_RDWR | O_SYNC)) < 0) {
	printf("FND open fail\n");
	exit(1);
}

init_keyboard();

printf("-------------------------------\n");
printf("   7Segment Program\n");
printf("-------------------------------\n");
printf("   [c] counter\n");
printf("   [t] system time\n");
printf("   [q] exit\n");
printf("-------------------------------\n");

printf("input %d %c\n", input, (char)input);

while (input != 'q') {
	input = 'r';
	if(kbhit()) {
		ch = readch();
		switch(ch) {
			case 'c': input = 'c'; break;
			case 't': input = 't'; break;
			case 'q' : input = 'q'; break;
		}
	}

	switch(input) {
	case 'c':
		printf("input counter value (0:exit program, 99~01) : ");
		close_keyboard();
		scanf("%d", &value);
		init_keyboard();
		count = value;
		printf("-------------------------------\n");
		printf("   Counter\n");
		printf("-------------------------------\n");
		printf("   [p] pause\n");
		printf("   [c] continue\n");
		printf("   [r] reset\n");
		printf("   [q] exit\n");
		printf("-------------------------------\n");

		ioctl(fd, 0, NULL, NULL);
		dir = 'c';

		while (dir != 'q') {
				if (dir == 'c') {
					if (count <= 0)
						break;
					for(i=0; i<14; i++ )
						write(fd, &count, 4);
					count--;
				}
				else if (dir == 'r') {
					count = value;
					dir = 'c';
				}
				else if (dir == 'p') {
					for (i = 0; i<14; i++)
						write(fd, &count, 4);
				}

				if (kbhit()) {
					ch = readch();
					switch(ch) {
					case 'c': dir = 'c'; break;
					case 'p': dir = 'p'; break;
					case 'r': dir = 'r'; break;
					case 'q': dir = 'q'; break;
				}
			}
		}

		printf("-------------------------------\n");
		printf("   7Segment Program\n");
		printf("-------------------------------\n");
		printf("   [c] counter\n");
		printf("   [t] system time\n");
		printf("   [q] exit\n");
		printf("-------------------------------\n");
		break;

	case 't':
	printf(" -------------------------------------\n");
	printf("   System Time\n");
	printf(" -------------------------------------\n");
	printf("   [c] continue\n");
	printf("   [p] pause\n");
	printf("   [q] exit\n");
	printf(" -----------------------------------\n\n");

	struct timeval val;
	struct tm *ptm;

	ioctl(fd, 1, NULL, NULL);
	dir = 'c';

	while(dir != 'q') {
    		if(dir == 'c') {
 			gettimeofday(&val, NULL);
 			ptm = localtime(&val.tv_sec);
 			clock = ptm->tm_hour * 10000 + ptm->tm_min * 100 + ptm->tm_sec;
 			write(fd, &clock, 4);
    		} else if( dir == 'p') {
 			write(fd, &clock, 4);
    		}

    		if(kbhit()) {
    			ch = readch();
    			switch(ch) {
    			case 'p': dir = 'p'; break;
    			case 'c': dir = 'c'; break;
    			case 'q': dir = 'q'; break;
    			}
    		}
	 }

	printf(" --------------------------------------\n");
 	printf("   7Segment IO Interface Procedure\n");
 	printf(" --------------------------------------\n");
 	printf("   [c] counter\n");
 	printf("   [t] system time\n");
 	printf("   [q] exit\n");
 	printf(" ------------------------------------\n\n");
 	break;

	case 'q' :
	break;
	}
}
	close_keyboard();
	close(fd);
	return 0;
}
