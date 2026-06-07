#include "../include/Retro_MFA.h"

void set_flip_alignment(t_manual *alignment)
{
	//white4: 20, 34 - 51, 53, 54, 57, 58, 59
	alignment[0].byte0 = build_4_bytes_int((uint8_t[4]){0xD7, 0xB1, 0x00, 0x00}); // 5
	alignment[0].addr = 0x21581;
	alignment[1].byte0 = build_4_bytes_int((uint8_t[4]){0x64, 0x86, 0x00, 0x00}); // 20
	alignment[1].addr = 0x69C4D;
	alignment[2].byte0 = build_4_bytes_int((uint8_t[4]){0x13, 0x20, 0x00, 0x00}); // 34
	alignment[2].addr = 0xB2319;
	alignment[3].byte0 = build_4_bytes_int((uint8_t[4]){0x72, 0xC4, 0x00, 0x00}); // 35
	alignment[3].addr = 0xBB54D;
	alignment[4].byte0 = build_4_bytes_int((uint8_t[4]){0x8A, 0x43, 0x00, 0x00}); // 36
	alignment[4].addr = 0xC0071;
	alignment[5].byte0 = build_4_bytes_int((uint8_t[4]){0x9A, 0x3B, 0x00, 0x00}); // 37
	alignment[5].addr = 0xC4B95;
	alignment[6].byte0 = build_4_bytes_int((uint8_t[4]){0xF5, 0x5C, 0x00, 0x00}); // 38
	alignment[6].addr = 0xC96B9;
	alignment[7].byte0 = build_4_bytes_int((uint8_t[4]){0x12, 0x5C, 0x00, 0x00}); // 39
	alignment[7].addr = 0xCE1DD;
	alignment[8].byte0 = build_4_bytes_int((uint8_t[4]){0x4A, 0x63, 0x00, 0x00}); // 40
	alignment[8].addr = 0xD2D01;
	alignment[9].byte0 = build_4_bytes_int((uint8_t[4]){0x38, 0xD3, 0x00, 0x00}); // 41
	alignment[9].addr = 0xD7825;
	alignment[10].byte0 = build_4_bytes_int((uint8_t[4]){0x9F, 0x16, 0x00, 0x00}); // 42
	alignment[10].addr = 0xDC349;
	alignment[11].byte0 = build_4_bytes_int((uint8_t[4]){0xA6, 0x76, 0x00, 0x00}); // 43
	alignment[11].addr = 0xE0E6D;
	alignment[12].byte0 = build_4_bytes_int((uint8_t[4]){0xBC, 0x44, 0x00, 0x00}); // 44
	alignment[12].addr = 0xE5991;
	alignment[13].byte0 = build_4_bytes_int((uint8_t[4]){0x17, 0x8D, 0x00, 0x00}); // 45
	alignment[13].addr = 0xEA4B5;
	alignment[14].byte0 = build_4_bytes_int((uint8_t[4]){0x83, 0x29, 0x00, 0x00}); // 46
	alignment[14].addr = 0xEEFD9;
	alignment[15].byte0 = build_4_bytes_int((uint8_t[4]){0x24, 0xC5, 0x00, 0x00}); // 47
	alignment[15].addr = 0xF3AFD;
	alignment[16].byte0 = build_4_bytes_int((uint8_t[4]){0x2D, 0x0E, 0x00, 0x00}); // 48
	alignment[16].addr = 0xF8621;
	alignment[17].byte0 = build_4_bytes_int((uint8_t[4]){0x30, 0xD9, 0x00, 0x00}); // 49
	alignment[17].addr = 0xFD145;
	alignment[18].byte0 = build_4_bytes_int((uint8_t[4]){0xAA, 0xBC, 0x00, 0x00}); // 50
	alignment[18].addr = 0x77E9;
	alignment[19].byte0 = build_4_bytes_int((uint8_t[4]){0x90, 0xE2, 0x00, 0x00}); // 51
	alignment[19].addr = 0x11E8D;
	alignment[20].byte0 = build_4_bytes_int((uint8_t[4]){0x20, 0x71, 0x00, 0x00}); // 52
	alignment[20].addr = 0x157C1;
	alignment[21].byte0 = build_4_bytes_int((uint8_t[4]){0x92, 0xAB, 0x00, 0x00}); // 54
	alignment[21].addr = 0x2897F;
	alignment[22].byte0 = build_4_bytes_int((uint8_t[4]){0xBC, 0x89, 0x00, 0x00}); // 55
	alignment[22].addr = 0x2FCCF;
	alignment[23].byte0 = build_4_bytes_int((uint8_t[4]){0x3C, 0x84, 0x00, 0x00}); // 58
	alignment[23].addr = 0x3C079;
	alignment[24].byte0 = build_4_bytes_int((uint8_t[4]){0x34, 0x60, 0x00, 0x00}); // 59
	alignment[24].addr = 0x4169F;
	alignment[25].byte0 = build_4_bytes_int((uint8_t[4]){0x6C, 0xBE, 0x00, 0x00}); // 60
	alignment[25].addr = 0x46CC5;
	alignment[26].byte0 = build_4_bytes_int((uint8_t[4]){0x6B, 0xEB, 0x00, 0x00}); // 3
	alignment[26].addr = 0x1B445;
	alignment[27].byte0 = build_4_bytes_int((uint8_t[4]){0xE0, 0x96, 0x00, 0x00}); // 4
	alignment[27].addr = 0x1E4E3;
	// starting from asset 0 in white1
	alignment[40].byte0 = build_4_bytes_int((uint8_t[4]){0x42, 0x8B, 0x00, 0x00});
	alignment[40].addr = 0x1D15;
	alignment[41].byte0 = build_4_bytes_int((uint8_t[4]){0xA2, 0x14, 0x00, 0x00});
	alignment[41].addr = 0x3839;
	alignment[42].byte0 = build_4_bytes_int((uint8_t[4]){0x2B, 0x2D, 0x00, 0x00});
	alignment[42].addr = 0x11323;
	alignment[43].byte0 = build_4_bytes_int((uint8_t[4]){0xBB, 0xD9, 0x00, 0x00});
	alignment[43].addr = 0x1B727;
	alignment[44].byte0 = build_4_bytes_int((uint8_t[4]){0x68, 0x7B, 0x00, 0x00});
	alignment[44].addr = 0x2024B;
	alignment[45].byte0 = build_4_bytes_int((uint8_t[4]){0x53, 0x21, 0x00, 0x00});
	alignment[45].addr = 0x24D6F;
	alignment[46].byte0 = build_4_bytes_int((uint8_t[4]){0xF2, 0x57, 0x00, 0x00});
	alignment[46].addr = 0x29893;
	alignment[47].byte0 = build_4_bytes_int((uint8_t[4]){0x67, 0x68, 0x00, 0x00});
	alignment[47].addr = 0x2E3B7;
	alignment[48].byte0 = build_4_bytes_int((uint8_t[4]){0x97, 0x89, 0x00, 0x00});
	alignment[48].addr = 0x32EDB;
	alignment[49].byte0 = build_4_bytes_int((uint8_t[4]){0x57, 0x9E, 0x00, 0x00});
	alignment[49].addr = 0x379FF;
	alignment[50].byte0 = build_4_bytes_int((uint8_t[4]){0x29, 0xF0, 0x00, 0x00});
	alignment[50].addr = 0x3C523;
	alignment[51].byte0 = build_4_bytes_int((uint8_t[4]){0xF7, 0x40, 0x00, 0x00});
	alignment[51].addr = 0x41047;
	alignment[52].byte0 = build_4_bytes_int((uint8_t[4]){0xF4, 0x3A, 0x00, 0x00});
	alignment[52].addr = 0x45B6B;
	alignment[53].byte0 = build_4_bytes_int((uint8_t[4]){0x5C, 0x81, 0x00, 0x00});
	alignment[53].addr = 0x4734F;
	alignment[54].byte0 = build_4_bytes_int((uint8_t[4]){0x9F, 0x6B, 0x00, 0x00});
	alignment[54].addr = 0x4B5B3;
	alignment[55].byte0 = build_4_bytes_int((uint8_t[4]){0xB5, 0xBC, 0x00, 0x00});
	alignment[55].addr = 0x500D7;
	alignment[56].byte0 = build_4_bytes_int((uint8_t[4]){0xBA, 0x7D, 0x00, 0x00});
	alignment[56].addr = 0x54BFB;
	alignment[57].byte0 = build_4_bytes_int((uint8_t[4]){0x31, 0xB2, 0x00, 0x00});
	alignment[57].addr = 0x5971F;
	alignment[58].byte0 = build_4_bytes_int((uint8_t[4]){0x1C, 0xE4, 0x00, 0x00});
	alignment[58].addr = 0x5E243;
	alignment[59].byte0 = build_4_bytes_int((uint8_t[4]){0x87, 0xA0, 0x00, 0x00});
	alignment[59].addr = 0x624A7;
	alignment[60].byte0 = build_4_bytes_int((uint8_t[4]){0x4E, 0x67, 0x00, 0x00});
	alignment[60].addr = 0x63C8B;
	alignment[61].byte0 = build_4_bytes_int((uint8_t[4]){0xDE, 0x82, 0x00, 0x00});
	alignment[61].addr = 0x687AF;
	alignment[62].byte0 = build_4_bytes_int((uint8_t[4]){0x07, 0x8A, 0x00, 0x00});
	alignment[62].addr = 0x6D2D3;
	alignment[63].byte0 = build_4_bytes_int((uint8_t[4]){0x94, 0x34, 0x00, 0x00});
	alignment[63].addr = 0x71DF7;
	alignment[64].byte0 = build_4_bytes_int((uint8_t[4]){0x96, 0x77, 0x00, 0x00});
	alignment[64].addr = 0x7691B;
	// the sofa
	alignment[65].byte0 = build_4_bytes_int((uint8_t[4]){0xD5, 0xF6, 0x00, 0x00});
	alignment[65].addr = 0x940CF;
	// now from the ende in reverse
	alignment[66].byte0 = build_4_bytes_int((uint8_t[4]){0x64, 0x12, 0x00, 0x00});
	alignment[66].addr = 0xEE43;
	alignment[67].byte0 = build_4_bytes_int((uint8_t[4]){0x38, 0x94, 0x00, 0x00});
	alignment[67].addr = 0x617F;
	alignment[68].byte0 = build_4_bytes_int((uint8_t[4]){0xAD, 0x72, 0x00, 0x00});
	alignment[68].addr = 0xFE417;
	alignment[69].byte0 = build_4_bytes_int((uint8_t[4]){0xDC, 0x41, 0x00, 0x00});
	alignment[69].addr = 0xFB013;
	alignment[70].byte0 = build_4_bytes_int((uint8_t[4]){0x15, 0x4A, 0x00, 0x00});
	alignment[70].addr = 0xF75CF;
	alignment[71].byte0 = build_4_bytes_int((uint8_t[4]){0x53, 0xD4, 0x00, 0x00});
	alignment[71].addr = 0xE437D;
	alignment[72].byte0 = build_4_bytes_int((uint8_t[4]){0xA6, 0xD8, 0x00, 0x00});
	alignment[72].addr = 0xD9DB9;
	alignment[73].byte0 = build_4_bytes_int((uint8_t[4]){0x78, 0xB5, 0x00, 0x00});
	alignment[73].addr = 0xD847B;
	alignment[74].byte0 = build_4_bytes_int((uint8_t[4]){0x19, 0xEC, 0x00, 0x00});
	alignment[74].addr = 0xD6777;
	alignment[76].byte0 = build_4_bytes_int((uint8_t[4]){0x55, 0x3C, 0x00, 0x00});
	alignment[76].addr = 0xD0C6D;
	alignment[76].byte0 = build_4_bytes_int((uint8_t[4]){0x4E, 0xCA, 0x00, 0x00});
	alignment[76].addr = 0xBF3EB;
}

void set_skip(t_manual *skip)
{
	skip[0].byte0 = build_4_bytes_int((uint8_t[4]){0x42, 0x8B, 0x00, 0x00});
	// skip[0].addr = 0x1D15;
	skip[1].byte0 = build_4_bytes_int((uint8_t[4]){0xA2, 0x14, 0x00, 0x00});
	// skip[1].addr = 0x3839;
	skip[2].byte0 = build_4_bytes_int((uint8_t[4]){0x82, 0x66, 0x00, 0x00});
	skip[2].addr = 0x1B988;
	skip[3].byte0 = build_4_bytes_int((uint8_t[4]){0x81, 0x86, 0x00, 0x00});
	skip[3].addr = 0x1C2FF;
	skip[4].byte0 = build_4_bytes_int((uint8_t[4]){0x29, 0x64, 0x00, 0x00});
	skip[4].addr = 0x797A5;
	skip[5].byte0 = build_4_bytes_int((uint8_t[4]){0x11, 0xCF, 0x00, 0x00});
	skip[5].addr = 0xA39FC;
	// these are the 2 for transparancy
	// skip[6].byte0 = build_4_bytes_int((uint8_t[4]){0x15, 0xF1, 0x00, 0x00});
	// skip[6].addr = 0xCBDF3;
	// skip[7].byte0 = build_4_bytes_int((uint8_t[4]){0xD5, 0x63, 0x00, 0x00});
	// skip[7].addr = 0xD83D5;
}

bool init(t_data *data, char *file) {
  memset(data, 0, sizeof (t_data));
  data->fd = open(file, O_RDONLY);
  if (data->fd == -1) {
    dprintf(STDERR_FILENO, "Error: couldn't open file %s\n", file);
    return false;
  }
  if (mlxu_setup_new_display(&data->visual) != 0)
  	return (false);
  if (mlxu_setup_new_win(&data->visual, file, (t_mlxu_2d){W,H,0}) != 0)
  	return (false);
  if (mlxu_setup_new_buffer(&data->visual) != 0)
    return (false);
  mlx_hook(data->visual.active.win->ptr,
		   DestroyNotify, NoEventMask, mlx_loop_end,
		   data->visual.mlx_ptr);
  mlx_key_hook(data->visual.active.win->ptr, keyhooks, data);
  set_flip_alignment(data->manual_alignment);
  set_skip(data->manual_skip);
  if (DEBUG)
  	printf("Display: %ix%i || Window: %ix%i (%ipx)\n",\
		data->visual.dsp_size.x, data->visual.dsp_size.y,
		data->visual.active.win->size.x, data->visual.active.win->size.y,
		data->visual.active.win->size.x * data->visual.active.win->size.y);
  return (true);
}
