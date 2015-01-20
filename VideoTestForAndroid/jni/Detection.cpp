#include "stdio.h"
#include <iostream>
#include <opencv2/opencv.hpp>

#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <math.h>
#include <float.h>
#include <limits.h>
#include <time.h>
#include <ctype.h>
#include <pris_videotest_JNIClient.h>

cv::BackgroundSubtractorMOG2 m_pBGSubMOG2;
double m_rFGSegThreshold;
int m_nVideoResizeW;
int m_nVideoResizeH;
//cv::Mat m_GrayFrameMat;
cv::Mat foregroundMat;
cv::Mat m_ResizeFrameMat;

JNIEXPORT jboolean JNICALL Java_pris_videotest_JNIClient_init(JNIEnv *, jclass,
		jbyteArray, jint width, jint height) {

	m_rFGSegThreshold = 0.01; ///<��ʼ��Ϊ0.01��ǰ������ռȫͼ��1%
	cv::Rect r;
	r.x = 0;
	r.y = 0;
	r.width = width;
	r.height = height;

	m_nVideoResizeW = 40;
	m_nVideoResizeH = 30;
	return true;
}

JNIEXPORT jboolean JNICALL Java_pris_videotest_JNIClient_detect(JNIEnv * env,
		jclass, jbyteArray pixels, jint width, jint height) {
	jbyte * cPixels;
	cPixels = env->GetByteArrayElements(pixels, 0);

	cv::Mat imgData(height, width, CV_8UC1, (unsigned char*) cPixels);

	IplImage *frame = cvCreateImage(cvSize(width, height), IPL_DEPTH_8U, 1);
	*frame = imgData.operator _IplImage();
	//imgData.release();

	cvSmooth(frame, frame, CV_GAUSSIAN, 3, 0, 0);     ///<��˹�˲�
	cv::Mat m_OriFrameMat = frame;
	//cvReleaseImage(&frame);
	resize(m_OriFrameMat, m_ResizeFrameMat,
			cv::Size(m_nVideoResizeW, m_nVideoResizeH), 0, 0, CV_INTER_LINEAR); ///<ѹ�� 640*480 m_pResizeFrame=30*40
	//m_OriFrameMat.release();
	//cvtColor(m_ResizeFrameMat, m_GrayFrameMat, CV_BGRA2GRAY, 1); ///<�ҶȻ�
	//m_ResizeFrameMat.release();
	m_pBGSubMOG2.operator()(m_ResizeFrameMat, foregroundMat, 0.001);
	m_ResizeFrameMat = foregroundMat;

	int i, j, k;
	k = 0;
	for (i = 0; i < m_nVideoResizeH; i++) {
		for (j = 0; j < m_nVideoResizeW; j++) {
			if (m_ResizeFrameMat.data[i * m_nVideoResizeW + j] != 0) {
				k++; ///<�����ֵǰ��ͼ���0���ص����
			}
		}
	}
	//m_GrayFrameMat.release();
	//delete frame;
	double k_ratio = (double) k / (double) (m_nVideoResizeW * m_nVideoResizeH);
	if (k_ratio <= 0.01) {
		env->ReleaseByteArrayElements(pixels, cPixels, 0);
		return false;
	}
	if (k_ratio / m_rFGSegThreshold > 1.5 || k_ratio / m_rFGSegThreshold < 0.79)
		m_rFGSegThreshold = k_ratio;

	///��⵽�˶���Ƶ��
	if (k_ratio >= m_rFGSegThreshold) {
		env->ReleaseByteArrayElements(pixels, cPixels, 0);
		return true;
	}
	env->ReleaseByteArrayElements(pixels, cPixels, 0);
	return false;
}

JNIEXPORT jintArray JNICALL Java_pris_videotest_JNIClient_detectWithReturn(
		JNIEnv * env, jclass, jintArray pixels, jint width, jint height) {
	jint * cPixels;
	cPixels = env->GetIntArrayElements(pixels, 0);

	cv::Mat imgData(height, width, CV_8UC4, (unsigned char*) cPixels);

	IplImage *frame = cvCreateImage(cvSize(width, height), IPL_DEPTH_8U, 4);
	*frame = imgData.operator _IplImage();
	//imgData.release();

	cvSmooth(frame, frame, CV_GAUSSIAN, 3, 0, 0);     ///<��˹�˲�
	cv::Mat m_OriFrameMat = frame;
	//cvReleaseImage(&frame);
	resize(m_OriFrameMat, m_ResizeFrameMat,
			cv::Size(m_nVideoResizeW, m_nVideoResizeH), 0, 0, CV_INTER_LINEAR); ///<ѹ�� 640*480 m_pResizeFrame=30*40
	//m_OriFrameMat.release();
	//cvtColor(m_ResizeFrameMat, m_GrayFrameMat, CV_BGRA2GRAY, 1); ///<�ҶȻ�
	//m_ResizeFrameMat.release();
	m_pBGSubMOG2.operator()(m_ResizeFrameMat, foregroundMat, 0.001);
	m_ResizeFrameMat = foregroundMat;

	int result[m_nVideoResizeH*m_nVideoResizeW];
	for(int i = 0; i<m_nVideoResizeH*m_nVideoResizeW; i++){
		result[i] = m_ResizeFrameMat.data[i];
	}
	env->ReleaseIntArrayElements(pixels, cPixels, 0);
	jintArray intArray = env->NewIntArray(m_nVideoResizeH*m_nVideoResizeW);
	env->SetIntArrayRegion(intArray, 0, m_nVideoResizeH*m_nVideoResizeW, result);
	return intArray;
}
