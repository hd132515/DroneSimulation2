#pragma once


#define MOTOR_NUM 4

#define CMD_INIT_MOTOR		-2
#define CMD_NULL_CMD		-1

//1 bit
#define CMD_MAIN_AUTO		0 //0b00000000
#define CMD_MAIN_MAN		1 //0b00000001
#define CMD_MAIN_FACTORFIND	2 //0b00000010
#define CMD_MAIN_LAND		3 //0b00000011

//2 bit
#define CMD_SUB_STABLE		0 //0b00000000
#define CMD_SUB_MOVE		1 //0b00000100

//3,4 bit
#define CMD_MOVE_AXIS1		0 //0b00000000
#define CMD_MOVE_AXIS2		1 //0b00001000
#define CMD_MOVE_UP			2 //0b00010000
#define CMD_MOVE_DOWN		3 //0b00011000

#define CMD_MAIN(a)			 (a & 0b00000011)
#define CMD_SUB(a)			 (a & 0b00000100) >> 2
#define CMD_MOVE(a)			 (a & 0b00011000) >> 3
#define CMD_MOVE_AMT_AXIS(a) (a & 0b11100000) >> 5

#define CMD_MAKE_MAIN(a)	a
#define CMD_MAKE_SUB(a)		a << 2
#define CMD_MAKE_MOVE(a)	a << 3
#define CMD_MAKE_AMT(a)		a << 5