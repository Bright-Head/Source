#include "parameters.h"
#include <fstream>
#include "bmp_lib.h"

struct Point 
{
  int x;
  int y;
  Point(int _x, int _y): x(_x), y(_y) {};
};

void read_file_file_resyx31(double *output_array, int &rows)
{
  string file_name = file_resyx31_txt;
  FILE* file = fopen(file_name.c_str(), "rb");
  fseek(file, 0, SEEK_END);
  long size = ftell(file);
  fseek(file, 0, SEEK_SET);
  if (!rows)
    rows = (int)(size / sizeof(double) / 2);
  int cols = 2;
  output_array = (double*)malloc(rows * cols);
  for (int i = 0; i < rows; ++i)
    for (int j = 0; j < cols; ++j)
      fread(&output_array[i * rows + cols], sizeof(double), 1, file);

  fclose(file);
  
}

// сместиться вдоль трека на определенную точку
void get_xy(double *res_yx, int rows, int cols, int coord, int &x, int &y) // coord = shift
{
  if (coord > rows)
    coord = rows - 1;
  if (coord < 0)
    coord = 0;
  int coord_int = (int)trunc(coord); //tc 
  if (coord_int == rows - 1)
    coord_int = rows - 2;
  x = res_yx[coord_int * rows + 1] * (coord_int + 1 - coord) + res_yx[(coord_int + 1) * rows + 1] * (coord - 1);
  y = res_yx[coord_int * rows] * (coord_int + 1 - coord) + res_yx[(coord_int + 1) * rows] * (coord - 1);
}

void resa_(double *res_yx, int rows, int dcoord, double* resa, double** resa_cs)
{
  int dnum = rows;
  int cols = 2; // для resyx cols = 2 by default
  resa = (double*)malloc((dnum) * sizeof(double));
  resa_cs = (double**)malloc((dnum) * sizeof(double*));
  for (int i = 0; i < dnum; ++i)
    resa_cs[i] = (double*)malloc(2 * sizeof(double));

  for (int n2 = 0; n2 < dnum; ++n2)
  {
    int x1 = 0,
      y1 = 0,
      x2 = 0,
      y2 = 0;
    get_xy(res_yx, rows, cols, n2 - dcoord, x1, y1);
    get_xy(res_yx, rows, cols, n2 + dcoord, x2, y2);
    try
    {
      resa[n2] = atan2( -(y2-y1),  x2-x1 );
    }
    catch (...)
    {
      continue;
    }
  }
  for (int n2 = 0; n2 < dnum; ++n2)
  {
    double res = resa[n2];
    while (res < 0)
      res += 2*M_PI;
    while (res >= 2*M_PI)
      res -= 2*M_PI;
    resa[n2] = res;
    resa_cs[n2][0] = cos(res);
    resa_cs[n2][1] = sin(res);
  }
}

double geta(double *resa, int rows_resa, int coord) //coord - int?
{
  int trn = rows_resa;
  if (coord > trn - 1)
    coord = trn - 1;
  if (coord < 0)
    coord = 0;
  int tc = trunc(coord);
  if (trn - 1 == tc)
    tc = trn - 2;
  double r1 = resa[tc];
  double r2 = resa[tc+1];
  if ((r2 - r1) - M_PI > 0.0001) 
    r1 += 2 * M_PI;
  if ((r1 - r2) - M_PI > 0.0001)
    r2 += 2 * M_PI;
  double resal = r1 * (tc + 1 - coord) + r2 *(coord - tc);
  while (resal > 2 * M_PI)
    resal -= 2 * M_PI;
  while (resal < 0)
    resal += 2 * M_PI;
  return resal;
}

void geta_cs(double** resa_cs, int rows_resa, int coord, double &)
{
  int trn = rows_resa;
  if (coord > trn - 1)
    coord = trn - 1;
  if (coord < 0)
    coord = 0;
    int tc = trunc(coord);
  if (trn - 1 == tc)
    tc = trn - 2;
  double ress1 = resa_cs[tc][0] * (tc + 1 - coord) + resa_cs[tc+1][0] * (coord - tc);
  double resc1 = resa_cs[tc][1] * (tc + 1 - coord) + resa_cs[tc+1][1] * (coord - tc);
}

///TODO, instead tr3_bin.bin
//void read_tr3_bmp()
//{
//  FILE* file = fopen(file_tr3_bmp.c_str(), "rb");
//  BMPheader header;
//  fread(&header, sizeof(header), 1, file);
//  int mx = header.biWidth;
//  int my = header.biHeight;
//
//
//
//
//}

void read_tr3_bin(unsigned char* tr3)
{
  FILE* file = fopen(file_tr3_bin.c_str(), "rb");
  tr3 = (unsigned char*)malloc(sizeof(unsigned char) * rows_tr3 * cols_tr3);
  fread(tr3, sizeof(unsigned char), rows_tr3 * cols_tr3, file);

}

void process_tr3(unsigned char* tr3, double* resa, int &rows_resa, double *ang2, 
                 double *resyx, int &rows_resyx, unsigned char* tr5)
{
  for (int n2 = 0; n2 < rows_resa; ++n2)
  {
    for (int k = 0; k < 10; ++k)
    {
      double ang1 = resa[n2];
      ang2[n2] = geta(resa, rows_resa, n2) + M_PI;
      if (n2 % 10 == 0)
      {
        double y = resyx[n2*rows_resyx] - k * sin(ang2[n2]);
        double x = resyx[n2* rows_resyx + 1] - k * cos(ang2[n2]);
        int y_ = (int)round(y);
        int x_ = (int)round(x);
        if (y_ >= 0 && x_ >=0) /// smth like this
          tr5[y_*rows_tr3 + x_] = 2;
      }
    }
  }
}

void shft_tr(double* resyx, int rows_resyx, double* resa, int rows_resa, int mv, double* resyx32)
{
  for (int n2 = 0; n2 < rows_resyx; ++n2)
  {
      double ang1 = resa[n2];
      double ang2 = geta(resa, rows_resa, n2) + M_PI; ///////array ang2 instead of var
      double y = resyx[n2*rows_resyx] - mv * sin(ang2);
      double x = resyx[n2* rows_resyx + 1] - mv * cos(ang2);
  }
}

void read_res2_synt_nbkg(unsigned char* synt, int rows_synt, int cols_synt)
{
  FILE* file = fopen(file_res2_synt_nbkg.c_str(), "rb");
  synt = (unsigned char*)malloc(sizeof(unsigned char) * rows_synt * cols_synt);
  fread(synt, sizeof(unsigned char), rows_synt * cols_synt, file);
}

void dr_tr(unsigned char* synt, double* resa, double* resyx, int rows_resyx, unsigned char* tr, double* ang2, int rows_synt)
{
  for (int i = 0; i < rows_resyx; ++i)
  {
    double ang1 = resa[i];
    ang2[i] = geta(resa, rows_resyx, i) + M_PI;
    int y = round(resyx[i * rows_resyx]);
    int x = round(resyx[i * rows_resyx + 1]);
    tr[y * rows_synt + x] = 0;
  }
}

//////
void read_file(int num_dig, int num, string dir)
{

}

//////

#if 0
int main() 
{
  double *resyx;
  int rows_resyx = 0; 
  int cols_resyx = 2;

  read_file_file_resyx31(resyx, rows_resyx);

  int dcoord = 3;
  double **resa_cs;
  double* resa;  
  resa_(resyx, rows_resyx, dcoord, resa, resa_cs);

  int rows_resa = rows_resyx; //dnum

  unsigned char* tr3;
  read_tr3_bin(tr3);

  unsigned char* tr5;
  for (int i = 0; i < rows_tr3 * cols_tr3; ++i)
    tr5[i * rows_tr3 + cols_tr3] = tr3[i * rows_tr3 + cols_tr3];

  double *ang2;
  ang2 = (double*)malloc(sizeof(double) * rows_resa);
  process_tr3(tr3, resa, rows_resa, ang2, resyx, rows_resyx, tr5);  //(tr5, ang2)
  
  
  double* resyx32;
  resyx32 = (double*)malloc(sizeof(double) * cols_resyx * rows_resyx);
    for (int i = 0; i < rows_resyx * cols_resyx; ++i)
    resyx32[i * rows_resyx + cols_resyx] = resyx[i * rows_resyx + cols_resyx];

  double* resyx33;
  resyx33 = (double*)malloc(sizeof(double) * cols_resyx * rows_resyx);
  for (int i = 0; i < rows_resyx * cols_resyx; ++i)
    resyx33[i * rows_resyx + cols_resyx] = resyx[i * rows_resyx + cols_resyx];

  int mv = 16; ///??????

  shft_tr(resyx, rows_resyx, resa, rows_resa, -mv, resyx32);
  shft_tr(resyx, rows_resyx, resa, rows_resa, mv, resyx33);

  unsigned char* tr2;
  for (int i = 0; i < rows_tr3 * cols_tr3; ++i)
    tr2[i * rows_tr3 + cols_tr3] = tr3[i * rows_tr3 + cols_tr3];

  //resyx read again ?

  unsigned char* synt;
  synt = (unsigned char*)malloc(sizeof(unsigned char) * rows_synt * cols_synt);
  read_res2_synt_nbkg(synt, rows_synt, cols_synt);
  
  unsigned char* tr;
  int rows_tr = rows_synt;
  int cols_tr = cols_synt;
  tr = (unsigned char*)malloc(sizeof(unsigned char) * rows_synt * cols_synt);
  dr_tr(synt, resa, resyx, rows_resyx, tr, ang2, rows_synt);

  return 0;
}
#endif

int main()
{

  return 0;
}