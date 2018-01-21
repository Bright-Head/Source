#ifndef GET_DISP_FUNCTIONS_H
#define GET_DISP_FUNCTIONS_H

#include <stdlib.h>
#include <string>
#include <stdio.h>
#include <math.h>
#include <cmath>
#include "opencv2\opencv.hpp"
#include <vector>

using namespace std;
using namespace cv;

void read_out3cr(string dir, int N, vector<Mat*>* images);

string get_file_name(int i);

void get_all_profiles(int ktr, int ktr_st, string dir3cr, int N, string dir_tmp0, string dir_tmp1,
	double kmx, double kmn, int N2, double dt, double cntr, double img_cntr,
	int dnum, int ndx,
	bool use_shifts, string dir_shifts);

void line_correction(string dir_shfv6b, int ktr, int x0, int dy, int rs, int dyd,
	string dir_result, int disp_size_rows, int disp_size_cols);

void blur_images(string dir_in, string dir_out, int ktr, int dn1, int dn2, int dn11st, int dn22st);

#endif // GET_DISP_FUNCTIONS_H