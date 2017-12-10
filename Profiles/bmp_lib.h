#include <stdlib.h>
#include <string>
#define uchar unsigned char
using namespace std;

typedef struct
{
	unsigned short    bfType;
	unsigned int   bfSize;
	unsigned short    bfReserved1;
	unsigned short    bfReserved2;
	unsigned int   bfOffBits;

	unsigned int    biSize;
	short             biWidth;
	short             biHeight;
	unsigned short  biPlanes;
	unsigned short  biBitCount;

	unsigned int    biCompression;
	unsigned int    biSizeImage;
	int             biXPelsPerMeter;
	int             biYPelsPerMeter;
	unsigned int    biClrUsed;
	unsigned int    biClrImportant;

} BITMAPFILEHEADER;

typedef struct {
	BITMAPFILEHEADER header;
	uchar* data;
} BMPIMAGE;

void read_bmp_08(string file_name, BMPIMAGE* image);