// pdf2img.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"

#include <mupdf/fitz.h>
#ifdef _DEBUG
#pragma comment(lib, "..\\debug\\libmupdf.lib")
#pragma comment(lib, "..\\debug\\libmupdf-js-none.lib")
#pragma comment(lib, "..\\debug\\libthirdparty.lib")
#else
#pragma comment(lib, "..\\release\\libmupdf.lib")
#pragma comment(lib, "..\\release\\libmupdf-js-none.lib")
#pragma comment(lib, "..\\release\\libthirdparty.lib")
#endif

#define LIBPDFEXPORT
#include "interface.h"
#include <string.h>
char * get_img_name(char * filename,char * imgname,int num)
{

	char * p = filename;
	int len = strlen(filename);
	int i = 0;
	char chnum [10] ={0};

	if(filename == NULL || imgname == NULL){
		return NULL;
	}
	sprintf(chnum,"%02d",num);
	strcpy(imgname,filename);
	p = imgname;
	for (i = len-1;i>0;i--)
	{
		if(p[i] == '.'){
			p[i] = '\0';
			strcat(p,chnum);
			strcat(p,".");
			strcat(p,"jpg");
			break;
		}
	}
	return imgname;
}

PDFEXPORT int pdf2img(char * chFileName,int iBeginPageNum,int iEndPageNum,int iZoom,int iRotation)
{
	fz_rect bounds;
	fz_irect bbox;
	fz_device *dev = NULL;
	fz_context *ctx = NULL;
	fz_document *doc = NULL;
	int pagecount = 0;
	fz_page *page = NULL;
	fz_matrix transform;
	fz_pixmap *pix = NULL;
	int pagenumber = 0;
	char imgname[100] = {0};

	//参数检查,下面情况 返回错误
	if(chFileName == NULL){
		return 0;
	}
	if(iBeginPageNum < 1 || iEndPageNum < iBeginPageNum){
		return 0;
	}
	// Create a context to hold the exception stack and various caches.

	ctx = fz_new_context(NULL, NULL, FZ_STORE_UNLIMITED);

	// Open the PDF, XPS or CBZ document.

	doc = fz_open_document(ctx, chFileName);

	// Retrieve the number of pages (not used in this example).

	pagecount = fz_count_pages(doc);
	iEndPageNum = iEndPageNum < pagecount ? iEndPageNum : pagecount;

	pagenumber = iBeginPageNum;
	while(pagenumber <= iEndPageNum){

		get_img_name(chFileName,imgname,pagenumber);

		// Load the page we want. Page numbering starts from zero.

		page = fz_load_page(doc, pagenumber - 1);

		// Calculate a transform to use when rendering. This transform
		// contains the scale and rotation. Convert zoom percentage to a
		// scaling factor. Without scaling the resolution is 72 dpi.

		//fz_matrix transform;
		fz_rotate(&transform, iRotation);
		fz_pre_scale(&transform, iZoom / 100.0f, iZoom / 100.0f);

		// Take the page bounds and transform them by the same matrix that
		// we will use to render the page.

		//fz_rect bounds;
		fz_bound_page(doc, page, &bounds);
		fz_transform_rect(&bounds, &transform);

		// Create a blank pixmap to hold the result of rendering. The
		// pixmap bounds used here are the same as the transformed page
		// bounds, so it will contain the entire page. The page coordinate
		// space has the origin at the top left corner and the x axis
		// extends to the right and the y axis extends down.

		//fz_irect bbox;
		fz_round_rect(&bbox, &bounds);
		pix = fz_new_pixmap_with_bbox(ctx, fz_device_rgb(ctx), &bbox);
		fz_clear_pixmap_with_value(ctx, pix, 0xff);

		// A page consists of a series of objects (text, line art, images,
		// gradients). These objects are passed to a device when the
		// interpreter runs the page. There are several devices, used for
		// different purposes:
		//
		//	draw device -- renders objects to a target pixmap.
		//
		//	text device -- extracts the text in reading order with styling
		//	information. This text can be used to provide text search.
		//
		//	list device -- records the graphic objects in a list that can
		//	be played back through another device. This is useful if you
		//	need to run the same page through multiple devices, without
		//	the overhead of parsing the page each time.

		// Create a draw device with the pixmap as its target.
		// Run the page with the transform.

		dev = fz_new_draw_device(ctx, pix);
		fz_run_page(doc, page, dev, &transform, NULL);
		fz_free_device(dev);

		// Save the pixmap to a file.

		fz_write_png(ctx, pix, imgname, 0);

		// Clean up.

		fz_drop_pixmap(ctx, pix);
		fz_free_page(doc, page);
		printf("convert page %d...\n",pagenumber);
		pagenumber ++ ;
	}
	printf("convert page complete\n");
	fz_close_document(doc);
	fz_free_context(ctx);
	return 1;
}

