#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "textlcd.h"

int main(void)
{
	int fd;

	fd = open("/dev/lhg_fpgaTextLCD_driver", O_WRONLY);
	assert(fd != -1);

	ioctl(fd, TEXTLCD_INIT);

for (;;)	// infinite loop
{
	char msgs[2][20];

	fprintf(stdout, "1st line msg: ");
	fscanf(stdin, "%16s", msgs[0]);
	fprintf(stdout, "2nd line msg: ");
	fscanf(stdin, "%16s", msgs[1]);

	fprintf(stdout, "%s\n%s\n", msgs[0], msgs[1]);

	ioctl(fd, TEXTLCD_CLEAR);
	ioctl(fd, TEXTLCD_LINE1);
	write(fd, msgs[0], strlen(msgs[0]));
	ioctl(fd, TEXTLCD_LINE2);
	write(fd, msgs[1], strlen(msgs[1]));

}
	ioctl(fd, TEXTLCD_OFF);
	close(fd);
	return 0;
}
