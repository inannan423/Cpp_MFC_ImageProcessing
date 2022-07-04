// Final


#ifndef _INC_FinalAPI
#define _INC_FinalAPI


// º¯ÊýÔ­ÐÍ
BOOL WINAPI CalThreshold (LPSTR lpDIBBits, LONG lWidth, LONG lHeight, double num);
BOOL WINAPI CalWindow (LPSTR lpDIBBits, LONG lWidth, LONG lHeight, double max, double min);
BOOL WINAPI GrayStretch(LPSTR lpDIBBits, LONG lWidth, LONG lHeight, BYTE bX1, BYTE bY1, BYTE bX2, BYTE bY2, long lLineBytes);
BOOL WINAPI Equalize (LPSTR lpDIBBits, LONG lWidth, LONG lHeight);
double Iterative (LPSTR lpDIBBits, LONG lWidth, LONG lHeight);
double Otsu(LPSTR lpDIBBits,LONG lWidth, LONG lHeight);
BOOL WINAPI MyCalThreshold (LPSTR lpDIBBits, LONG lWidth, LONG lHeight);
int  dealer_four(LPSTR image, int width, int height, int Bg);
int  dealer_eight(LPSTR image, int width, int height, int Bg);
LONG WINAPI getArea_four(LPSTR start, LONG lWidth, LONG lHeight, int Bg);
LONG WINAPI getArea_eight(LPSTR start, LONG lWidth, LONG lHeight, int Bg);
#endif //!_INC_FinalAPI