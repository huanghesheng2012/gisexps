#pragma once
#include <functional>
#include <map>
using namespace std;
#define PI 3.1415926535897932384626433832795

/*
�����࣬���е�ͼʸ��������Ļ��� 
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
	//��ͼ����, ���������ʵ�ָú���
	virtual void Draw(CDC *pDC)=0;
	//���û�ͼ����
	virtual void SetSymbolProperty(map<char *,double> propertyMap);
	//-----------��װ�����Ϣ
	virtual void OnLButtonDown(UINT nFlags, CPoint point);
	virtual void OnRButtonDown(UINT nFlags, CPoint point);
	virtual void OnLButtonUp(UINT nFlags, CPoint point);
	virtual void OnRButtonUp(UINT nFlags, CPoint point);
	virtual void OnMouseMove(UINT nFlags, CPoint point);
	//-----------��װ�����Ϣ
	//���û�ͼ��CDC�࣬�ڻ�ͼ����ǰ������øú�������CDC ָ��
	void SetDC(CDC *pDC);
	
	bool LineIsIntersect(double x0, double y0, double x1, double y1, double x2, double y2, double x3, double y3);

public:
	CDC *pDC;
	CPen *pDrawPen;
	CBrush *pBrush;
	bool Active;//��ʾ�Ƿ��ڻ�ͼ����״̬
	bool IsDrawed;//��ʾ��ͼ�������

	int PenColor;
	int BrushColor;
	int PenWidth;
	bool useBrush;
};

