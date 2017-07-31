/*************************************************
  Copyright (C), 2015-2020, ���������ɷ����޹�˾
  File name:  interface.h
  Author:    ����
  Date:     2017-01-09
  Description:  pdfת��jpg�ӿ�
*************************************************/

#ifdef LIBPDFEXPORT
#define PDFEXPORT  __declspec(dllexport)
#else
#define PDFEXPORT  extern "C" __declspec(dllimport)
#endif

/*
*	@bref:  pdf ת jpg �ӿ�
*	@param:	chFileName      pdf�ļ�·��
*			iBeginPageNum   ��ʼҳ������1��ʼ��
*			iEndPageNum     ����ҳ��
*			iZoom           �Ŵ��� (100��1����99 ��0.99����200:2��)
*			iRotation       ��ת�Ƕ�
*	@return 
		error:0
		success:1
*			
*	
*/
PDFEXPORT int pdf2img(char * chFileName,int iBeginPageNum,int iEndPageNum,int iZoom,int iRotation);
