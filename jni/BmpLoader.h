#ifndef _BMP_LOADER_H_
#define _BMP_LOADER_H_


#ifndef DWORD
	typedef unsigned long DWORD;
	typedef int LONG;
	typedef unsigned short WORD;
#endif
#pragma pack (1)
typedef struct tagBITMAPFILEHEADER { /* bmfh */
	WORD bfType;  //说明文件的类型，该值必需是0x4D42，也就是字符'BM'。
	DWORD bfSize;  //说明该位图文件的大小，用字节为单位
	WORD bfReserved1;  //保留，必须设置为0
	WORD bfReserved2;   //保留，必须设置为0
	DWORD bfOffBits;  //说明从文件头开始到实际的图象数据之间的字节的偏移量
} BITMAPFILEHEADER;

typedef struct tagBITMAPINFOHEADER { /* bmih */
	DWORD biSize;    //BITMAPINFOHEADER结构所需要的字节
	LONG biWidth;    //图象的宽度，以象素为单位。
	LONG biHeight;   //图象的高度，以象素为单位，如果是正数，则图片是倒向的 ，负数则说明是正向。
	WORD biPlanes;   //目标设备说明位面数，其值将总是被设为1。
	WORD biBitCount;    //比特数/象素，其值为1、4、8、16、24、或32。
	DWORD biCompression;    //图象数据压缩的类型，同样我们只讨论没有压缩的类型：BI_RGB。
	DWORD biSizeImage;    //图象的大小，以字节为单位。当用BI_RGB格式时，可设置为0。
	LONG biXPelsPerMeter;    //水平分辨率，用象素/米表示。
	LONG biYPelsPerMeter;    //垂直分辨率，用象素/米表示。
	DWORD biClrUsed;    //图实际使用的彩色表中的颜色索引数（设为0的话，则说明使用所有调色板项）。
	DWORD biClrImportant;    //对图象显示有重要影响的颜色索引的数目，如果是0，表示都重要。
} BITMAPINFOHEADER;
#pragma pack ()

#endif


