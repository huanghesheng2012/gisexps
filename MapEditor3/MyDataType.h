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
	int pattern; //���ͣ��ţ�
	long dotNum; //�߽ڵ���
	long datOff; //�߽ڵ��������ݴ洢λ��

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