#pragma once
#include "stdafx.h"
#include <math.h>
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
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

	// ��ʼ��ͼ��Ϊԭʼͼ��
	memcpy(lpNewDIBBits, lpDIBBits, lLineBytes * lHeight);

	// ��(��ȥ��Ե����)
	for (i = iTempMY; i < lHeight - iTempH + iTempMY + 1; i++)
	{
		// ��(��ȥ��Ե����)
		for (j = iTempMX; j < lWidth - iTempW + iTempMX + 1; j++)
		{
			// ָ����DIB��i�У���j�����ص�ָ��
			lpDst = (unsigned char*)lpNewDIBBits + lLineBytes * (lHeight - 1 - i) + j;

			fResult = 0;

			// ����
			for (k = 0; k < iTempH; k++)
			{
				for (l = 0; l < iTempW; l++)
				{
					// ָ��DIB��i - iTempMY + k�У���j - iTempMX + l�����ص�ָ��
					lpSrc = (unsigned char*)lpDIBBits + lLineBytes * (lHeight - 1 - i + iTempMY - k)
						+ j - iTempMX + l;

					// ��������ֵ
					fResult += (*lpSrc) * Arr[k * iTempW + l];
				}
			}

			// ����ϵ��
			fResult *= fCoef;

			// ȡ����ֵ
			fResult = (FLOAT)fabs(fResult);

			// �ж��Ƿ񳬹�255
			if (fResult > 255)
			{
				// ֱ�Ӹ�ֵΪ255
				*lpDst = 255;
			}
			else
			{
				// ��ֵ
				*lpDst = (unsigned char)(fResult + 0.5);
			}

		}
	}

	// ���Ʊ任���ͼ��
	memcpy(lpDIBBits, lpNewDIBBits, lLineBytes * lHeight);

	// �ͷ��ڴ�
	LocalUnlock(hNewDIBBits);
	LocalFree(hNewDIBBits);

	// ����
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

	// �м����
	if ((iFilterLen & 1) > 0)
	{
		// ������������Ԫ�أ������м�һ��Ԫ��
		bTemp = bArray[(iFilterLen + 1) / 2];
	}
	else
	{
		// ������ż����Ԫ�أ������м�����Ԫ��ƽ��ֵ
		bTemp = (bArray[iFilterLen / 2] + bArray[iFilterLen / 2 + 1]) / 2;
	}

	// ������ֵ
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
	//������ֵ
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
	//������ֵ
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
	// ָ��Դͼ���ָ��
	unsigned char*	lpSrc;
	unsigned char*	lpSrc1;
	unsigned char*	lpSrc2;
	// ѭ������
	LONG	i;
	LONG	j;
	// ͼ��ÿ�е��ֽ���
	LONG	lLineBytes;
	// �м����
	BYTE	bTemp;
	// ����ͼ��ÿ�е��ֽ���
	lLineBytes = GDI_WIDTHBYTES(lWidth * 8);
	// ÿ��
	for (i = 0; i < lHeight; i++)
	{
		// ÿ��
		for (j = 0; j < lWidth; j++)
		{
			lpSrc = (unsigned char*)lpDIBBits + lLineBytes * (lHeight - 1 - i) + j;
			// ָ��DIB��i+1�У���j�����ص�ָ��
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

	// ��ʼ��ͼ��Ϊԭʼͼ��
	memcpy(lpNewDIBBits, lpDIBBits, lLineBytes * lHeight);

	// ��(��ȥ��Ե����)
	for (i = iTempMY; i < lHeight - iTempH + iTempMY + 1; i++)
	{
		// ��(��ȥ��Ե����)
		for (j = iTempMX; j < lWidth - iTempW + iTempMX + 1; j++)
		{
			// ָ����DIB��i�У���j�����ص�ָ��
			lpDst = (unsigned char*)lpNewDIBBits + lLineBytes * (lHeight - 1 - i) + j;

			fResult = 0;
			fTemp = 0;
			// ����
			for (k = 0; k < iTempH; k++)
			{
				for (l = 0; l < iTempW; l++)
				{
					// ָ��DIB��i - iTempMY + k�У���j - iTempMX + l�����ص�ָ��
					lpSrc = (unsigned char*)lpDIBBits + lLineBytes * (lHeight - 1 - i + iTempMY - k)
						+ j - iTempMX + l;

					// ��������ֵ
					fResult += (*lpSrc) * Arr[k * iTempW + l];
					
				}
			}

			// ����ϵ��
			fResult *= fCoef;

			// ȡ����ֵ
			fResult = (FLOAT)fabs(fResult);

			// �ж��Ƿ񳬹�255
			if (fResult > 255)
			{
				// ֱ�Ӹ�ֵΪ255
				*lpDst = 255;
			}
			else
			{
				// ��ֵ
				*lpDst = (unsigned char)((fResult + 0.5)+*lpDst);
				if (*lpDst > 255)
				{
					*lpDst = 255;
				}
			}

		}
	}

	// ���Ʊ任���ͼ��
	memcpy(lpDIBBits, lpNewDIBBits, lLineBytes * lHeight);

	// �ͷ��ڴ�
	LocalUnlock(hNewDIBBits);
	LocalFree(hNewDIBBits);

	// ����
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


	// ��ʼ��ͼ��Ϊԭʼͼ��
	memcpy(lpNewDIBBits, lpDIBBits, lLineBytes * lHeight);

	// ��(��ȥ��Ե����)
	for (i = iTempMY; i < lHeight - iTempH + iTempMY + 1; i++)
	{
		// ��(��ȥ��Ե����)
		for (j = iTempMX; j < lWidth - iTempW + iTempMX + 1; j++)
		{
			// ָ����DIB��i�У���j�����ص�ָ��
			lpDst = (unsigned char*)lpNewDIBBits + lLineBytes * (lHeight - 1 - i) + j;

			fResult1 = 0;
			fResult2 = 0;

			// ����
			for (k = 0; k < iTempH; k++)
			{
				for (l = 0; l < iTempW; l++)
				{
					// ָ��DIB��i - iTempMY + k�У���j - iTempMX + l�����ص�ָ��
					lpSrc = (unsigned char*)lpDIBBits + lLineBytes * (lHeight - 1 - i + iTempMY - k)
						+ j - iTempMX + l;

					// ��������ֵ
					fResult1 += (*lpSrc) * aTemplate2[k * iTempW + l];
					fResult2 += (*lpSrc) * aTemplate1[k * iTempW + l];
				
				//	fResult1 += fResult2;
				}
			}

			// ����ϵ��
			fResult1 *= fCoef;

			// ȡ����ֵ
			fResult1 = (FLOAT)fabs(fResult1);
			fResult2 *= fCoef;

			// ȡ����ֵ
			fResult2= (FLOAT)fabs(fResult1);
			//fResult1 += fResult2;
			if (fResult1 < fResult2)
				fResult1 = fResult2;
			// �ж��Ƿ񳬹�255
			if (fResult1 > 255)
			{
				// ֱ�Ӹ�ֵΪ255
				*lpDst = 255;
			}
			else
			{
				// ��ֵ
				*lpDst = (unsigned char)(fResult1 + 0.5);
			}

		}
	}

	// ���Ʊ任���ͼ��
	memcpy(lpDIBBits, lpNewDIBBits, lLineBytes * lHeight);

	// �ͷ��ڴ�
	LocalUnlock(hNewDIBBits);
	LocalFree(hNewDIBBits);

	// ����
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










