/*************************************************
  Copyright (C), 2015-2020, 理邦精密仪器股份有限公司
  File name:  interface.h
  Author:    李宁
  Date:     2017-01-09
  Description:  pdf转换jpg接口
*************************************************/

#ifdef LIBPDFEXPORT
#define PDFEXPORT  __declspec(dllexport)
#else
#define PDFEXPORT  extern "C" __declspec(dllimport)
#endif

/*
*	@bref:  pdf 转 jpg 接口
*	@param:	chFileName      pdf文件路径
*			iBeginPageNum   开始页数（从1开始）
*			iEndPageNum     结束页数
*			iZoom           放大倍数 (100：1倍，99 ：0.99倍。200:2倍)
*			iRotation       旋转角度
*	@return 
		error:0
		success:1
*			
*	
*/
PDFEXPORT int pdf2img(char * chFileName,int iBeginPageNum,int iEndPageNum,int iZoom,int iRotation);
