#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "font.h"

int main() {
	int dev, i, j, offset = 20, ch, len;
	char result[600], tmp[2], input[100];

	dev = open("/dev/lhg_fpgaDotMatrix_driver", O_WRONLY);

	if (dev != -1) {
		printf("Input text : ");

		scanf("%s", input);

		len = strlen(input);

		for (j = 0; j < 20; j++)
			result[j] = '0';

		for (i = 0; i < len; i++) {
			ch = input[i];

			ch -= 0x20;

			for (j = 0; j < 5; j++) {
				sprintf(tmp, "%x%x", font[ch][j] / 16, font[ch][j] % 16);

				result[offset++] = tmp[0];
				result[offset++] = tmp[1];
			}
			result[offset++] = '0';
			result[offset++] = '0';
		}

		for (j = 0; j < 20; j++)
			result[offset++] = '0';

		for (i = 0; i < (offset - 18) / 2; i++) {
			for (j = 0; j < 20; j++) {
				write(dev, &result[2 * i], 20);
			}
		}
	} else {
		printf("Device Open ERROR!\n");
		exit(1);
	}

	close(dev);
	printf("Program Exit !!\n");

	return 0;
}
