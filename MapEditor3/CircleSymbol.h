#pragma once
#include "pointsymbol.h"
class CircleSymbol :
	public PointSymbol
{
public:
	CircleSymbol(void);
	virtual ~CircleSymbol(void);
	

	virtual void Draw(CDC *pDC);
	virtual void SetSymbolProperty(map<char *,double> propertyMap);
};

