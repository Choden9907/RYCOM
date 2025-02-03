#ifndef HEX2BIN_H
#define HEX2BIN_H
 
typedef unsigned char uint8_t;
typedef unsigned short uint16_t;
typedef unsigned int uint32_t;
 #include <QString>

extern QByteArray text;

#define HEX_MAX_LENGTH		521
#define HEX_MIN_LEN		11
 
typedef enum {
	RES_OK = 0,		//��ȷ
	RES_DATA_TOO_LONG,	//����̫��
	RES_DATA_TOO_SHORT,	//����̫��
	RES_NO_COLON,		//�ޱ��
	RES_TYPE_ERROR,		//���ͳ�����������
	RES_LENGTH_ERROR,	//���ݳ����ֶκ����ݵ��ܳ��Ȳ���Ӧ
	RES_CHECK_ERROR,	//У�����
	RES_HEX_FILE_NOT_EXIST,	//HEX�ļ�������
	RES_BIN_FILE_PATH_ERROR,//BIN�ļ�·�����ܲ���ȷ
	RES_WRITE_ERROR,	//д���ݳ���
	RES_HEX_FILE_NO_END	//hex�ļ�û�н�����
} RESULT_STATUS;
 
typedef struct {
	uint8_t len;
	uint8_t	type;
	uint16_t addr;
	uint8_t *data;
} BinFarmat;
 
RESULT_STATUS HexFile2BinFile(char *src, char *dest,uint32_t* addr);
#endif
