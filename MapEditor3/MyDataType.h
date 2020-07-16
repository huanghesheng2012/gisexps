#ifndef MYDATATYPE_H
#define MYDATATYPE_H

typedef struct{
	double x;
	double y;
	COLORREF color;
	int pattern;
	char isDel;
}PNT_STRU;

typedef struct{
	char isDel;
	COLORREF color;
	int pattern; //线型（号）
	long dotNum; //线节点数
	long datOff; //线节点坐标数据存储位置

}LIN_NDX_STRU;

typedef struct{
	double x;
	double y;
}D_DOT;

typedef struct{
	char flag[3];
	int version;
}VERSION;


#endif