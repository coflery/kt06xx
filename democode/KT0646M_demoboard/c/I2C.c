//*****************************************************************************
//  File Name: I2C.c
//  Function:  KT Wireless Mic Transmitter Products Demoboard I2C Function Define
//*****************************************************************************
//        Revision History
//  Version Date        Description
//  V1.0    2012-08-01  Initial draft
//  V1.1    2013-11-22  �ı�������Ͷ��巽��
//  V1.2    2017-02-08  ��ʽ�淶������
//  V0.3    2017-04-27  �Ӽ�Ƶ�ʵ�ʱ���Ȱѵ�Ƶ���ˣ�tune��̨���ٻָ�ԭ����Ƶ�����ã�main.c��
//						��̨��һֱ����ͬ�Ĳ�������tunę�������һ��ʱ��󲽽����4����10����main.c��
//*****************************************************************************

//-----------------------------------------------------------------------------
// Includes
//-----------------------------------------------------------------------------
#include <interface.h> 
#include <intrins.h>

#ifdef I2C

//-----------------------------------------------------------------------------
// Global VARIABLES
//-----------------------------------------------------------------------------
BOOL Ack_Flag=0; // I2C Ack Flag

#ifdef I2C_BYTE_MODE //I2C��Byte����ģ

//-----------------------------------------------------------------------------
//�� �� ����I2C_Byte_Write
//����������I2C��Byteд����
//����˵����
//ȫ�ֱ�������
//��    �룺uchar device_address,uchar reg_add,uchar writedata
//��    �أ���
//�� �� �ߣ�PAE                     ʱ�䣺2012-08-01
//�� �� �ߣ�                        ʱ�䣺
//��    ����V1.0
//-----------------------------------------------------------------------------
void I2C_Byte_Write(UINT8 device_address, UINT8 reg_add, UINT8 writedata)
{
    I2C_Start();
    I2C_Senddata(device_address & 0xFE);
    I2C_Ack();
    if (Ack_Flag == 0)
    {
        I2C_Senddata(reg_add);
        I2C_Ack();
        if (Ack_Flag == 0)
        {
            I2C_Senddata(writedata);
            I2C_Ack();
        }
        else
            SCL = 0;            
    }
    else
        SCL = 0;
    I2C_Stop();    
}

//-----------------------------------------------------------------------------
//�� �� ����I2C_Byte_Read
//����������I2C��Byte������
//����˵����
//ȫ�ֱ�������
//��    �룺uchar device_address,uchar reg_add
//��    �أ���ȷ��uchar readdata    ����0x00
//�� �� �ߣ�PAE                     ʱ�䣺2012-08-01
//�� �� �ߣ�                        ʱ�䣺
//��    ����V1.0
//-----------------------------------------------------------------------------
UINT8 I2C_Byte_Read(UINT8 device_address, UINT8 reg_add)
{
    UINT8 readdata;
    I2C_Start();
    I2C_Senddata(device_address & 0xFE);
    I2C_Ack();
    if (Ack_Flag == 0)
    {
        I2C_Senddata(reg_add);
        I2C_Ack();
        if (Ack_Flag == 0)
        {
            I2C_Start();
            I2C_Senddata(device_address | 0x01);
            I2C_Ack();
            if (Ack_Flag == 0)
            {
                //    SDA pin is high Z
                readdata = I2C_Receivedata();
                I2C_Ack();
                I2C_Stop();    
                return(readdata);
            }
            else
            {
                I2C_Stop();
                return(0x00);
            }
        }
        else
        {
            I2C_Stop();
             return(0x00);
        }            
    }
    else
    {
        I2C_Stop();
        return(0x00);
    }
}
#endif


#ifdef I2C_WORD_MODE //I2C��WORD����ģʽ

//-----------------------------------------------------------------------------
//�� �� ����I2C_Word_Write
//����������I2C��WORDд����
//����˵����
//ȫ�ֱ�������
//��    �룺uchar device_address, uchar reg_add, uint writeword
//��    �أ���
//�� �� �ߣ�PAE                     ʱ�䣺2012-08-01
//�� �� �ߣ�                        ʱ�䣺
//��    ����V1.0
//-----------------------------------------------------------------------------
void I2C_Word_Write(UINT8 device_address, UINT8 reg_add, UINT16 writeword)
{
    UINT8 writeword_high,writeword_low;

    writeword_low = writeword;
    writeword_high = writeword>>8;

    I2C_Start();
    I2C_Senddata(device_address & 0xFE);
    I2C_Ack();
    if (Ack_Flag == 0)
    {
        I2C_Senddata(reg_add);
        I2C_Ack();
        if (Ack_Flag == 0)
        {
            I2C_Senddata(writeword_high);
            I2C_Ack();
            if (Ack_Flag == 0)
            {
                I2C_Senddata(writeword_low);
                I2C_Ack();
            }
            else
                SCL = 0;    
        }
        else
            SCL = 0;            
    }
    else
        SCL = 0;
    I2C_Stop();    
}

//-----------------------------------------------------------------------------
//�� �� ����I2C_Word_Read
//����������I2C��Word������
//����˵����
//ȫ�ֱ�������
//��    �룺uchar device_address,uchar reg_add
//��    �أ���ȷ��UINT16 readdata    ����0x0000
//�� �� �ߣ�PAE                     ʱ�䣺2012-08-01
//�� �� �ߣ�                        ʱ�䣺
//��    ����V1.0
//-----------------------------------------------------------------------------
UINT16 I2C_Word_Read(UINT8 device_address, UINT8 reg_add)
{
    UINT8 readdata_low;
    UINT16 readdata,readdata_high,temp=0;

    I2C_Start();
    I2C_Senddata(device_address & 0xFE);
    I2C_Ack();
    if (Ack_Flag == 0)
    {
        I2C_Senddata(reg_add);
        I2C_Ack();
        if (Ack_Flag == 0)
        {
            I2C_Start();
            I2C_Senddata(device_address | 0x01);
            I2C_Ack();
            if (Ack_Flag == 0)
            {
                // SDA = 1;//SDA ��Ϊ���룬������
                readdata_high = I2C_Receivedata();
                SDA = 0;
                I2C_Delay();I2C_Delay();
                SCL = 1;
                I2C_Delay();I2C_Delay();
                SCL = 0;
                I2C_Delay();I2C_Delay();
                SDA = 1;

                if (Ack_Flag == 0)
                {
                    readdata_low = I2C_Receivedata();
                    I2C_Ack();
                    I2C_Stop();
        
                    temp = readdata_high << 8;
                    readdata = temp | readdata_low;
                    return(readdata);
                }
                else
                {
                    I2C_Stop();
                    return(0x0000);
                }
            }
            else
            {
                I2C_Stop();
                return(0x0000);
            }
        }
        else
        {
            I2C_Stop();
             return(0x0000);            
        }
    }
    else
    {
        I2C_Stop();
        return(0x0000);
    }
}
#endif

//-----------------------------------------------------------------------------
//�� �� ����I2C_Delay
//����������I2C��ʱ
//����˵����
//ȫ�ֱ�������
//��    �룺��
//��    �أ���
//�� �� �ߣ�PAE                     ʱ�䣺2012-08-01
//�� �� �ߣ�                        ʱ�䣺
//��    ����V1.0
//-----------------------------------------------------------------------------
void I2C_Delay(void)
{
    UINT8 i;

    for(i=0;i<=40;i++)
    {
        _nop_();
    }
}

//-----------------------------------------------------------------------------
//�� �� ����I2C_Start
//����������I2C����֡��ʼ
//����˵����
//ȫ�ֱ�������
//��    �룺��
//��    �أ���
//�� �� �ߣ�PAE                     ʱ�䣺2012-08-01
//�� �� �ߣ�                        ʱ�䣺
//��    ����V1.0
//-----------------------------------------------------------------------------
void I2C_Start(void)
{
    I2C_Delay();I2C_Delay();
    SDA = 1;
    I2C_Delay();I2C_Delay();
    SCL = 1;
    I2C_Delay();I2C_Delay();
    SDA = 0;
    I2C_Delay();I2C_Delay();
    SCL = 0;
    I2C_Delay();I2C_Delay();
}

//-----------------------------------------------------------------------------
//�� �� ����I2C_Senddata
//����������I2C��������
//����˵����
//ȫ�ֱ�������
//��    �룺uchar senddata
//��    �أ���
//�� �� �ߣ�PAE                     ʱ�䣺2012-08-01
//�� �� �ߣ�                        ʱ�䣺
//��    ����V1.0
//-----------------------------------------------------------------------------
void I2C_Senddata(UINT8 senddata)
{
    UINT8 i;

    for (i=0;i<8;i++)
    {    
        I2C_Delay();
        if ((senddata & 0x80) != 0x80)
            SDA = 0;
        else
            SDA = 1;
        senddata = senddata << 1;
        I2C_Delay();
        SCL = 1;
        I2C_Delay();
        SCL = 0;
    }
    I2C_Delay();
}

//-----------------------------------------------------------------------------
//�� �� ����I2C_Receivedata
//����������I2C��������
//����˵����
//ȫ�ֱ�������
//��    �룺��
//��    �أ�uchar receivedata
//�� �� �ߣ�PAE                     ʱ�䣺2012-08-01
//�� �� �ߣ�                        ʱ�䣺
//��    ����V1.0
//-----------------------------------------------------------------------------
UINT8 I2C_Receivedata(void)
{
    UINT8 i,temp,receivedata=0;

    for (i=0;i<8;i++)
    {
        receivedata = receivedata << 1;
        I2C_Delay();
        SCL = 1;
        I2C_Delay();
        temp = SDA;
        SCL = 0;
        receivedata = receivedata | temp;
    }
    I2C_Delay();
    return(receivedata);    
}

//-----------------------------------------------------------------------------
//�� �� ����I2C_Ack
//����������I2C_Ack
//����˵����
//ȫ�ֱ�����Ack_Flag
//��    �룺��
//��    �أ���
//�� �� �ߣ�PAE                     ʱ�䣺2012-08-01
//�� �� �ߣ�                        ʱ�䣺
//��    ����V1.0
//-----------------------------------------------------------------------------
void I2C_Ack(void)
{
    SDA = 1;
    I2C_Delay();I2C_Delay();
    SCL = 1;
    I2C_Delay();
    Ack_Flag = SDA;
    SCL = 0;
    I2C_Delay();I2C_Delay();
}

//-----------------------------------------------------------------------------
//�� �� ����I2C_Stop
//����������I2C����֡����
//����˵����
//ȫ�ֱ�������
//��    �룺��
//��    �أ���
//�� �� �ߣ�PAE                     ʱ�䣺2012-08-01
//�� �� �ߣ�                        ʱ�䣺
//��    ����V1.0
//-----------------------------------------------------------------------------
void I2C_Stop(void)
{
    SCL = 0;
    I2C_Delay();I2C_Delay();
    SDA = 0;
    I2C_Delay();I2C_Delay();
    SCL = 1;
    I2C_Delay();I2C_Delay();
    SDA = 1;
    I2C_Delay();I2C_Delay();
}

#endif

