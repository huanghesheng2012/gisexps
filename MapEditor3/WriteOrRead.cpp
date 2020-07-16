#include "stdafx.h"
#include "WriteOrRead.h"

void WritePntToFile(CFile* PntTmpF, int i, PNT_STRU point)
{
	PntTmpF->Seek(i*sizeof(PNT_STRU),CFile::begin);
	PntTmpF->Write(&point,sizeof(PNT_STRU));
}

void ReadTempFileToPnt(CFile* PntTmpF, int i, PNT_STRU&point)
{
	PntTmpF->Seek(i*sizeof(PNT_STRU),CFile::begin);
	PntTmpF->Read(&point,sizeof(PNT_STRU));
}

//将第i条线的索引写入临时索引文件
void WriteLinNdxToFile(CFile*LinTmpNdxF, int i, LIN_NDX_STRU line)
{
	LinTmpNdxF->Seek(i*sizeof(LIN_NDX_STRU),CFile::begin);
	LinTmpNdxF->Write(&line,sizeof(LIN_NDX_STRU));
}

//将线的点数据写入文件

void WriteLinDatToFile(CFile*linTmpDatF, long datOff, int i , D_DOT point)
{
	linTmpDatF->Seek(datOff+i*sizeof(D_DOT),CFile::begin);
	linTmpDatF->Write(&point,sizeof(D_DOT));
}


