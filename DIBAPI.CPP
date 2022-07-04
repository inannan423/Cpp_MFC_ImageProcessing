// ************************************************************************
//  文件名：dibapi.cpp
//
//  DIB(Independent Bitmap) API函数库：
//
//  PaintDIB()          - 绘制DIB对象
//  CreateDIBPalette()  - 创建DIB对象调色板
//  FindDIBBits()       - 返回DIB图像象素起始位置
//  DIBWidth()          - 返回DIB宽度
//  DIBHeight()         - 返回DIB高度
//  PaletteSize()       - 返回DIB调色板大小
//  DIBNumColors()      - 计算DIB调色板颜色数目
//  CopyHandle()        - 拷贝内存块
//
//  SaveDIB()           - 将DIB保存到指定文件中
//  ReadDIBFile()       - 重指定文件中读取DIB对象
//
//  DIBToPCX256()		- 将指定的256色DIB对象保存为256色PCX文件
//  ReadPCX256()		- 读取256色PCX文件
//
// ************************************************************************
//用于图像旋转变换
#include "stdafx.h"
#include "dibapi.h"
#include <io.h>
#include <errno.h>
#include <math.h>
#include <direct.h>

/*
 * Dib文件头标志（字符串"BM"，写DIB时用到该常数）
 */
#define DIB_HEADER_MARKER   ((WORD) ('M' << 8) | 'B')

/*************************************************************************
 *
 * 函数名称：
 *   PaintDIB()
 *
 * 参数:
 *   HDC hDC            - 输出设备DC
 *   LPRECT lpDCRect    - 绘制矩形区域
 *   HDIB hDIB          - 指向DIB对象的指针
 *   LPRECT lpDIBRect   - 要输出的DIB区域
 *   CPalette* pPal     - 指向DIB对象调色板的指针
 *
 * 返回值:
 *   BOOL               - 绘制成功返回TRUE，否则返回FALSE。
 *
 * 说明:
 *   该函数主要用来绘制DIB对象。其中调用了StretchDIBits()或者
 * SetDIBitsToDevice()来绘制DIB对象。输出的设备由由参数hDC指
 * 定；绘制的矩形区域由参数lpDCRect指定；输出DIB的区域由参数
 * lpDIBRect指定。
 *
 ************************************************************************/

BOOL WINAPI PaintDIB(HDC     hDC,
					LPRECT  lpDCRect,
					HDIB    hDIB,
					LPRECT  lpDIBRect,
					CPalette* pPal)
{
	LPSTR    lpDIBHdr;            // BITMAPINFOHEADER指针
	LPSTR    lpDIBBits;           // DIB象素指针
	BOOL     bSuccess=FALSE;      // 成功标志
	HPALETTE hPal=NULL;           // DIB调色板
	HPALETTE hOldPal=NULL;        // 以前的调色板

	// 判断DIB对象是否为空
	if (hDIB == NULL)
	{
		// 返回
		return FALSE;
	}

	// 锁定DIB
	lpDIBHdr  = (LPSTR) ::GlobalLock((HGLOBAL) hDIB);

	// 找到DIB图像象素起始位置
	lpDIBBits = ::FindDIBBits(lpDIBHdr);

	// 获取DIB调色板，并选中它
	if (pPal != NULL)
	{
		hPal = (HPALETTE) pPal->m_hObject;

		// 选中调色板
		hOldPal = ::SelectPalette(hDC, hPal, TRUE);
	}

	// 设置显示模式
	::SetStretchBltMode(hDC, COLORONCOLOR);

	// 判断是调用StretchDIBits()还是SetDIBitsToDevice()来绘制DIB对象
	if ((RECTWIDTH(lpDCRect)  == RECTWIDTH(lpDIBRect)) &&
	   (RECTHEIGHT(lpDCRect) == RECTHEIGHT(lpDIBRect)))
	{
		// 原始大小，不用拉伸。
		bSuccess = ::SetDIBitsToDevice(hDC,                    // hDC
								   lpDCRect->left,             // DestX
								   lpDCRect->top,              // DestY
								   RECTWIDTH(lpDCRect),        // nDestWidth
								   RECTHEIGHT(lpDCRect),       // nDestHeight
								   lpDIBRect->left,            // SrcX
								   (int)DIBHeight(lpDIBHdr) -
									  lpDIBRect->top -
									  RECTHEIGHT(lpDIBRect),   // SrcY
								   0,                          // nStartScan
								   (WORD)DIBHeight(lpDIBHdr),  // nNumScans
								   lpDIBBits,                  // lpBits
								   (LPBITMAPINFO)lpDIBHdr,     // lpBitsInfo
								   DIB_RGB_COLORS);            // wUsage
	}
    else
	{
		// 非原始大小，拉伸。
		bSuccess = ::StretchDIBits(hDC,                          // hDC
							   lpDCRect->left,                 // DestX
							   lpDCRect->top,                  // DestY
							   RECTWIDTH(lpDCRect),            // nDestWidth
							   RECTHEIGHT(lpDCRect),           // nDestHeight
							   lpDIBRect->left,                // SrcX
							   lpDIBRect->top,                 // SrcY
							   RECTWIDTH(lpDIBRect),           // wSrcWidth
							   RECTHEIGHT(lpDIBRect),          // wSrcHeight
							   lpDIBBits,                      // lpBits
							   (LPBITMAPINFO)lpDIBHdr,         // lpBitsInfo
							   DIB_RGB_COLORS,                 // wUsage
							   SRCCOPY);                       // dwROP
	}
	
    // 解除锁定
	::GlobalUnlock((HGLOBAL) hDIB);
	
	// 恢复以前的调色板
	if (hOldPal != NULL)
	{
		::SelectPalette(hDC, hOldPal, TRUE);
	}
	
	// 返回
	return bSuccess;
}

/*************************************************************************
 *
 * 函数名称：
 *   CreateDIBPalette()
 *
 * 参数:
 *   HDIB hDIB          - 指向DIB对象的指针
 *   CPalette* pPal     - 指向DIB对象调色板的指针
 *
 * 返回值:
 *   BOOL               - 创建成功返回TRUE，否则返回FALSE。
 *
 * 说明:
 *   该函数按照DIB创建一个逻辑调色板，从DIB中读取颜色表并存到调色板中，
 * 最后按照该逻辑调色板创建一个新的调色板，并返回该调色板的句柄。这样
 * 可以用最好的颜色来显示DIB图像。
 *
 ************************************************************************/


BOOL WINAPI CreateDIBPalette(HDIB hDIB, CPalette* pPal)
{
	// 指向逻辑调色板的指针
	LPLOGPALETTE lpPal;
	
	// 逻辑调色板的句柄
	HANDLE hLogPal;
	
	// 调色板的句柄
	HPALETTE hPal = NULL;
	
	// 循环变量
	int i;
	
	// 颜色表中的颜色数目
	WORD wNumColors;
	
	// 指向DIB的指针
	LPSTR lpbi;
	
	// 指向BITMAPINFO结构的指针（Win3.0）
	LPBITMAPINFO lpbmi;
	
	// 指向BITMAPCOREINFO结构的指针
	LPBITMAPCOREINFO lpbmc;
	
	// 表明是否是Win3.0 DIB的标记
	BOOL bWinStyleDIB;
	
	// 创建结果
	BOOL bResult = FALSE;
	
	// 判断DIB是否为空
	if (hDIB == NULL)
	{
		// 返回FALSE
		return FALSE;
	}
	
	// 锁定DIB
	lpbi = (LPSTR) ::GlobalLock((HGLOBAL) hDIB);
	
	// 获取指向BITMAPINFO结构的指针（Win3.0）
	lpbmi = (LPBITMAPINFO)lpbi;
	
	// 获取指向BITMAPCOREINFO结构的指针
	lpbmc = (LPBITMAPCOREINFO)lpbi;
	
	// 获取DIB中颜色表中的颜色数目
	wNumColors = ::DIBNumColors(lpbi);
	
	if (wNumColors != 0)
	{
		// 分配为逻辑调色板内存
		hLogPal = ::GlobalAlloc(GHND, sizeof(LOGPALETTE)
									+ sizeof(PALETTEENTRY)
									* wNumColors);
		
		// 如果内存不足，退出
		if (hLogPal == 0)
		{
			// 解除锁定
			::GlobalUnlock((HGLOBAL) hDIB);
			
			// 返回FALSE
			return FALSE;
		}
		
		lpPal = (LPLOGPALETTE) ::GlobalLock((HGLOBAL) hLogPal);
		
		// 设置版本号
		lpPal->palVersion = PALVERSION;
		
		// 设置颜色数目
		lpPal->palNumEntries = (WORD)wNumColors;
		
		// 判断是否是WIN3.0的DIB
		bWinStyleDIB = IS_WIN30_DIB(lpbi);

		// 读取调色板
		for (i = 0; i < (int)wNumColors; i++)
		{
			if (bWinStyleDIB)
			{
				// 读取红色分量
				lpPal->palPalEntry[i].peRed = lpbmi->bmiColors[i].rgbRed;
				
				// 读取绿色分量
				lpPal->palPalEntry[i].peGreen = lpbmi->bmiColors[i].rgbGreen;
				
				// 读取蓝色分量
				lpPal->palPalEntry[i].peBlue = lpbmi->bmiColors[i].rgbBlue;
				
				// 保留位
				lpPal->palPalEntry[i].peFlags = 0;
			}
			else
			{
				// 读取红色分量
				lpPal->palPalEntry[i].peRed = lpbmc->bmciColors[i].rgbtRed;
				
				// 读取绿色分量
				lpPal->palPalEntry[i].peGreen = lpbmc->bmciColors[i].rgbtGreen;
				
				// 读取红色分量
				lpPal->palPalEntry[i].peBlue = lpbmc->bmciColors[i].rgbtBlue;
				
				// 保留位
				lpPal->palPalEntry[i].peFlags = 0;
			}
		}
		
		// 按照逻辑调色板创建调色板，并返回指针
		bResult = pPal->CreatePalette(lpPal);
		
		// 解除锁定
		::GlobalUnlock((HGLOBAL) hLogPal);
		
		// 释放逻辑调色板
		::GlobalFree((HGLOBAL) hLogPal);
	}
	
	// 解除锁定
	::GlobalUnlock((HGLOBAL) hDIB);
	
	// 返回结果
	return bResult;
}

/*************************************************************************
 *
 * 函数名称：
 *   FindDIBBits()
 *
 * 参数:
 *   LPSTR lpbi         - 指向DIB对象的指针
 *
 * 返回值:
 *   LPSTR              - 指向DIB图像象素起始位置
 *
 * 说明:
 *   该函数计算DIB中图像象素的起始位置，并返回指向它的指针。
 *
 ************************************************************************/


LPSTR WINAPI FindDIBBits(LPSTR lpbi)
{
	return (lpbi + *(LPDWORD)lpbi + ::PaletteSize(lpbi));
}


/*************************************************************************
 *
 * 函数名称：
 *   DIBWidth()
 *
 * 参数:
 *   LPSTR lpbi         - 指向DIB对象的指针
 *
 * 返回值:
 *   DWORD              - DIB中图像的宽度
 *
 * 说明:
 *   该函数返回DIB中图像的宽度。对于Windows 3.0 DIB，返回BITMAPINFOHEADER
 * 中的biWidth值；对于其它返回BITMAPCOREHEADER中的bcWidth值。
 *
 ************************************************************************/


DWORD WINAPI DIBWidth(LPSTR lpDIB)
{
	// 指向BITMAPINFO结构的指针（Win3.0）
	LPBITMAPINFOHEADER lpbmi;
	
	// 指向BITMAPCOREINFO结构的指针
	LPBITMAPCOREHEADER lpbmc;

	// 获取指针
	lpbmi = (LPBITMAPINFOHEADER)lpDIB;
	lpbmc = (LPBITMAPCOREHEADER)lpDIB;

	// 返回DIB中图像的宽度
	if (IS_WIN30_DIB(lpDIB))
	{
		// 对于Windows 3.0 DIB，返回lpbmi->biWidth
		return lpbmi->biWidth;
	}
	else
	{
		// 对于其它格式的DIB，返回lpbmc->bcWidth
		return (DWORD)lpbmc->bcWidth;
	}
}


/*************************************************************************
 *
 * 函数名称：
 *   DIBHeight()
 *
 * 参数:
 *   LPSTR lpDIB        - 指向DIB对象的指针
 *
 * 返回值:
 *   DWORD              - DIB中图像的高度
 *
 * 说明:
 *   该函数返回DIB中图像的高度。对于Windows 3.0 DIB，返回BITMAPINFOHEADER
 * 中的biHeight值；对于其它返回BITMAPCOREHEADER中的bcHeight值。
 *
 ************************************************************************/


DWORD WINAPI DIBHeight(LPSTR lpDIB)
{
	// 指向BITMAPINFO结构的指针（Win3.0）
	LPBITMAPINFOHEADER lpbmi;
	
	// 指向BITMAPCOREINFO结构的指针
	LPBITMAPCOREHEADER lpbmc;

	// 获取指针
	lpbmi = (LPBITMAPINFOHEADER)lpDIB;
	lpbmc = (LPBITMAPCOREHEADER)lpDIB;

	// 返回DIB中图像的宽度
	if (IS_WIN30_DIB(lpDIB))
	{
		// 对于Windows 3.0 DIB，返回lpbmi->biHeight
		return lpbmi->biHeight;
	}
	else
	{
		// 对于其它格式的DIB，返回lpbmc->bcHeight
		return (DWORD)lpbmc->bcHeight;
	}
}


/*************************************************************************
 *
 * 函数名称：
 *   PaletteSize()
 *
 * 参数:
 *   LPSTR lpbi         - 指向DIB对象的指针
 *
 * 返回值:
 *   WORD               - DIB中调色板的大小
 *
 * 说明:
 *   该函数返回DIB中调色板的大小。对于Windows 3.0 DIB，返回颜色数目×
 * RGBQUAD的大小；对于其它返回颜色数目×RGBTRIPLE的大小。
 *
 ************************************************************************/


WORD WINAPI PaletteSize(LPSTR lpbi)
{
	// 计算DIB中调色板的大小
	if (IS_WIN30_DIB (lpbi))
	{
		//返回颜色数目×RGBQUAD的大小
		return (WORD)(::DIBNumColors(lpbi) * sizeof(RGBQUAD));
	}
	else
	{
		//返回颜色数目×RGBTRIPLE的大小
		return (WORD)(::DIBNumColors(lpbi) * sizeof(RGBTRIPLE));
	}
}


/*************************************************************************
 *
 * 函数名称：
 *   DIBNumColors()
 *
 * 参数:
 *   LPSTR lpbi         - 指向DIB对象的指针
 *
 * 返回值:
 *   WORD               - 返回调色板中颜色的种数
 *
 * 说明:
 *   该函数返回DIB中调色板的颜色的种数。对于单色位图，返回2，
 * 对于16色位图，返回16，对于256色位图，返回256；对于真彩色
 * 位图（24位），没有调色板，返回0。
 *
 ************************************************************************/
WORD WINAPI DIBNumColors(LPSTR lpbi)
{
	WORD wBitCount;

	// 对于Windows的DIB, 实际颜色的数目可以比象素的位数要少。
	// 对于这种情况，则返回一个近似的数值。
	
	// 判断是否是WIN3.0 DIB
	if (IS_WIN30_DIB(lpbi))
	{
		DWORD dwClrUsed;
		
		// 读取dwClrUsed值
		dwClrUsed = ((LPBITMAPINFOHEADER)lpbi)->biClrUsed;
		
		if (dwClrUsed != 0)
		{
			// 如果dwClrUsed（实际用到的颜色数）不为0，直接返回该值
			return (WORD)dwClrUsed;
		}
	}

	// 读取象素的位数
	if (IS_WIN30_DIB(lpbi))
	{
		// 读取biBitCount值
		wBitCount = ((LPBITMAPINFOHEADER)lpbi)->biBitCount;
	}
	else
	{
		// 读取biBitCount值
		wBitCount = ((LPBITMAPCOREHEADER)lpbi)->bcBitCount;
	}
	
	// 按照象素的位数计算颜色数目
	switch (wBitCount)
	{
		case 1:
			return 2;

		case 4:
			return 16;

		case 8:
			return 256;

		default:
			return 0;
	}
}


/*************************************************************************
 *
 * 函数名称：
 *   DIBBitCount()
 *
 * 参数:
 *   LPSTR lpbi         - 指向DIB对象的指针
 *
 * 返回值:
 *   WORD               - 返回调色板中颜色的种数
 *
 * 说明:
 *   该函数返回DIBBitCount。
 *
 ************************************************************************/
WORD WINAPI DIBBitCount(LPSTR lpbi)
{
	WORD wBitCount;

	// 读取象素的位数
	if (IS_WIN30_DIB(lpbi))
	{
		// 读取biBitCount值
		wBitCount = ((LPBITMAPINFOHEADER)lpbi)->biBitCount;
	}
	else
	{
		// 读取biBitCount值
		wBitCount = ((LPBITMAPCOREHEADER)lpbi)->bcBitCount;
	}
	
	// 返回wBitCount
	return wBitCount;
}

/*************************************************************************
 *
 * 函数名称：
 *   CopyHandle()
 *
 * 参数:
 *   HGLOBAL h          - 要复制的内存区域
 *
 * 返回值:
 *   HGLOBAL            - 复制后的新内存区域
 *
 * 说明:
 *   该函数复制指定的内存区域。返回复制后的新内存区域，出错时返回0。
 *
 ************************************************************************/

HGLOBAL WINAPI CopyHandle1 (HGLOBAL h)
{
	if (h == NULL)
		return NULL;

	// 获取指定内存区域大小
	DWORD dwLen = ::GlobalSize((HGLOBAL) h);
	
	// 分配新内存空间
	HGLOBAL hCopy = ::GlobalAlloc(GHND, dwLen);
	
	// 判断分配是否成功
	if (hCopy != NULL)
	{
		// 锁定
		void* lpCopy = ::GlobalLock((HGLOBAL) hCopy);
		void* lp     = ::GlobalLock((HGLOBAL) h);
		
		// 复制
		memcpy(lpCopy, lp, dwLen);
		
		// 解除锁定
		::GlobalUnlock(hCopy);
		::GlobalUnlock(h);
	}

	return hCopy;
}



/*************************************************************************
 *
 * 函数名称：
 *   SaveDIB()
 *
 * 参数:
 *   HDIB hDib          - 要保存的DIB
 *   CFile& file        - 保存文件CFile
 *
 * 返回值:
 *   BOOL               - 成功返回TRUE，否则返回FALSE或者CFileException
 *
 * 说明:
 *   该函数将指定的DIB对象保存到指定的CFile中。该CFile由调用程序打开和关闭。
 *
 *************************************************************************/


BOOL WINAPI SaveDIB(HDIB hDib, CFile& file)
{
	// Bitmap文件头
	BITMAPFILEHEADER bmfHdr;
	
	// 指向BITMAPINFOHEADER的指针
	LPBITMAPINFOHEADER lpBI;
	
	// DIB大小
	DWORD dwDIBSize;

	if (hDib == NULL)
	{
		// 如果DIB为空，返回FALSE
		return FALSE;
	}

	// 读取BITMAPINFO结构，并锁定
	lpBI = (LPBITMAPINFOHEADER) ::GlobalLock((HGLOBAL) hDib);
	
	if (lpBI == NULL)
	{
		// 为空，返回FALSE
		return FALSE;
	}
	
	// 判断是否是WIN3.0 DIB
	if (!IS_WIN30_DIB(lpBI))
	{
		// 不支持其它类型的DIB保存
		
		// 解除锁定
		::GlobalUnlock((HGLOBAL) hDib);
		
		// 返回FALSE
		return FALSE;
	}

	// 填充文件头

	// 文件类型"BM"
	bmfHdr.bfType = DIB_HEADER_MARKER;

	// 计算DIB大小时，最简单的方法是调用GlobalSize()函数。但是全局内存大小并
	// 不是DIB真正的大小，它总是多几个字节。这样就需要计算一下DIB的真实大小。
	
	// 文件头大小＋颜色表大小
	// （BITMAPINFOHEADER和BITMAPCOREHEADER结构的第一个DWORD都是该结构的大小）
	dwDIBSize = *(LPDWORD)lpBI + ::PaletteSize((LPSTR)lpBI);
	
	// 计算图像大小
	if ((lpBI->biCompression == BI_RLE8) || (lpBI->biCompression == BI_RLE4))
	{
		// 对于RLE位图，没法计算大小，只能信任biSizeImage内的值
		dwDIBSize += lpBI->biSizeImage;
	}
	else
	{
		// 象素的大小
		DWORD dwBmBitsSize;

		// 大小为Width * Height
		dwBmBitsSize = WIDTHBYTES((lpBI->biWidth)*((DWORD)lpBI->biBitCount)) * lpBI->biHeight;
		
		// 计算出DIB真正的大小
		dwDIBSize += dwBmBitsSize;

		// 更新biSizeImage（很多BMP文件头中biSizeImage的值是错误的）
		lpBI->biSizeImage = dwBmBitsSize;
	}


	// 计算文件大小：DIB大小＋BITMAPFILEHEADER结构大小
	bmfHdr.bfSize = dwDIBSize + sizeof(BITMAPFILEHEADER);
	
	// 两个保留字
	bmfHdr.bfReserved1 = 0;
	bmfHdr.bfReserved2 = 0;

	// 计算偏移量bfOffBits，它的大小为Bitmap文件头大小＋DIB头大小＋颜色表大小
	bmfHdr.bfOffBits = (DWORD)sizeof(BITMAPFILEHEADER) + lpBI->biSize
											  + PaletteSize((LPSTR)lpBI);
	// 尝试写文件
	TRY
	{
		// 写文件头
		file.Write((LPSTR)&bmfHdr, sizeof(BITMAPFILEHEADER));
		
		// 写DIB头和象素
		//file.WriteHuge(lpBI, dwDIBSize);
		file.Write(lpBI, dwDIBSize);
	}
	CATCH (CFileException, e)
	{
		// 解除锁定
		::GlobalUnlock((HGLOBAL) hDib);
		
		// 抛出异常
		THROW_LAST();
	}
	END_CATCH
	
	// 解除锁定
	::GlobalUnlock((HGLOBAL) hDib);
	
	// 返回TRUE
	return TRUE;
}


/*************************************************************************
 *
 * 函数名称：
 *   ReadDIBFile()
 *
 * 参数:
 *   CFile& file        - 要读取得文件文件CFile
 *
 * 返回值:
 *   HDIB               - 成功返回DIB的句柄，否则返回NULL。
 *
 * 说明:
 *   该函数将指定的文件中的DIB对象读到指定的内存区域中。除BITMAPFILEHEADER
 * 外的内容都将被读入内存。
 *
 *************************************************************************/

HDIB WINAPI ReadDIBFile(CFile& file)
{
	BITMAPFILEHEADER bmfHeader;
	DWORD dwBitsSize;
	HDIB hDIB;
	LPSTR pDIB;

	// 获取DIB（文件）长度（字节）
	dwBitsSize = file.GetLength();

	// 尝试读取DIB文件头
	if (file.Read((LPSTR)&bmfHeader, sizeof(bmfHeader)) != sizeof(bmfHeader))
	{
		// 大小不对，返回NULL。
		return NULL;
	}

	// 判断是否是DIB对象，检查头两个字节是否是"BM"
	if (bmfHeader.bfType != DIB_HEADER_MARKER)
	{
		// 非DIB对象，返回NULL。
		return NULL;
	}

	// 为DIB分配内存
	hDIB = (HDIB) ::GlobalAlloc(GMEM_MOVEABLE | GMEM_ZEROINIT, dwBitsSize);
	if (hDIB == 0)
	{
		// 内存分配失败，返回NULL。
		return NULL;
	}
	
	// 锁定
	pDIB = (LPSTR) ::GlobalLock((HGLOBAL) hDIB);

	// 读象素
	//if (file.ReadHuge(pDIB, dwBitsSize - sizeof(BITMAPFILEHEADER)) !=
	if (file.Read(pDIB, dwBitsSize - sizeof(BITMAPFILEHEADER)) !=
		dwBitsSize - sizeof(BITMAPFILEHEADER) )
	{
		// 大小不对。
		
		// 解除锁定
		::GlobalUnlock((HGLOBAL) hDIB);
		
		// 释放内存
		::GlobalFree((HGLOBAL) hDIB);
		
		// 返回NULL。
		return NULL;
	}
	
	// 解除锁定
	::GlobalUnlock((HGLOBAL) hDIB);
	
	// 返回DIB句柄
	return hDIB;
}

/*************************************************************************
 *
 * 函数名称：
 *   DIBToPCX256()
 *
 * 参数:
 *   LPSTR lpDIB        - 指向DIB对象的指针
 *   CFile& file        - 要保存的文件
 *
 * 返回值:
 *   BOOL               - 成功返回True，否则返回False。
 *
 * 说明:
 *   该函数将指定的256色DIB对象保存为256色PCX文件。
 *
 *************************************************************************/
BOOL WINAPI DIBToPCX256(LPSTR lpDIB, CFile& file)
{
	// 循环变量
	LONG	i;
	LONG	j;
	
	// DIB高度
	WORD	wHeight;
	
	// DIB宽度
	WORD	wWidth;
	
	// 中间变量
	BYTE	bChar1;
	BYTE	bChar2;
	
	// 指向源图像象素的指针
	BYTE *	lpSrc;
	
	// 指向编码后图像数据的指针
	BYTE *	lpDst;
	
	// 图像每行的字节数
	LONG	lLineBytes;
	
	// 重复像素计数
	int		iCount;
	
	// 缓冲区已使用的字节数
	DWORD	dwBuffUsed;
	
	// 指向DIB象素指针
	LPSTR   lpDIBBits;
	
	// 获取DIB高度
	wHeight = (WORD) DIBHeight(lpDIB);
	
	// 获取DIB宽度
	wWidth  = (WORD) DIBWidth(lpDIB);
	
	// 找到DIB图像象素起始位置
	lpDIBBits = FindDIBBits(lpDIB);
	
	// 计算图像每行的字节数
	lLineBytes = WIDTHBYTES(wWidth * 8);
	
	
	//*************************************************************************
	// PCX文件头
	PCXHEADER pcxHdr;
	
	// 给文件头赋值
	
	// PCX标识码
	pcxHdr.bManufacturer = 0x0A;
	
	// PCX版本号
	pcxHdr.bVersion = 5;
	
	// PCX编码方式（1表示RLE编码）
	pcxHdr.bEncoding = 1;
	
	// 像素位数（256色为8位）
	pcxHdr.bBpp = 8;
	
	// 图像相对于屏幕的左上角X坐标（以像素为单位）
	pcxHdr.wLeft = 0;
	
	// 图像相对于屏幕的左上角Y坐标（以像素为单位）
	pcxHdr.wTop = 0;
	
	// 图像相对于屏幕的右下角X坐标（以像素为单位）
	pcxHdr.wRight = wWidth - 1;
	
	// 图像相对于屏幕的右下角Y坐标（以像素为单位）
	pcxHdr.wBottom = wHeight - 1;
	
	// 图像的水平分辨率
	pcxHdr.wXResolution = wWidth;
	
	// 图像的垂直分辨率
	pcxHdr.wYResolution = wHeight;
	
	// 调色板数据（对于256色PCX无意义，直接赋值为0）
	for (i = 0; i < 48; i ++)
	{
		pcxHdr.bPalette[i] = 0;
	}
	
	// 保留域，设定为0。
	pcxHdr.bReserved = 0;
	
	// 图像色彩平面数目（对于256色PCX设定为1）。
	pcxHdr.bPlanes = 1;
	
	// 图像的宽度（字节为单位），必须为偶数。
//	if ((wWidth & 1) == 0)
//	{
		pcxHdr.wLineBytes = wWidth;
//	}
//	else
//	{
//		pcxHdr.wLineBytes = wWidth + 1;
//	}
	
	// 图像调色板的类型，1表示彩色或者单色图像，2表示图像是灰度图。
	pcxHdr.wPaletteType = 1;
	
	// 制作该图像的屏幕宽度（像素为单位）
	pcxHdr.wSrcWidth = 0;
	
	// 制作该图像的屏幕高度（像素为单位）
	pcxHdr.wSrcDepth = 0;
	
	// 保留域，取值设定为0。
	for (i = 0; i < 54; i ++)
	{
		pcxHdr.bFiller[i] = 0;
	}
	
	// 写入文件头
	file.Write((LPSTR)&pcxHdr, sizeof(PCXHEADER));
	
	//*******************************************************************************
	// 开始编码
	
	// 开辟一片缓冲区(2被原始图像大小)以保存编码结果
	lpDst = new BYTE[wHeight * wWidth * 2];
	
	// 指明当前已经用了多少缓冲区（字节数）
	dwBuffUsed = 0;
	
	// 每行
	for (i = 0; i < wHeight; i++)
	{
		// 指向DIB第i行，第0个象素的指针
		lpSrc = (BYTE *)lpDIBBits + lLineBytes * (wHeight - 1 - i);
		
		// 给bChar1赋值
		bChar1 = *lpSrc;
		
		// 设置iCount为1
		iCount = 1;
		
		// 剩余列
		for (j = 1; j < wWidth; j ++)
		{
			// 指向DIB第i行，第j个象素的指针
			lpSrc++;
			
			// 读取下一个像素
			bChar2 = *lpSrc;
			
			// 判断是否和bChar1相同并且iCount < 63
			if ((bChar1 == bChar2) && (iCount < 63))
			{
				// 相同，计数加1
				iCount ++;
				
				// 继续读下一个
			}
			else
			{
				// 不同，或者iCount = 63
				
				// 写入缓冲区
				if ((iCount > 1) || (bChar1 >= 0xC0))
				{
					// 保存码长信息
					lpDst[dwBuffUsed] = iCount | 0xC0;
					
					// 保存bChar1
					lpDst[dwBuffUsed + 1] = bChar1;
					
					// 更新dwBuffUsed
					dwBuffUsed += 2;
				}
				else
				{
					// 直接保存该值
					lpDst[dwBuffUsed] = bChar1;
					
					// 更新dwBuffUsed
					dwBuffUsed ++;
				}
				
				// 重新给bChar1赋值
				bChar1 = bChar2;
				
				// 设置iCount为1
				iCount = 1;
			}
		}
		
		// 保存每行最后一部分编码
		if ((iCount > 1) || (bChar1 >= 0xC0))
		{
			// 保存码长信息
			lpDst[dwBuffUsed] = iCount | 0xC0;
			
			// 保存bChar1
			lpDst[dwBuffUsed + 1] = bChar1;
			
			// 更新dwBuffUsed
			dwBuffUsed += 2;
		}
		else
		{
			// 直接保存该值
			lpDst[dwBuffUsed] = bChar1;
			
			// 更新dwBuffUsed
			dwBuffUsed ++;
		}
	}
	
	// 写入编码结果
	//file.WriteHuge((LPSTR)lpDst, dwBuffUsed);
	file.Write((LPSTR)lpDst, dwBuffUsed);
	
	// 释放内存
	delete lpDst;
	
	//**************************************************************************
	// 写入调色板信息
	
	// 指向BITMAPINFO结构的指针（Win3.0）
	LPBITMAPINFO lpbmi;
	
	// 指向BITMAPCOREINFO结构的指针
	LPBITMAPCOREINFO lpbmc;
	
	// 表明是否是Win3.0 DIB的标记
	BOOL bWinStyleDIB;
	
	// 开辟一片缓冲区以保存调色板
	lpDst = new BYTE[769];
	
	// 调色板起始字节
	* lpDst = 0x0C;
	
	// 获取指向BITMAPINFO结构的指针（Win3.0）
	lpbmi = (LPBITMAPINFO)lpDIB;
	
	// 获取指向BITMAPCOREINFO结构的指针
	lpbmc = (LPBITMAPCOREINFO)lpDIB;
	
	// 判断是否是WIN3.0的DIB
	bWinStyleDIB = IS_WIN30_DIB(lpDIB);
	
	// 读取当前DIB调色板
	for (i = 0; i < 256; i ++)
	{
		if (bWinStyleDIB)
		{
			// 读取DIB调色板红色分量
			lpDst[i * 3 + 1] = lpbmi->bmiColors[i].rgbRed;
			
			// 读取DIB调色板绿色分量
			lpDst[i * 3 + 2] = lpbmi->bmiColors[i].rgbGreen;
			
			// 读取DIB调色板蓝色分量
			lpDst[i * 3 + 3] = lpbmi->bmiColors[i].rgbBlue;
		}
		else
		{
			// 读取DIB调色板红色分量
			lpDst[i * 3 + 1] = lpbmc->bmciColors[i].rgbtRed;
			
			// 读取DIB调色板绿色分量
			lpDst[i * 3 + 2] = lpbmc->bmciColors[i].rgbtGreen;
			
			// 读取DIB调色板蓝色分量
			lpDst[i * 3 + 3] = lpbmc->bmciColors[i].rgbtBlue;
		}
	}
	
	// 写入调色板信息
	file.Write((LPSTR)lpDst, 769);
	
	// 返回
	return TRUE;
}

/*************************************************************************
 *
 * 函数名称：
 *   ReadPCX256()
 *
 * 参数:
 *   CFile& file        - 要读取的文件
 *
 * 返回值:
 *   HDIB               - 成功返回DIB的句柄，否则返回NULL。
 *
 * 说明:
 *   该函数将读取指定的256色PCX文件。将读取的结果保存在一个未压缩
 * 编码的DIB对象中。
 *
 *************************************************************************/
HDIB WINAPI ReadPCX256(CFile& file)
{
	// PCX文件头
	PCXHEADER pcxHdr;
	
	// DIB大小（字节数）
	DWORD	dwDIBSize;
	
	// DIB句柄
	HDIB	hDIB;
	
	// DIB指针
	LPSTR	pDIB;
	
	// 循环变量
	LONG	i;
	LONG	j;
	
	// 重复像素计数
	int		iCount;
	
	// DIB高度
	WORD	wHeight;
	
	// DIB宽度
	WORD	wWidth;
	
	// 图像每行的字节数
	LONG	lLineBytes;
	
	// 中间变量
	BYTE	bChar;
	
	// 指向源图像象素的指针
	BYTE *	lpSrc;
	
	// 指向编码后图像数据的指针
	BYTE *	lpDst;
	
	// 临时指针
	BYTE *	lpTemp;
	
	// 尝试读取PCX文件头
	if (file.Read((LPSTR)&pcxHdr, sizeof(PCXHEADER)) != sizeof(PCXHEADER))
	{
		// 大小不对，返回NULL。
		return NULL;
	}
	
	// 判断是否是256色PCX文件，检查第一个字节是否是0x0A，
	if ((pcxHdr.bManufacturer != 0x0A) || (pcxHdr.bBpp != 8) || (pcxHdr.bPlanes != 1))
	{
		// 非256色PCX文件，返回NULL。
		return NULL;
	}
	
	// 获取图像高度
	wHeight = pcxHdr.wBottom - pcxHdr.wTop + 1;
	
	// 获取图像宽度
	wWidth  = pcxHdr.wRight - pcxHdr.wLeft + 1;
	
	// 计算图像每行的字节数
	lLineBytes = WIDTHBYTES(wWidth * 8);
	
	// 计算DIB长度（字节）
	dwDIBSize = sizeof(BITMAPINFOHEADER) + 1024 + wHeight * lLineBytes;
	
	// 为DIB分配内存
	hDIB = (HDIB) ::GlobalAlloc(GMEM_MOVEABLE | GMEM_ZEROINIT, dwDIBSize);
	if (hDIB == 0)
	{
		// 内存分配失败，返回NULL。
		return NULL;
	}
	
	// 锁定
	pDIB = (LPSTR) ::GlobalLock((HGLOBAL) hDIB);
	
	// 指向BITMAPINFOHEADER的指针
	LPBITMAPINFOHEADER lpBI;
	
	// 赋值
	lpBI = (LPBITMAPINFOHEADER) pDIB;
	
	// 给lpBI成员赋值
	lpBI->biSize = 40;
	lpBI->biWidth = wWidth;
	lpBI->biHeight = wHeight;
	lpBI->biPlanes = 1;
	lpBI->biBitCount = 8;
	lpBI->biCompression = BI_RGB;
	lpBI->biSizeImage = wHeight * lLineBytes;
	lpBI->biXPelsPerMeter = pcxHdr.wXResolution;
	lpBI->biYPelsPerMeter = pcxHdr.wYResolution;
	lpBI->biClrUsed = 0;
	lpBI->biClrImportant = 0;
	
	// 分配内存以读取编码后的象素
	lpSrc = new BYTE[file.GetLength() - sizeof(PCXHEADER) - 769];
	lpTemp = lpSrc;
	
	// 读取编码后的象素
	//if (file.ReadHuge(lpSrc, file.GetLength() - sizeof(PCXHEADER) - 769) !=
	if (file.Read(lpSrc, file.GetLength() - sizeof(PCXHEADER) - 769) !=
		file.GetLength() - sizeof(PCXHEADER) - 769 )
	{
		// 大小不对。
		
		// 解除锁定
		::GlobalUnlock((HGLOBAL) hDIB);
		
		// 释放内存
		::GlobalFree((HGLOBAL) hDIB);
		
		// 返回NULL。
		return NULL;
	}
	
	// 计算DIB中像素位置
	lpDst = (BYTE *) FindDIBBits(pDIB);
	
	// 一行一行解码
	for (j = 0; j <wHeight; j++)
	{
		i = 0;
		while (i < wWidth)
		{
			// 读取一个字节
			bChar = *lpTemp;
			lpTemp++;
			
			if ((bChar & 0xC0) == 0xC0)
			{
				// 行程
				iCount = bChar & 0x3F;
				
				// 读取下一个字节
				bChar = *lpTemp;
				lpTemp++;
				
				// bChar重复iCount次保存
				memset(&lpDst[(wHeight - j - 1) * lLineBytes + i], bChar, iCount);

				// 已经读取像素的个数加iCount
				i += iCount;
			}
			else
			{
				// 保存当前字节
				lpDst[(wHeight - j - 1) * lLineBytes + i] = bChar;
				
				// 已经读取像素的个数加1
				i += 1;
			}
		}
	}
	
	// 释放内存
	delete lpSrc;
	
	//*************************************************************
	// 调色板
	
	// 读调色板标志位
	file.Read(&bChar, 1);
	if (bChar != 0x0C)
	{
		// 出错
		
		// 解除锁定
		::GlobalUnlock((HGLOBAL) hDIB);
		
		// 释放内存
		::GlobalFree((HGLOBAL) hDIB);
		
		// 返回NULL。
		return NULL;
	}
	
	// 分配内存以读取编码后的象素
	lpSrc = new BYTE[768];
	
	// 计算DIB中调色板的位置
	lpDst = (BYTE *) pDIB + sizeof(BITMAPINFOHEADER);
	
	// 读取调色板
	if (file.Read(lpSrc, 768) != 768)
	{
		// 大小不对。
		
		// 解除锁定
		::GlobalUnlock((HGLOBAL) hDIB);
		
		// 释放内存
		::GlobalFree((HGLOBAL) hDIB);
		
		// 返回NULL。
		return NULL;
	}
	
	// 给调色板赋值
	for (i = 0; i < 256; i++)
	{
		lpDst[i * 4] = lpSrc[i * 3 + 2];
		lpDst[i * 4 + 1] = lpSrc[i * 3 + 1];
		lpDst[i * 4 + 2] = lpSrc[i * 3];
		lpDst[i * 4 + 3] = 0;
	}
	
	// 释放内存
	delete lpSrc;
	
	// 解除锁定
	::GlobalUnlock((HGLOBAL) hDIB);
	
	// 返回DIB句柄
	return hDIB;
}


HGLOBAL WINAPI RotateDIB(LPSTR lpDIB, int iRotateAngle)
{

	// 源图像的宽度和高度
	LONG	lWidth;
	LONG	lHeight;

	// 旋转后图像的宽度和高度
	LONG	lNewWidth;
	LONG	lNewHeight;

	// 原来的图像每行的字节数
	LONG	lLineBytes;
	// 旋转后图像的宽度（lNewWidth'，必须是4的倍数）
	LONG	lNewLineBytes;

	// 指向整个源图像的指针
	LPSTR	lpDIBBits;

	// 指向源图像象素部分的指针
	LPSTR	lpSrc;

	// 旋转后新DIB句柄
	HGLOBAL	hDIB;

	// 指向旋转图像对应象素的指针
	LPSTR	lpDst;

	// 指向旋转后的整个图像的指针
	LPSTR	lpNewDIB;
	//新的图像中的像素开始部分
	LPSTR	lpNewDIBBits;


	BITMAPINFOHEADER* lpbmc;

	// 循环变量（象素在新DIB中的坐标）
	LONG	i;
	LONG	j;

	// 象素在源DIB中的坐标
	LONG	i0;
	LONG	j0;

	// 旋转角度（弧度）
	float	fRotateAngle;

	// 旋转角度的正弦和余弦
	float	fSina, fCosa;

	// 源图四个角的坐标（以图像中心为坐标系原点）
	float	fSrcX1, fSrcY1, fSrcX2, fSrcY2, fSrcX3, fSrcY3, fSrcX4, fSrcY4;

	// 旋转后四个角的坐标（以图像中心为坐标系原点）
	float	fDstX1, fDstY1, fDstX2, fDstY2, fDstX3, fDstY3, fDstX4, fDstY4;

	// 两个中间常量
	float	f1, f2;

	// 找到源DIB图像象素起始位置
	lpDIBBits = FindDIBBits(lpDIB);

	// 获取图像的"宽度"（4的倍数）
	lWidth = DIBWidth(lpDIB);

	// 计算图像每行的字节数
	lLineBytes = (lWidth + 3) / 4 * 4;

	// 获取图像的高度
	lHeight = DIBHeight(lpDIB);

	// 将旋转角度从度转换到弧度
	fRotateAngle = (iRotateAngle * 1.0) * 3.1415 / 180;

	// 计算旋转角度的正弦
	fSina = (float)sin((double)fRotateAngle);

	// 计算旋转角度的余弦
	fCosa = (float)cos((double)fRotateAngle);

	// 计算原图的四个角的坐标（以图像中心为坐标系原点）
	fSrcX1 = (float)(-(lWidth - 1) / 2);
	fSrcY1 = (float)((lHeight - 1) / 2);
	fSrcX2 = (float)((lWidth - 1) / 2);
	fSrcY2 = (float)((lHeight - 1) / 2);
	fSrcX3 = (float)(-(lWidth - 1) / 2);
	fSrcY3 = (float)(-(lHeight - 1) / 2);
	fSrcX4 = (float)((lWidth - 1) / 2);
	fSrcY4 = (float)(-(lHeight - 1) / 2);

	// 计算新图四个角的坐标（以图像中心为坐标系原点）
	fDstX1 = fCosa * fSrcX1 + fSina * fSrcY1;
	fDstY1 = -fSina * fSrcX1 + fCosa * fSrcY1;
	fDstX2 = fCosa * fSrcX2 + fSina * fSrcY2;
	fDstY2 = -fSina * fSrcX2 + fCosa * fSrcY2;
	fDstX3 = fCosa * fSrcX3 + fSina * fSrcY3;
	fDstY3 = -fSina * fSrcX3 + fCosa * fSrcY3;
	fDstX4 = fCosa * fSrcX4 + fSina * fSrcY4;
	fDstY4 = -fSina * fSrcX4 + fCosa * fSrcY4;

	// 计算旋转后的图像实际宽度
	lNewWidth = (LONG)(max(fabs(fDstX4 - fDstX1), fabs(fDstX3 - fDstX2)) + 0.5);

	// 计算新图像每行的字节数
	lNewLineBytes = (lNewWidth + 3) / 4 * 4;

	// 计算旋转后的图像高度
	lNewHeight = (LONG)(max(fabs(fDstY4 - fDstY1), fabs(fDstY3 - fDstY2)) + 0.5);

	// 两个常数，这样不用以后每次都计算了
	f1 = (float)(-0.5 * (lNewWidth - 1) * fCosa - 0.5 * (lNewHeight - 1) * fSina
		+ 0.5 * (lWidth - 1));
	f2 = (float)(0.5 * (lNewWidth - 1) * fSina - 0.5 * (lNewHeight - 1) * fCosa
		+ 0.5 * (lHeight - 1));

	// 分配内存，以保存新DIB
	//一个新的内存块
	hDIB = (HGLOBAL) ::GlobalAlloc(GHND, lNewLineBytes * lNewHeight + 40 + 1024);

	// 判断是否内存分配失败
	if (hDIB == NULL)
	{
		// 分配内存失败
		return NULL;
	}

	// 锁定内存
	lpNewDIB = (char*)::GlobalLock((HGLOBAL)hDIB);

	// 复制DIB信息头和调色板
	memcpy(lpNewDIB, lpDIB, 40 + 1024);

	// 找到新DIB象素起始位置
	lpNewDIBBits = FindDIBBits(lpNewDIB);

	// 获取指针
	lpbmc = (BITMAPINFOHEADER*)lpNewDIB;

	// 更新DIB中图像的高度和宽度

	lpbmc->biWidth = lNewWidth;
	lpbmc->biHeight = lNewHeight;



	// 针对图像每行进行操作
	for (i = 0; i < lNewHeight; i++)
	{
		// 针对图像每列进行操作
		for (j = 0; j < lNewWidth; j++)
		{
			// 指向新DIB第i行，第j个象素的指针
			// 注意此处宽度和高度是新DIB的宽度和高度
			lpDst = (char*)lpNewDIBBits + lNewLineBytes * (lNewHeight - 1 - i) + j;

			// 计算该象素在源DIB中的坐标
			i0 = (LONG)(-((float)j) * fSina + ((float)i) * fCosa + f2 + 0.5);
			j0 = (LONG)(((float)j) * fCosa + ((float)i) * fSina + f1 + 0.5);

			// 判断是否在源图范围内
			if ((j0 >= 0) && (j0 < lWidth) && (i0 >= 0) && (i0 < lHeight))
			{
				// 指向源DIB第i0行，第j0个象素的指针
				lpSrc = (char*)lpDIBBits + lLineBytes * (lHeight - 1 - i0) + j0;

				// 复制象素
				*lpDst = *lpSrc;
			}
			else
			{
				// 对于源图中没有的象素，直接赋值为255
				*((unsigned char*)lpDst) = 200;
			}

		}

	}

	// 返回
	return hDIB;
}
//水平镜像变换

//给像素赋值
void assignPixel(LPSTR lpSrcStartBits, int r, int c, int dataSizePerLine, unsigned char* lpSrcStartBitsNew, int rNew, int cNew, int dataSizePerLineNew)
{
	unsigned char* pixel;
	pixel = (unsigned char*)lpSrcStartBits + r * dataSizePerLine + c;
	*(lpSrcStartBitsNew + rNew * dataSizePerLineNew + cNew) = *pixel;
}


void  WINAPI HorizantalMirrorTrans(LPSTR lpSrcDib, LONG lWidth, LONG lHeight, unsigned char*& lpSrcDibNew, LONG lWidthNew, LONG lHeightNew)
{
	int dataSizePerLineNew = (lWidthNew * 8 / 8 + 3) / 4 * 4;
	lpSrcDibNew = new unsigned char[sizeof(BITMAPINFOHEADER) + 256 * 4 + dataSizePerLineNew * lHeightNew];//用来存储新的位图
																										  //初始化
	memset(lpSrcDibNew, 200, sizeof(BITMAPINFOHEADER) + 256 * 4 + dataSizePerLineNew * lHeightNew);

	int dataSizePerLine = (lWidth * 8 / 8 + 3) / 4 * 4;

	BITMAPINFOHEADER* pHead;//新建的一个指向位图信息头类型变量的指针
	RGBQUAD* pColorTable;//新建的一个指向颜色表类型变量的指针

	memcpy(lpSrcDibNew, lpSrcDib, sizeof(BITMAPINFOHEADER) + 256 * 4);

	int offset = sizeof(BITMAPINFOHEADER) + 256 * 4;

	LPSTR lpSrcStartBits = lpSrcDib + offset;
	unsigned char* lpSrcStartBitsNew = lpSrcDibNew + offset;




	for (int r = 0; r < lHeight; r++)
	{
		for (int c = 0; c < lWidth; c++)
		{
			int rNew = r;//因为位图像素的规则，应该是减法
			int cNew = lWidth - 1 - c;
			if (rNew < lHeightNew && rNew >= 0 && cNew >= 0 && cNew < lWidthNew)
			{
				assignPixel(lpSrcStartBits, r, c, dataSizePerLine, lpSrcStartBitsNew, rNew, cNew, dataSizePerLineNew);
			}
		}
	}

	memcpy(lpSrcDib, lpSrcDibNew, sizeof(BITMAPINFOHEADER) + 256 * 4 + dataSizePerLineNew * lHeightNew);

}
