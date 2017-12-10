#define _USE_MATH_DEFINES
#include <stdlib.h>
#include <string>
#include <stdio.h>
#include <math.h>
#include <cmath>
using namespace std;

// исходные данные
// координаты точек трека
string file_resyx31_txt = "input_data/resyx31.txt";
// карта изменения скорости вдоль трека и во времени
string file_shfv6b_txt = "input_data/shfv6b.txt";
// 
string file_sig03_mkms_txt = "input_data/sig03_mkms.txt";

string file_tr3_bmp = "input_data/tr3.bmp";
string file_tr3_bin = "input_data/tr3_bin.bin";
string file_res2_synt_nbkg = "input_data/res2_synt_nbkg.txt";

int rows_tr3 = 289;
int cols_tr3 = 215;

int rows_synt = 289;
int cols_synt = 215;

int num_dig = 5;
int num_min = 0;
int num_max = 2099;
int N = num_max - num_min + 1;

typedef unsigned __int16 WORD;

//typedef struct {
//      WORD   bfType;         // 0x4d42 | 0x4349 | 0x5450
//      int    bfSize;         // размер файла
//      int    bfReserved;     // 0
//      int    bfOffBits;      // смещение до поля данных,
//                             // обычно 54 = 16 + biSize
//      int    biSize;         // размер струкуры в байтах:
//                             // 40(BITMAPINFOHEADER) или 108(BITMAPV4HEADER)
//                             // или 124(BITMAPV5HEADER)
//      int    biWidth;        // ширина в точках
//      int    biHeight;       // высота в точках
//      WORD   biPlanes;       // всегда должно быть 1
//      WORD   biBitCount;     // 0 | 1 | 4 | 8 | 16 | 24 | 32
//      int    biCompression;  // BI_RGB | BI_RLE8 | BI_RLE4 |
//                             // BI_BITFIELDS | BI_JPEG | BI_PNG
//                             // реально используется лишь BI_RGB
//      int    biSizeImage;    // Количество байт в поле данных
//                             // Обычно устанавливается в 0
//      int    biXPelsPerMeter;// горизонтальное разрешение, точек на дюйм
//      int    biYPelsPerMeter;// вертикальное разрешение, точек на дюйм
//      int    biClrUsed;      // Количество используемых цветов
//                             // (если есть таблица цветов)
//      int    biClrImportant; // Количество существенных цветов.
//                             // Можно считать, просто 0
//} BMPheader;
