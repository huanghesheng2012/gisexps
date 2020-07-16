#ifndef PAINT_H
#define PAINT_H
#include "MyDataType.h"
void DrawPnt(CClientDC* dc,PNT_STRU point);

void DrawSeg(CClientDC*dc, LIN_NDX_STRU line, POINT point1, POINT point2);

#endif