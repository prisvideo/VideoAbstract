#include <cv.h>
#include <highgui.h>
#include <windows.h>
#include <interface_server.h>

using namespace cv;

int save(id_image_t *imgs, size_t imgs_count, void *tag){
	static int count = 0;
	printf("detected %d frames.\n", imgs_count);
	for (int i = 0; i < imgs_count; i++){
		Mat m(imgs[i].height, imgs[i].width, CV_8UC3, imgs[i].buffer);
		std::ostringstream oss;
		oss << "..\\imgs\\ " << i + count << ".jpg";
		std::string result = oss.str();
		imwrite(result, m);
	}
	count = count + imgs_count;
	return 0;
}

int main(){
	//JSON��ʽ�����ļ���Ŀǰֻ֧�ֶ���һ��direction��һ��area��
	//�����ʾ��directionΪdown2up,right2left��areaΪ��Ƶ�������
	const char config[] = "{\"version\": \"1\",\"alg-params\": [{\"direction\": [\"down2up\",\"right2left\"],\"target\": [\"person\"],\"areas\": [{\"left\": \"0\",\"top\": \"0\",\"width\": \"320\",\"height\": \"480\"}]}]}";
	//�ص��������Ա���ÿһ֡��ͼƬΪ����
	PFNInstrusionDetectCB cb = &save;
	//��ʼ����⣬������JSON���á�
	if (IntrusionDetectStart(config, NULL) == 0)
		printf("Detection start.\n");
	//���ļ�����ʽ������Ƶ�������м�⡣����м�⵽��Ŀ�꣬����ûص�������
	//��������Ƶ������ʽ��δ��ɣ������Ժ�İ汾���¡�
	IntrusionDetectOpenFile("..\\videos\\00015_H_fusion.avi", cb);
	//ֹͣ��⣬�ͷ��ڴ档
	if(IntrusionDetectStop()==0)
		printf("Done.\n");

	system("pause");
	return 0;
}