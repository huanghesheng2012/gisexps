#include "StdAfx.h"
#include "CircleSymbol.h"


CircleSymbol::CircleSymbol(void)
{
}


CircleSymbol::~CircleSymbol(void)
{
}

void CircleSymbol::SetSymbolProperty(map<char *,double> propertyMap)
{
	PointSymbol::SetSymbolProperty(propertyMap);

	if(propertyMap.find("brushcolor")!=propertyMap.end() && !this->useBrush)
	{
		propertyMap["brushcolor"]=RGB(255,255,255);
	}

}
void CircleSymbol::Draw(CDC *pDC)
{

	
	CPen newpen=CPen(PS_SOLID,this->PenWidth, this->PenColor);
	int mybrushcolor=pDC->GetBkColor();
	if(!this->useBrush)
	{
		this->BrushColor=mybrushcolor;
	}
	CBrush brush=CBrush(this->BrushColor);
	CBrush *oldbrush=pDC->SelectObject(&brush);
	CPen *oldpen=pDC->SelectObject(&newpen);

	pDC->Ellipse(this->centerPoint.x-r,this->centerPoint.y+r,this->centerPoint.x+r,this->centerPoint.y-r);

	pDC->SelectObject(oldpen);
	pDC->SelectObject(oldbrush);
}
