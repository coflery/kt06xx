//*****************************************************************************
//  File Name: LCD_KEY.c
//  Function:  KT Wireless Mic Transmitter Products Handheld Demoboard LCD AND KEY Function Define
//*****************************************************************************
//        Revision History
//  Version Date        Description
//  V1.0    2012-08-01  Initial draft
//  V1.1    2013-11-22  �ı�������Ͷ��巽��
//  V1.2    2017-02-08  ��ʽ�淶������
//  V0.3    2017-04-27  �Ӽ�Ƶ�ʵ�ʱ���Ȱѵ�Ƶ���ˣ�tune��̨���ٻָ�ԭ����Ƶ�����ã�main.c��
//						��̨��һֱ����ͬ�Ĳ�������tunę�������һ��ʱ��󲽽����4����10����main.c��
//-----------------------------------------------------------------------------
// Includes
//-----------------------------------------------------------------------------
#include "KT_WirelessMicTxdrv.h"

//1621��ʾ��Ƶ��ֵ��ʾ����
UINT8 code FREQ_NUM[] ={    FREQ_ZERO_A,    FREQ_ZERO_B,    FREQ_ZERO_C,    FREQ_ZERO_D,
                            FREQ_ONE_A,     FREQ_ONE_B,     FREQ_ONE_C,     FREQ_ONE_D,     
                            FREQ_TWO_A,     FREQ_TWO_B,     FREQ_TWO_C,     FREQ_TWO_D,     
                            FREQ_THREE_A,   FREQ_THREE_B,   FREQ_THREE_C,   FREQ_THREE_D,
                            FREQ_FOUR_A,    FREQ_FOUR_B,    FREQ_FOUR_C,    FREQ_FOUR_D,    
                            FREQ_FIVE_A,    FREQ_FIVE_B,    FREQ_FIVE_C,    FREQ_FIVE_D,
                            FREQ_SIX_A,     FREQ_SIX_B,     FREQ_SIX_C,     FREQ_SIX_D,  
                            FREQ_SEVEN_A,   FREQ_SEVEN_B,   FREQ_SEVEN_C,   FREQ_SEVEN_D,
                            FREQ_EIGHT_A,   FREQ_EIGHT_B,   FREQ_EIGHT_C,   FREQ_EIGHT_D,
                            FREQ_NINE_A,    FREQ_NINE_B,    FREQ_NINE_C,    FREQ_NINE_D
                        };

//1621��ʾ��ͨ��ֵ��ʾ����
UINT8 code CH_NUM[] ={  CH_ZERO_A,   CH_ZERO_B, 
                        CH_ONE_A,    CH_ONE_B,     
                        CH_TWO_A,    CH_TWO_B,     
                        CH_THREE_A,  CH_THREE_B,
                        CH_FOUR_A,   CH_FOUR_B ,
                        CH_FIVE_A,   CH_FIVE_B ,
                        CH_SIX_A,    CH_SIX_B ,    
                        CH_SEVEN_A,  CH_SEVEN_B,
                        CH_EIGHT_A,  CH_EIGHT_B,
                        CH_NINE_A,   CH_NINE_B
                    };

//1621��ʾ��RF�ź�ǿ����ʾ����
UINT8 xdata RF = 0<<3;
UINT8 xdata RF_S1 = 0<<2;
UINT8 xdata RF_S2 = 0<<3;
UINT8 xdata RF_S3 = 0<<3;
UINT8 xdata RF_S4 = 0<<3;
UINT8 xdata RF_S5 = 0<<3;
UINT8 xdata RF_S6 = 0<<2;
UINT8 xdata RF_S7 = 0<<3;


//1621��ʾ�������־��ʾ����
UINT8 xdata Dot = 1<<2,K4 = 0<<3,MHz = 1<<3;

//1621��ʾ��Audio�ź�ǿ����ʾ����
UINT8 xdata AF = 0<<3;
UINT8 xdata AF_S8 = 0<<2;
UINT8 xdata AF_S9 = 0<<2;
UINT8 xdata AF_S10 = 0<<1;
UINT8 xdata AF_S11 = 0<<0;
UINT8 xdata AF_S12 = 0<<3;
UINT8 xdata AF_S13 = 0<<2;
UINT8 xdata AF_S14 = 0<<3;

//-----------------------------------------------------------------------------
//�� �� ����Delay_us                                                              
//����������us����ʱ                                                             
//����˵����                                                                     
//ȫ�ֱ�������                                                                     
//��    �룺iTime_Number                                                                     
//��    �أ���                                                                     
//�� �� �ߣ�ZDF                     ʱ�䣺2012-08-01                                         
//�� �� �ߣ�                        ʱ�䣺                                         
//��    ����                                                                     
//-----------------------------------------------------------------------------
void Delay_us(UINT8 iTime_Number)
{
    UINT8 i;

    for(i=0;i<=iTime_Number;i++)
    {
        _nop_();
    }
}

//-----------------------------------------------------------------------------
//�� �� ����Delay_ms
//����������ms����ʱ
//����˵����
//ȫ�ֱ�������
//��    �룺iTime_Number
//��    �أ���
//�� �� �ߣ�Zhou Dongfeng           ʱ�䣺2015-12-23
//�� �� �ߣ�                        ʱ�䣺
//��    ����V1.0
//-----------------------------------------------------------------------------
void Delay_ms(UINT16 iTime_Number)
{
    UINT16 i;
    UINT16 j;

    for (j=0;j<iTime_Number;j++)
    {
        for (i=0;i<1035;i++)
        {
            _nop_();
        }
    }
}

//-----------------------------------------------------------------------------
//�� �� ����Key_Scan
//��������������ɨ�����
//����˵����
//ȫ�ֱ�������
//��    �룺��
//��    �أ�key_value
//�� �� �ߣ�Kanghekai               ʱ�䣺2012-08-01
//�� �� �ߣ�                        ʱ�䣺
//��    ����
//-----------------------------------------------------------------------------
UINT8 Key_Scan (void)
{
    INT8 key_value=0;

    if(Key_UP==0) // �ж��Ƿ��м�����
    {
        Delay_ms(100); // ��ʱȥ����
        if(Key_UP==0)
            key_value=1;
    }
    else if(Key_DOWN==0) // �ж��Ƿ��м�����
    {
        Delay_ms(100); // ��ʱȥ����
        if (Key_DOWN==0)    
            key_value=2;
    }
    else if(Key_SET==0) // �ж��Ƿ��м�����
    {
        Delay_ms(100); // ��ʱȥ����
        if (Key_SET==0)    
            key_value=3;
    }
    else
        key_value=0;
    return(key_value);
}

//-----------------------------------------------------------------------------
//�� �� ����LCD_Init                                                              
//����������LCD��ʼ��                                                             
//����˵����                                                                     
//ȫ�ֱ�������                                                                     
//��    �룺��                                                                     
//��    �أ���                                                                     
//�� �� �ߣ�Kanghekai               ʱ�䣺2012-08-01                                         
//�� �� �ߣ�                        ʱ�䣺                                         
//��    ����                                                                     
//-----------------------------------------------------------------------------
void LCD_Init(void)
{
    LCD_LED=0; // ������

    LCD_CS = 1;
    Delay_us(50);
    LCD_CS = 0;
    Delay_us(10);
    SendBit_1621(CMD_MODE,    3);
    SendBit_1621(SYS_EN,    9);
    SendBit_1621(INT_256K,    9);
    SendBit_1621(LCD_BIAS,    9);
    SendBit_1621(LCD_ON,    9);

    Scan_segs(0x00,0);

//K
    Write_1621(0,0x0B);
    Write_1621(1,0);
    Write_1621(2,5);
    Write_1621(3,0);
//T
    Write_1621(4,0);
    Write_1621(5,5);
    Write_1621(6,0);
    Write_1621(7,0);

#ifdef KT0606M
//0606
    Display_Freq_Num(2,0);
    Display_Freq_Num(3,6);
    Display_Freq_Num(4,0);
    Display_Freq_Num(5,6);
#endif

#ifdef KT0605M
//0605
    Display_Freq_Num(2,0);
    Display_Freq_Num(3,6);
    Display_Freq_Num(4,0);
    Display_Freq_Num(5,5);
#endif

#ifdef KT0616M
//0616
    Display_Freq_Num(2,0);
    Display_Freq_Num(3,6);
    Display_Freq_Num(4,1);
    Display_Freq_Num(5,6);
#endif

#ifdef KT0646M
//0616
    Display_Freq_Num(2,0);
    Display_Freq_Num(3,6);
    Display_Freq_Num(4,4);
    Display_Freq_Num(5,6);
#endif

    Delay_ms(600);
    Scan_segs(0x00,0);
}

//-----------------------------------------------------------------------------
//�� �� ����SendBit_1621                                                          
//��������������ģʽ                                                             
//����˵����                                                                     
//ȫ�ֱ�������                                                                     
//��    �룺cSenddata;cCounter                                                                 
//��    �أ���                                                                     
//�� �� �ߣ�Kanghekai               ʱ�䣺2012-08-01                                         
//�� �� �ߣ�                        ʱ�䣺                                         
//��    ����                                                                     
//-----------------------------------------------------------------------------
void SendBit_1621(UINT8 cSenddata, UINT8 cCounter) //data�ĸ�λ��д��HT1621����λ��ǰ
{
    UINT8 i;

    LCD_WR = 0;
    for (i = 0; i < cCounter; i++)
    {
        LCD_DATA = cSenddata & 0x80;
        cSenddata = cSenddata << 1;
        Delay_us(20);
        LCD_WR = 1;
        Delay_us(20);
        LCD_WR = 0;
        Delay_us(20);
    }
}

//-----------------------------------------------------------------------------
//�� �� ����SendComBit_1621                                                              
//����������д����                                                                 
//����˵����                                                                     
//ȫ�ֱ�������                                                                     
//��    �룺cSenddata                                                                 
//��    �أ���                                                                     
//�� �� �ߣ�Kanghekai               ʱ�䣺2012-08-01                                         
//�� �� �ߣ�                        ʱ�䣺                                         
//��    ����                                                                     
//-----------------------------------------------------------------------------
void SendComBit_1621(UINT8 cSenddata) //data�ĵ�λ��д��HT1621����λ��ǰ
{
    UINT8 i;

    for(i =0; i <4; i ++)
    {
        LCD_DATA = cSenddata & 0x01;
        cSenddata = cSenddata >> 1;
        Delay_us(20);
        LCD_WR = 1;
        Delay_us(20);
        LCD_WR = 0;
        Delay_us(20);
    }
}

//-----------------------------------------------------------------------------
//�� �� ����WriteFix_1621                                                              
//����������д����                                                                 
//����˵����                                                                     
//ȫ�ֱ�������                                                                     
//��    �룺iSenddata                                                                 
//��    �أ���                                                                     
//�� �� �ߣ�Kanghekai               ʱ�䣺2012-08-01                                         
//�� �� �ߣ�                        ʱ�䣺                                         
//��    ����                                                                     
//-----------------------------------------------------------------------------
void WriteFix_1621(UINT16 iSenddata)
{
    Write_1621(iSenddata>>4,iSenddata);
}

//-----------------------------------------------------------------------------
//�� �� ����Write_1621                                                                  
//����������д��ַ                                                                 
//����˵����                                                                     
//ȫ�ֱ�������                                                                     
//��    �룺CAddr,cCom                                                                 
//��    �أ���                                                                     
//�� �� �ߣ�Kanghekai               ʱ�䣺2012-08-01                                         
//�� �� �ߣ�                        ʱ�䣺                                         
//��    ����                                                                     
//-----------------------------------------------------------------------------
void Write_1621(UINT8 cAddr,UINT8 cCom)
{
    LCD_CS = 1;
    Delay_us(50);
    LCD_CS = 0;
    Delay_us(10);
    cAddr = cAddr <<  2;
    SendBit_1621(WR_MODE,3);
    SendBit_1621(cAddr,6);
    SendComBit_1621(cCom);
    LCD_CS=1;
    Delay_us(50);
}

//-----------------------------------------------------------------------------
//�� �� ����Scan_segs                                                              
//����������������ʾ                                                             
//����˵����                                                                     
//ȫ�ֱ�������                                                                     
//��    �룺dByte;Tscan                                                             
//��    �أ���                                                                     
//�� �� �ߣ�ZDF                     ʱ�䣺2012-08-01                                         
//�� �� �ߣ�                        ʱ�䣺                                         
//��    ����                                                                     
//-----------------------------------------------------------------------------
void Scan_segs(UINT8 dByte, UINT16 Tscan)
{
    UINT8 segs;

    LCD_CS = 1;
    Delay_us(50);
    LCD_CS = 0;
    Delay_us(10);
    SendBit_1621(WR_MODE,3);
    SendBit_1621(0,6);
    for (segs = 0; segs < LCD_SEG; segs++)
    {
        SendComBit_1621(dByte);
        Delay_ms(Tscan);
    }
    LCD_CS=1;
    Delay_us(50);
}

//-----------------------------------------------------------------------------
//�� �� ����Display_Frequency_and_RFPower                                                      
//����������Ƶ�ʺͷ��书����ʾ                                                             
//����˵����                                                                     
//ȫ�ֱ�������                                                                     
//��    �룺lFreq                                                             
//��    �أ���                                                                     
//�� �� �ߣ�Kanghekai               ʱ�䣺2012-08-01                                     
//�� �� �ߣ�                        ʱ�䣺                                         
//��    ����                                                                     
//-----------------------------------------------------------------------------
void Display_Frequency_and_RFPower(INT32 lFreq)  
{
    UINT16 M_Fre,K_Fre;

    M_Fre = lFreq/1000;
    K_Fre = lFreq%1000;
    
    if( (M_Fre<1000) && (M_Fre>=100) )
    {
        Display_Freq_Num(0,M_Fre/100);
        M_Fre = M_Fre%100;
        Display_Freq_Num(1,M_Fre/10);
        Display_Freq_Num(2,M_Fre%10);
    }

    if (K_Fre==0) 
    {
        Display_Freq_Num(3,0);
        Display_Freq_Num(4,0);
        Display_Freq_Num(5,0);
    }
    else if((K_Fre < 10) && (K_Fre > 0) )
    {
        Display_Freq_Num(3,0);
        Display_Freq_Num(4,0);
        Display_Freq_Num(5,K_Fre);
    }
    else if( (K_Fre < 100) && (K_Fre >= 10) )
    {
        Display_Freq_Num(3,0);
        Display_Freq_Num(4,K_Fre / 10);
        Display_Freq_Num(5,K_Fre % 10);
    }            
    else if( (K_Fre < 1000) && (K_Fre >= 100) )
    {
        Display_Freq_Num(3,K_Fre / 100);
        K_Fre = K_Fre % 100;
        Display_Freq_Num(4,K_Fre / 10);
        Display_Freq_Num(5,K_Fre % 10);
    }

    Write_1621(31,0 | AF_S12 | AF_S11 | AF_S10 | AF_S9);
}

//-----------------------------------------------------------------------------
//�� �� ����RF_Power
//������������Ƶ���ʼ����л�
//����˵����
//ȫ�ֱ�����
//��    �룺cPower_Level
//��    �أ���
//�� �� �ߣ�Kanghekai               ʱ�䣺2012-08-01
//�� �� �ߣ�                        ʱ�䣺
//��    ����
//-----------------------------------------------------------------------------
void RF_Power(UINT8 cPower_Level)
{
    switch(cPower_Level)
    {
        case 0:
        {
            RF = 1<<3; 
            RF_S1 = 0<<2; 
            RF_S2 = 0<<3; 
            RF_S3 = 0<<3; 
            RF_S4 = 0<<3; 
            RF_S5 = 0<<3; 
            RF_S6 = 0<<2; 
            RF_S7 = 0<<3; 
        }break;
        case 1:
        { 
            RF = 1<<3; 
            RF_S1 = 1<<2; 
            RF_S2 = 0<<3; 
            RF_S3 = 0<<3; 
            RF_S4 = 0<<3;
            RF_S5 = 0<<3; 
            RF_S6 = 0<<2;
            RF_S7 = 0<<3; 
        }break;
        case 2:
        { 
            RF = 1<<3; 
            RF_S1 = 1<<2; 
            RF_S2 = 1<<3; 
            RF_S3 = 0<<3; 
            RF_S4 = 0<<3; 
            RF_S5 = 0<<3; 
            RF_S6 = 0<<2;    
            RF_S7 = 0<<3; 
        }break;
        case 3:
        {
            RF = 1<<3;
            RF_S1 = 1<<2; 
            RF_S2 = 1<<3; 
            RF_S3 = 1<<3;
            RF_S4 = 0<<3;
            RF_S5 = 0<<3;
            RF_S6 = 0<<2;
            RF_S7 = 0<<3;
        }break;
        case 4:
        { 
            RF = 1<<3; 
            RF_S1 = 1<<2; 
            RF_S2 = 1<<3;
            RF_S3 = 1<<3; 
            RF_S4 = 1<<3; 
            RF_S5 = 0<<3; 
            RF_S6 = 0<<2;
            RF_S7 = 0<<3; 
        }break;
        case 5:
        { 
            RF = 1<<3; 
            RF_S1 = 1<<2; 
            RF_S2 = 1<<3; 
            RF_S3 = 1<<3; 
            RF_S4 = 1<<3; 
            RF_S5 = 1<<3; 
            RF_S6 = 0<<2; 
            RF_S7 = 0<<3; 
        }break;
        case 6:
        { 
            RF = 1<<3; 
            RF_S1 = 1<<2; 
            RF_S2 = 1<<3;
            RF_S3 = 1<<3; 
            RF_S4 = 1<<3;
            RF_S5 = 1<<3; 
            RF_S6 = 1<<2; 
            RF_S7 = 0<<3; 
        }break;
        case 7:
        { 
            RF = 1<<3; 
            RF_S1 = 1<<2; 
            RF_S2 = 1<<3;
            RF_S3 = 1<<3; 
            RF_S4 = 1<<3; 
            RF_S5 = 1<<3; 
            RF_S6 = 1<<2; 
            RF_S7 = 1<<3; 
        }break;
        default: break;
    } 
}

#ifdef KT0616M
//-----------------------------------------------------------------------------
//�� �� ����Audio_Lever
//��������������ָʾ�����л�
//����˵����
//ȫ�ֱ�����
//��    �룺cAF_Level
//��    �أ���
//�� �� �ߣ�Kanghekai                ʱ�䣺2012-08-01
//�� �� �ߣ�                        ʱ�䣺
//��    ����
//-----------------------------------------------------------------------------
void Audio_Lever(UINT8 cAF_Level)
{
    switch(cAF_Level)
    {
        case 0:
        { 
            AF = 1<<3; 
            AF_S14 = 0<<3; 
            AF_S13 = 0<<2; 
            AF_S12 = 0<<3; 
            AF_S11 = 0<<0; 
            AF_S10 = 0<<1; 
            AF_S9 =  0<<2; 
            AF_S8 =  0<<2; 
        }break;
        case 1:
        { 
            AF = 1<<3; 
            AF_S14 = 1<<3; 
            AF_S13 = 0<<2; 
            AF_S12 = 0<<3; 
            AF_S11 = 0<<0;
            AF_S10 = 0<<1; 
            AF_S9  = 0<<2; 
            AF_S8  = 0<<2; 
        }break;
        case 2:
        { 
            AF = 1<<3; 
            AF_S14 = 1<<3; 
            AF_S13 = 1<<2; 
            AF_S12 = 0<<3; 
            AF_S11 = 0<<0; 
            AF_S10 = 0<<1; 
            AF_S9  = 0<<2; 
            AF_S8  = 0<<2; 
        }break;
        case 3:
        { 
            AF = 1<<3; 
            AF_S14 = 1<<3; 
            AF_S13 = 1<<2; 
            AF_S12 = 1<<3; 
            AF_S11 = 0<<0; 
            AF_S10 = 0<<1; 
            AF_S9  = 0<<2; 
            AF_S8  = 0<<2; 
        }break;
        case 4:
        { 
            AF = 1<<3; 
            AF_S14 = 1<<3; 
            AF_S13 = 1<<2; 
            AF_S12 = 1<<3; 
            AF_S11 = 1<<0; 
            AF_S10 = 0<<1; 
            AF_S9  = 0<<2; 
            AF_S8  = 0<<2; 
        }break;
        case 5:
        { 
            AF = 1<<3; 
            AF_S14 = 1<<3; 
            AF_S13 = 1<<2; 
            AF_S12 = 1<<3; 
            AF_S11 = 1<<0; 
            AF_S10 = 1<<1; 
            AF_S9  = 0<<2; 
            AF_S8  = 0<<2; 
        }break;
        case 6:
        { 
            AF = 1<<3; 
            AF_S14 = 1<<3; 
            AF_S13 = 1<<2; 
            AF_S12 = 1<<3; 
            AF_S11 = 1<<0; 
            AF_S10 = 1<<1; 
            AF_S9  = 1<<2;
            AF_S8  = 0<<2; 
        }break;
        case 7:
        {
            AF = 1<<3; 
            AF_S14 = 1<<3; 
            AF_S13 = 1<<2; 
            AF_S12 = 1<<3; 
            AF_S11 = 1<<0; 
            AF_S10 = 1<<1; 
            AF_S9  = 1<<2;
            AF_S8  = 1<<2; 
        }break;
        default: break;
    } 
}
#endif

//-----------------------------------------------------------------------------
//�� �� ����Display_Freq_Num
//����������Ƶ��������ʾ����
//����˵����
//ȫ�ֱ�������
//��    �룺cAddress,cNum
//��    �أ���
//�� �� �ߣ�Kanghekai               ʱ�䣺2012-08-01
//�� �� �ߣ�                        ʱ�䣺
//��    ����
//-----------------------------------------------------------------------------
void Display_Freq_Num(UINT8 cAddress, UINT8 cNum)
{
    UINT8 i;

    if(cAddress == 0)
    {
        Write_1621(cAddress*4+0, FREQ_NUM[cNum*4+0]);
        Write_1621(cAddress*4+1, FREQ_NUM[cNum*4+1]);
        Write_1621(cAddress*4+2, FREQ_NUM[cNum*4+2] | RF);
        Write_1621(cAddress*4+3, FREQ_NUM[cNum*4+3] | RF_S1 |RF_S2);
    }
    else if(cAddress == 2)
    {
        Write_1621(cAddress*4+0,FREQ_NUM[cNum*4+0]);
        Write_1621(cAddress*4+1,FREQ_NUM[cNum*4+1]);
        Write_1621(cAddress*4+2,FREQ_NUM[cNum*4+2] | RF_S3);
        Write_1621(cAddress*4+3,FREQ_NUM[cNum*4+3] | RF_S4 | Dot);
    }
    else if(cAddress == 3)
    {
        Write_1621(cAddress*4+0,FREQ_NUM[cNum*4+0]);
        Write_1621(cAddress*4+1,FREQ_NUM[cNum*4+1]);
        Write_1621(cAddress*4+2,FREQ_NUM[cNum*4+2] | RF_S5);
        Write_1621(cAddress*4+3,FREQ_NUM[cNum*4+3] | RF_S6 | RF_S7);
    }
    else if(cAddress == 4)
    {
        Write_1621(cAddress*4+0,FREQ_NUM[cNum*4+0]);
        Write_1621(cAddress*4+1,FREQ_NUM[cNum*4+1]);
        Write_1621(cAddress*4+2,FREQ_NUM[cNum*4+2] | K4);
        Write_1621(cAddress*4+3,FREQ_NUM[cNum*4+3] | AF_S13 | AF_S14);
    }
    else if(cAddress == 5)
    {
        Write_1621(cAddress*4+0,FREQ_NUM[cNum*4+0]);
        Write_1621(cAddress*4+1,FREQ_NUM[cNum*4+1]);
        Write_1621(cAddress*4+2,FREQ_NUM[cNum*4+2] | MHz);
        Write_1621(cAddress*4+3,FREQ_NUM[cNum*4+3] | AF_S8 | AF);

    }
/*    else if(cAddress == 6)
    {
                Write_1621(24,0 | MHz);
                Write_1621(25,0 | AF_S8    | AF);
    }
    else if(cAddress == 7)
    {
                Write_1621(26,0 | MHz);
                Write_1621(27,0 | AF_S8    | AF);
    }
    else if(cAddress == 8)
    {
                Write_1621(28,0 | MHz);
                Write_1621(29,0 | AF_S8    | AF);
    }
*/    
    else if(cAddress == 9)
    {
//        Write_1621(30,0 | MHz);
        Write_1621(31,0 | AF_S12 | AF_S11 | AF_S10 | AF_S9);
    }
    else
    {
        for(i=0;i<4;i++)
        {
            Write_1621(cAddress*4+i,FREQ_NUM[cNum*4+i]);
        }
    }
}

//-----------------------------------------------------------------------------
//�� �� ����Display_Ch_Num                                                          
//����������Ƶ����ʾ                                                             
//����˵����
//ȫ�ֱ�������
//��    �룺address,num                                                                     
//��    �أ���                                                                     
//�� �� �ߣ�Kanghekai               ʱ�䣺2012-08-01                                         
//�� �� �ߣ�                        ʱ�䣺                                         
//��    ����                                                                     
//-----------------------------------------------------------------------------
void Display_Ch_Num(UINT8 address, UINT8 num)
{
    UINT8 i;

    for(i=0;i<2;i++)
    {
        Write_1621(address*2+i,CH_NUM[num*2+i]);
    }
}

