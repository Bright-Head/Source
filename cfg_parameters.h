#ifndef CFG_PARAMETERS_H
#define CFG_PARAMETERS_H

#include <string>
#include <fstream>
#include <map>
using namespace std;

struct CfgParametersNames
{
	string DIR_INPUT = "DIR_INPUT";
	string DIR_OUTPUT = "DIR_OUTPUT"; //".\\input_data\\dir_tmp1"
	string KTR = "KTR"; // 27
	string KTR_ST = "KTR_ST"; // 27
	string DIR_INPUT_OUT3CR = "DIR_INPUT_OUT3CR"; // ".\\input_data\\out3cr"
	string N = "N"; // 50
	string DIR_BLURRED = "DIR_BLURRED"; // ".\\input_data\\dir_tmp0"
	string KMX = "KMX"; // 2.5
	string KMN = "KMN"; // -0.2
	string N2 = "N2"; // 50
	string DT = "DT"; // 1
	string CNTR = "CNTR"; // 1.75
	string IMG_CNTR = "IMG_CNTR"; // 4.5
	string DNUM = "DNUM"; //282
	string NDX = "NDX"; //16
	string GET_ALL_PROFILES = "GET_ALL_PROFILES";
	string LINE_CORRECTION = "LINE_CORRECTION";
	string DIR_SHFV6B = "DIR_SHFV6B"; //.\\input_data\\dir_tmp2
	string X0 = "X0"; //100
	string DY = "DY"; //7
	string RS = "RS"; //24
	string DYD = "DYD"; //32
	string DIR_LINE_CORRECTION = "DIR_LINE_CORRECTION"; //".\\input_data\\"
	string GET_ALL_PROFILES_USE_SHIFTS = "GET_ALL_PROFILES_USE_SHIFTS";
	string DIR_SHIFTS = "DIR_SHIFTS";
};

// set default values
struct CfgParametersValues
{
	int GET_ALL_PROFILES = 1;
	string DIR_INPUT = "";
	string DIR_OUTPUT = "";
	int KTR = 0;
	int KTR_ST = 0;
	string DIR_INPUT_OUT3CR = "";
	int N = 0;
	string DIR_BLURRED = "";
	double KMX = 0.;
	double KMN = 0.;
	int N2 = 0;
	double DT = 0.;
	double CNTR = 0.;
	double IMG_CNTR = 0.;
	int DNUM = 0;
	int NDX = 0;
	
	int LINE_CORRECTION = 1;
	string DIR_SHFV6B = "";
	int X0 = 0;
	int DY = 0;
	int RS = 0; // int - ??
	int DYD = 0;
	string DIR_LINE_CORRECTION = "";

	int GET_ALL_PROFILES_USE_SHIFTS = 1;
	string DIR_SHIFTS = "";


};

int process_cfg_file(string cfg_file_path, CfgParametersValues& params);

#endif // CFG_PARAMETERS_H
