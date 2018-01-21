#include "cfg_parameters.h"

int process_cfg_file(string cfg_file_path, CfgParametersValues& params)
{
	ifstream cfg_file;
	cfg_file.open(cfg_file_path.c_str(), std::ifstream::in);

	map<string, string> params_map;

	while (!cfg_file.eof())
	{
		string cfg_line;
		getline(cfg_file, cfg_line);
		if (cfg_line.empty())
			continue;
		if (cfg_line.find('*') == 0)
			continue;
		size_t eq_position = cfg_line.find('=');
		if (eq_position == std::string::npos)
			return 1;
		string param_name = cfg_line.substr(0, eq_position);
		string param_value = cfg_line.substr(eq_position + 1);
		printf("Found param: name = %s, value = %s\n", param_name.c_str(), param_value.c_str());
		params_map.insert(pair<string, string>(param_name, param_value));
	}

	CfgParametersNames CfgParamNames;

	std::map<string, string>::iterator it;

	//// DIR_INPUT - string
	//it = params_map.find(CfgParamNames.DIR_INPUT);
	//if (it == params_map.end())
	//{
	//	printf("Unable to process %s parameters\n", CfgParamNames.DIR_INPUT); //
	//	return 1;
	//}
	//params.DIR_INPUT = params_map[CfgParamNames.DIR_INPUT];

	// DIR_OUTPUT - string
	it = params_map.find(CfgParamNames.DIR_OUTPUT);
	if (it == params_map.end())
		return 1;
	params.DIR_OUTPUT = params_map[CfgParamNames.DIR_OUTPUT];

	// KTR - int
	it = params_map.find(CfgParamNames.KTR);
	if (it == params_map.end())
		return 1;
	params.KTR = atoi(params_map[CfgParamNames.KTR].c_str());

	// KTR_ST - int
	it = params_map.find(CfgParamNames.KTR_ST);
	if (it == params_map.end())
		return 1;
	params.KTR_ST = atoi(params_map[CfgParamNames.KTR_ST].c_str());

	// DIR_INPUT_OUT3CR - string
	it = params_map.find(CfgParamNames.DIR_INPUT_OUT3CR);
	if (it == params_map.end())
		return 1;
	params.DIR_INPUT_OUT3CR = params_map[CfgParamNames.DIR_INPUT_OUT3CR];

	// N - int
	it = params_map.find(CfgParamNames.N);
	if (it == params_map.end())
		return 1;
	params.N = atoi(params_map[CfgParamNames.N].c_str());
	
	// DIR_BLURRED - string
	it = params_map.find(CfgParamNames.DIR_BLURRED);
	if (it == params_map.end())
		return 1;
	params.DIR_BLURRED = params_map[CfgParamNames.DIR_BLURRED];

	// KMX - double
	it = params_map.find(CfgParamNames.KMX);
	if (it == params_map.end())
		return 1;
	params.KMX = stod(params_map[CfgParamNames.KMX].c_str());

	// KMN - double
	it = params_map.find(CfgParamNames.KMN);
	if (it == params_map.end())
		return 1;
	params.KMN = stod(params_map[CfgParamNames.KMN].c_str());

	// N2 - int
	it = params_map.find(CfgParamNames.N2);
	if (it == params_map.end())
		return 1;
	params.N2 = atoi(params_map[CfgParamNames.N2].c_str());

	// DT - double
	it = params_map.find(CfgParamNames.DT);
	if (it == params_map.end())
		return 1;
	params.DT = stod(params_map[CfgParamNames.DT].c_str());

	// CNTR - double
	it = params_map.find(CfgParamNames.CNTR);
	if (it == params_map.end())
		return 1;
	params.CNTR = stod(params_map[CfgParamNames.CNTR].c_str());

	// IMG_CNTR - double
	it = params_map.find(CfgParamNames.IMG_CNTR);
	if (it == params_map.end())
		return 1;
	params.IMG_CNTR = stod(params_map[CfgParamNames.IMG_CNTR].c_str());

	// NDX - int
	it = params_map.find(CfgParamNames.NDX);
	if (it == params_map.end())
		return 1;
	params.NDX = atoi(params_map[CfgParamNames.NDX].c_str());

	// DNUM - int
	it = params_map.find(CfgParamNames.DNUM);
	if (it == params_map.end())
		return 1;
	params.DNUM = atoi(params_map[CfgParamNames.DNUM].c_str());
	
	// X0 - int
	it = params_map.find(CfgParamNames.X0);
	if (it == params_map.end())
		return 1;
	params.X0 = atoi(params_map[CfgParamNames.X0].c_str());

	// DY - int
	it = params_map.find(CfgParamNames.DY);
	if (it == params_map.end())
		return 1;
	params.DY = atoi(params_map[CfgParamNames.DY].c_str());

	// RS - int
	it = params_map.find(CfgParamNames.RS);
	if (it == params_map.end())
		return 1;
	params.RS = atoi(params_map[CfgParamNames.RS].c_str());

	// DYD - int
	it = params_map.find(CfgParamNames.DYD);
	if (it == params_map.end())
		return 1;
	params.DYD = atoi(params_map[CfgParamNames.DYD].c_str());

	// DIR_SHFV6B - string
	it = params_map.find(CfgParamNames.DIR_SHFV6B);
	if (it == params_map.end())
		return 1;
	params.DIR_SHFV6B = params_map[CfgParamNames.DIR_SHFV6B];

	// DIR_LINE_CORRECTION - string
	it = params_map.find(CfgParamNames.DIR_LINE_CORRECTION);
	if (it == params_map.end())
		return 1;
	params.DIR_LINE_CORRECTION = params_map[CfgParamNames.DIR_LINE_CORRECTION];

	// GET_ALL_PROFILES - int/bool
	it = params_map.find(CfgParamNames.GET_ALL_PROFILES);
	if (it == params_map.end())
		return 1;
	params.GET_ALL_PROFILES = atoi(params_map[CfgParamNames.GET_ALL_PROFILES].c_str());

	// DIR_LINE_CORRECTION - int/bool
	it = params_map.find(CfgParamNames.LINE_CORRECTION);
	if (it == params_map.end())
		return 1;
	params.LINE_CORRECTION = atoi(params_map[CfgParamNames.LINE_CORRECTION].c_str());

	// GET_ALL_PROFILES_USE_SHIFTS - int/bool
	it = params_map.find(CfgParamNames.GET_ALL_PROFILES_USE_SHIFTS);
	if (it == params_map.end())
		return 1;
	params.GET_ALL_PROFILES_USE_SHIFTS = atoi(params_map[CfgParamNames.GET_ALL_PROFILES_USE_SHIFTS].c_str());
	
	return 0;
}
