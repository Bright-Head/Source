#define _CRT_SECURE_NO_DEPRECATE
#include "parameters.h"
#include "get_disp_functions.h"

string get_file_name(int i) 
{
	string name;
	string addi = to_string(i);
	int nadd = num_dig - addi.length();
	for (int k = 0; k < nadd; k++)
	{
		addi = "0" + addi;
	}
	name = addi;
	return name;
}

void read_out3cr(string dir, int N, vector<Mat>& images)
{
	printf("read_out3cr\n");
	for (int i = 0; i < N; ++i)
	{
		Mat image;
		string file_name = dir + "\\" + get_file_name(i) + ".bmp";
		image = imread(file_name, CV_LOAD_IMAGE_GRAYSCALE);
		images.push_back(image);
	}
}

void write_file_ktr(string dir, int N, vector<Mat>& images, int ktr, int ktr1)
{
	printf("write_file_ktr\n");
	for (int i = 0; i < N; i++)
	{
		string file_name = dir + "\\krt_" + to_string(ktr) + "_krt1_" + to_string(ktr1) + "_" + get_file_name(i) + ".bmp"; //png - ?
		imwrite(file_name, images[i]);
	}
}

void read_file_ktr(string dir, Mat& image, int ktr, int ktr1, int i)
{
	string file_name = dir + "\\ktr_" + to_string(ktr) + "_ktr1_" + to_string(ktr1) + "_" + get_file_name(i) + ".bmp"; //png - ?
	image = imread(file_name, CV_LOAD_IMAGE_GRAYSCALE);
}

void read_shfv6b(string path, double* shfv6b, int rows=2100, int cols=282)
{
	printf("read_shfv6b: path = %s\n", path.c_str());
	ifstream fl;
	fl.open(path.c_str(), std::ifstream::in);
	for (int i = 0; i < rows; ++i)
		for (int j = 0; j < cols; ++j)
		{
			double temp;
			fl >> temp;
			shfv6b[i * cols + j] = temp;
		}
}

void write_shfv6b(string path, double* shfv6b, int rows = 2100, int cols = 282)
{
	ofstream file_shfv6b_txt;
	file_shfv6b_txt.open(path);
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			file_shfv6b_txt << shfv6b[i * cols + j] << " ";
		}
		file_shfv6b_txt << endl;
	}
}

void mult_ktr_shfv6b(double* shfv6b, double ktr, double* shfv6b_mult, int rows = 2100, int cols = 282)
{
	for (int i = 0; i < rows; ++i)
		for (int j = 0; j < cols; ++j)
			shfv6b_mult[i * cols + j] = shfv6b[i * cols + j] * ktr;
}

void gg1(double* gg, int rr1_max = 150,int rad = 100)
{
	
	for (int i = 0; i < rr1_max; i++)
	{
		double result = 0;
		if (i <= 100)
			result = 0.125 + pow((1 + cos(M_PI * i / rad)), 0.75);
			//result = 0.125 + (1 + cos(M_PI * i / rad));
		gg[i] = result;
	}

}

void blr_pvf32(vector <Mat>& images, vector <Mat>& resA3r1, double* shfv6b, int ndx, int dnum,
	double dt, int N2, double cntr) 
{
	int N = min((int)images.size(), N2);
	int Y = images[0].rows;
	int X = images[0].cols;
	int s = images.size(); ////???

	//resA3r1.resize(s);
	for (int i = 0; i < s; ++i)
		resA3r1.push_back(images[i].clone());	 

	for (int n = 0; n < N; n++)
	{
		if (n % 100 == 0)
			printf("blr_pvf32: n = %d\n", n);
		
		vector <Mat> resA3r2;
		resA3r2.resize(ndx * 2);

		Mat result = images[n].clone(); 

		double *vs;
		vs = (double*)malloc(sizeof(double) * 150);
		double *gg;
		gg = (double*)malloc(sizeof(double) * 150);
		gg1(gg);

		for (int j = -ndx; j < ndx; j++)
		{
			if (n + j >= 0 && n + j <= N - 1)
			{
				resA3r2[j + ndx] = images[n + j].clone();
				vs[j + ndx] = gg[(int)round(abs(j * 50) / ndx)];
			}
		}

		for (int y = 0; y < Y; ++y)
		{
			for (int x = 0; x < X; ++x)
			{
				double sum = 0;
				double zn = 0;
				double spd = 0;
				int x2 = x;
				for (int ndx1 = 0; ndx1 < ndx; ++ndx1)
				{
					if (n + ndx1 >= 0 && n + ndx1 <= N - 1)
					{
						x2 += spd;
						int x2r = round(x2); //?
						if (x2r >= 0 && x2r <= dnum - 1)
						{
							spd = shfv6b[n * cols_shfv6b + x2r] / dt;
							Mat img = resA3r2[ndx + ndx1].clone();
							sum += vs[ndx + ndx1] * img.at<uchar>(y, x2r);
							zn += vs[ndx + ndx1];
						}
					}
				}
				spd = 0;
				x2 = x;
				for (int ndx1 = -ndx; ndx1 < 0; ++ndx1)
				{
					if (n + ndx1 >= 0 && n + ndx1 <= N - 1)
					{
						x2 -= spd;
						int x2r = round(x2); //?
						if (x2r >= 0 && x2r <= dnum - 1)
						{
							spd = shfv6b[n * cols_shfv6b + x2r] / dt;
							Mat img = resA3r2[ndx + ndx1].clone();
							sum += vs[ndx + ndx1] * img.at<unsigned char>(y, x2r);
							zn += vs[ndx + ndx1];
						}
					}
				}
				double res = 127.0 + cntr*(sum / zn - 127.0);
				if (res < 0.000001)
					res = 0.0;
				if (abs(res - 255) < 0.00001)
					res = 255.0;
				result.at<uchar>(y, x) = (uchar)res;
			}
		}
		resA3r1[n] = result;
	}
}

void get_stdev(uchar* arr, int size, double& result) 
{
	double mean = 0;
	for (int i = 0; i < size; i++)
		mean += arr[i];

	mean /= size;

	double variance = 0;
	for (int i = 0; i < size; i++)
		variance = variance + (arr[i] - mean) * (arr[i] - mean);

	variance /= (size - 1);

	result = sqrt(variance);
}

void transform_images(uchar** arr, string dir, int N, int ktr, int ktr1, int image_rows, int image_cols)
{
	for (int i = 0; i < N; i++)
	{
		Mat image;
		read_file_ktr(dir, image, ktr, ktr1, i);
		for (int r = 0; r < image_rows; r++)
			for (int c = 0; c < image_cols; c++)
			{
				arr[r * image_cols + c][i] = image.at<uchar>(r, c);
			}
	}	
}

void get_disp(string dir, int N, int ktr, int ktr1, int image_rows, int image_cols, string dir_out, double cntr)
{
	uchar** arr; // arr = pixels X image count (image_rows * image_cols  X N)
	arr = (uchar**)malloc(sizeof(uchar*) * image_rows * image_cols);
	for (int i = 0; i < image_rows * image_cols; i++)
		arr[i] = (uchar*)malloc(sizeof(uchar) * N);

	transform_images(arr, dir, N, ktr, ktr1, image_rows, image_cols);

	Mat image_disp(image_rows, image_cols, DataType<uchar>::type);

	double* disp;
	disp = (double*)malloc(sizeof(double) * image_cols * image_rows);
	//double sum = 0;

	for (int i = 0; i < image_rows; i++)
		for (int j = 0; j < image_cols; j++)
		{
			double res = 0;
			get_stdev(arr[i * image_cols + j], N, res);
			//sum += res;
			disp[i * image_cols + j] = res;
		}

	// write result as image and as txt
	for (int i = 0; i < image_rows; i++)
		for (int j = 0; j < image_cols; j++)
		{
			//disp[i * image_cols + j] /= sum;
			uchar temp = uchar(disp[i * image_cols + j] *cntr);
			image_disp.at<uchar>(i, j) = temp;
		}


	string img_file_name_txt = dir_out + "\\img_ktr_" + to_string(ktr) + "_ktr1_" + to_string(ktr1) + ".txt"; 
	ofstream file_disp_txt;
	file_disp_txt.open(img_file_name_txt);
	for (int i = 0; i < image_rows; i++)
	{
		for (int j = 0; j < image_cols; j++)
		{
			file_disp_txt << disp[i * image_cols + j] << "  ";
		}
		file_disp_txt << endl;
	}
	string img_file_name = dir_out + "\\img_ktr_" + to_string(ktr) + "_ktr1_" + to_string(ktr1) + ".bmp"; 
	imwrite(img_file_name, image_disp);

}




double g1(int r)
{
	return 0.125 + pow((1 + cos(M_PI * r / 100)), 0.75);
}

double ves2d(int y1, int x1, int ym, int xm)
{
	double sqr = y1*y1 + (x1 * ym / xm) * (x1 * ym / xm);
	double g2 = 0;
	if (sqr <= (ym*ym))
		g2 = g1((int)round(sqr * 100 / (ym*ym)));
	else
		g2 = 0;
	return  g2;
}

void blur_images(string dir_in, string dir_out, int ktr, int dn1, int dn2, int dn11st, int dn22st)
{
	for (int ktr1 = 0; ktr1 <= ktr; ++ktr1)
	{
		string img_file_name = dir_in + "\\img_ktr_" + to_string(ktr) + "_ktr1_" + to_string(ktr1) + ".bmp";
		Mat image;
		image = imread(img_file_name, CV_LOAD_IMAGE_GRAYSCALE);
		int N = image.rows;
		int dnum = image.cols;
		
		double* gv;
		gv = (double*)malloc(sizeof(double) * (dn1 + 1) * (dn2 + 1));
		for (int dn11 = 0; dn11 <= dn1; ++dn11)
			for (int dn22 = 0; dn22 <= dn2; ++dn22)
				gv[dn11 * dn2 + dn22] = ves2d(dn11, dn22, dn1, dn2);

		Mat img_result = image.clone();

		for (int n1 = 0; n1 < N; ++n1)
			for (int n2 = 0; n2 < dnum; ++n2)
			{
				double sum = 0;
				double z = 0;

				int na_min = n1 - dn1;
				if (na_min < 0)
					na_min = n1 % dn11st;

				int na_max = 0;
				na_max = min(N - 1, n1 + dn1 - 1);

				int aa_min = n2 - dn2;
				if (aa_min < 0)
					aa_min = n2 % dn22st;

				int dnum_max = dnum; ///?

				int aa_max = 0;
				aa_max = min(dnum_max - 1, n2 + dn2 - 1);

				for (int dn11 = na_min; dn11 < na_max; dn11 += dn11st)
					for (int dn22 = aa_min; dn22 < aa_max; dn22 += dn22st)
					{
						double resg = gv[abs(dn11 - n1)*dn2 + abs(dn22 - n2)];
						sum += ((double)image.at<uchar>(dn11, dn22)) * resg;
						z += resg;
					}
				if (z > 0.000001)
				{
					double temp = sum / z;
					img_result.at<uchar>(n1, n2) = (uchar)(sum / z);
				}
				else
					img_result.at<uchar>(n1, n2) = 0;
			}
		string img_result_file_name = dir_out + "\\img_ktr_" + to_string(ktr) + "_ktr1_" + to_string(ktr1) + ".bmp";
		imwrite(img_result_file_name, img_result);
	}

}

void line_correction(string dir_shfv6b, int ktr, int x0, int dy, int rs, int dyd, 
					 string dir_result, int disp_size_rows=49, int disp_size_cols=282)
{
	//from matchcad: data1 = arr(ktr, [disp, shifts]);

	//read all disps per ktr
	double** disp_per_ktr;
	disp_per_ktr = (double**)malloc(sizeof(double) * (ktr + 1));
	for (int ktr1 = 0; ktr1 <= ktr; ++ktr1)
	{
		disp_per_ktr[ktr1] = (double*)malloc(sizeof(double) * disp_size_cols * disp_size_rows);
		string img_file_name_txt = dir_shfv6b + "\\img_ktr_" + to_string(ktr) + "_ktr1_" + to_string(ktr1) + ".txt";
		ifstream file_disp_txt;
		file_disp_txt.open(img_file_name_txt);
		for (int i = 0; i < disp_size_rows; i++)
			for (int j = 0; j < disp_size_cols; j++)
				file_disp_txt >> disp_per_ktr[ktr1][i * disp_size_cols + j];
	}
	Mat image_rc;
	string img_file_name_bmp = dir_shfv6b + "\\img_ktr_" + to_string(ktr) + "_ktr1_" + to_string(0) + ".bmp";
	image_rc = imread(img_file_name_bmp, CV_LOAD_IMAGE_GRAYSCALE);

	for (int i = 0; i < disp_size_rows; ++i)
		for (int j = 0; j < disp_size_cols; ++j)
			image_rc.at<uchar>(i, j) *= 3;
	
	double* dys_22;
	dys_22 = (double*)malloc(sizeof(double) * disp_size_cols * disp_size_rows);
	memcpy(dys_22, disp_per_ktr[0], sizeof(double) * disp_size_cols * disp_size_rows); 

	int Y = disp_size_rows;
	int X = disp_size_cols;

	double *vs;
	vs = (double*)malloc(sizeof(double) * 150);
	double *gg;
	gg = (double*)malloc(sizeof(double) * 150);
	gg1(gg);

	for (int y = 0; y < Y; ++y)
	{
		double** sig0;
		int sig0_size = (2 * dyd + 1);
		sig0 = (double**)malloc(sizeof(double) * sig0_size);
		for (int i = 0; i < sig0_size; ++i)
			sig0[i] = (double*)malloc(sizeof(double) * (ktr + 1));

		for (int y1 = y - dyd; y1 <= y + dyd; ++y1)
		{
			if (y1 >= 0 && y1 <= (Y - 1))
			{
				for (int ktr1 = 0; ktr1 <= ktr; ++ktr1)
					sig0[y1 - y + dyd][ktr1] = disp_per_ktr[ktr1][y1 * disp_size_cols + x0];
				vs[y1 - y + dyd] = gg[(int)round(abs((y1 - y) * 99) / dyd)];
			}
		}
		if (y % 5 == 0)
			printf("line_correction: y = %d / %d\n", y, Y);

		for (int x = 0; x < X; ++x)
		{
			double **sig;
			int sig_size = (2 * dyd + 1);
			sig = (double**)malloc(sizeof(double) * (2 * dyd + 1));
			for (int i = 0; i < sig_size; ++i)
				sig[i] = (double*)malloc(sizeof(double) * (ktr + 1));

			for (int y1 = y - dyd; y1 < y + dyd; ++y1)
			{				
				if (y1 >= 0 && y1 <= (Y - 1))
					for (int ktr1 = 0; ktr1 <= ktr; ++ktr1)
						sig[y1 - y + dyd][ktr1] = disp_per_ktr[ktr1][y1 * disp_size_cols + x];
			}
			double max1 = INT32_MAX; // min in reality
			int max1y = 0;
			for (int dy1 = -dy; dy1 <= dy; ++dy1)
			{
				double dsig = 0;
				double z = 0;
				for (int y1 = y - dyd; y1 < y + dyd; ++y1)
				{
					if (y1 >= 0 && y1 <= (Y - 1))
					{
						int ys = y1 + dy1;
						if (ys >= 0 && ys <= (Y - 1) && ys >= (y - dyd) && ys <= (y + dyd))
						{
							for (int ktr1 = 0; ktr1 <= ktr; ++ktr1)
								dsig = dsig + vs[y1 - y + dyd] * (sig[y1 - y + dyd][ktr1] - sig0[y1 - y + dyd][ktr1]) * (sig[y1 - y + dyd][ktr1] - sig0[y1 - y + dyd][ktr1]);
							z += vs[y1 - y + dyd];
						}
					}
				}
				dsig = sqrt(dsig) / z;
				if (dsig < max1)
				{
					max1 = dsig;
					max1y = dy1;
				}
			}

			dys_22[y * disp_size_cols + x] = max1y;
			int y2 = y + max1y;
			if (y2 > 0 && y2 <= Y - 1 && y >= 3 && y <= Y - 4 && (y % 5 == 0))
				image_rc.at<uchar>(y2, x) = 0;
		}
	}
	imwrite(dir_result + "line_correction_result.bmp", image_rc);

	string dys22_file_txt = dir_result + "\\_line_correction_shifts_dy.txt";
	ofstream file_dys22_txt;
	file_dys22_txt.open(dys22_file_txt);
	for (int i = 0; i < disp_size_rows; ++i)
	{
		for (int j = 0; j < disp_size_cols; ++j)
			file_dys22_txt << dys_22[i * disp_size_cols + j] << " ";
		file_dys22_txt << endl;
	}
}

void blf_pvf_use_shifts(vector <Mat>& images, vector <Mat>& resA3r1, double* shfv6b, string dir_shifts, 
	int ndx, int dnum, double dt, int N2, double cntr)
{
	int N = min((int)images.size(), N2);
	int Y = images[0].rows;
	int X = images[0].cols;
	int s = images.size(); 

	int disp_size_rows = Y;
	int disp_size_cols = X;

	double* dys_22;
	dys_22 = (double*)malloc(sizeof(double) * disp_size_cols * disp_size_rows);
	
	string shifts_file_txt = dir_shifts + "\\_line_correction_shifts_dy.txt";
	ifstream file_dys22_txt;
	file_dys22_txt.open(shifts_file_txt);
	for (int i = 0; i < disp_size_rows; ++i)
		for (int j = 0; j < disp_size_cols; ++j)
			file_dys22_txt >> dys_22[i * disp_size_cols + j];	

	for (int i = 0; i < s; ++i)
		resA3r1.push_back(images[i].clone());

	for (int n = 0; n < N; n++)
	{
		if (n % 100 == 0)
			printf("blf_pvf_use_shifts: n = %d\n", n);

		vector <Mat> resA3r2;
		resA3r2.resize(ndx * 2);

		Mat result = images[n].clone();

		double *vs;
		vs = (double*)malloc(sizeof(double) * 150);
		double *gg;
		gg = (double*)malloc(sizeof(double) * 150);
		gg1(gg);

		for (int j = -ndx; j < ndx; j++)
		{
			if (n + j >= 0 && n + j <= N - 1)
			{
				resA3r2[j + ndx] = images[n + j].clone();
				vs[j + ndx] = gg[(int)round(abs(j * 50) / ndx)];
			}
		}

		for (int y = 0; y < Y; ++y)
		{
			for (int x = 0; x < X; ++x)
			{
				double sum = 0;
				double zn = 0;
				double spd = 0;
				int x2 = x;
				int dy0 = dys_22[y * disp_size_cols + x];
				for (int ndx1 = 0; ndx1 < ndx; ++ndx1)
				{
					if (n + ndx1 >= 0 && n + ndx1 <= N - 1)
					{
						x2 += spd;
						int x2r = round(x2); //?
						if (x2r >= 0 && x2r <= dnum - 1)
						{
							spd = shfv6b[n * cols_shfv6b + x2r] / dt;
							int y2 = y + (dys_22[y * disp_size_cols + x2r] - dy0);
							if (y2 >= 0 && y2 <= (Y - 1)) 
							{
								Mat img = resA3r2[ndx + ndx1].clone();
								sum += vs[ndx + ndx1] * img.at<uchar>(y, x2r);
								zn += vs[ndx + ndx1];
							}							
						}
					}
				}
				spd = 0;
				x2 = x;
				for (int ndx1 = -ndx; ndx1 < 0; ++ndx1)
				{
					if (n + ndx1 >= 0 && n + ndx1 <= N - 1)
					{
						x2 -= spd;
						int x2r = round(x2); //?
						if (x2r >= 0 && x2r <= dnum - 1)
						{
							spd = shfv6b[n * cols_shfv6b + x2r] / dt;
							int y2 = y + (dys_22[y * disp_size_cols + x2r] - dy0);
							if (y2 >= 0 && y2 <= (Y - 1))
							{
								Mat img = resA3r2[ndx + ndx1].clone();
								sum += vs[ndx + ndx1] * img.at<unsigned char>(y, x2r);
								zn += vs[ndx + ndx1];
							}

						}
					}
				}
				double res = 127.0 + cntr*(sum / zn - 127.0);
				if (res < 0.000001)
					res = 0.0;
				if (abs(res - 255) < 0.00001)
					res = 255.0;
				result.at<uchar>(y, x) = (uchar)res;
			}
		}
		resA3r1[n] = result;
	}
}

void get_all_profiles(int ktr, int ktr_st, string dir3cr, int N, string dir_tmp0, string dir_tmp1,
	double kmx, double kmn, int N2, double dt, double cntr, double img_cntr,
	int dnum, int ndx,
	bool use_shifts=0, string dir_shifts="")
{
	printf("get_all_profilles\n");
	vector <Mat> images;
	read_out3cr(dir3cr, N, images);

	int rows = images[0].rows;
	int cols = images[0].cols;

	double *shfv6b;
	shfv6b = (double*)malloc(sizeof(double) * rows_shfv6b * cols_shfv6b);
	read_shfv6b(file_shfv6b_txt, shfv6b);

	for (int ktr1 = 0; ktr1 <= ktr_st; ++ktr1)
	{
		printf("ktr=%d\n", ktr1);
		double *shfv6b_mult;
		shfv6b_mult = (double*)malloc(sizeof(double*) * rows_shfv6b * cols_shfv6b);

		double shfv6b_ktr = kmn + (kmx - kmn) * ktr1 / ktr;
		mult_ktr_shfv6b(shfv6b, shfv6b_ktr, shfv6b_mult);

		//save shfv6b
		string shfv6b_file_name = dir_tmp1 + "\\shfv6b_ktr_" + to_string(ktr) + "_ktr1_" + to_string(ktr1) + ".txt";
		write_shfv6b(shfv6b_file_name, shfv6b_mult);

		vector <Mat> resA3r;
		if (use_shifts)
			blf_pvf_use_shifts(images, resA3r, shfv6b_mult, dir_shifts, ndx, dnum, dt, N2, cntr);
		else
			blr_pvf32(images, resA3r, shfv6b_mult, ndx, dnum, dt, N2, cntr);

		write_file_ktr(dir_tmp0, N, resA3r, ktr, ktr1);

		get_disp(dir_tmp0, N, ktr, ktr1, rows, cols, dir_tmp1, img_cntr);
	}
}