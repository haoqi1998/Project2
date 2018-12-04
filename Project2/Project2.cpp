// Project2.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <iostream>
using namespace std;
#include "./gdal/gdal_priv.h"
#pragma comment(lib, "gdal_i.lib")
int main()

{

	//����ͼ��

	GDALDataset* poSrcDs;

	//���ͼ��

	GDALDataset* poDstDs;

	//ͼ��Ŀ�Ⱥ͸߶�

	int imgXlen, imgYlen;

	//��ȡͼ��Ŀ�Ⱥ͸߶�

	int tmpXlen, tmpYlen;

	//��ʼ������

	int startX, startY;

	//����ͼ��·��

	const char* srcPath = "wind.jpg";

	//���ͼ��·��

	const char* dstPath = "res.tif";

	//ͼ���ڴ�

	GByte* buffTmp;

	//ͼ�񲨶���

	int i, j, k, BandNum;

	//ע������

	GDALAllRegister();



	//��ͼ��

	poSrcDs = (GDALDataset*)GDALOpenShared(srcPath, GA_ReadOnly);



	//��ȡͼ��Ŀ��,�߶�,����

	imgXlen = poSrcDs->GetRasterXSize();

	imgYlen = poSrcDs->GetRasterYSize();

	BandNum = poSrcDs->GetRasterCount();



	//�����ڴ�

	buffTmp = (GByte*)CPLMalloc(imgXlen*imgYlen * sizeof(GByte));



	//�������ͼ��

	poDstDs = GetGDALDriverManager()->GetDriverByName("GTiff")->Create(

		dstPath, imgXlen, imgYlen, BandNum, GDT_Byte, NULL);



	//����ͼ��

	for (i = 0; i < BandNum; i++)

	{

		poSrcDs->GetRasterBand(i + 1)->RasterIO(GF_Read,

			0, 0, imgXlen, imgYlen, buffTmp, imgXlen, imgYlen, GDT_Byte, 0, 0);

		poDstDs->GetRasterBand(i + 1)->RasterIO(GF_Write,

			0, 0, imgXlen, imgYlen, buffTmp, imgXlen, imgYlen, GDT_Byte, 0, 0);

	}

	//����ڴ�

	CPLFree(buffTmp);



	//��ɰ�ɫ

	startX = 300, startY = 300;

	tmpXlen = 100, tmpYlen = 50;



	//�����ڴ�

	buffTmp = (GByte*)CPLMalloc(tmpXlen*tmpYlen * sizeof(GByte));



	//��ȡRBGͨ��

	for (k = 1; k <= 3; k++)

	{

		poSrcDs->GetRasterBand(k)->RasterIO(GF_Read, startX, startY,

			tmpXlen, tmpYlen, buffTmp, tmpXlen, tmpYlen, GDT_Byte, 0, 0);

		for (j = 0; j < tmpYlen; j++)

		{

			for (i = 0; i < tmpXlen; i++)

			{

				buffTmp[j*tmpXlen + i] = (GByte)255;

			}

		}

		//����д��poDstDs

		poDstDs->GetRasterBand(k)->RasterIO(GF_Write,

			startX, startY, tmpXlen, tmpYlen, buffTmp, tmpXlen, tmpYlen, GDT_Byte, 0, 0);



	}

	//����ڴ�

	CPLFree(buffTmp);



	//��ɫ��

	startX = 500, startY = 500;

	tmpXlen = 50, tmpYlen = 100;



	//�����ڴ�

	buffTmp = (GByte*)CPLMalloc(tmpXlen*tmpYlen * sizeof(GByte));



	//��ȡRBGͨ��

	for (k = 1; k <= 3; k++)

	{

		poSrcDs->GetRasterBand(k)->RasterIO(GF_Read, startX, startY,

			tmpXlen, tmpYlen, buffTmp, tmpXlen, tmpYlen, GDT_Byte, 0, 0);

		for (j = 0; j < tmpYlen; j++)

		{

			for (i = 0; i < tmpXlen; i++)

			{

				buffTmp[j*tmpXlen + i] = (GByte)0;

			}

		}

		//����д��poDstDs

		poDstDs->GetRasterBand(k)->RasterIO(GF_Write,

			startX, startY, tmpXlen, tmpYlen, buffTmp, tmpXlen, tmpYlen, GDT_Byte, 0, 0);



	}

	//����ڴ�

	CPLFree(buffTmp);



	//�ر�dataset

	GDALClose(poDstDs);

	GDALClose(poSrcDs);



	system("PAUSE");







	return 0;

}

