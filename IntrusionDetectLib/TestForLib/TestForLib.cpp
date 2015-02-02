#include <cv.h>
#include <highgui.h>
#include <windows.h>
#include <interface_server.h>
#include <stdint.h>

#define INBUF_SIZE 4096
#define FF_INPUT_BUFFER_PADDING_SIZE 8

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
	//������Ƶ��
	FILE *fin = fopen("..\\videos\\test.264", "rb");
	uint8_t inbuf[INBUF_SIZE + FF_INPUT_BUFFER_PADDING_SIZE];
	memset(inbuf + INBUF_SIZE, 0, FF_INPUT_BUFFER_PADDING_SIZE);
	int size = 1;
	id_stream_t * stream = new id_stream_t();
	while (size > 0){
		size = fread(inbuf, 1, INBUF_SIZE, fin);
		stream->type = 1;
		stream->buffer = inbuf;
		stream->len = INBUF_SIZE;
		IntrusionDetectPushStream(stream, cb);
	}
	delete stream;
	//���ļ�����ʽ������Ƶ�������м�⡣����м�⵽��Ŀ�꣬����ûص�������
	//��������Ƶ������ʽ��δ��ɣ������Ժ�İ汾���¡�
	//IntrusionDetectOpenFile("..\\videos\\00015_H_fusion.avi", cb);
	//ֹͣ��⣬�ͷ��ڴ档
	if(IntrusionDetectStop()==0)
		printf("Done.\n");

	system("pause");
	return 0;
}