#ifndef CALCULATE_H
#define CALCULATE_H

void PntToDot(D_DOT *dot, POINT *pnt,int num);
void PntToDot(D_DOT &dot,POINT pnt);
void DotToPnt(POINT *pnt,D_DOT *dot,int num);
void DotToPnt(POINT &pnt,D_DOT dot);

#endif