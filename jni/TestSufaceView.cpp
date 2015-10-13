#include <jni.h>
#include <android/log.h>
#include <android/native_window_jni.h>
#include <android/native_window.h>
#include <android/asset_manager_jni.h>
#include <android/asset_manager.h>
#include <stdio.h>
#include <stdlib.h>
#include "conver.h"
#include "BmpLoader.h"
extern "C"
{
#define LOG_TAG "JNI_LOG"
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)
static int ALIGN(int x, int y) {
    // y must be a power of 2.
    return (x + y - 1) & ~(y - 1);
}

	static ANativeWindow* g_nativeWindow = NULL;
	static AAssetManager* g_assetManager;
	static int g_nWidth = 0;
	static int g_nHeight = 0;
	static unsigned char* g_buffer = NULL;
	static int g_bufferLen = 0;

	bool getYV12Data(const char *path,unsigned char * pYUVData,int size){
	     FILE *fp = fopen(path,"rb");
	     if(fp == NULL){
	         printf("read %s fail !!!!!!!!!!!!!!!!!!!\n",path);
	         return false;
	     }
	     fread(pYUVData,size,1,fp);
	     fclose(fp);
	     return true;
	 }

	void Java_com_test_surfaceview_TestNative_ShowYuv()
	{
		int width,height;
		width = 352;
		height = 240;
		int size = width * height*3/2;
		unsigned char *data = new unsigned char[size];
		getYV12Data("/sdcard/yuv/fg001.yuv",data,size);
		unsigned char * out =new unsigned char[width * height*3];
		YV12_to_RGB24(data,out,width,height);
		ANativeWindow_Buffer buf;
		if(ANativeWindow_lock(g_nativeWindow,&buf,NULL) <0 )
		{
			LOGE("cannot lock window");
		}
		else
		{
			memcpy(buf.bits,out,width * height *3);
			ANativeWindow_unlockAndPost(g_nativeWindow);
		}

	}
	void Java_com_test_surfaceview_TestNative_Init(JNIEnv* env,jobject obj
			,jobject surface,jobject assetManager)
	{
		g_nativeWindow =  ANativeWindow_fromSurface(env,surface);
		if(g_nativeWindow == NULL)
		{
			LOGE("Get AAssetManager ERROR!");
		}
		//ANativeWindow_acquire(g_nativeWindow);
		g_assetManager = AAssetManager_fromJava(env, assetManager);
		if(g_assetManager == NULL)
		{
			LOGE("Get AAssetManager ERROR!");
		}
	}
	void Java_com_test_surfaceview_TestNative_Destroye(JNIEnv* env,jobject obj)
	{
		ANativeWindow_release(g_nativeWindow);
		g_nWidth = 0;
		g_nHeight = 0;
		g_nativeWindow = NULL;
	}
	char* jstring2string(JNIEnv* env, jstring jstr)
	{
	       char* rtn = NULL;
	       jclass clsstring = env->FindClass("java/lang/String");
	       jstring strencode = env->NewStringUTF("utf-8");
	       jmethodID mid = env->GetMethodID(clsstring, "getBytes", "(Ljava/lang/String;)[B");
	       jbyteArray barr= (jbyteArray)env->CallObjectMethod(jstr, mid, strencode);
	       jsize alen = env->GetArrayLength(barr);
	       jbyte* ba = env->GetByteArrayElements(barr, JNI_FALSE);
	       if (alen > 0)
	       {
	                 rtn = (char*)malloc(alen + 1);
	                 memcpy(rtn, ba, alen);
	                 rtn[alen] = 0;
	       }
	       env->ReleaseByteArrayElements(barr, ba, 0);
	       return rtn;
	}
#define RGB565(R,G,B)         ((unsigned short)( (((unsigned int)B&0xF8)>>3) | (((unsigned int)G&0xFC)<<3) | (((unsigned int)R&0xF8)<<8)))
	void Java_com_test_surfaceview_TestNative_Draw(JNIEnv* env,jobject obj,jstring jstr)
	{
		LOGI("Java_com_test_surfaceview_TestNative_Draw");
		char* path = jstring2string(env,jstr);
		if(g_assetManager == NULL)
		{
			LOGE("Get AAssetManager ERROR!");
		}
		 AAsset* asset = AAssetManager_open(g_assetManager, path,AASSET_MODE_UNKNOWN);
		 free(path);
		 path = NULL;
		 if(asset == NULL)
			 return ;
		 int  bufferLen = AAsset_getLength(asset);
		 unsigned char* buffer = (unsigned char*)malloc(bufferLen+1);
		 buffer[bufferLen] = 0;
		 int numBytesRead = AAsset_read(asset, buffer, bufferLen);
		 g_buffer = buffer;
		 g_bufferLen = bufferLen;
		 AAsset_close(asset);
		 LOGI("g_bufferLen=%d",g_bufferLen);
		BITMAPFILEHEADER  filehead;
		BITMAPINFOHEADER  head;
		memcpy(&filehead,g_buffer,sizeof(BITMAPFILEHEADER));
		memcpy(&head,g_buffer+sizeof(BITMAPFILEHEADER),sizeof(BITMAPINFOHEADER));
		if(filehead.bfType != 0x4D42)
		{
			free(buffer);
			buffer=NULL;
			return ;
		}
		ANativeWindow_setBuffersGeometry(g_nativeWindow,head.biWidth,head.biHeight,WINDOW_FORMAT_RGB_565);
		g_nWidth = ANativeWindow_getWidth(g_nativeWindow);
		g_nHeight = ANativeWindow_getHeight(g_nativeWindow);
		int nfomat  = ANativeWindow_getFormat(g_nativeWindow);
		LOGI("bfOffBits=%d,g_nWidth=%d,g_nHeight=%d,nfomat=%d",filehead.bfOffBits,g_nWidth,g_nHeight,nfomat);
		ANativeWindow_Buffer windowBuffer;
		if(ANativeWindow_lock(g_nativeWindow,&windowBuffer,NULL) <0 )
		{
			LOGE("cannot lock window");
		}
		else
		{
//			unsigned char* tmp =(unsigned char*)( g_buffer+filehead.bfOffBits);
//			unsigned int* data =(unsigned int*) windowBuffer.bits;
//			for(int i=0;i<head.biHeight;i++)
//			{
//				for(int j=0;j<head.biWidth;j++)
//				{
//					int nFlag = 0;
//					memcpy(&nFlag,tmp+(head.biWidth*i+j)*3,3);
//					data[i*windowBuffer.stride+j] = nFlag;
//				}
//				//memcpy(data+i*buffer.stride*2,tmp+(600-i-1)*800*2,800*2);
//			}
			unsigned short* data =(unsigned short*) windowBuffer.bits;
			unsigned char* tmp = (unsigned char*)(g_buffer+filehead.bfOffBits);
			LOGI("%d,%d,%d",head.biWidth,head.biHeight,head.biBitCount);
			int offsize = head.biBitCount/8;
			int lineByte=(head.biWidth* head.biBitCount/8+3)/4*4;
			LOGI("lineByte=%d",lineByte);
			for(int i=0;i<head.biHeight;i++)
			{
				for(int j=0;j<head.biWidth;j++,tmp+=offsize)
				{
					if(offsize>2)
						data[(head.biHeight-i-1)*windowBuffer.stride+j] = RGB565(*(tmp+2),*(tmp+1),*(tmp));
					else
						memcpy(&data[(head.biHeight-i-1)*windowBuffer.stride+j],tmp,2);
				}
				tmp+=(lineByte-offsize*head.biWidth);
			}
			LOGI("buffer.stride=%d,buffer.format=%d",windowBuffer.stride,windowBuffer.format);
			ANativeWindow_unlockAndPost(g_nativeWindow);
		}
		free(buffer);
		buffer=NULL;
		LOGI("Java_com_test_surfaceview_TestNative_Draw END!");
	}
	void Java_com_test_surfaceview_TestNative_TestFFMPEG(JNIEnv* env,jobject obj)
	{
		LOGI("~~TestFFMPEG~~");
	}
}
