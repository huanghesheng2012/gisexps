#pragma once
#include <functional>
#include <map>
using namespace std;
#define PI 3.1415926535897932384626433832795

/*
抽象类，所有地图矢量符号类的基类 
*/

template <class T>
struct point_y_less :public binary_function < T,T,bool >
{
	bool operator()(const T& p1 ,const T& p2) const { return p1.y<=p2.y ;}
};

class AbstractSymbol
{
public:
	AbstractSymbol(void);
	
	virtual ~AbstractSymbol(void);

public:
	//画图函数, 派生类必须实现该函数
	virtual void Draw(CDC *pDC)=0;
	//设置绘图参数
	virtual void SetSymbolProperty(map<char *,double> propertyMap);
	//-----------封装鼠标消息
	virtual void OnLButtonDown(UINT nFlags, CPoint point);
	virtual void OnRButtonDown(UINT nFlags, CPoint point);
	virtual void OnLButtonUp(UINT nFlags, CPoint point);
	virtual void OnRButtonUp(UINT nFlags, CPoint point);
	virtual void OnMouseMove(UINT nFlags, CPoint point);
	//-----------封装鼠标消息
	//设置画图的CDC类，在画图操作前必须调用该函数传递CDC 指针
	void SetDC(CDC *pDC);
	
	bool LineIsIntersect(double x0, double y0, double x1, double y1, double x2, double y2, double x3, double y3);

public:
	CDC *pDC;
	CPen *pDrawPen;
	CBrush *pBrush;
	bool Active;//标示是否处于画图激活状态
	bool IsDrawed;//标示画图输入完毕

	int PenColor;
	int BrushColor;
	int PenWidth;
	bool useBrush;
};

