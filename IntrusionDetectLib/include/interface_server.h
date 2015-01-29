#ifndef __INSTRUSION_DETECT_ALG_H__
#define __INSTRUSION_DETECT_ALG_H__
#ifdef DLL_API  
#else  
#define DLL_API __declspec(dllexport)  
#endif  
/*,
�㷨����������ΪJSON��ʽ�������ĺô����Ժ��㷨���Ӳ��������������ܣ���������ǩ���Ͳ���Ҫ�޸���

JSON���ṹ����
version��Ϊ�汾�ţ���ǰΪ1������Ժ��������Ҫ������޸ģ�����˳������
alg-params����Ӧ��ֵΪ���飬������ÿһ�����һ�������߸���Ȥ������
����ṹ��
	direction�����򣬿���һ��ѡ����, ��ѡ�ַ�Ϊ all left2right right2left up2down down2up
		���磺
		all : ���з���
		up2down|down2up�����ϵ��»���µ��ϵķ���
	target������Ŀ�꣬��ѡ�ַ�Ϊ person animal all
	areas�������򣬵�ǰΪ���������������������Ϊ�����������⼸����������ͬ�ķ����Ŀ��
		left : �������Ͻǵ�X����
		top  : �������Ͻǵ�Y����
		width : �������򳤶�
		height : ��������߶�

JSONʾ�����£�
{
    "version": "1",
    "alg-params": [
        {
            "direction": [
                "up2down",
                "down2up"
            ],
            "target": [
                "person"
            ],
            "areas": [
                {
                    "left": "0",
                    "top": "0",
                    "width": "100",
                    "height": "100"
                },
                {
                    "left": "100",
                    "top": "100",
                    "width": "200",
                    "height": "200"
                }
            ]
        },
        {
            "direction": [
                "all"
            ],
            "target": [
                "all"
            ],
            "areas": [
                {
                    "left": "500",
                    "top": "500",
                    "width": "600",
                    "height": "600"
                }
            ]
        }
    ]
}


*/

/*
 * �����壬��ǰtypeΪ1����H264 frame, ��0x0001��ͷ��ÿ��I֡ǰ����SPS��PPS֡��
*/
typedef struct _id_stream_t
{
	int type; // 1 : H264
	unsigned char *buffer;
	size_t len;
} id_stream_t;


/*
 * ͼ���壬��ǰtypeΪ1����YUV420SP��ʽ
*/
typedef struct _id_image_t
{
	int type; // 1��YUV420SP(Android)��2��RGB
	int width;
	int height;
	int buf_size;
	unsigned char *buffer;
} id_image_t;


/*
 * @brief ��⵽���ֺ�Ļص�����
 * param imgs �������ּ�⾯����ͼ������
 *			  �����buffer���㷨����й�������������ڻص����غ�Ҫʹ�ã�����Ҫ�����Ǹ��Ƶ��Լ����ڴ��
 * param imgs_count ������ͼ��ĸ���
 * param tag 
 */
typedef int(*PFNInstrusionDetectCB)(id_image_t *imgs, size_t imgs_count, void *tag);

/**
 * @brief �������ּ�⡣Ϊͬ������
 * @param config ���ּ��Ĳ�����Ϊjson��ʽ
 * @param tag ������ָ���Ļص�������͸������
			  ��ǰ�趨1������ֻ����һ�ξ����ص�
 * @return ����ֵ0����ɹ�������������󣬾�����������㷨�����
 */
DLL_API int IntrusionDetectStart(
	char const *config,
	void *tag
	);

/**
 * @brief ֹͣ��⡣Ϊͬ������
 * @return ����ֵ0����ɹ�
 */
DLL_API int IntrusionDetectStop(
	);

/**
 * @brief �������е�����������Ϊͬ���������˺���Ҫ�����ܿ�ķ���
 * @stream ��Ƶ������ǰΪRTPЭ���װ��H264��ʽ���㷨��Ӧ���ں������÷���ǰ
		   ���������е����ݵ��Լ��Ļ�����
 * @return ����ֵ0����ɹ�
 */
DLL_API int IntrusionDetectPushStream(
	id_stream_t *stream
	);

//************************************
// Method:    IntrusionDetectOpenFile
// FullName:  IntrusionDetectOpenFile
// Access:    public 
// Returns:   int ����ֵ0����ɹ�
// Qualifier:
// Parameter: const char * filename ��Ƶ�ļ�·��
// Parameter: PFNInstrusionDetectCB cb ��⵽���ֵĻص�����
//************************************
DLL_API int IntrusionDetectOpenFile(const char * filename, PFNInstrusionDetectCB cb);
#endif

