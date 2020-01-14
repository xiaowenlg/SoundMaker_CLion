/*
ϵͳ���������ڴ�
*/


#ifndef _MAINCONFIG_H_
#define _MAINCONFIG_H_
#include "stdint.h"
#include "stm32f1xx_hal.h"
//#include "system.h"
#define REED_Pin GPIO_PIN_0   //�ɻɹ�����
#define REED_GPIO_Port GPIOA
#define REED_EXTI_IRQn EXTI0_IRQn

//------------------------------------------ ����оƬWTN6040 æ����
#define WTN_BUSY_Pin			GPIO_PIN_15//æ����
#define WTN_GPIO_Port			GPIOB
#define WTN_BUSY_EXTI_IRQn		EXTI15_10_IRQn
#define  CLK_2A                 PBout(13) //ʱ�������λ��������
#define  P_DATA_2A               PBout(12) //���������λ��������
#define  CLK_2A_PIN             GPIO_PIN_13//ʱ������
#define  P_DATA_2A_PIN          GPIO_PIN_12//��������
#define  SYSCLOSE_PIN		GPIO_PIN_8 //�ر�ϵͳ���ţ��ߵ�ƽ�ر�
#define  SYSCLOSE_PORT		GPIOB
#define  SYSIO				PBout(8)   //λ������

//DTH11����
#define DHT11_DATA_PIN			GPIO_PIN_15 //����
#define DTH11_PORT				GPIOA     
#define DHT11_OUT				PAout(15)	//����
#define DTH11_IN				PAin(15)	//����

#define TIMER2_T                  1000       //T = 1000ms   //�����ɼ�����
#define TIMER2_PLAY_WAIT          5*1000
#define M_SIZE                 sizeof(struct Customerinfo*)   //��Ϣ��С
#define TIMER_CLOSESYSTEM		  5								//5��
//��·��ϵ��
#define HOT_CAR                7            //����
#define HOT_MANBUJI			   5           //������
#define HOT_NOUYAOQI		   3			//Ť����
#define HOT_HUACHUANQI		   4			//������
#define HOT_FUJIBAN			   8			//������
#define HOT_ZZBANMO			   6			//����ʽ������Ħ
#define HOT_TUOYUANJI		   4            //��Բ��
#define HOT_TJROUTUI		   1			//̫������
#define HOT_TUIJU			   8			//�ƾ�
#define HOT_QQBAN			   4			//���ΰ�
#define HOT_QIMA			   5			//������
#define HOT_ZHONGBAI		   3			//�Ӱ���
#define MAXSPORTFREQ		   5			//����˶�Ƶ��     ���˶�Ƶ�ʴ��ڴ���ʱ������ʾ

#define PLAYARRAYLENGTH        50			//�������鳤��
//������ַ
#define S_TEN               10               //ʮ
#define S_HUNDRED			11				//��
#define S_THOUSAND          12				//ǧ
#define S_THISSPORT         13				//��������ˣ�
#define S_SPORTTIM          14              //�ʱ��
#define S_THISKCAL          15				//��������
#define S_NUMBER			16				//��
#define S_HOUR				17				//ʱ
#define S_MINUTE            18				//��
#define S_SECOND			19				//��
#define S_KCAL              20				//ǧ��
#define S_POINT             21           //�� ��ַ
#define S_WELCOME           22				//��ӭ�ٴ�ʹ��
#define S_MAXSPORT_TIP		0x20            //�˶�Ƶ�ʹ�����ʾ

//TFT���
#define REGISTERREAD		0x81			//���Ĵ���
#define REGISTERWRITE		0x80
#define VOL_STATUS			0x55			//����״̬

//HMI���
#define HMIARRAYLENGTH      64				//���������С
#define QRCODE				"https://weixin.hbqifan.com?DevName=WH-BLE 102&DevAddress=9C:A5:25:95:80:1F&EquipmentNumber=00010000300009000004&"   //��ά��������Ϣ
//---------------------------HMI�ؼ�
#define HMI_SPEED			"n0.val="		//�ٶ�
#define HMI_HOUR			"n1.val="		//ʱ
#define HMI_MINUTE			"n2.val="		//��
#define HMI_SECOND			"n3.val="		//��
#define HMI_COUNT			"n4.val="		//����
#define HMI_KCAL			"x0.val="		//����
#define HMI_GIF_EN			"gm0.en="       //�������� 0=�أ�1=��
#define HTM_GIF_DIS			"gm0.dis="		//�����ٶ� 0----100
#define HTM_BATTERY_J       "j0.val="		//��ص���������
#define HTM_QRCODE			"qr0.txt="		//��ά��ؼ�
#define HTM_AUDIO1			"audio1="		//��Ƶͨ��1����
#define HTM_T1				"t1.txt="
//HMI ����
#define HMI_UART			&huart3        //HMI����
//���Կ���
//#define MYDEBUG
//�����ź�������
#define UART_MUTEX           0                 //�����Ƿ�ʹ�û����ź���������ʹ��=1����ʹ��=0
//������ַ����
#define MAC_LENGTH			19
//stm32��ַ��
#define STM32_FLASH_BASE			0x08000000   //��ʼ��ַ
#define STM32_FLASH_SIZE			1024*128	//flash��С128K
#define STM_SECTOR_SIZE				1024*2           //������С
#define ENDADRR             STM32_FLASH_BASE+STM32_FLASH_SIZE-1024   //��β��ַ
#define EEPROMLARGE			1024*2           //eeprom��С2K
#define EEPROM_BEGIN_ADRR   ENDADRR-EEPROMLARGE   //eeprom��ʼ��ַ
#define READLEN				17					//��ȡ���ݳ���

//�ַ���ƴ��
#define QR_HEAD				"https://weixin.hbqifan.com?DevName=WH-BLE 102&DevAddress="
#define QR_EQNUM			"&EquipmentNumber="
#define QR_END				"&"
//Ԥ����ѡ��
//#define TFTPLAY
extern uint16_t SportCount;        //�˶��ƴ�
extern uint16_t TempCount;
//�ϴ�������Ϣ
#define SERIALDATLEN			20				//�ϴ����ݳ���
#define BLE_UART				&huart2         //���������豸�ӿ�


#define DEBUG_UART				&huart1			//���Դ��ڽӿ�

//�豸���ڲ���������
#define UART_BAND_1				115200         //��������
#define UART_BAND_2				115200        //�����ô���
#define UART_BAND_3				9600		  //HML������(�Ծ���)
#define TESTLEN                 12            //���볤��
#define TEST_P                  "cao-xiao-wen"
#define TEST_USECOUNT           10                          //��û����������������ʹ�õĴ���
//Flash ��ַ
#define ADRLEN                 32  //����С����
#define GETADRESS(n)           EEPROM_BEGIN_ADRR+ADRLEN*n           //�����洢��ַ  n:�ڼ�������Сɽ����n��Z��
#define PASS_ADRESS            GETADRESS(1)          //����洢��ַ
#define BLE_ADRESS             GETADRESS(2)           //�����洢��ַ
#define PASS_RIGHT_ADRESS             GETADRESS(3)           //����ȽϽ��

#define WAITTIM                 5000         //���ý�����ʾʱ�䵥λms
#define VERSION                 0            //�汾�ţ�0Ϊ���ã�1Ϊ�������ð�
typedef struct SportInfo      //�˶���Ϣ
{
	uint16_t count;//�˶�����
	uint16_t freq;//�˶�Ƶ��
	long hot;//��������
	uint16_t tim;//�˶�ʱ��
	uint8_t    playstate;//����״̬
}Customerinfo;
/*
 * extern uint8_t ReceData[256];//�������ݻ�����
extern _Bool ReceOver;//������ϱ�־
extern  uint8_t DataLen;
 */
/*���ڽ��� �ṹ������*/

#endif // !_MAINCONFIG_H_
