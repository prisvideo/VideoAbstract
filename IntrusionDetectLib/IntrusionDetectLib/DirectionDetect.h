#pragma once

#include "cv.h"
#include "highgui.h"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#define _USE_MATH_DEFINES
#include <math.h>
#include <windows.h>
//#include "videoProcess.h"
using namespace std;
using namespace cv;

typedef struct _IntrOb{
	Rect detecR;
	int segID;
	int module;
	double orient;     //angle
	CvPoint center;
	Mat sift_src;
}IntrOb;

#define GRADIENT 0x0001
#define THETA 0x0002


class DirectionDetect
{
public:
	//�˲���������ݿ�
	float computeCos(CvPoint p1,CvPoint p2);//�����������б��
	float computeGradient(CvPoint p1,CvPoint p2);//�����������б��
	float computeTheta(CvPoint p1,CvPoint p2);//�������㷽���
	int computeTrajectory(vector<CvPoint>* trajectory,vector<float>* result,UINT flag,int delta=23);//����켣�ķ���ǻ���б��
	int computeCenterOfTrajectory(vector<CvPoint>* cornerPoint,int width,int height,vector<CvPoint>* centerPoint);//���켣�����Ͻ�����ת��Ϊ��������
	//����Ҫ���ݿ����ָ��Ƚӿ�

	//�������demo,�ӿڲ���Ϊ������֡����
	bool computeOrientByTwoFrame(vector<IntrOb>* befOb, vector<IntrOb>*curOb, int direction);
	void drawOrient(Mat mat, vector<IntrOb>*curOb);
	int computeModule(CvPoint p1,CvPoint p2);


	//2015.3.8
	bool initHistoryData(int deltaFrame);
	bool computeOrient(vector<IntrOb>*curOb, int direction);//�ø�һ����������֡���ݼ��㷽��

protected:
private:
	int aver_k; //average k of orientationƽ��б��
	int delta;
	queue<vector<IntrOb>> historyData;
};