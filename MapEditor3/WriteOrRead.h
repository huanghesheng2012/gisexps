#ifndef WRITEORREAD_H
#define WRITEORREAD_H
#include "MyDataType.h"
void WritePntToFile(CFile* PntTmpF, int i, PNT_STRU point);

void ReadTempFileToPnt(CFile* PntTmpF, int i, PNT_STRU&point);

//��������д������ʱ�����ļ��ĺ�������
void WriteLinNdxToFile(CFile*linTmpNdxF, int i, LIN_NDX_STRU line);

//���߽ڵ�����д������ʱ�����ļ��ĺ�������
void WriteLinDatToFile(CFile*linTmpDatF, long datOff, int i , D_DOT point);


#endif