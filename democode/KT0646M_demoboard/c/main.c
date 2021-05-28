//*****************************************************************************
//  File Name: main.c
//  Function:  KT Wireless Mic Transmitter Products Demoboard
//*****************************************************************************
//        Revision History
//  Version    Date        Description
//  V1.0    2016-04-26  ��ʼ�汾
//  V1.1    2017-02-08  ��ʽ�淶������
//  V0.3    2017-04-27  �Ӽ�Ƶ�ʵ�ʱ���Ȱѵ�Ƶ���ˣ�tune��̨���ٻָ�ԭ����Ƶ�����ã�main.c��
//						��̨��һֱ����ͬ�Ĳ�������tunę�������һ��ʱ��󲽽����4����10����main.c��
//*****************************************************************************

//-----------------------------------------------------------------------------
// Includes
//-----------------------------------------------------------------------------
#include "KT_WirelessMicTxdrv.h"

//-----------------------------------------------------------------------------
// Global VARIABLES
//-----------------------------------------------------------------------------
#ifdef IR_RECEIVE
extern UINT16 IR_Counter;
extern BOOL Int_Mode_Flag;
extern UINT8 xdata IRDataCode[4];
#endif

BOOL temp_RF_POW_SW=0; //���书��״̬��ʱ�洢


//-----------------------------------------------------------------------------
//�� �� ����main
//����������������
//����˵����
//ȫ�ֱ�������
//��    �룺
//��    �أ���
//�� �� �ߣ�Zhou Dongfeng            ʱ�䣺2015-12-28
//�� �� �ߣ�Zhou Dongfeng            ʱ�䣺2016-01-28
//��    ����V2.0        �������Զ���̨������Ƶѡ��        
//-----------------------------------------------------------------------------
void main (void)
{
    UINT32 lCounter=0x20000;
    
    PORT_Init ();    
    SYSCLK_Init ();                                        
    LCD_Init();
    
#ifdef IR_RECEIVE             
    timer0Init();
    ex2Init();
#endif

    while(!KT_WirelessMicTx_PreInit());
       while(!KT_WirelessMicTx_Init());
    KT_MicTX_Init();
    
    while (1)
    {
         if ((lCounter >= 0x20000))
        {
            LCD_LED = 1; // �ر���
            KT_MicTX_Batter_Detecter();
            if(RF_POW_SW != temp_RF_POW_SW)
            {
                KT_MicTX_RFSwitch();
            }
            lCounter=0;
        } 
        else
        {
            lCounter++;
        }
        KT_MicTX_PowerDown_Detecter();
        switch(Key_Scan())
        {
            case 1    :    LCD_LED = 0;    KT_MicTX_Next_Fre();        lCounter=0;    break;
            case 2    :    LCD_LED = 0;    KT_MicTX_Previous_Fre();    lCounter=0;    break;
            case 3    :    LCD_LED = 0;    KT_MicTX_Mute();            lCounter=0;    break;
            default    :    Key_UP_flag=0;    Key_DOWN_flag=0;            break; 
        }
        
#ifdef IR_RECEIVE
//IRDataCode[1]�ĸ�4bitΪͨ����ַ������A��B·�ֱ�����8bitΪƵ����Ϣ�����λ��
//IRDataCode[2]ΪƵ����Ϣ����λ��IRDataCode[3]ΪƵ����Ϣ�����λ
        if(KT_IRB_ADDRESS == (IRDataCode[1] & 0xF0) )
        {
            IRDataCode[1] &= 0x0F;
//            EA=0;
            Memery_Frequency = *((INT32 xdata*)IRDataCode);
            KT_WirelessMicTx_Tune(Memery_Frequency);
            Display_Frequency_and_RFPower(Memery_Frequency);
//            Save_Freq();
//            EA=1;
        }
#endif
    }
}

//-----------------------------------------------------------------------------
//�� �� ����KT_MicTX_Init
//����������оƬ��ʼ��
//����˵����
//ȫ�ֱ�����Memery_Frequency; Load_Frequency;
//��    �룺
//��    �أ���
//�� �� �ߣ�KANG Hekai                ʱ�䣺2012-08-01
//�� �� �ߣ�Zhou Dongfeng            ʱ�䣺2015-12-28
//��    ����V1.0
//-----------------------------------------------------------------------------
void KT_MicTX_Init(void)
{
    Load_Freq();
    Memery_Frequency=Load_Frequency;
    KT_WirelessMicTx_Tune(Memery_Frequency);
    KT_WirelessMicTx_EQGAIN(EQ_25H,EQ_GAIN_0dB);
    KT_WirelessMicTx_EQGAIN(EQ_40H,EQ_GAIN_0dB);
    KT_WirelessMicTx_EQGAIN(EQ_63H,EQ_GAIN_0dB);

    KT_WirelessMicTx_EQGAIN(EQ_100H,EQ_GAIN_0dB);
    KT_WirelessMicTx_EQGAIN(EQ_160H,EQ_GAIN_0dB);
    KT_WirelessMicTx_EQGAIN(EQ_250H,EQ_GAIN_0dB);

    KT_WirelessMicTx_EQGAIN(EQ_400H,EQ_GAIN_0dB);
    KT_WirelessMicTx_EQGAIN(EQ_630H,EQ_GAIN_0dB);
    KT_WirelessMicTx_EQGAIN(EQ_1KH,EQ_GAIN_0dB);

    KT_WirelessMicTx_EQGAIN(EQ_1K6,EQ_GAIN_0dB);
    KT_WirelessMicTx_EQGAIN(EQ_2K5,EQ_GAIN_0dB);
    KT_WirelessMicTx_EQGAIN(EQ_4KH,EQ_GAIN_0dB);

    KT_WirelessMicTx_EQGAIN(EQ_6K3,EQ_GAIN_0dB);
    KT_WirelessMicTx_EQGAIN(EQ_10K,EQ_GAIN_0dB);
    KT_WirelessMicTx_EQGAIN(EQ_16K,EQ_GAIN_0dB);

    KT_WirelessMicTx_EQSW(EQ_DISABLE);
    KT_WirelessMicTx_ECHO(ECHO_DISABLE,ECHO_RATIO_0,ECHO_DELAY_22ms);
    Delay_ms(200);
        
    KT_MicTX_RFSwitch();
    KT_WirelessMicTx_PASW(PA_ON);

    KT_WirelessMicTx_Pilot_Fdev(PILOT_FDEV_5K);
    KT_WirelessMicTx_Pilot(PILOT_ENABLE);
    WriteFix_1621(LCD_PILOT);
}

//-----------------------------------------------------------------------------
//�� �� ����PORT_Init
//����������MCU�˿ڳ�ʼ��
//����˵����Configure the Crossbar and GPIO ports.
//ȫ�ֱ�������
//��    �룺
//��    �أ���
//�� �� �ߣ�Zhou Dongfeng            ʱ�䣺2015-12-22
//�� �� �ߣ�                        ʱ�䣺
//��    ����V1.0                
//-----------------------------------------------------------------------------
void PORT_Init(void) 
{
    //  PX M0 M1 ����IO��״̬��
    //��Ϊ 0  0 ��Ϊ ׼˫��ģʽ��
    //��Ϊ 0  1 ��Ϊ �������ģʽ��
    //��Ϊ 1  0 ��Ϊ ����ģʽ(����̬)��
    //��Ϊ 1  1 ��Ϊ ��©ģʽ��
    P1M0 = 0x44;     
    P1M1 = 0x83;    
    P1     = 0xbc;
      
    P3M0 = 0x01;
    P3M1 = 0xb3;
    P3     = 0x7c;    

    P4M0 = 0x01;                 
    P4M1 = 0x02;       
    P4     = 0x04;
}

//-----------------------------------------------------------------------------
//�� �� ����SYSCLK_Init
//����������MCUʱ�ӳ�ʼ��
//����˵����use the internal 16.6MHz
//ȫ�ֱ�������
//��    �룺
//��    �أ���
//�� �� �ߣ�Zhou Dongfeng            ʱ�䣺2014-04-11
//�� �� �ߣ�                        ʱ�䣺
//��    ����V1.0                
//-----------------------------------------------------------------------------
void SYSCLK_Init(void)
{
    CLKCON = 0x00; //  f SYS = fOSCS =16.6MHz     
//    CLKCON = 0x20; //  f SYS = fOSCS1/2
//    CLKCON = 0x40; //  f SYS = fOSCS1/4
    //CLKCON = 0x60; //  f SYS = fOSCS1/12
    //ADCON  = 0x00;
    //CMPCON = 0x00;  
}

//-----------------------------------------------------------------------------
//�� �� ����KT_MicTX_PowerDown_Detecter
//�����������ػ�����
//����˵����
//ȫ�ֱ�����
//��    �룺��
//��    �أ���
//�� �� �ߣ�Zhou Dongfeng            ʱ�䣺2015-12-28
//�� �� �ߣ�                        ʱ�䣺
//��    ����V1.0                                        
//-----------------------------------------------------------------------------
void KT_MicTX_PowerDown_Detecter (void)
{
    if(VBAT_IN == 0)
    {
        Delay_ms(5);
        if(VBAT_IN == 0) //��ֹ���ݷŵ粻�ɾ������ϵ�
        {    
            if(    Memery_Frequency != Load_Frequency )
                Save_Freq();
            KT_WirelessMicTx_PowerDownProcedure();    
            LDO_CTRL = 0;
            Delay_ms(15);
            if(LDO_CTRL==0)
            {
                (*((void (code*)(void))0x0000))();
            }
        }
    }
}

//-----------------------------------------------------------------------------
//�� �� ����KT_MicTX_Batter_Detecter
//������������ص�ѹ��Ⲣ��ʾ
//����˵����
//ȫ�ֱ�������
//��    �룺
//��    �أ���
//�� �� �ߣ�KANG Hekai                ʱ�䣺2012-08-01
//�� �� �ߣ�                        ʱ�䣺
//��    ����V1.0
//-----------------------------------------------------------------------------
void KT_MicTX_Batter_Detecter (void)
{
    UINT16 xdata Batter_Voltage;

    Batter_Voltage = KT_WirelessMicTx_BatteryMeter_Read();

    if( (Batter_Voltage <= BATTERY_MAX) && (Batter_Voltage > BATTERY_HIGHTH) )
    {
        WriteFix_1621(LCD_BATH);
    }
    else if( (Batter_Voltage <= BATTERY_HIGHTH) && (Batter_Voltage > BATTERY_MIDDLETH) )
    {
        WriteFix_1621(LCD_BATM);
    }
    else if( (Batter_Voltage <= BATTERY_MIDDLETH) && (Batter_Voltage > BATTERY_LOWTH) )
    {
        WriteFix_1621(LCD_BATL);
    }
    else
    { 
        WriteFix_1621(LCD_BATZ);
    }
}

//-----------------------------------------------------------------------------
//�� �� ����KT_MicTX_RFSwitch
//�������������书���л�
//����˵����
//ȫ�ֱ�����temp_RF_POW_SW
//��    �룺
//��    �أ���
//�� �� �ߣ�KANG Hekai                ʱ�䣺2012-08-01
//�� �� �ߣ�                        ʱ�䣺
//��    ����V1.0
//-----------------------------------------------------------------------------
void KT_MicTX_RFSwitch (void)
{
    if (RF_POW_SW == 0)
    {
        if(Key_RF_POW_flag)//ȥ��
            Delay_ms(100);
        if (RF_POW_SW == 0) 
        {
            KT_WirelessMicTx_PAGain(10); //���10dBm������7dBm
            RF_Power(3);
        }
    }
    else
    {
        if(Key_RF_POW_flag)//ȥ��
            Delay_ms(100); 
        if (RF_POW_SW == 1)    
        {
            KT_WirelessMicTx_PAGain(42); //���18dBm������15dBm
            RF_Power(7);
        }
    }
    temp_RF_POW_SW = RF_POW_SW;
    Display_Frequency_and_RFPower(Memery_Frequency);
}

//-----------------------------------------------------------------------------
//�� �� ����KT_MicTX_Next_Fre
//����������Ƶ�ʼ�BAND_STEP��������4����BAND_STEP����������40����BAND_STEP
//����˵����
//ȫ�ֱ�����Memery_Frequency; Key_UP_flag; Key_DOWN_flag;
//��    �룺
//��    �أ���
//�� �� �ߣ�KANG Hekai                ʱ�䣺2012-08-01
//�� �� �ߣ�KANG Hekai                ʱ�䣺2013-03-29
//��    ����V1.2
//          V1.5    2013-03-29    �л�Ƶ�ʺ���RF���ص�λ�þ������书��
//  		V1.6    2017-04-27    ��Ƶ�ʵ�ʱ���Ȱѵ�Ƶ���ˣ�tune��̨���ٻָ�ԭ����Ƶ������
//								  ��̨��һֱ����ͬ�Ĳ�������tunę�������һ��ʱ��󲽽����4����10��
//-----------------------------------------------------------------------------
void KT_MicTX_Next_Fre (void) // ��250KHz
{
    UINT16 pilotSave;
	Key_RF_POW_flag = 0;
	pilotSave=KT_Bus_Read(0x1F);	  //����Ƶ������
 	KT_WirelessMicTx_Pilot(PILOT_DISABLE);
    KT_WirelessMicTx_PAGain(0);
    KT_WirelessMicTx_PASW(PA_OFF);                        
    Delay_ms(5);

    do
    {
        Delay_ms(100);
        Memery_Frequency = Memery_Frequency + BAND_STEP;
        if((Memery_Frequency > BAND_TOP) || (Memery_Frequency < BAND_BOTTOM))
		{
        	Memery_Frequency = BAND_BOTTOM;
		}
		Display_Frequency_and_RFPower(Memery_Frequency);
    }while(Key_UP==0);

    KT_WirelessMicTx_Tune(Memery_Frequency);
    KT_MicTX_RFSwitch();
    KT_WirelessMicTx_PASW(PA_ON);
	KT_Bus_Write(0x1F,pilotSave);//�ָ���Ƶ������
    Key_RF_POW_flag = 1;
}

//-----------------------------------------------------------------------------
//�� �� ����KT_MicTX_Previous_Fre
//����������Ƶ�ʼ�BAND_STEP��������4����BAND_STEP����������20����BAND_STEP
//����˵����
//ȫ�ֱ�����Memery_Frequency; Key_UP_flag; Key_DOWN_flag;
//��    �룺
//��    �أ���
//�� �� �ߣ�KANG Hekai                ʱ�䣺2012-08-01
//�� �� �ߣ�KANG Hekai                ʱ�䣺2013-03-29
//��    ����V1.2
//          V1.5    2013-03-29    �л�Ƶ�ʺ���RF���ص�λ�þ������书��
//  		V1.6    2017-04-27    ��Ƶ�ʵ�ʱ���Ȱѵ�Ƶ���ˣ�tune��̨���ٻָ�ԭ����Ƶ������
//								  ��̨��һֱ����ͬ�Ĳ�������tunę�������һ��ʱ��󲽽����4����10��
//-----------------------------------------------------------------------------
void KT_MicTX_Previous_Fre (void) // ��250KHz
{
    UINT16 pilotSave;
	Key_RF_POW_flag = 0;
	pilotSave=KT_Bus_Read(0x1F);	  //����Ƶ������
	KT_WirelessMicTx_Pilot(PILOT_DISABLE);
    KT_WirelessMicTx_PAGain(0);
    KT_WirelessMicTx_PASW(PA_OFF);                    
    Delay_ms(5);

	do
    {
        Delay_ms(100);
        Memery_Frequency = Memery_Frequency - BAND_STEP;
        if((Memery_Frequency > BAND_TOP) || (Memery_Frequency < BAND_BOTTOM))
		{
        	Memery_Frequency = BAND_TOP;
		}
		Display_Frequency_and_RFPower(Memery_Frequency);
    }while(Key_DOWN==0);

    KT_WirelessMicTx_Tune(Memery_Frequency);
    KT_MicTX_RFSwitch();
    KT_WirelessMicTx_PASW(PA_ON);
	KT_Bus_Write(0x1F,pilotSave);//�ָ���Ƶ������
    Key_RF_POW_flag = 1;
}

//-----------------------------------------------------------------------------
//�� �� ����KT_MicTX_Mute
//���������������ھ�������������ģʽ�����ر仯
//����˵����
//ȫ�ֱ�����Key_UP_flag; Key_DOWN_flag;
//��    �룺
//��    �أ���
//�� �� �ߣ�KANG Hekai                ʱ�䣺2012-08-01
//�� �� �ߣ�                        ʱ�䣺
//��    ����V1.0
//-----------------------------------------------------------------------------
void KT_MicTX_Mute (void)
{
    UINT16 reg1C;

    reg1C = KT_Bus_Read(0x1C);
    if( (reg1C & 0x0001) == 0) // �������¼�龲����־λ�����������־Ϊ������
    {
        KT_WirelessMicTx_MuteSel(AUDIO_MUTE);
        KT_WirelessMicTx_Pilot(PILOT_DISABLE);
        WriteFix_1621(LCD_MUTE);    
    }
    else // �������¼�龲����־λ�����������־Ϊ����ȡ������
    {
        KT_WirelessMicTx_MuteSel(AUDIO_UNMUTE);
        KT_WirelessMicTx_Pilot(PILOT_ENABLE);
        WriteFix_1621(LCD_UNMUTE);    
    }
    Key_UP_flag=0;
    Key_DOWN_flag=0;
}

//-----------------------------------------------------------------------------
//�� �� ����Erase_Eeprom
//��������������EEPROM
//����˵����
//ȫ�ֱ�������
//��    �룺uchar page
//��    �أ���
//�� �� �ߣ�Zhou Dongfeng            ʱ�䣺2015-12-23
//�� �� �ߣ�                        ʱ�䣺
//��    ����V1.0                
//-----------------------------------------------------------------------------
void Erase_Eeprom (UINT8 page)
{
    EA = 0;    //Disable global interrupt
    FLASHCON = 0x01;    // for EEPROM
    
    XPAGE = page;

    IB_CON1 = 0xE6;    //sector erase
    IB_CON2 = 0x05;
    IB_CON3 = 0x0A;
    IB_CON4 = 0x09;
    IB_CON5 = 0x06;
    _nop_();        // these 4 nops are necessary
    _nop_();
    _nop_();
    _nop_();
    FLASHCON = 0x00;    // restore FLASHCON
    XPAGE = 0x00;    // clear XPAGE
    EA = 1;
}

//-----------------------------------------------------------------------------
//�� �� ����Write_Eeprom
//����������EEPROMд����
//����˵����EEPROM,��ָ��λ��д��һ���ֽ�����
//ȫ�ֱ�������
//��    �룺wr_data:Ҫд������ݡ�offset��λ��
//��    �أ���
//�� �� �ߣ�Zhou Dongfeng            ʱ�䣺2015-12-23
//�� �� �ߣ�                        ʱ�䣺
//��    ����V1.0                
//-----------------------------------------------------------------------------
void Write_Eeprom(UINT8 wr_data,UINT8 page,UINT8 offset)
{ 
    EA = 0;    //Disable global interrupt
    FLASHCON = 0x01;    // for EEPROM
    XPAGE =  page;
    IB_OFFSET = offset;
    IB_DATA = wr_data;

    IB_CON1 = 0x6E;    //program one byte
    IB_CON2 = 0x05;
    IB_CON3 = 0x0A;
    IB_CON4 = 0x09;
    IB_CON5 = 0x06;
    _nop_();        // these 4 nops are necessary           
    _nop_();                                                         
    _nop_();
    _nop_();
    FLASHCON = 0x00;    // restore FLASHCON
    XPAGE = 0x00;    // clear XPAGE
    EA = 1;
}

//-----------------------------------------------------------------------------
//�� �� ����Read_Eeprom
//����������EEPROM��Byte����
//����˵������ȡEEPROMָ��λ���ֽ�����
//ȫ�ֱ�������
//��    �룺addr:��ַ
//��    �أ�����
//�� �� �ߣ�Zhou Dongfeng            ʱ�䣺2015-12-23
//�� �� �ߣ�                        ʱ�䣺
//��    ����V1.0                
//-----------------------------------------------------------------------------
UINT8 Read_Eeprom(UINT8 code *addr)
{
    UINT8 num = 0;

    FLASHCON |= 0x01;    //FAC = 1     choose the information block
    num = *(addr);

    FLASHCON &= 0xFE;    //FAC = 0     choose the main block
    return num;
}

//-----------------------------------------------------------------------------
//�� �� ����Load_Freq
//������������ȡ������MCU��FLASH���Ƶ��ֵ
//����˵����
//ȫ�ֱ�����Load_Frequency
//��    �룺
//��    �أ���
//�� �� �ߣ�KANG Hekai                ʱ�䣺2012-08-01
//�� �� �ߣ�                        ʱ�䣺
//��    ����V1.0
//-----------------------------------------------------------------------------
void Load_Freq (void)
{
    INT8 i;
    Load_Frequency=0;
    for(i=2;i>=0;i--)
    {
        Load_Frequency = (Load_Frequency<<8) | Read_Eeprom((UINT8 code *)i);
    }
}

//-----------------------------------------------------------------------------
//�� �� ����Save_Freq
//������������Ƶ�ʱ�����MCU��FLASH��
//����˵����
//ȫ�ֱ�����Memery_Frequency
//��    �룺
//��    �أ���
//�� �� �ߣ�KANG Hekai                ʱ�䣺2012-08-01
//�� �� �ߣ�                        ʱ�䣺
//��    ����V1.0
//-----------------------------------------------------------------------------
void Save_Freq (void)
{
    INT8 i;
    UINT8 a[4];
    a[0]= Memery_Frequency;
    a[1]= Memery_Frequency>>8;
    a[2]= Memery_Frequency>>16;
    a[3]= Memery_Frequency>>24;
    Erase_Eeprom(0);
    for(i=3;i>=0;i--)
    {
        Write_Eeprom(a[i],0,i);
    }
}

#ifdef IR_RECEIVE
//

//-----------------------------------------------------------------------------
//�� �� ����timer0Init
//������������ʱ��0��ʼ��
//����˵����default 1/12 system clock
//ȫ�ֱ�������
//��    �룺��
//��    �أ���
//�� �� �ߣ�PAE                     ʱ�䣺2012-08-01
//�� �� �ߣ�                        ʱ�䣺
//��    ����V1.0
//-----------------------------------------------------------------------------
void timer0Init(void)
{
    TCON1 = 0x00;
    TMOD = 0x01;//timer0 16bit
    TL0 = 0;
    TH0 = 0;
}

//-----------------------------------------------------------------------------
//�� �� ����ex2Init
//�����������ⲿ�ж�2��ʼ��
//����˵����
//ȫ�ֱ�������
//��    �룺��
//��    �أ���
//�� �� �ߣ�PAE                     ʱ�䣺2012-08-01
//�� �� �ߣ�                        ʱ�䣺
//��    ����V1.0
//-----------------------------------------------------------------------------
void ex2Init(void)
{    
    EXF0 = 0x04;//�½��ش���
    IEN1 |= 0x04;//ex2=1
    EA = 1;
}

//-----------------------------------------------------------------------------
//�� �� ����ex2Int
//�����������ⲿ�ж�2�жϷ������
//����˵����
//ȫ�ֱ�������
//��    �룺��
//��    �أ���
//�� �� �ߣ�PAE                     ʱ�䣺2012-08-01
//�� �� �ߣ�                        ʱ�䣺
//��    ����V1.0
//-----------------------------------------------------------------------------
void ex2Int(void) interrupt 9
{
    IEN1 &= ~0x04; //EX2=0���ⲿ�ж�2
    TR0 = 0; //ֹͣ��ʱ��0
    IR_Counter = TH0;
    IR_Counter = (IR_Counter << 8) | TL0;
    TL0 = 0;
    TH0 = 0;
    TR0 = 1; //������ʱ��0 
    if(EXF0==0x08)
    {Int_Mode_Flag=0;}
    else
    {Int_Mode_Flag=1;}
    EXF0 ^=0x0c;
    //������빦����ʱû�����
    //Task_IR();
    IEN1 |= 0x04; //EX2=1���ⲿ�ж�2ʹ��
}
#endif

