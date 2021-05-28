//*****************************************************************************
//  File Name: interface.h
//  Function:  KT Wireless Mic Transmitter Products Demoboard Interface Function Define
//*****************************************************************************
//        Revision History
//  Version Date        Description
//  V1.0    2015-8-27   ��ʼ�汾
//  V1.1    2017-02-08  ��ʽ�淶������
//  V0.3    2017-04-27  �Ӽ�Ƶ�ʵ�ʱ���Ȱѵ�Ƶ���ˣ�tune��̨���ٻָ�ԭ����Ƶ�����ã�main.c��
//						��̨��һֱ����ͬ�Ĳ�������tunę�������һ��ʱ��󲽽����4����10����main.c��
//*****************************************************************************

//-----------------------------------------------------------------------------
// Includes
//-----------------------------------------------------------------------------
#include "sh88f4051.h" 
#include "intrins.h"
//#include "IR.h"

//-----------------------------------------------------------------------------
// ���ܼ���������
//-----------------------------------------------------------------------------
#define I2C //I2C���ܶ���

#ifdef I2C
    #define I2C_WORD_MODE
#endif

//#define IR        //�����Ƶ
//#define SOUTAI        //�Զ���̨��Ƶ

#ifdef IR
    #define    MIC      MIC_B
    #define    MIC_A    0xA0
    #define    MIC_B    0xB0
#endif

#ifdef SOUTAI
    //�Զ���̨��Ƶ����Ƶ�ʿ��޸ģ����Ƿ��Ȳ���̫�󣬲�����Ҫ��RXһ��
    #define MIC_Frequency     645350    
#endif

//-----------------------------------------------------------------------------
//�����������Ͷ���
//-----------------------------------------------------------------------------
typedef unsigned char   UINT8;
typedef unsigned int    UINT16;
typedef unsigned long   UINT32;
typedef char            INT8;
typedef int             INT16;
typedef long            INT32;
typedef bit             BOOL;

//-----------------------------------------------------------------------------
// Global VARIABLES
//-----------------------------------------------------------------------------
static UINT32 xdata Memery_Frequency; //����Ƶ����Ϣ 
static UINT32 xdata Load_Frequency;   //flash���汣���Ƶ����Ϣ
//static UINT8 VOLUME = 6;
static UINT8 Key_UP_flag=0;    //���������������ϼӱ�־״̬
static UINT8 Key_DOWN_flag=0;  //���������������¼���־״̬
static BOOL Key_RF_POW_flag=1; //�����л��Ƿ�ȥ����־
//static BOOL temp_RF_POW_SW=0;

//-----------------------------------------------------------------------------
//����VOLUME ����
//-----------------------------------------------------------------------------
#define    key_Vol     0
#define    key_Freq    1

#define    Dis_None    0
#define    Dis_Freq    1
#define    Dis_Vol     2

#define    VOLUME_TOP       15 //volume=15
#define    VOLUME_BOTTOM    0  //volume=0

#define    VBAT_FULL       0x190 //�������׼ֵ������Ч�������е���
#define    VBAT_LOW        0x177 //�͵�ѹ����ֵ������Ч�������е���

#define    LED_ON        0
#define    LED_OFF       1

//-----------------------------------------------------------------------------
//����LCD & KEY����
//-----------------------------------------------------------------------------
#define RD_MODE     0xC0    // 110 Binary
#define WR_MODE     0xA0    // 101
#define RMW_MODE    0xA0    // 101
#define CMD_MODE    0x80    // 100

#define LCD_COM        4
#define LCD_SEG        32

#define SYS_EN        0x01    // Enable System Clock
#define SYS_DIS       0x00

#define LCD_ON        0x03    // Turn on LCD
#define LCD_OFF       0x02    // Turn off LCD

#define CRYSTAL_32K    0x14
#define INT_256K    0x18
#define EXT_256K    0x1C

#define LCD_BIAS    0x29    // 1/3 bias, 4coms used
//#define LCD_BIAS    0x28    // 1/2 bias, 4coms used

#define FREQ_ZERO_A     0x09
#define FREQ_ZERO_B     0x09
#define FREQ_ZERO_C     0x00
#define FREQ_ZERO_D     0x03/*0*/

#define FREQ_ONE_A      0x00
#define FREQ_ONE_B      0x00
#define FREQ_ONE_C      0x00
#define FREQ_ONE_D      0x03/*1*/

#define FREQ_TWO_A      0x0A
#define FREQ_TWO_B      0x09
#define FREQ_TWO_C      0x02
#define FREQ_TWO_D      0x01/*2*/

#define FREQ_THREE_A    0x00
#define FREQ_THREE_B    0x09/*3*/
#define FREQ_THREE_C    0x02
#define FREQ_THREE_D    0x03/*3*/

#define FREQ_FOUR_A     0x03
#define FREQ_FOUR_B     0x00/*4*/
#define FREQ_FOUR_C     0x02
#define FREQ_FOUR_D     0x03/*4*/

#define FREQ_FIVE_A     0x03
#define FREQ_FIVE_B     0x09/*5*/
#define FREQ_FIVE_C     0x02
#define FREQ_FIVE_D     0x02/*5*/

#define FREQ_SIX_A      0x0B
#define FREQ_SIX_B      0x09/*6*/
#define FREQ_SIX_C      0x02
#define FREQ_SIX_D      0x02/*6*/

#define FREQ_SEVEN_A    0x00
#define FREQ_SEVEN_B    0x01/*7*/
#define FREQ_SEVEN_C    0x00
#define FREQ_SEVEN_D    0x03/*7*/

#define FREQ_EIGHT_A    0x0B
#define FREQ_EIGHT_B    0x09/*8*/
#define FREQ_EIGHT_C    0x02
#define FREQ_EIGHT_D    0x03/*8*/

#define FREQ_NINE_A     0x03
#define FREQ_NINE_B     0x09/*9*/
#define FREQ_NINE_C     0x02
#define FREQ_NINE_D     0x03/*9*/

#define CH_ZERO_A       0x0F       
#define CH_ZERO_B       0x05/*0*/
                               
#define CH_ONE_A        0x06       
#define CH_ONE_B        0x00/*1*/  
                               
#define CH_TWO_A        0x0B       
#define CH_TWO_B        0x06/*2*/  
                               
#define CH_THREE_A      0x0F     
#define CH_THREE_B      0x02/*3*/
                               
#define CH_FOUR_A       0x06     
#define CH_FOUR_B       0x03/*4*/
                               
#define CH_FIVE_A       0x0D     
#define CH_FIVE_B       0x03/*5*/
                               
#define CH_SIX_A        0x0D       
#define CH_SIX_B        0x07/*6*/  
                               
#define CH_SEVEN_A      0x07     
#define CH_SEVEN_B      0x00/*7*/
                               
#define CH_EIGHT_A      0x0F     
#define CH_EIGHT_B      0x07/*8*/
                               
#define CH_NINE_A       0x0F     
#define CH_NINE_B       0x03/*9*/

#define LCD_PILOT       ((29<<4) | 0x08)
#define LCD_PILOT_DIS   ((29<<4) | 0x00)
#define LCD_MUTE        ((25<<4) | 0x08)
#define LCD_UNMUTE      ((25<<4) | 0x00)
#define LCD_LOCK        ((18<<4) | 0x08)
#define LCD_DOT         ((11<<4) | 0x04)

#define LCD_BATH        ((30<<4) | 0x0F)
#define LCD_BATM        ((30<<4) | 0x0D)
#define LCD_BATL        ((30<<4) | 0x09)
#define LCD_BATZ        ((30<<4) | 0x01)

//-----------------------------------------------------------------------------
//EEPROM�������ֺ궨��
//-----------------------------------------------------------------------------
#define EEPROM_UNLOCK_KEY1     0x56  //��һ����Կ
#define EEPROM_UNLOCK_KEY2     0xAE  //�ڶ�����Կ

//-----------------------------------------------------------------------------
//�ػ��������Ŷ���
//-----------------------------------------------------------------------------
sbit LDO_CTRL   =    P1^7; // ���ƿ��ػ�POP��
sbit VBAT_IN    =    P1^6; // ���ƿ��ػ�POP��

//-----------------------------------------------------------------------------
//I2C���Ŷ���
//-----------------------------------------------------------------------------
sbit SDA        =    P3^0;                                            
sbit SCL        =    P3^1;

//-----------------------------------------------------------------------------
//KEY���Ŷ���
//-----------------------------------------------------------------------------
sbit RF_POW_SW  =   P4^0; // ��Ƶ��С����
sbit IR_SEND    =   P1^3;
sbit powerOn    =   P3^5;
sbit porN       =   P3^4;

//-----------------------------------------------------------------------------
//LCD���Ŷ���
//-----------------------------------------------------------------------------
sbit LCD_LED    =    P1^1; // LCD ����
sbit LCD_WR     =    P1^0; // LCD ����
sbit LCD_DATA   =    P3^7; // LCD ����
sbit LCD_CS     =    P4^1; // LCD Ƭѡ

sbit Key_UP     =    P4^2; // Ƶ�����Ͽ���
sbit Key_DOWN   =    P3^2; // Ƶ�����¿���
sbit Key_SET    =    P3^3; // Ƶ���趨

//-----------------------------------------------------------------------------
// SYS Function PROTOTYPES
//-----------------------------------------------------------------------------
void SYSCLK_Init(void);
void PORT_Init(void);
void Erase_Eeprom (UINT8 page);
void Write_Eeprom(UINT8 wr_data,UINT8 page,UINT8 offset);
UINT8 Read_Eeprom(UINT8 code *addr);
void Save_Freq (void);
void Load_Freq (void);
void KT_MicTX_Batter_Detecter (void);
void KT_MicTX_RFSwitch (void);
void KT_MicTX_Next_Fre (void); // KT_MicTX��100KHz
void KT_MicTX_Previous_Fre (void); // KT_MicTX��100KHz
void KT_MicTX_Mute (void); // KT_MicTX����
void ex2Init(void);
void timer0Init(void);
void KT_MicTX_Init (void); // KT_MicTX��ʼ��
void KEY_UP (void);
void KEY_DOWN (void);
void KEY_DIS (void);
void KT_MicTX_PowerDown_Detecter (void);

//-----------------------------------------------------------------------------
// LCD_KEY Function PROTOTYPES
//-----------------------------------------------------------------------------
void Delay_ms(UINT16 iTime_Number);
void Delay_us(UINT8 iTime_Number);
UINT8 Key_Scan (void);
void LCD_Init(void);
void Scan_segs(UINT8 dByte, UINT16 Tscan);
void SendBit_1621(UINT8 cSenddata, UINT8 cCounter);
void SendComBit_1621(UINT8 cSenddata); //data�ĵ�λ��д��HT1621����λ��ǰ
void WriteFix_1621(UINT16 iSenddata);
void Write_1621(UINT8 cAddr,UINT8 cCom);
void Display_Freq_Num(UINT8 cAddress,UINT8 cNum);
void Display_Frequency_and_RFPower(INT32 lFreq);
void RF_Power(UINT8 cPower_Level);
void Display_Ch_Num(UINT8 address, UINT8 num);

//-----------------------------------------------------------------------------
// I2C Function PROTOTYPES
//-----------------------------------------------------------------------------
void I2C_Delay(void);                                            
void I2C_Start(void);
void I2C_Senddata(UINT8 senddata);
void I2C_Ack(void);
void I2C_Stop(void);
UINT8 I2C_Receivedata(void);
void I2C_Word_Write(UINT8 device_address, UINT8 reg_add, UINT16 writeword);
UINT16 I2C_Word_Read(UINT8 device_address, UINT8 reg_add);

//-----------------------------------------------------------------------------
// IR_SEND Function PROTOTYPES
//-----------------------------------------------------------------------------
void H_26us(UINT8 udelay);
void L_26us(UINT8 udelay);
void IR_8byte(UINT8 udata);
void IR_send(UINT32 CHAN);

