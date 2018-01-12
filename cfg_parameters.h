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
	string DNUM = "DNUM";
	string NDX = "NDX";
};

// set default values
struct CfgParametersValues
{
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

};

int process_cfg_file(string cfg_file_path, CfgParametersValues& params);

#endif // CFG_PARAMETERS_H
