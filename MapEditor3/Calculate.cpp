#include "stdafx.h"
#include "MyDataType.h"
#include "Calculate.h"

//POINT ת D_DOT�ĺ������ߣ�����
void PntToDot(D_DOT *dot, POINT *pnt,int num)
{
	for (int i =0;i<num;++i)
	{
		dot[i].x = pnt[i].x;
		dot[i].y = pnt[i].y;
	}
}

//point תD_DOT�ĺ���

void PntToDot(D_DOT &dot, POINT pnt)
{
	dot.x = pnt.x;
	dot.y = pnt.y;
}

//D_DOTתPOINT �ĺ������ߡ�����
void DotToPnt(POINT *pnt,D_DOT *dot,int num)
{
	for (int i =0;i<num;++i)
	{
		pnt[i].x = (long)dot[i].x;
		pnt[i].y = (long)dot[i].y;

	}
}

//D_DOTתpoint�ĺ������㣩
void DotToPnt(POINT &pnt, D_DOT dot)
{
	pnt.x = (long)dot.x;
	pnt.y = (long)dot.y;

}
