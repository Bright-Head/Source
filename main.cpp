#include "get_disp_functions.h"
#include "cfg_parameters.h"
#include <fstream>

int main()
{
	CfgParametersValues params;
	if (process_cfg_file("conf.txt", params))
	{
		return 1;
	}
	if (params.GET_ALL_PROFILES)
		get_all_profiles(
			params.KTR,
			params.KTR_ST,
			params.DIR_INPUT_OUT3CR,
			params.N,
			params.DIR_BLURRED,
			params.DIR_OUTPUT,
			params.KMX,
			params.KMN,
			params.N2,
			params.DT,
			params.CNTR,
			params.IMG_CNTR,
			params.DNUM,
			params.NDX,
			0,
			""
		); 

	//blur_images(".\\input_data\\dir_tmp1\\",
	//	".\\input_data\\dir_blurred\\",
	//	params.KTR,
	//	3,
	//	6,
	//	1,
	//	1
	//);

	if (params.LINE_CORRECTION)
		line_correction(
			params.DIR_SHFV6B,
			params.KTR,
			params.X0,
			params.DY,
			params.RS,
			params.DYD,
			params.DIR_LINE_CORRECTION,
			49,
			282
		);

	if (params.GET_ALL_PROFILES_USE_SHIFTS)
		get_all_profiles(
			params.KTR,
			params.KTR_ST,
			params.DIR_INPUT_OUT3CR,
			params.N,
			params.DIR_BLURRED,
			params.DIR_OUTPUT,
			params.KMX,
			params.KMN,
			params.N2,
			params.DT,
			params.CNTR,
			params.IMG_CNTR,
			params.DNUM,
			params.NDX,
			1,
			params.DIR_SHIFTS
		);

	system("pause");
	return 0;
}