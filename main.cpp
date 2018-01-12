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
		params.NDX// img_cntr = 4.5 (?) for saving images in get_disp()
	); // add ndx = 16, 
	// add dnum = 282
	system("pause");
	return 0;
}