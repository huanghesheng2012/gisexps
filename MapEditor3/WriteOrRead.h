#ifndef WRITEORREAD_H
#define WRITEORREAD_H
#include "MyDataType.h"
void WritePntToFile(CFile* PntTmpF, int i, PNT_STRU point);

void ReadTempFileToPnt(CFile* PntTmpF, int i, PNT_STRU&point);

//将线数据写入线临时数据文件的函数声明
void WriteLinNdxToFile(CFile*linTmpNdxF, int i, LIN_NDX_STRU line);

//将线节点数据写入线临时数据文件的函数声明
void WriteLinDatToFile(CFile*linTmpDatF, long datOff, int i , D_DOT point);


#endif