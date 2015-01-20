#include "pris_videotest_JNIClient.h"
#include <opencv2/opencv.hpp>
#include <segmentation_1208_wf.h>

cv::Mat gray;

JNIEXPORT jboolean JNICALL Java_pris_videotest_JNIClient_initShift(JNIEnv * env,
		jclass, jintArray pixels, jint width, jint height) {
	///�����ǳ�ʼ���Ĳ���
	jint * cPixels;
	cPixels = env->GetIntArrayElements(pixels, 0);
	cv::Mat imgData(height, width, CV_8UC4, (unsigned char*) cPixels);
	cv::cvtColor(imgData, gray, CV_RGB2GRAY);
//	cv::Mat gray32;
	gray.convertTo(gray, CV_32FC1);
	CvMat g = gray;
	Initial(&g);
	env->ReleaseIntArrayElements(pixels, cPixels, 0);
	return true;
}
JNIEXPORT jboolean JNICALL Java_pris_videotest_JNIClient_detectWithShift(
		JNIEnv * env, jclass, jintArray pixels, jint width, jint height) {
	jint * cPixels;
	cPixels = env->GetIntArrayElements(pixels, 0);

	cv::Mat imgData(height, width, CV_8UC4, (unsigned char*) cPixels);
	int result[width * height];
	////////ÿһ֡������ͼ��ΪimgData������01////////

	cv::cvtColor(imgData, gray, CV_RGB2GRAY);
//	cv::Mat gray32;
	gray.convertTo(gray, CV_32FC1);
	CvMat g = gray;
	env->ReleaseIntArrayElements(pixels, cPixels, 0);
	return FrameProcessing(&g);
	////////����д����////////
}
