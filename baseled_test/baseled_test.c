#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char * argv[]) {
	//to do
	int dev, i;
	char temp, buf[8]={0};
	unsigned char t =0;

	if (argc <= 1) {
		printf("please input the parameter! ex)./test 0xff\n");
		return -1;
	}

	dev = open("/dev/baseled", O_WRONLY);
		if (dev != -1){
			if(argv[1][0] == '0' &&
				(argv[1][1] == 'x' || argv[1][1] == 'X'))
				temp = (unsigned short)strtol(&argv[1][2], NULL, 16);
			else
				temp = atoi(argv[1]);

			for(i=0; i<8; i++) {
				if((temp>>i) & 1)
					buf[i] = 1;
			}
		}
		else {
			printf("Device Open error!\n");
			return -1;
		}

		write(dev, buf, 8);
			close(dev);
			exit(0);
}
