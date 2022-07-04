// ************************************************************************
//  文件名：Final.cpp
//
//  课程设计函数库：
//  CalThreshold 输入阈值后对图像进行处理
//  Iterative 迭代法求阈值
//  Otsu算法求阈值
//  MyCalThreshold 自适应阈值分割
//  CalWindow 窗口变换
//  CalGray 灰度拉伸
//  Equalize 直方图均衡化
//  dealer 计数
//
// ************************************************************************

#include "stdafx.h"
#include "Coursedesign.h"
#include "DIBAPI.h"

#include <math.h>
#include <direct.h>
#include <queue>
//#include <complex>
//#include<Windows.h>
#define PI 3.1415926535
#define RADIAN(angle) ((angle)*PI/180.0)
using namespace std;

struct point {
	int i;
	int j;
};

/*************************************************************************
 *
 * 函数名称：
 *   CalThreshold()
 *
 * 参数:
 *   LPSTR lpDIBBits    - 指向源DIB图像指针
 *   LONG  lWidth       - 源图像宽度（象素数）
 *   LONG  lHeight      - 源图像高度（象素数）
 *   double num		    - 阈值
 *
 * 返回值:
 *   BOOL               - 成功返回TRUE，否则返回FALSE。
 *
 * 说明:
 *   该函数用来对图像进行二值化操作。
 *
 ************************************************************************/
BOOL WINAPI CalThreshold(LPSTR lpDIBBits, LONG lWidth, LONG lHeight, double num)
{
	// 指向源图像的指针
	unsigned char* lpSrc;

	// 循环变量
	LONG	i;
	LONG	j;

	// 图像每行的字节数
	LONG	lLineBytes;

	// 中间变量
	FLOAT	fTemp;

	// 计算图像每行的字节数
	lLineBytes = WIDTHBYTES(lWidth * 8);

	// 每行
	for (i = 0; i < lHeight; i++)
	{
		// 每列
		for (j = 0; j < lWidth; j++)
		{
			// 指向DIB第i行，第j个象素的指针
			lpSrc = (unsigned char*)lpDIBBits + lLineBytes * (lHeight - 1 - i) + j;

			// 输出像素值
			fTemp = *lpSrc;

			// 判断是否超出阈值
			if (fTemp > num)
			{
				// 直接赋值为255
				*lpSrc = 255;
			}
			else
			{
				// 直接赋值为0
				*lpSrc = 0;
			}
		}
	}

	// 返回
	return TRUE;
}

/*************************************************************************
 *
 * 函数名称：
 *   MyCalThreshold()
 *
 * 参数:
 *   LPSTR lpDIBBits    - 指向源DIB图像指针
 *   LONG  lWidth       - 源图像宽度（象素数）
 *   LONG  lHeight      - 源图像高度（象素数）
 *
 * 返回值:
 *   BOOL               - 成功返回TRUE，否则返回FALSE。
 *
 * 说明:
 *   该函数用来对图像进行自适应阈值分割操作。
 *
 ************************************************************************/

BOOL WINAPI MyCalThreshold(LPSTR lpDIBBits, LONG lWidth, LONG lHeight)
{
	// 指向源图像的指针
	unsigned char* lpSrc;

	// 循环变量
	LONG	i;
	LONG	j;

	// 图像每行的字节数
	LONG	lLineBytes;

	// 中间变量
	FLOAT	fTemp;

	// 计算图像每行的字节数
	lLineBytes = WIDTHBYTES(lWidth * 8);


	//左上角
	LONG sum = 0;
	LONG count = 0;
	LONG num = 0;
	// 每行
	for (i = 0; i < lHeight / 2; i++)
	{
		// 每列
		for (j = 0; j < lWidth / 2; j++)
		{
			// 指向DIB第i行，第j个象素的指针
			lpSrc = (unsigned char*)lpDIBBits + lLineBytes * (lHeight - 1 - i) + j;

			// 输出像素值
			fTemp = *lpSrc;
			sum += fTemp;
			count++;
		}
	}
	num = sum / count;
	// 每行
	for (i = 0; i < lHeight / 2; i++)
	{
		// 每列
		for (j = 0; j < lWidth / 2; j++)
		{
			// 指向DIB第i行，第j个象素的指针
			lpSrc = (unsigned char*)lpDIBBits + lLineBytes * (lHeight - 1 - i) + j;

			// 输出像素值
			fTemp = *lpSrc;

			// 判断是否超出阈值
			if (fTemp > num)
			{
				// 直接赋值为255
				*lpSrc = 255;
			}
			else
			{
				// 直接赋值为0
				*lpSrc = 0;
			}
		}
	}

	//右上角
	sum = 0;
	count = 0;
	num = 0;
	// 每行
	for (i = 0; i < lHeight / 2; i++)
	{
		// 每列
		for (j = lWidth / 2; j < lWidth; j++)
		{
			// 指向DIB第i行，第j个象素的指针
			lpSrc = (unsigned char*)lpDIBBits + lLineBytes * (lHeight - 1 - i) + j;

			// 输出像素值
			fTemp = *lpSrc;
			sum += fTemp;
			count++;
		}
	}
	num = sum / count;
	// 每行
	for (i = 0; i < lHeight / 2; i++)
	{
		// 每列
		for (j = lWidth / 2; j < lWidth; j++)
		{
			// 指向DIB第i行，第j个象素的指针
			lpSrc = (unsigned char*)lpDIBBits + lLineBytes * (lHeight - 1 - i) + j;

			// 输出像素值
			fTemp = *lpSrc;

			// 判断是否超出阈值
			if (fTemp > num)
			{
				// 直接赋值为255
				*lpSrc = 255;
			}
			else
			{
				// 直接赋值为0
				*lpSrc = 0;
			}
		}
	}

	//左下角
	sum = 0;
	count = 0;
	num = 0;
	// 每行
	for (i = lHeight / 2; i < lHeight; i++)
	{
		// 每列
		for (j = 0; j < lWidth / 2; j++)
		{
			// 指向DIB第i行，第j个象素的指针
			lpSrc = (unsigned char*)lpDIBBits + lLineBytes * (lHeight - 1 - i) + j;

			// 输出像素值
			fTemp = *lpSrc;
			sum += fTemp;
			count++;
		}
	}
	num = sum / count;
	// 每行
	for (i = lHeight / 2; i < lHeight; i++)
	{
		// 每列
		for (j = 0; j < lWidth / 2; j++)
		{
			// 指向DIB第i行，第j个象素的指针
			lpSrc = (unsigned char*)lpDIBBits + lLineBytes * (lHeight - 1 - i) + j;

			// 输出像素值
			fTemp = *lpSrc;

			// 判断是否超出阈值
			if (fTemp > num)
			{
				// 直接赋值为255
				*lpSrc = 255;
			}
			else
			{
				// 直接赋值为0
				*lpSrc = 0;
			}
		}
	}

	//右下角
	sum = 0;
	count = 0;
	num = 0;
	// 每行
	for (i = lHeight / 2; i < lHeight; i++)
	{
		// 每列
		for (j = lWidth / 2; j < lWidth; j++)
		{
			// 指向DIB第i行，第j个象素的指针
			lpSrc = (unsigned char*)lpDIBBits + lLineBytes * (lHeight - 1 - i) + j;

			// 输出像素值
			fTemp = *lpSrc;
			sum += fTemp;
			count++;
		}
	}
	num = sum / count;
	// 每行
	for (i = lHeight / 2; i < lHeight; i++)
	{
		// 每列
		for (j = lWidth / 2; j < lWidth; j++)
		{
			// 指向DIB第i行，第j个象素的指针
			lpSrc = (unsigned char*)lpDIBBits + lLineBytes * (lHeight - 1 - i) + j;

			// 输出像素值
			fTemp = *lpSrc;

			// 判断是否超出阈值
			if (fTemp > num)
			{
				// 直接赋值为255
				*lpSrc = 255;
			}
			else
			{
				// 直接赋值为0
				*lpSrc = 0;
			}
		}
	}

	// 返回
	return TRUE;
}

/*************************************************************************
 *
 * 函数名称：
 *   Iterative()
 *
 * 参数:
 *   LPSTR lpDIBBits    - 指向源DIB图像指针
 *   LONG  lWidth       - 源图像宽度（象素数）
 *   LONG  lHeight      - 源图像高度（象素数）
 *
 * 返回值:
 *   BOOL               - 成功返回TRUE，否则返回FALSE。
 *
 * 说明:
 *   该函数通过迭代法用来对图像进行二值化操作。
 *
 ************************************************************************/

double Iterative(LPSTR lpDIBBits, LONG lWidth, LONG lHeight)
{
	double result;
	double T0 = 1;
	double T = 128;
	double T1 = 0;

	// 指向源图像的指针
	unsigned char* lpSrc;

	// 图像每行的字节数
	LONG	lLineBytes;

	// 中间变量
	FLOAT	fTemp;

	// 计算图像每行的字节数
	lLineBytes = WIDTHBYTES(lWidth * 8);

	while (((T - T1) > T0) || ((T - T1) < -T0))
	{
		double G1 = 0;
		double G2 = 0;
		int count1 = 0;
		int count2 = 0;

		// 每行
		for (long i = 0; i < lHeight; i++)
		{
			// 每列
			for (long j = 0; j < lWidth; j++)
			{
				// 指向DIB第i行，第j个象素的指针
				lpSrc = (unsigned char*)lpDIBBits + lLineBytes * (lHeight - 1 - i) + j;

				// 输出像素值
				fTemp = *lpSrc;

				// 判断是否超出阈值
				if (fTemp > T)
				{
					//大的分为G1类
					G1 += fTemp;
					count1++;
				}
				else
				{
					//小的分为G2类
					G2 += fTemp;
					count2++;
				}
			}
		}

		T1 = T;
		T = ((G1 / count1) + (G2 / count2)) / 2;
		result = T;
	}
	// 返回
	return result;
}

/*************************************************************************
 *
 * 函数名称：
 *   Otsu()
 *
 * 参数:
 *   LPSTR lpDIBBits    - 指向源DIB图像指针
 *   LONG  lWidth       - 源图像宽度（象素数）
 *   LONG  lHeight      - 源图像高度（象素数）
 *
 * 返回值:
 *   BOOL               - 成功返回TRUE，否则返回FALSE。
 *
 * 说明:
 *   该函数用来对图像进行二值化操作。
 *
 ************************************************************************/

double Otsu(LPSTR lpDIBBits, LONG lWidth, LONG lHeight)
{
	double T = 0;
	double varflaga = 0; //类间方差中间值保存  
	double w0 = 0; //前景像素点数所占比例  
	double w1 = 0; //背景像素点数所占比例  
	double u0 = 0; //前景平均灰度  
	double u1 = 0; //背景平均灰度
	double Histogram[256] = { 0 }; //灰度直方图，下标是灰度值，保存内容是灰度值对应的像素点总数  
	LONG i, j, k;
	double totalNum = lWidth * lHeight; //像素总数  

	// 指向源图像的指针
	unsigned char* lpSrc;

	// 图像每行的字节数
	LONG	lLineBytes;

	// 计算图像每行的字节数
	lLineBytes = WIDTHBYTES(lWidth * 8);

	//计算灰度直方图分布，Histogram数组下标是灰度值，保存内容是灰度值对应像素点数  
	for (i = 0; i < lHeight; i++)
	{
		for (j = 0; j < lWidth; j++)
		{
			// 指向DIB第i行，第j个象素的指针
			lpSrc = (unsigned char*)lpDIBBits + lLineBytes * (lHeight - 1 - i) + j;
			Histogram[*(lpSrc)]++;
		}
	}

	for (i = 0; i < 255; i++)
	{
		w1 = 0; u1 = 0; w0 = 0; u0 = 0;

		//背景各分量值计算 
		for (j = 0; j <= i; j++) //背景部分各值计算  
		{
			w1 += Histogram[j];  //背景部分像素点总数  
			u1 += j * Histogram[j]; //背景部分像素总灰度和  
		}
		u1 = u1 / w1; //背景像素平均灰度  
		w1 = w1 / totalNum; // 背景部分像素点数所占比例  


		//前景各分量值计算
		for (k = i + 1; k < 255; k++)
		{
			w0 += Histogram[k];  //前景部分像素点总数  
			u0 += k * Histogram[k]; //前景部分像素总灰度和  
		}
		u0 = u0 / w0; //前景像素平均灰度  
		w0 = w0 / totalNum; // 前景部分像素点数所占比例  

		//类间方差计算 
		double varflagaI = w0 * w1 * (u1 - u0) * (u1 - u0); //当前类间方差计算  
		if (varflaga < varflagaI)
		{
			varflaga = varflagaI;
			T = i;
		}
	}
	return T;
}

/*************************************************************************
 *
 * 函数名称：
 *   CalWindow()
 *
 * 参数:
 *   LPSTR lpDIBBits    - 指向源DIB图像指针
 *   LONG  lWidth       - 源图像宽度（象素数）
 *   LONG  lHeight      - 源图像高度（象素数）
 *   double max		    - 窗口上限
 *   double min		    - 窗口下限
 *
 * 返回值:
 *   BOOL               - 成功返回TRUE，否则返回FALSE。
 *
 * 说明:
 *   该函数用来对图像进行窗口变换操作。
 *
 ************************************************************************/

BOOL WINAPI CalWindow(LPSTR lpDIBBits, LONG lWidth, LONG lHeight, double max, double min)
{
	// 指向源图像的指针
	unsigned char* lpSrc;

	// 循环变量
	LONG	i;
	LONG	j;

	// 图像每行的字节数
	LONG	lLineBytes;

	// 中间变量
	FLOAT	fTemp;

	// 计算图像每行的字节数
	lLineBytes = WIDTHBYTES(lWidth * 8);

	// 每行
	for (i = 0; i < lHeight; i++)
	{
		// 每列
		for (j = 0; j < lWidth; j++)
		{
			// 指向DIB第i行，第j个象素的指针
			lpSrc = (unsigned char*)lpDIBBits + lLineBytes * (lHeight - 1 - i) + j;

			// 输出像素值
			fTemp = *lpSrc;

			// 判断是否超出阈值
			if (fTemp > max)
			{
				// 直接赋值为255
				*lpSrc = 255;
			}
			else if (fTemp < min)
			{
				// 直接赋值为0
				*lpSrc = 0;
			}
		}
	}

	// 返回
	return TRUE;
}

/*************************************************************************
 *
 * 函数名称：
 *   CalGray()
 *
 * 参数:
 *   LPSTR lpDIBBits    - 指向源DIB图像指针
 *   LONG  lWidth       - 源图像宽度（象素数）
 *   LONG  lHeight      - 源图像高度（象素数）
 *   double x1		    - x1
 *   double y1		    - y1
 *   double x2		    - x2
 *   double y2		    - y2
 *
 * 返回值:
 *   BOOL               - 成功返回TRUE，否则返回FALSE。
 *
 * 说明:
 *   该函数用来对图像进行灰度拉伸操作。
 *
 ************************************************************************/

BOOL WINAPI GrayStretch(LPSTR lpDIBBits, LONG lWidth, LONG lHeight, BYTE bX1, BYTE bY1, BYTE bX2, BYTE bY2, long lLineBytes)
{

	// 指向源图像的指针
	unsigned char* lpSrc;

	// 循环变量
	LONG	i;
	LONG	j;

	// 灰度映射表
	BYTE	bMap[256];

	// 图像每行的字节数
	//LONG	lLineBytes;

	// 计算图像每行的字节数
	//lLineBytes = WIDTHBYTES(lWidth * 8);

	// 计算灰度映射表
	for (i = 0; i <= bX1; i++)
	{
		// 判断bX1是否大于0（防止分母为0）
		if (bX1 > 0)
		{
			// 线性变换
			bMap[i] = (BYTE)bY1 * i / bX1;
		}
		else
		{
			// 直接赋值为0
			bMap[i] = 0;
		}
	}
	for (; i <= bX2; i++)
	{
		// 判断bX1是否等于bX2（防止分母为0）
		if (bX2 != bX1)
		{
			// 线性变换
			bMap[i] = bY1 + (BYTE)((bY2 - bY1) * (i - bX1) / (bX2 - bX1));
		}
		else
		{
			// 直接赋值为bY1
			bMap[i] = bY1;
		}
	}
	for (; i < 256; i++)
	{
		// 判断bX2是否等于255（防止分母为0）
		if (bX2 != 255)
		{
			// 线性变换
			bMap[i] = bY2 + (BYTE)((255 - bY2) * (i - bX2) / (255 - bX2));
		}
		else
		{
			// 直接赋值为255
			bMap[i] = 255;
		}
	}

	// 每行
	for (i = 0; i < lHeight; i++)
	{
		// 每列
		for (j = 0; j < lWidth; j++)
		{
			// 指向DIB第i行，第j个象素的指针
			lpSrc = (unsigned char*)lpDIBBits + lLineBytes * (lHeight - 1 - i) + j;

			// 计算新的灰度值
			*lpSrc = bMap[*lpSrc];
		}
	}

	// 返回
	return TRUE;
}

/*************************************************************************
 *
 * 函数名称：
 *   Equalize()
 *
 * 参数:
 *   LPSTR lpDIBBits    - 指向源DIB图像指针
 *   LONG  lWidth       - 源图像宽度（象素数）
 *   LONG  lHeight      - 源图像高度（象素数）
 *
 * 返回值:
 *   BOOL               - 成功返回TRUE，否则返回FALSE。
 *
 * 说明:
 *   该函数用来对图像进行直方图均衡。
 *
 ************************************************************************/
BOOL WINAPI Equalize(LPSTR lpDIBBits, LONG lWidth, LONG lHeight)
{

	// 指向源图像的指针
	unsigned char* lpSrc;

	// 临时变量
	LONG	lTemp;

	// 循环变量
	LONG	i;
	LONG	j;

	// 灰度映射表
	BYTE	bMap[256];

	// 灰度映射表
	LONG	lCount[256];

	// 图像每行的字节数
	LONG	lLineBytes;

	// 计算图像每行的字节数
	lLineBytes = WIDTHBYTES(lWidth * 8);

	// 重置计数为0
	for (i = 0; i < 256; i++)
	{
		// 清零
		lCount[i] = 0;
	}

	// 计算各个灰度值的计数
	for (i = 0; i < lHeight; i++)
	{
		for (j = 0; j < lWidth; j++)
		{
			lpSrc = (unsigned char*)lpDIBBits + lLineBytes * i + j;

			// 计数加1
			lCount[*(lpSrc)]++;
		}
	}

	// 计算灰度映射表
	for (i = 0; i < 256; i++)
	{
		// 初始为0
		lTemp = 0;

		for (j = 0; j <= i; j++)
		{
			lTemp += lCount[j];
		}

		// 计算对应的新灰度值
		bMap[i] = (BYTE)(lTemp * 255 / lHeight / lWidth);
	}

	// 每行
	for (i = 0; i < lHeight; i++)
	{
		// 每列
		for (j = 0; j < lWidth; j++)
		{
			// 指向DIB第i行，第j个象素的指针
			lpSrc = (unsigned char*)lpDIBBits + lLineBytes * (lHeight - 1 - i) + j;

			// 计算新的灰度值
			*lpSrc = bMap[*lpSrc];
		}
	}

	// 返回
	return TRUE;
}

/*************************************************************************
 *
 * 函数名称：
 *   dealer()
 *
 * 参数:
 *   LPSTR lpDIBBits    - 指向源DIB图像指针
 *   LONG  lWidth       - 源图像宽度（象素数）
 *   LONG  lHeight      - 源图像高度（象素数）
 *
 * 返回值:
 *   int               - 米粒
 *
 * 说明:
 *   该函数用来计算图中物体个数。
 *
 ************************************************************************/

 //4连通计数
 /*************************************************************************
 *
 * 函数名称：
 *   dealer()
 *
 * 参数:
 *   LPSTR lpDIBBits    - 指向源DIB图像指针
 *   LONG  lWidth       - 源图像宽度（象素数）
 *   LONG  lHeight      - 源图像高度（象素数）
 *
 * 返回值:
 *   int               - 米粒
 *
 * 说明:
 *   该函数用来计算图中物体个数。
 *
 ************************************************************************/

int  dealer_four(LPSTR image, int width, int height, int Bg)
//bg即物体颜色
{
	int** flag_max;
	flag_max = new int* [height];
	for (int i = 0; i < height; i++) {
		flag_max[i] = new int[width];
	}//按照尺寸分配数组，用于判断该像素点是否已经被标记过了   
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			flag_max[i][j] = 0;
		}
	}
	int count_flag = 0;
	queue<point> buffer;	//创建线性表（队列）
	int count = 1;    //区域标记
	int color;
	unsigned char* ptemp = (unsigned char*)image;

	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if ((*(ptemp + i * width + j) == Bg) && (flag_max[i][j] == 0))
			//当点的颜色等于待寻找物体颜色时
			{
				point temp;	// point结构体对象，记录坐标值
				temp.i = i;	
				temp.j = j;	// 赋予xy坐标值
				buffer.push(temp);// 将该点加入线性表（在末尾）
				while (buffer.size() > 0)// 线性表非空（直到这个区域所有点都遍历完
				{
					count_flag = 1; //进入循环
					temp = buffer.front();	//返回 queue 中第一个元素的引用，取出第一个元素给temp
					buffer.pop(); //将第一个元素弹出
					if (temp.i >= 0 && temp.i <= height && temp.j >= 0 && temp.j <= width && *(ptemp + temp.i * width + temp.j) == Bg && flag_max[temp.i][temp.j] == 0)
					{	// 当刚刚弹出的在图像内并且颜色符合时
						//标记
						flag_max[temp.i][temp.j] = count;//将这个点标记为区域x(从1开始）
						if (temp.i - 1 >= 0 && temp.i - 1 < height && temp.j >= 0 && temp.j < width && *(ptemp + (temp.i - 1) * width + temp.j) == Bg && flag_max[temp.i - 1][temp.j] == 0) {
							// 当左边的点颜色也符合时，并且未被标记过
							point linyu; // 新建节点并加入到队列中
							linyu.i = temp.i - 1;
							linyu.j = temp.j;
							buffer.push(linyu);
						}
						if (temp.i >= 0 && temp.i < height && temp.j - 1 >= 0 && temp.j - 1 < width && *(ptemp + temp.i * width + temp.j - 1) == Bg && flag_max[temp.i][temp.j - 1] == 0) {
							// 当上面的节点也符合要求时，并且未被标记过
							point linyu; // 新建节点并加入到队列中
							linyu.i = temp.i;
							linyu.j = temp.j - 1;
							buffer.push(linyu);
						}
						if (temp.i >= 0 && temp.i < height && temp.j + 1 >= 0 && temp.j + 1 < width && *(ptemp + temp.i * width + temp.j + 1) == Bg && flag_max[temp.i][temp.j + 1] == 0) {
							// 当下面的节点也符合要求时，并且未被标记过
							point linyu;// 新建节点并加入到队列中
							linyu.i = temp.i;
							linyu.j = temp.j + 1;
							buffer.push(linyu);
						}
						if (temp.i + 1 >= 0 && temp.i + 1 < height && temp.j >= 0 && temp.j < width && *(ptemp + (temp.i + 1) * width + temp.j) == Bg && flag_max[temp.i + 1][temp.j] == 0) {
							// 当右边的节点也符合要求时，并且未被标记过
							point linyu;// 新建节点并加入到队列中
							linyu.i = temp.i + 1;
							linyu.j = temp.j;
							buffer.push(linyu);
						}
					}
				}//while
			}//if

			 //j++;
			if (count_flag == 1)
			{
				count++; //当这个区域所有点都弹出后，换下一个区域
				count_flag = 0;
			}
		}
	}
	return count - 1;//返回区域数
}

//8连通计数
/*************************************************************************
*
* 函数名称：
*   dealer()
*
* 参数:
*   LPSTR lpDIBBits    - 指向源DIB图像指针
*   LONG  lWidth       - 源图像宽度（象素数）
*   LONG  lHeight      - 源图像高度（象素数）
*
* 返回值:
*   int               - 米粒
*
* 说明:
*   该函数用来计算图中物体个数。
*
************************************************************************/

int  dealer_eight(LPSTR image, int width, int height, int Bg)
{
	int** flag_max;
	flag_max = new int* [height];
	for (int i = 0; i < height; i++) {
		flag_max[i] = new int[width];
	}                                         //动态分配二维数组
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			flag_max[i][j] = 0;
		}
	}


	int count_flag = 0;
	queue<point> buffer;
	int count = 1;    //区域标记
	int color;
	unsigned char* ptemp = (unsigned char*)image;



	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if ((*(ptemp + i * width + j) == Bg) && (flag_max[i][j] == 0))
			{
				point temp;
				temp.i = i;
				temp.j = j;
				buffer.push(temp);
				while (buffer.size() > 0)
				{
					count_flag = 1;//表明进入循环
					temp = buffer.front();
					buffer.pop();
					if (temp.i >= 0 && temp.i <= height && temp.j >= 0 && temp.j <= width && *(ptemp + temp.i * width + temp.j) == Bg && flag_max[temp.i][temp.j] == 0)
					{
						//标记
						flag_max[temp.i][temp.j] = count;
						if (temp.i - 1 >= 0 && temp.i - 1 < height && temp.j - 1 >= 0 && temp.j - 1 < width && *(ptemp + (temp.i - 1) * width + temp.j - 1) == Bg && flag_max[temp.i - 1][temp.j - 1] == 0) {
							point linyu;
							linyu.i = temp.i - 1;
							linyu.j = temp.j - 1;
							buffer.push(linyu);
						}
						if (temp.i - 1 >= 0 && temp.i - 1 < height && temp.j >= 0 && temp.j < width && *(ptemp + (temp.i - 1) * width + temp.j) == Bg && flag_max[temp.i - 1][temp.j] == 0) {
							point linyu;
							linyu.i = temp.i - 1;
							linyu.j = temp.j;
							buffer.push(linyu);
						}
						if (temp.i - 1 >= 0 && temp.i - 1 < height && temp.j + 1 >= 0 && temp.j + 1 < width && *(ptemp + (temp.i - 1) * width + temp.j + 1) == Bg && flag_max[temp.i - 1][temp.j + 1] == 0) {
							point linyu;
							linyu.i = temp.i - 1;
							linyu.j = temp.j + 1;
							buffer.push(linyu);
						}
						if (temp.i >= 0 && temp.i < height && temp.j - 1 >= 0 && temp.j - 1 < width && *(ptemp + temp.i * width + temp.j - 1) == Bg && flag_max[temp.i][temp.j - 1] == 0) {
							point linyu;
							linyu.i = temp.i;
							linyu.j = temp.j - 1;
							buffer.push(linyu);
						}
						if (temp.i >= 0 && temp.i < height && temp.j + 1 >= 0 && temp.j + 1 < width && *(ptemp + temp.i * width + temp.j + 1) == Bg && flag_max[temp.i][temp.j + 1] == 0) {
							point linyu;
							linyu.i = temp.i;
							linyu.j = temp.j + 1;
							buffer.push(linyu);
						}
						if (temp.i + 1 >= 0 && temp.i + 1 < height && temp.j - 1 >= 0 && temp.j - 1 < width && *(ptemp + (temp.i + 1) * width + temp.j - 1) == Bg && flag_max[temp.i + 1][temp.j - 1] == 0) {
							point linyu;
							linyu.i = temp.i + 1;
							linyu.j = temp.j - 1;
							buffer.push(linyu);
						}
						if (temp.i + 1 >= 0 && temp.i + 1 < height && temp.j >= 0 && temp.j < width && *(ptemp + (temp.i + 1) * width + temp.j) == Bg && flag_max[temp.i + 1][temp.j] == 0) {
							point linyu;
							linyu.i = temp.i + 1;
							linyu.j = temp.j;
							buffer.push(linyu);
						}
						if (temp.i + 1 >= 0 && temp.i + 1 < height && temp.j + 1 >= 0 && temp.j + 1 < width && *(ptemp + (temp.i + 1) * width + temp.j + 1) == Bg && flag_max[temp.i + 1][temp.j + 1] == 0) {
							point linyu;
							linyu.i = temp.i + 1;
							linyu.j = temp.j + 1;
							buffer.push(linyu);
						}
					}
				}//while
			}//if

			 //j++;
			if (count_flag == 1)
			{
				count++;
				count_flag = 0;
			}
		}
	}
	return count - 1;
}




#define MAX 10000
typedef struct Dots
{
	int Dot;
	int flaga;
}Dot;

LONG WINAPI getArea_four(LPSTR start, LONG lWidth, LONG lHeight, int Bg)
{
	LONG max_area = 0;	//面积
	LONG temp = 0;
	int a = 0;
	Dot(*x)[MAX] = new Dot[lHeight][MAX];
	//初始化
	for (long i = 0; i < lHeight; i++) {
		for (long j = 0; j < lWidth; j++)
		{
			x[i][j].flaga = 0;
			x[i][j].Dot = 0;
		}
	}
		
	//赋像素值
	for (long i = 0; i < lHeight; i++)
		for (long j = 0; j < lWidth; j++)
			x[i][j].Dot = unsigned char(start[i * lWidth + j]);
	int i, j;

	for (i = 1; i < lHeight - 1;) {
		int temp_x = i;
		for (j = 1; j < lWidth - 1;)
		{
			int temp_y = j;
			if (x[i][j].Dot == Bg && x[i][j].flaga == 0)
			{//颜色一致
				a = 0;
				int x1, x2, x3;//四个邻域
				int y1, y2, y3;//四个邻域
				x1 = i - 1; x2 = i; x3 = i + 1; y1 = j - 1; y2 = j; y3 = j + 1;
				x[i][j].flaga = 1; temp++;//暂时统计面积
				//判断四邻域

				if (x2 >= 1 && y1 >= 1 && x[x2][y1].Dot == Bg && x[x2][y1].flaga == 0)
				{
					i = x2; j = y1; a = 1; continue;
				}

				else if (x1 >= 1 && x[x1][y2].Dot == Bg && x[x1][y2].flaga == 0)
				{
					i = x1; j = y2; a = 1; continue;
				}

				else if (x3 <= lHeight - 1 && x[x3][y2].Dot == Bg && x[x3][y2].flaga == 0)
				{
					i = x3; j = y2; a = 1; continue;
				}


				else if (y3 <= lWidth - 1 && x[x2][y3].Dot == Bg && x[x2][y3].flaga == 0)
				{
					i = x2; j = y3; a = 1; continue;
				}

				j = temp_y++;
				if (temp > max_area)
					max_area = temp;
				temp = 0;
			}
			else
				j++;
		}
		i = temp_x + 1;
	}
	delete[]x;
	return max_area;
}


LONG WINAPI getArea_eight(LPSTR start, LONG lWidth, LONG lHeight, int Bg)
{
	LONG max_area = 0;
	LONG temp = 0;
	int a = 0;
	Dot(*x)[MAX] = new Dot[lHeight][MAX];
	//初始化
	for (long i = 0; i < lHeight; i++)
		for (long j = 0; j < lWidth; j++)
		{
			x[i][j].flaga = 0;
			x[i][j].Dot = 0;
		}
	//赋值
	for (long i = 0; i < lHeight; i++)
		for (long j = 0; j < lWidth; j++)
			x[i][j].Dot = unsigned char(start[i * lWidth + j]);
	int i, j;

	for (i = 1; i < lHeight - 1;) {
		int temp_x = i;
		for (j = 1; j < lWidth - 1;)
		{
			int temp_y = j;
			if (x[i][j].Dot == Bg && x[i][j].flaga == 0)
			{
				a = 0;
				int x1, x2, x3;
				int y1, y2, y3;
				x1 = i - 1; x2 = i; x3 = i + 1; y1 = j - 1; y2 = j; y3 = j + 1;
				x[i][j].flaga = 1; temp++;
				//判断八邻域
				if (x1 >= 1 && y1 >= 1 && x[x1][y1].Dot == Bg && x[x1][y1].flaga == 0)
				{
					i = x1; j = y1; a = 1; continue;
				}

				else if (y1 >= 1 && y1 >= 1 && x[x2][y1].Dot == Bg && x[x2][y1].flaga == 0)
				{
					i = x2; j = y1; a = 1; continue;
				}

				else if (x3 <= lHeight - 1 && y1 >= 1 && x[x3][y1].Dot == Bg && x[x3][y1].flaga == 0)
				{
					i = x3; j = y1; a = 1; continue;
				}

				else if (x1 >= 1 && x[x1][y2].Dot == Bg && x[x1][y2].flaga == 0)
				{
					i = x1; j = y2; a = 1; continue;
				}

				else if (x3 <= lHeight - 1 && x[x3][y2].Dot == Bg && x[x3][y2].flaga == 0)
				{
					i = x3; j = y2; a = 1; continue;
				}

				else if (x1 >= 1 && y3 <= lWidth - 1 && x[x1][y3].Dot == Bg && x[x1][y3].flaga == 0)
				{
					i = x1; j = y3; a = 1; continue;
				}

				else if (y3 <= lWidth - 1 && x[x2][y3].Dot == Bg && x[x2][y3].flaga == 0)
				{
					i = x2; j = y3; a = 1; continue;
				}

				else if (y3 <= lWidth - 1 && x3 <= lHeight - 1 && x[x3][y3].Dot == Bg && x[x3][y3].flaga == 0)
				{
					i = x3; j = y3; a = 1; continue;
				}

				j = temp_y++;
				if (temp > max_area)
					max_area = temp;
				temp = 0;
			}
			else
				j++;
		}
		i = temp_x + 1;
	}
	delete[]x;
	return max_area;
}
