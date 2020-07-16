#include "StdAfx.h"
#include "AbstractSymbol.h"


AbstractSymbol::AbstractSymbol(void)
{
	this->Active=false;
	this->PenColor=RGB(0,125,125);
	this->PenWidth=1;
	this->pDrawPen=new CPen(PS_SOLID,this->PenWidth, this->PenColor);
	this->BrushColor=RGB(255,255,255);
	this->pBrush=new CBrush(this->BrushColor);
	this->IsDrawed=false;
	this->pDC=NULL;
}



AbstractSymbol::~AbstractSymbol(void)
{
	delete this->pDrawPen;
}

void AbstractSymbol::SetSymbolProperty(map<char *,double> propertyMap)
{
	if(propertyMap.find("pencolor")!=propertyMap.end())
	{
		this->PenColor=propertyMap["pencolor"];
	}
	if(propertyMap.find("brushcolor")!=propertyMap.end())
	{
		this->BrushColor=propertyMap["brushcolor"];
	}
	if(propertyMap.find("penwidth")!=propertyMap.end())
	{
		this->PenWidth=propertyMap["penwidth"];
	}
}

void AbstractSymbol::OnLButtonDown(UINT nFlags, CPoint point)
{

}
void AbstractSymbol::OnRButtonDown(UINT nFlags, CPoint point)
{

}
void AbstractSymbol::OnLButtonUp(UINT nFlags, CPoint point)
{

}
void AbstractSymbol::OnRButtonUp(UINT nFlags, CPoint point)
{

}
void AbstractSymbol::OnMouseMove(UINT nFlags, CPoint point)
{

}

void AbstractSymbol::SetDC(CDC *pDC)
{
	this->pDC=pDC;
}//判断线段相交
bool AbstractSymbol::LineIsIntersect(double x0, double y0, double x1, double y1, double x2, double y2, double x3, double y3)
{ //两条线段是否相交X0X1 AND X1X2
   double x, y;
   double Minx01 = min(x0, x1);
   double Miny01 = min(y0, y1);
   double Minx23 = min(x2, x3);
   double Miny23 = min(y2, y3);
   double Maxx01 = max(x0, x1);
   double Maxy01 = max(y0, y1);
   double Maxx23 = max(x2, x3);
   double Maxy23 = max(y2, y3);
  
   if(x1!=x0 && x2!=x3)
   {
       double k1 = (y1-y0)/(x1-x0);
       double k2 = (y3-y2)/(x3-x2);
       double Den = (y1-y0)*(x3-x2) - (y3-y2)*(x1-x0);
       if(k1==k2)
       { //平行不相交
          double d1 = abs(int(y0*(x1-x0)-x0*(y1-y0)-y2*(x3-x2)+x2*(y3-y2))); //距离公式d = abs(c1-c2) / sqrt(a*a+b*b)
          if(d1==0)
          {//直线重合
             if((x2>Minx01 && x2<Maxy01 && y2>Miny01 && y2<Maxy01) || (x3>Minx01 && x3<Maxy01 && y3>Miny01 && y3<Maxy01)
             || (x0>Minx23 && x0<Maxy23 && y0>Miny23 && y0<Maxy23) || (x1>Minx23 && x1<Maxy23 && y1>Miny23 && y1<Maxy23))
             {  //实际碰撞问题线段重合认为相交了
                return true;
             }
             else
             {
                return false;
             }
          }
          else
          {
             return false;
          }  
       }
       x = ((y2-y0)*(x1-x0)*(x3-x2)+(y1-y0)*(x3-x2)*x0-(y3-y2)*(x1-x0)*x2)/Den;
       y = ((y1-y0)*(x-x0))/(x1-x0) + y0;

       if(Minx01<=x && x<=Maxx01 && Miny01<=y && y<=Maxy01 && Minx23<=x && x<=Maxx23 && Miny23<=y && y<=Maxy23)
       {
         /* InterX = x;
          InterY = y;*/
          return true;
       }
   }
   else if(x1==x0 && x2!=x3)
   {
       x = x0;
       y = ((y3-y2)*(x0-x2))/(x3-x2) + y2;
       if(Minx01<=x && x<=Maxx01 && Miny01<=y && y<=Maxy01 && Minx23<=x && x<=Maxx23 && Miny23<=y && y<=Maxy23)
       {
          /*InterX = x;
          InterY = y;*/
          return true;
       }
   }
   else if(x1!=x0 && x2==x3)
   {
       x = x2;
       y = ((y1-y0)*(x2-x0))/(x1-x0) + y0;
       if(Minx01<=x && x<=Maxx01 && Miny01<=y && y<=Maxy01 && Minx23<=x && x<=Maxx23 && Miny23<=y && y<=Maxy23)
       {
         /* InterX = x;
          InterY = y;*/
          return true;
       }      
   }
   return false;
}