#ifndef PARAMETERS_H
#define PARAMETERS_H
#define _USE_MATH_DEFINES
#include <stdlib.h>
#include <string>
#include <stdio.h>
#include <math.h>
#include <cmath>
#include <fstream>
#include "opencv2\opencv.hpp"
using namespace std;
using namespace cv;

// исходные данные
// координаты точек трека
string file_resyx31_txt = "input_data/resyx31.txt";
// карта изменения скорости вдоль трека и во времени
string file_shfv6b_txt = ".\\input_data\\shfv6b.txt";
int rows_shfv6b = 2100;
int cols_shfv6b = 282;
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

//int ndx = 16; //??????
//int dnum = 282;

string dir3cr = "input_data/out3cr";


#endif // PARAMETERS_H