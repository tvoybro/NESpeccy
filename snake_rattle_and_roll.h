const unsigned char char_space[2*2]={
	0x00,0x00,
	0x00,0x00
};

const unsigned char char_0[2*2]={
	0x02,0x03,
	0x12,0x13
};

const unsigned char char_1[2*2]={
	0x04,0x05,
	0x14,0x15
};

const unsigned char char_2[2*2]={
	0x06,0x07,
	0x16,0x17
};

const unsigned char char_3[2*2]={
	0x08,0x09,
	0x18,0x19
};

const unsigned char char_4[2*2]={
	0x0a,0x0b,
	0x1a,0x1b
};

const unsigned char char_5[2*2]={
	0x0c,0x0d,
	0x1c,0x1d
};

const unsigned char char_6[2*2]={
	0x0e,0x0f,
	0x1e,0x1f
};

const unsigned char char_7[2*2]={
	0x20,0x21,
	0x30,0x31
};

const unsigned char char_8[2*2]={
	0x22,0x23,
	0x32,0x33
};

const unsigned char char_9[2*2]={
	0x24,0x25,
	0x34,0x35
};

const unsigned char char_A[2*2]={
	0x26,0x27,
	0x36,0x37
};

const unsigned char char_B[2*2]={
	0x28,0x29,
	0x38,0x39
};

const unsigned char char_C[2*2]={
	0x2a,0x2b,
	0x3a,0x3b
};

const unsigned char char_D[2*2]={
	0x2c,0x2d,
	0x3c,0x3d
};

const unsigned char char_E[2*2]={
	0x2e,0x2f,
	0x3e,0x3f
};

const unsigned char char_F[2*2]={
	0x40,0x41,
	0x50,0x51
};

const unsigned char char_G[2*2]={
	0x42,0x43,
	0x52,0x53
};

const unsigned char char_H[2*2]={
	0x44,0x45,
	0x54,0x55
};

const unsigned char char_I[2*2]={
	0x46,0x47,
	0x56,0x57
};

const unsigned char char_J[2*2]={
	0x48,0x49,
	0x58,0x59
};

const unsigned char char_K[2*2]={
	0x4a,0x4b,
	0x5a,0x5b
};

const unsigned char char_L[2*2]={
	0x4c,0x4d,
	0x5c,0x5d
};

const unsigned char char_M[2*2]={
	0x4e,0x4f,
	0x5e,0x5f
};

const unsigned char char_N[2*2]={
	0x60,0x61,
	0x70,0x71
};

const unsigned char char_O[2*2]={
	0x62,0x63,
	0x72,0x73
};

const unsigned char char_P[2*2]={
	0x64,0x65,
	0x74,0x75
};

const unsigned char char_Q[2*2]={
	0x66,0x67,
	0x76,0x77
};

const unsigned char char_R[2*2]={
	0x68,0x69,
	0x78,0x79
};

const unsigned char char_S[2*2]={
	0x6a,0x6b,
	0x7a,0x7b
};

const unsigned char char_T[2*2]={
	0x6c,0x6d,
	0x7c,0x7d
};

const unsigned char char_U[2*2]={
	0x6e,0x6f,
	0x7e,0x7f
};

const unsigned char char_V[2*2]={
	0x80,0x81,
	0x90,0x91
};

const unsigned char char_W[2*2]={
	0x82,0x83,
	0x92,0x93
};

const unsigned char char_X[2*2]={
	0x84,0x85,
	0x94,0x95
};

const unsigned char char_Y[2*2]={
	0x86,0x87,
	0x96,0x97
};

const unsigned char char_Z[2*2]={
	0x88,0x89,
	0x98,0x99
};

const unsigned char char_period[2*2]={
	0x00,0x00,
	0x9a,0x00
};

const unsigned char char_comma[2*2]={
	0x00,0x00,
	0x9b,0x00
};

const unsigned char char_hyphen[2*2]={
	0x8c,0x00,
	0x9c,0x00
};

const unsigned char char_exclamation[2*2]={
	0x8d,0x00,
	0x9d,0x00
};

const unsigned char tbl_ascii[42]={
	' ', '0', '1', '2', '3', '4', '5', '6', '7', '8',
	'9', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I',
	'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S',
	'T', 'U', 'V', 'W', 'X', 'Y', 'Z', '.', ',', '-',
	'!',
	0x0ff
};

const unsigned char const* tbl_alphabet[41]={
char_space, char_0, char_1, char_2, char_3, char_4, char_5, char_6, char_7, char_8, char_9,
char_A, char_B, char_C, char_D, char_E, char_F, char_G, char_H, char_I, char_J, char_K, char_L,
char_M, char_N, char_O, char_P, char_Q, char_R, char_S, char_T, char_U, char_V, char_W, char_X,
char_Y, char_Z, char_period, char_comma, char_hyphen, char_exclamation
};