#ifndef __SNAIL_DATA_H__
#define __SNAIL_DATA_H__

#define MAX_LEN_STR 64

#define MAX_PONTS_X 5000
#define MAX_PONTS_Y 5000

struct element_dat_t
{
	char RefDes[MAX_LEN_STR];
	char PatternName[MAX_LEN_STR];
	char Value[MAX_LEN_STR];
	char Layer[MAX_LEN_STR];
    float LocationX;
    float LocationY;
	float Rotation;
};

struct snail_data_t
{
	quint32 offs_x;
	quint32 offs_y;

	element_dat_t *p_elements;
	quint8 points[MAX_PONTS_Y][MAX_PONTS_X];
};

#endif /// __SNAIL_DATA_H__
