#include "stdafx.h"
#include "MyDataType.h"
#include "Calculate.h"

//POINT 转 D_DOT的函数（线，区）
void PntToDot(D_DOT *dot, POINT *pnt,int num)
{
	for (int i =0;i<num;++i)
	{
		dot[i].x = pnt[i].x;
		dot[i].y = pnt[i].y;
	}
}

//point 转D_DOT的函数

void PntToDot(D_DOT &dot, POINT pnt)
{
	dot.x = pnt.x;
	dot.y = pnt.y;
}

//D_DOT转POINT 的函数，线。。区
void DotToPnt(POINT *pnt,D_DOT *dot,int num)
{
	for (int i =0;i<num;++i)
	{
		pnt[i].x = (long)dot[i].x;
		pnt[i].y = (long)dot[i].y;

	}
}

//D_DOT转point的函数（点）
void DotToPnt(POINT &pnt, D_DOT dot)
{
	pnt.x = (long)dot.x;
	pnt.y = (long)dot.y;

}
