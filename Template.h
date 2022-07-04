#pragma once
#include "stdafx.h"
#include <math.h>
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "MFCTemplate.h"
#endif
//#include "CDlgGama.h"
//#include "DlgThreshold.h"
#include "MFCTemplateDoc.h"
//#include "CDlgInverseV.h"
//#include "CDlgV.h"
//#include "value.h"
//#include "CDlgL.h"
//#include "CDlgLog.h"
//#include "CDlgRestore.h"
//#include "CDlgHistogram.h"
#include "MFCTemplateView.h"
//#include "CDlgDisp.h"
//#include "CDlgLinerPara.h"
//#include "CDlgInverseL.h"


BOOL WINAPI Template(LPSTR lpDIBBits, LONG lWidth, LONG lHeight,
	int iTempH, int iTempW,
	int iTempMX, int iTempMY,
	FLOAT * Arr, FLOAT fCoef)
{
	LPSTR lpNewDIBBits;
	HLOCAL hNewDIBBits;
	unsigned char* lpSrc;
	unsigned char* lpDst;
	LONG i, j, k, l;
	FLOAT fResult;
	LONG lLineBytes;
	lLineBytes = GDI_WIDTHBYTES(lWidth * 8);
	hNewDIBBits = LocalAlloc(LHND, lLineBytes*lHeight);
	if (hNewDIBBits == NULL)
	{
		return FALSE;
	}
	lpNewDIBBits = (char *)LocalLock(hNewDIBBits);

	// 初始化图像为原始图像
	memcpy(lpNewDIBBits, lpDIBBits, lLineBytes * lHeight);

	// 行(除去边缘几行)
	for (i = iTempMY; i < lHeight - iTempH + iTempMY + 1; i++)
	{
		// 列(除去边缘几列)
		for (j = iTempMX; j < lWidth - iTempW + iTempMX + 1; j++)
		{
			// 指向新DIB第i行，第j个象素的指针
			lpDst = (unsigned char*)lpNewDIBBits + lLineBytes * (lHeight - 1 - i) + j;

			fResult = 0;

			// 计算
			for (k = 0; k < iTempH; k++)
			{
				for (l = 0; l < iTempW; l++)
				{
					// 指向DIB第i - iTempMY + k行，第j - iTempMX + l个象素的指针
					lpSrc = (unsigned char*)lpDIBBits + lLineBytes * (lHeight - 1 - i + iTempMY - k)
						+ j - iTempMX + l;

					// 保存象素值
					fResult += (*lpSrc) * Arr[k * iTempW + l];
				}
			}

			// 乘上系数
			fResult *= fCoef;

			// 取绝对值
			fResult = (FLOAT)fabs(fResult);

			// 判断是否超过255
			if (fResult > 255)
			{
				// 直接赋值为255
				*lpDst = 255;
			}
			else
			{
				// 赋值
				*lpDst = (unsigned char)(fResult + 0.5);
			}

		}
	}

	// 复制变换后的图像
	memcpy(lpDIBBits, lpNewDIBBits, lLineBytes * lHeight);

	// 释放内存
	LocalUnlock(hNewDIBBits);
	LocalFree(hNewDIBBits);

	// 返回
	return TRUE;


}


unsigned char WINAPI GetMedianNum(unsigned char * bArray, int iFilterLen)
{
	int		i;
	int		j;
	unsigned char bTemp;
	for (j = 0; j < iFilterLen - 1; j++)
	{
		for (i = 0; i < iFilterLen - j - 1; i++)
		{
			if (bArray[i] > bArray[i + 1])
			{
				bTemp = bArray[i];
				bArray[i] = bArray[i + 1];
				bArray[i + 1] = bTemp;
			}
		}
	}

	// 中间变量
	if ((iFilterLen & 1) > 0)
	{
		// 数组有奇数个元素，返回中间一个元素
		bTemp = bArray[(iFilterLen + 1) / 2];
	}
	else
	{
		// 数组有偶数个元素，返回中间两个元素平均值
		bTemp = (bArray[iFilterLen / 2] + bArray[iFilterLen / 2 + 1]) / 2;
	}

	// 返回中值
	return bTemp;
}








BOOL WINAPI MedianFilter(LPSTR lpDIBBits, LONG lWidth, LONG lHeight,
	int iFilterH, int iFilterW,
	int iFilterMX, int iFilterMY)
{
	unsigned char* lpSrc;
	unsigned char* lpDst;
	LPSTR lpNewDIBBits;
	HLOCAL hNewDIBBits;
	unsigned char *aValue;
	HLOCAL hArray;
	LONG i, j, k, l;
	LONG lLineBytes;
	lLineBytes = GDI_WIDTHBYTES(lWidth * 8);
	hNewDIBBits = LocalAlloc(LHND, lLineBytes*lHeight);
	if (hNewDIBBits == NULL)
	{
		return FALSE;
	}
	lpNewDIBBits = (char*)LocalLock(hNewDIBBits);
	memcpy(lpNewDIBBits, lpDIBBits, lLineBytes*lHeight);
	hArray = LocalAlloc(LHND, iFilterH*iFilterW);
	if (hArray == NULL)
	{
		LocalUnlock(hNewDIBBits);
		LocalFree(hNewDIBBits);
		return FALSE;
	}
	aValue = (unsigned char*)LocalLock(hArray);
	for (i = iFilterMY; i < lHeight - iFilterH + iFilterMY + 1; i++)
	{
		for (j = iFilterMX; j < lWidth - iFilterW + iFilterMX + 1; j++)
		{
			lpDst = (unsigned char*)lpNewDIBBits + lLineBytes * (lHeight - 1 - i) + j;
			for (k = 0; k < iFilterH; k++)
			{
				for (l = 0; l < iFilterW; l++)
				{
					lpSrc = (unsigned char*)lpDIBBits + lLineBytes * (lHeight - 1 - i + iFilterMY - k) + j - iFilterMX + 1;
					aValue[k*iFilterW + 1] = *lpSrc;

				}
			}
			*lpDst = GetMedianNum(aValue, iFilterH*iFilterW);
		}
	}
	memcpy(lpDIBBits, lpNewDIBBits, lLineBytes*lHeight);
	LocalUnlock(hNewDIBBits);
	LocalFree(hNewDIBBits);
	LocalUnlock(hArray);
	LocalFree(hArray);
	return TRUE;
}




unsigned char WINAPI GetMaxNum(unsigned char * bArray, int iFilterLen)
{
	int		i;
	int		j;
	unsigned char bTemp;
	for (j = 0; j < iFilterLen - 1; j++)
	{
		for (i = 0; i < iFilterLen - j - 1; i++)
		{
			if (bArray[i] > bArray[i + 1])
			{
				bTemp = bArray[i];
				bArray[i] = bArray[i + 1];
				bArray[i + 1] = bTemp;
			}
		}
	}
	bTemp = bArray[iFilterLen-2];
	//返回最值
	return bTemp;
}



unsigned char WINAPI GetMinNum(unsigned char * bArray, int iFilterLen)
{
	int		i;
	int		j;
	unsigned char bTemp;
	for (j = 0; j < iFilterLen - 1; j++)
	{
		for (i = 0; i < iFilterLen - j - 1; i++)
		{
			if (bArray[i] < bArray[i + 1])
			{
				bTemp = bArray[i];
				bArray[i] = bArray[i + 1];
				bArray[i + 1] = bTemp;
			}
		}
	}
	bTemp = bArray[iFilterLen - 2];
	//返回最值
	return bTemp;
}





BOOL WINAPI MaxMinFilter(LPSTR lpDIBBits, LONG lWidth, LONG lHeight,
	int iFilterH, int iFilterW,
	int iFilterMX, int iFilterMY,int flag)
{
	unsigned char* lpSrc;
	unsigned char* lpDst;
	LPSTR lpNewDIBBits;
	HLOCAL hNewDIBBits;
	unsigned char *aValue;
	HLOCAL hArray;
	LONG i, j, k, l;
	LONG lLineBytes;
	lLineBytes = GDI_WIDTHBYTES(lWidth * 8);
	hNewDIBBits = LocalAlloc(LHND, lLineBytes*lHeight);
	if (hNewDIBBits == NULL)
	{
		return FALSE;
	}
	lpNewDIBBits = (char*)LocalLock(hNewDIBBits);
	memcpy(lpNewDIBBits, lpDIBBits, lLineBytes*lHeight);
	hArray = LocalAlloc(LHND, iFilterH*iFilterW);
	if (hArray == NULL)
	{
		LocalUnlock(hNewDIBBits);
		LocalFree(hNewDIBBits);
		return FALSE;
	}
	aValue = (unsigned char*)LocalLock(hArray);
	for (i = iFilterMY; i < lHeight - iFilterH + iFilterMY + 1; i++)
	{
		for (j = iFilterMX; j < lWidth - iFilterW + iFilterMX + 1; j++)
		{
			lpDst = (unsigned char*)lpNewDIBBits + lLineBytes * (lHeight - 1 - i) + j;
			for (k = 0; k < iFilterH; k++)
			{
				for (l = 0; l < iFilterW; l++)
				{
					lpSrc = (unsigned char*)lpDIBBits + lLineBytes * (lHeight - 1 - i + iFilterMY - k) + j - iFilterMX + 1;
					aValue[k*iFilterW + 1] = *lpSrc;

				}
			}
			if(flag==1)
				*lpDst = GetMaxNum(aValue, iFilterH*iFilterW);
			else
				*lpDst = GetMinNum(aValue, iFilterH*iFilterW);
		}
	}
	memcpy(lpDIBBits, lpNewDIBBits, lLineBytes*lHeight);
	LocalUnlock(hNewDIBBits);
	LocalFree(hNewDIBBits);
	LocalUnlock(hArray);
	LocalFree(hArray);
	return TRUE;
}


BOOL WINAPI GradSharp(LPSTR lpDIBBits, LONG lWidth, LONG lHeight, BYTE bThre)
{
	// 指向源图像的指针
	unsigned char*	lpSrc;
	unsigned char*	lpSrc1;
	unsigned char*	lpSrc2;
	// 循环变量
	LONG	i;
	LONG	j;
	// 图像每行的字节数
	LONG	lLineBytes;
	// 中间变量
	BYTE	bTemp;
	// 计算图像每行的字节数
	lLineBytes = GDI_WIDTHBYTES(lWidth * 8);
	// 每行
	for (i = 0; i < lHeight; i++)
	{
		// 每列
		for (j = 0; j < lWidth; j++)
		{
			lpSrc = (unsigned char*)lpDIBBits + lLineBytes * (lHeight - 1 - i) + j;
			// 指向DIB第i+1行，第j个象素的指针
			lpSrc1 = (unsigned char*)lpDIBBits + lLineBytes * (lHeight - 2 - i) + j;
			lpSrc2 = (unsigned char*)lpDIBBits + lLineBytes * (lHeight - 1 - i) + j + 1;
			bTemp = abs((*lpSrc) - (*lpSrc1)) + abs((*lpSrc) - (*lpSrc2));
			if (bTemp < 255)
			{
				if (bTemp >= bThre)
				{
					*lpSrc = bTemp;
				}
			}
			else
			{
				*lpSrc = 255;
			}
		}
	}
	return TRUE;
}



BOOL WINAPI LTemplate(LPSTR lpDIBBits, LONG lWidth, LONG lHeight,
	int iTempH, int iTempW,
	int iTempMX, int iTempMY,
	FLOAT * Arr, FLOAT fCoef)
{
	LPSTR lpNewDIBBits;
	HLOCAL hNewDIBBits;
	unsigned char* lpSrc;
	unsigned char* lpDst;
	LONG i, j, k, l;
	FLOAT fResult,fTemp;
	LONG lLineBytes;
	lLineBytes = GDI_WIDTHBYTES(lWidth * 8);
	hNewDIBBits = LocalAlloc(LHND, lLineBytes*lHeight);
	if (hNewDIBBits == NULL)
	{
		return FALSE;
	}
	lpNewDIBBits = (char *)LocalLock(hNewDIBBits);

	// 初始化图像为原始图像
	memcpy(lpNewDIBBits, lpDIBBits, lLineBytes * lHeight);

	// 行(除去边缘几行)
	for (i = iTempMY; i < lHeight - iTempH + iTempMY + 1; i++)
	{
		// 列(除去边缘几列)
		for (j = iTempMX; j < lWidth - iTempW + iTempMX + 1; j++)
		{
			// 指向新DIB第i行，第j个象素的指针
			lpDst = (unsigned char*)lpNewDIBBits + lLineBytes * (lHeight - 1 - i) + j;

			fResult = 0;
			fTemp = 0;
			// 计算
			for (k = 0; k < iTempH; k++)
			{
				for (l = 0; l < iTempW; l++)
				{
					// 指向DIB第i - iTempMY + k行，第j - iTempMX + l个象素的指针
					lpSrc = (unsigned char*)lpDIBBits + lLineBytes * (lHeight - 1 - i + iTempMY - k)
						+ j - iTempMX + l;

					// 保存象素值
					fResult += (*lpSrc) * Arr[k * iTempW + l];
					
				}
			}

			// 乘上系数
			fResult *= fCoef;

			// 取绝对值
			fResult = (FLOAT)fabs(fResult);

			// 判断是否超过255
			if (fResult > 255)
			{
				// 直接赋值为255
				*lpDst = 255;
			}
			else
			{
				// 赋值
				*lpDst = (unsigned char)((fResult + 0.5)+*lpDst);
				if (*lpDst > 255)
				{
					*lpDst = 255;
				}
			}

		}
	}

	// 复制变换后的图像
	memcpy(lpDIBBits, lpNewDIBBits, lLineBytes * lHeight);

	// 释放内存
	LocalUnlock(hNewDIBBits);
	LocalFree(hNewDIBBits);

	// 返回
	return TRUE;


}





BOOL WINAPI STemplate(LPSTR lpDIBBits, LONG lWidth, LONG lHeight,
	int iTempH, int iTempW,
	int iTempMX, int iTempMY,
	FLOAT * Arr, FLOAT fCoef)
{
	FLOAT aTemplate1[9] = {-1.0,-1.0,-1.0,0.0,0.0,0.0,1.0,1.0,1.0};
	FLOAT aTemplate2[9] = {1.0,0.0,-1.0,1.0,0.0,-1.0,1.0,0.0,-1.0};
	LPSTR lpNewDIBBits;
	HLOCAL hNewDIBBits;
	unsigned char* lpSrc;
	unsigned char* lpDst;
	LONG i, j, k, l;
	FLOAT fResult1,fResult2;
	LONG lLineBytes;
	lLineBytes = GDI_WIDTHBYTES(lWidth * 8);
	hNewDIBBits = LocalAlloc(LHND, lLineBytes*lHeight);
	if (hNewDIBBits == NULL)
	{
		return FALSE;
	}
	lpNewDIBBits = (char *)LocalLock(hNewDIBBits);


	// 初始化图像为原始图像
	memcpy(lpNewDIBBits, lpDIBBits, lLineBytes * lHeight);

	// 行(除去边缘几行)
	for (i = iTempMY; i < lHeight - iTempH + iTempMY + 1; i++)
	{
		// 列(除去边缘几列)
		for (j = iTempMX; j < lWidth - iTempW + iTempMX + 1; j++)
		{
			// 指向新DIB第i行，第j个象素的指针
			lpDst = (unsigned char*)lpNewDIBBits + lLineBytes * (lHeight - 1 - i) + j;

			fResult1 = 0;
			fResult2 = 0;

			// 计算
			for (k = 0; k < iTempH; k++)
			{
				for (l = 0; l < iTempW; l++)
				{
					// 指向DIB第i - iTempMY + k行，第j - iTempMX + l个象素的指针
					lpSrc = (unsigned char*)lpDIBBits + lLineBytes * (lHeight - 1 - i + iTempMY - k)
						+ j - iTempMX + l;

					// 保存象素值
					fResult1 += (*lpSrc) * aTemplate2[k * iTempW + l];
					fResult2 += (*lpSrc) * aTemplate1[k * iTempW + l];
				
				//	fResult1 += fResult2;
				}
			}

			// 乘上系数
			fResult1 *= fCoef;

			// 取绝对值
			fResult1 = (FLOAT)fabs(fResult1);
			fResult2 *= fCoef;

			// 取绝对值
			fResult2= (FLOAT)fabs(fResult1);
			//fResult1 += fResult2;
			if (fResult1 < fResult2)
				fResult1 = fResult2;
			// 判断是否超过255
			if (fResult1 > 255)
			{
				// 直接赋值为255
				*lpDst = 255;
			}
			else
			{
				// 赋值
				*lpDst = (unsigned char)(fResult1 + 0.5);
			}

		}
	}

	// 复制变换后的图像
	memcpy(lpDIBBits, lpNewDIBBits, lLineBytes * lHeight);

	// 释放内存
	LocalUnlock(hNewDIBBits);
	LocalFree(hNewDIBBits);

	// 返回
	return TRUE;


}




BOOL WINAPI Template24(LPSTR lpDIBBits, LONG lWidth, LONG lHeight,
	int iTempH, int iTempW,
	int iTempMX, int iTempMY,
	FLOAT * Arr, FLOAT fCoef, int constant)
{
	lWidth = lWidth * 3;
	char *a = new char[lWidth*lHeight];
	for (int i = iTempMX; i < lHeight; i++)
	{
		for (int j = iTempMY; j < lWidth; j++)
			a[i*lWidth + j] = lpDIBBits[i*lWidth + j];
	}
	for (int i = iTempMX; i < lHeight + iTempMX - 2; i++)
	{
		for (int j = iTempMY; j < lWidth + iTempMY - 2; j++)
		{
			unsigned char temp[9] = { 0,0,0,0,0,0,0,0,0 };
			temp[0] = lpDIBBits[(i - iTempMX)*lWidth + j - iTempMY];
			temp[1] = lpDIBBits[(i - iTempMX)*lWidth + j - iTempMY + 1];
			temp[2] = lpDIBBits[(i - iTempMX)*lWidth + j - iTempMY + 2];
			temp[3] = lpDIBBits[(i - iTempMX + 1)*lWidth + j - iTempMY];
			temp[4] = lpDIBBits[(i - iTempMX + 1)*lWidth + j - iTempMY + 1];
			temp[5] = lpDIBBits[(i - iTempMX + 1)*lWidth + j - iTempMY + 2];
			temp[6] = lpDIBBits[(i - iTempMX + 2)*lWidth + j - iTempMY];
			temp[7] = lpDIBBits[(i - iTempMX + 2)*lWidth + j - iTempMY + 1];
			temp[8] = lpDIBBits[(i - iTempMX + 2)*lWidth + j - iTempMY + 2];
			double x;
			double sum = 0.0;
			for (int i = 0; i < 9; i++)
			{
				sum += (Arr[i] * temp[i]);
			}
			x = sum * fCoef + constant;
			if (x < 0)x = 0;
			if (x > 255)x = 255;
			a[i*lWidth + j] = unsigned char(x);
		}
	}
	for(int i=iTempMX;i<lHeight;i++)
		for (int j = iTempMY; j < lWidth; j++)
		{
			lpDIBBits[i*lWidth + j] = a[i*lWidth + j];
		}
	return TRUE;
}










