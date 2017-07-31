#include <stdio.h>

#include "../pdf2img/interface.h"

int main()
{
	char *filename = "applicate.pdf";
	int pagenumber = 1;
	int beginpagenum = 1;
	int endpagenum = 2;
	int zoom = 100;
	int rotation = 0;

	pdf2img(filename,beginpagenum,endpagenum,zoom,rotation);
	getchar();
	return 0;
}