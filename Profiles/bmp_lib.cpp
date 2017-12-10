#include <stdlib.h>
#include <string>
#include "bmp_lib.h"
#define uchar unsigned char
using namespace std;

void read_bmp_08(string file_name, BMPIMAGE* image)
{
	FILE* bmp_file = fopen(file_name.c_str(), "rb");
	BITMAPFILEHEADER header;
	fread(&header, sizeof(BITMAPFILEHEADER), 1, bmp_file);
	int img_size = header.biHeight * header.biWidth;
	image->data = (uchar*)malloc(sizeof(uchar)*img_size);
	fread(&image->data, sizeof(uchar)* img_size, 1, bmp_file);
	return;
}

