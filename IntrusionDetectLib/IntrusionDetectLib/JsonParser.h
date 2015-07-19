#pragma  once

#include "json.h"
#include "stdio.h"
#include <fstream>
#include <cstring>
#include <vector>

////direction  ���ѡ����
//#define all         0
//#define up2down     1
//#define down2up     2
//#define left2right  3
//#define right2left  4
////target ֻ��ѡһ��
//#define   all       0
//#define   person    1
//#define   animal    2

typedef struct _Areas{
	int left;
	int top;
	int width;
	int height;
}Areas;

typedef struct _Params{
	int direction[2];
	int target;
	Areas areas[5];
	int direction_size;   //�����������鲻����Ŀ
	int areas_size;       //
}Params;

class JsonParser
{
public:
	int ParseJsonFromFile(const char* filename) ;
	int parseJsonFromString(const char* str);
	Params params[5];
private:
	int parse(Json::Value root);
	int params_size;
};
