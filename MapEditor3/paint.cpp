#include "stdafx.h"
#include "paint.h"
#include <math.h>

//根据传入DrawPnt函数的参数不同而画出不同颜色和不同类型的点

void DrawPnt(CClientDC* dc, PNT_STRU point)
{
	CBrush brush(point.color);
	CPen pen(PS_SOLID,1,point.color);
	CObject* oldObject;
	switch(point.pattern)
	{
		//点的不同形状：十字形、圆形、五角星形
	case 0:
		oldObject = dc->SelectObject(&pen);
		dc->MoveTo((long)point.x - 4,(long)point.y);
		dc->LineTo((long)point.x + 4,(long)point.y);
		dc->MoveTo((long)point.x,(long)point.y - 4);
		dc->LineTo((long)point.x,(long)point.y + 4);
	break;
	case 1:
		oldObject = dc->SelectObject(&pen);
		POINT external_pt[5],interior_pt[5];
		double external_r = 10,interior_r = external_r/2;

		external_pt[0].x = (long)point.x;
		external_pt[0].y = long(point.y - external_r);
		external_pt[1].x = long(point.x + (external_r * cos(18.0*3.14/180)));
		external_pt[1].y = long(point.y - (external_r * sin(18.0*3.14/180)));
		external_pt[2].x = long(point.x + (external_r * sin(36.0*3.14/180)));
		external_pt[2].y = long(point.y + (external_r * cos(36.0*3.14/180)));
		external_pt[3].x = long(point.x - (external_r * sin(36.0*3.14/180)));
		external_pt[3].y = long(external_pt[2].y);
		external_pt[4].x = long(point.x - (external_r * cos(18.0*3.14/180)));
		external_pt[4].y = long(external_pt[1].y);

		interior_pt[0].x = long(point.x + (interior_r * cos(54.0 * 3.14 /180)));
		interior_pt[0].y = long(point.y - (interior_r * sin(54.0 * 3.14 / 180)));

		dc->MoveTo((long)external_pt[0].x,(long)external_pt[0].y);
		dc->LineTo((long)interior_pt[0].x,(long)interior_pt[0].y);
		for (int i =1;i<5;i++)
		{
			dc->LineTo((long)external_pt[i].x,(long)external_pt[i].y);
			dc->LineTo((long)interior_pt[i].x,(long)interior_pt[i].y);
		}
		dc->LineTo((long)external_pt[0].x,(long)external_pt[0].y);
	break;


	}
	dc->SelectObject(oldObject);

}

/*绘制线，构造线段*/

void DrawSeg(CClientDC*dc, LIN_NDX_STRU line, POINT point1, POINT point2)
{
	CPen pen;
	switch(line.pattern)
	{	
	case 0:
		pen.CreatePen(PS_SOLID,1,line.color);//创建一个实线的画笔
		break;
	case 1:
		pen.CreatePen(PS_DASH,1,line.color);//创建一个虚线的画笔
		break;
	case 2:
		pen.CreatePen(PS_DOT,1,line.color);//创建一个点线的画笔
		break;
	default:
		break;
			
	}
	CPen*oldPen = dc->SelectObject(&pen);
	dc->MoveTo(point1.x,point1.y);
	dc->LineTo(point2.x,point2.y);
	dc->SelectObject(oldPen);
}