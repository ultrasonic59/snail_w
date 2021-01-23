/* Includes ------------------------------------------------------------------*/
#include "VS1003/vs1003.h"

/* Private variables ---------------------------------------------------------*/

/* VS1003���ò��� */ 
/* 0 , henh.1 , hfreq.2 , lenh.3 , lfreq 5 ,������ */
uint8_t vs1003ram[5] = { 0 , 0 , 0 , 0 , 250 };

/*******************************************************************************
* Function Name  : delay_ms
* Description    : delay time
* Input          : - ms: time
* Output         : None
* Return         : None
* Attention		 : None
*******************************************************************************/
static void delay_ms(uint32_t ms)
{
    uint32_t len;
    for (;ms > 0; ms --)
        for (len = 0; len < 100; len++ );
}
		
/*******************************************************************************
* Function Name  : VS1003_SPI_Init
* Description    : VS1003 SPI Init
* Input          : None
* Output         : None
* Return         : None
* Attention		 : None
*******************************************************************************/
static void VS1003_SPI_Init(void)
{
  	SPI_InitTypeDef  SPI_InitStructure;

	RCC_APB1PeriphClockCmd(Open_SPIx_CLK,ENABLE);
	SPI_I2S_DeInit(Open_SPIx);
	SPI_InitStructure.SPI_Direction= SPI_Direction_2Lines_FullDuplex;
	SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b; 
	SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
	SPI_InitStructure.SPI_CPOL = SPI_CPOL_High;
	SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge;
	SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_4;
	SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
	SPI_InitStructure.SPI_CRCPolynomial = 7;
	SPI_Init(Open_SPIx, &SPI_InitStructure);

	SPI_Cmd(Open_SPIx, ENABLE);
}

/*******************************************************************************
* Function Name  : VS1003_SPI_SetSpeed
* Description    : None
* Input          : - SpeedSet: SPI_SPEED_HIGH 1  SPI_SPEED_LOW 0
* Output         : None
* Return         : None
* Attention		 : None
*******************************************************************************/
static void VS1003_SPI_SetSpeed( uint8_t SpeedSet)
{
  SPI_InitTypeDef SPI_InitStructure ;
    
  SPI_InitStructure.SPI_Direction=SPI_Direction_2Lines_FullDuplex ;
  SPI_InitStructure.SPI_Mode=SPI_Mode_Master ;
  SPI_InitStructure.SPI_DataSize=SPI_DataSize_8b ;
  SPI_InitStructure.SPI_CPOL=SPI_CPOL_High ;
  SPI_InitStructure.SPI_CPHA=SPI_CPHA_2Edge ;
  SPI_InitStructure.SPI_NSS=SPI_NSS_Soft ;

  if( SpeedSet == SPI_SPEED_LOW )
  {
      SPI_InitStructure.SPI_BaudRatePrescaler=SPI_BaudRatePrescaler_128;
  }
  else 
  {
      SPI_InitStructure.SPI_BaudRatePrescaler=SPI_BaudRatePrescaler_8;
  }
  SPI_InitStructure.SPI_FirstBit=SPI_FirstBit_MSB ;
  SPI_InitStructure.SPI_CRCPolynomial=7 ;
  SPI_Init(Open_SPIx,&SPI_InitStructure);
}

/*******************************************************************************
* Function Name  : VS1003_SPI_ReadWriteByte
* Description    : None
* Input          : - TxData: Write Byte
* Output         : None
* Return         : None
* Attention		 : None
*******************************************************************************/
static uint16_t VS1003_SPI_ReadWriteByte( uint16_t TxData )
{
	while(SPI_I2S_GetFlagStatus(Open_SPIx, SPI_I2S_FLAG_TXE)==RESET);
	SPI_I2S_SendData(Open_SPIx,TxData);
	
	while(SPI_I2S_GetFlagStatus(Open_SPIx, SPI_I2S_FLAG_RXNE)==RESET);
	return SPI_I2S_ReceiveData(Open_SPIx);
}

/*******************************************************************************
* Function Name  : VS1003_Init
* Description    : VS1003�˿ڳ�ʼ��
* Input          : None
* Output         : None
* Return         : None
* Attention		 : None
*******************************************************************************/	 
void VS1003_Init(void)
{		  
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_AHB1PeriphClockCmd( RCC_AHB1Periph_GPIOA | RCC_AHB1Periph_GPIOB , ENABLE);
	
	GPIO_PinAFConfig(Open_SPIx_SCK_GPIO_PORT, Open_SPIx_SCK_SOURCE,  Open_SPIx_SCK_AF);
	GPIO_PinAFConfig(Open_SPIx_MISO_GPIO_PORT, Open_SPIx_MISO_SOURCE, Open_SPIx_MISO_AF);
	GPIO_PinAFConfig(Open_SPIx_MOSI_GPIO_PORT, Open_SPIx_MOSI_SOURCE, Open_SPIx_MOSI_AF);
	
	GPIO_InitStructure.GPIO_Pin = Open_SPIx_SCK_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_DOWN;  
	GPIO_Init(Open_SPIx_SCK_GPIO_PORT, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = Open_SPIx_MISO_PIN;
	GPIO_Init(Open_SPIx_MISO_GPIO_PORT, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = Open_SPIx_MOSI_PIN;
	GPIO_Init(Open_SPIx_MOSI_GPIO_PORT, &GPIO_InitStructure);

	/* XCS */
	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_12;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	/* XDCS */
	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_4;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	/* Reset */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	 
	/* DREQ */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
	GPIO_Init(GPIOA, &GPIO_InitStructure); 
	
	MP3_Reset(0);
	delay_ms(1);
	MP3_Reset(1);
	
	MP3_DCS(1); 
	MP3_CCS(1); 
	
	VS1003_SPI_Init();
}


/*******************************************************************************
* Function Name  : VS1003_WriteReg
* Description    : VS1003д�Ĵ���
* Input          : - reg: �����ַ
*				   - value: ��������
* Output         : None
* Return         : None
* Attention		 : None
*******************************************************************************/
void VS1003_WriteReg( uint8_t reg,uint16_t value )
{  
   while(  MP3_DREQ ==0 );           /* �ȴ����� */
   
   VS1003_SPI_SetSpeed( SPI_SPEED_LOW );	 
   MP3_DCS(1); 
   MP3_CCS(0); 
   VS1003_SPI_ReadWriteByte(VS_WRITE_COMMAND); /* ����VS1003��д���� */
   VS1003_SPI_ReadWriteByte(reg);             
   VS1003_SPI_ReadWriteByte(value>>8);        
   VS1003_SPI_ReadWriteByte(value);	          
   MP3_CCS(1);         
   VS1003_SPI_SetSpeed( SPI_SPEED_HIGH );
} 

/*******************************************************************************
* Function Name  : VS1003_ReadReg
* Description    : VS1003���Ĵ���
* Input          : - reg: �����ַ
* Output         : None
* Return         : - value: ����
* Attention		 : None
*******************************************************************************/
uint16_t VS1003_ReadReg( uint8_t reg)
{ 
   uint16_t value;
    
   while(  MP3_DREQ ==0 );           /* �ȴ����� */
   VS1003_SPI_SetSpeed( SPI_SPEED_LOW );
   MP3_DCS(1);     
   MP3_CCS(0);     
   VS1003_SPI_ReadWriteByte(VS_READ_COMMAND);/* ����VS1003�Ķ����� */
   VS1003_SPI_ReadWriteByte( reg );   
   value = VS1003_SPI_ReadWriteByte(0xff);		
   value = value << 8;
   value |= VS1003_SPI_ReadWriteByte(0xff); 
   MP3_CCS(1);   
   VS1003_SPI_SetSpeed( SPI_SPEED_HIGH );
   return value; 
} 

/*******************************************************************************
* Function Name  : VS1003_ResetDecodeTime
* Description    : None
* Input          : None
* Output         : None
* Return         : None
* Attention		 : None
*******************************************************************************/                       
void VS1003_ResetDecodeTime(void)
{
   VS1003_WriteReg(SPI_DECODE_TIME,0x0000);
   VS1003_WriteReg(SPI_DECODE_TIME,0x0000); /* �������� */
}

/*******************************************************************************
* Function Name  : VS1003_GetDecodeTime
* Description    : None
* Input          : None
* Output         : None
* Return         : None
* Attention		 : None
*******************************************************************************/    
uint16_t VS1003_GetDecodeTime(void)
{ 
   return VS1003_ReadReg(SPI_DECODE_TIME);   
} 

/*******************************************************************************
* Function Name  : VS1003_SoftReset
* Description    : VS1003��λ
* Input          : None
* Output         : None
* Return         : None
* Attention		 : None
*******************************************************************************/
void VS1003_SoftReset(void)
{
   uint8_t retry; 	
   			   
   while(  MP3_DREQ ==0 );   /* �ȴ������λ���� */
   VS1003_SPI_ReadWriteByte(0xff);  /* �������� */
   retry = 0;
   while( VS1003_ReadReg(0) != 0x0804 )   /* �����λ,��ģʽ */  
   {
	   VS1003_WriteReg(SPI_MODE,0x0804);  /* �����λ,��ģʽ */
	   delay_ms(2);                        /* �ȴ�����1.35ms */
	   if( retry++ > 100 )
	   { 
	      break; 
	   }
   }	 	

   while(  MP3_DREQ ==0 );   /* �ȴ������λ���� */

   retry = 0;

   while( VS1003_ReadReg(SPI_CLOCKF) != 0X9800 ) /* ����vs1003��ʱ��,3��Ƶ ,1.5xADD */ 
   {
	   VS1003_WriteReg(SPI_CLOCKF,0X9800);       /* ����vs1003��ʱ��,3��Ƶ ,1.5xADD */
	   if( retry++ > 100 )
	   { 
	      break; 
	   }
   }		   
   retry = 0;

   while( VS1003_ReadReg(SPI_AUDATA) != 0XBB81 ) /* ����vs1003��ʱ��,3��Ƶ ,1.5xADD */
   {
	   VS1003_WriteReg(SPI_AUDATA,0XBB81);
	   if( retry++ > 100 )
	   { 
	      break; 
	   }   
   }

   VS1003_WriteReg(11,0x2020);	 /* ���� */			 
   VS1003_ResetDecodeTime();     /* ��λ����ʱ�� */	     
   /* ��vs1003����4���ֽ���Ч���ݣ���������SPI���� */	
   MP3_DCS(0);  /* ѡ�����ݴ��� */
   VS1003_SPI_ReadWriteByte(0XFF);
   VS1003_SPI_ReadWriteByte(0XFF);
   VS1003_SPI_ReadWriteByte(0XFF);
   VS1003_SPI_ReadWriteByte(0XFF);
   MP3_DCS(1);  /* ȡ�����ݴ��� */
   delay_ms(20);
} 

/*******************************************************************************
* Function Name  : VS1003_Reset
* Description    : VS1003��λ
* Input          : None
* Output         : None
* Return         : None
* Attention		 : None
*******************************************************************************/
void VS1003_Reset(void)
{
   delay_ms(20);
   VS1003_SPI_ReadWriteByte(0XFF);
   MP3_DCS(1);              /* ȡ�����ݴ��� */
   MP3_CCS(1);              /* ȡ�����ݴ��� */

   while(  MP3_DREQ ==0 );  /* �ȴ�DREQΪ�� */
   delay_ms(20);			 
}

/*******************************************************************************
* Function Name  : VS1003_SineTest
* Description    : VS1003���Ҳ���
* Input          : None
* Output         : None
* Return         : None
* Attention		 : None
*******************************************************************************/
void VS1003_SineTest(void)
{	
   VS1003_WriteReg(0x0b,0X2020);	  /* �������� */	 
   VS1003_WriteReg(SPI_MODE,0x0820); /* ����vs1003�Ĳ���ģʽ */	    
   while(  MP3_DREQ ==0 );  /* �ȴ�DREQΪ�� */
 	
   /* ��vs1003�������Ҳ������0x53 0xef 0x6e n 0x00 0x00 0x00 0x00 */
   MP3_DCS(0);/* ѡ�����ݴ��� */
   VS1003_SPI_ReadWriteByte(0x53);
   VS1003_SPI_ReadWriteByte(0xef);
   VS1003_SPI_ReadWriteByte(0x6e);
   VS1003_SPI_ReadWriteByte(0x24);
   VS1003_SPI_ReadWriteByte(0x00);
   VS1003_SPI_ReadWriteByte(0x00);
   VS1003_SPI_ReadWriteByte(0x00);
   VS1003_SPI_ReadWriteByte(0x00);
   delay_ms(100);
   MP3_DCS(1); 
   /* �˳����Ҳ��� */
   MP3_DCS(0);/* ѡ�����ݴ��� */
   VS1003_SPI_ReadWriteByte(0x45);
   VS1003_SPI_ReadWriteByte(0x78);
   VS1003_SPI_ReadWriteByte(0x69);
   VS1003_SPI_ReadWriteByte(0x74);
   VS1003_SPI_ReadWriteByte(0x00);
   VS1003_SPI_ReadWriteByte(0x00);
   VS1003_SPI_ReadWriteByte(0x00);
   VS1003_SPI_ReadWriteByte(0x00);
   delay_ms(100);
   MP3_DCS(1);		 

   /* �ٴν������Ҳ��Բ�����nֵΪ0x44���������Ҳ���Ƶ������Ϊ�����ֵ */
   MP3_DCS(0);/* ѡ�����ݴ��� */      
   VS1003_SPI_ReadWriteByte(0x53);
   VS1003_SPI_ReadWriteByte(0xef);
   VS1003_SPI_ReadWriteByte(0x6e);
   VS1003_SPI_ReadWriteByte(0x44);
   VS1003_SPI_ReadWriteByte(0x00);
   VS1003_SPI_ReadWriteByte(0x00);
   VS1003_SPI_ReadWriteByte(0x00);
   VS1003_SPI_ReadWriteByte(0x00);
   delay_ms(100);
   MP3_DCS(1);
   /* �˳����Ҳ��� */
   MP3_DCS(0);/* ѡ�����ݴ��� */      
   VS1003_SPI_ReadWriteByte(0x45);
   VS1003_SPI_ReadWriteByte(0x78);
   VS1003_SPI_ReadWriteByte(0x69);
   VS1003_SPI_ReadWriteByte(0x74);
   VS1003_SPI_ReadWriteByte(0x00);
   VS1003_SPI_ReadWriteByte(0x00);
   VS1003_SPI_ReadWriteByte(0x00);
   VS1003_SPI_ReadWriteByte(0x00);
   delay_ms(100);
   MP3_DCS(1);	 
}	 

/*******************************************************************************
* Function Name  : VS1003_RamTest
* Description    : VS1003 RAM����
* Input          : None
* Output         : None
* Return         : None
* Attention		 : None
*******************************************************************************/																			 
void VS1003_RamTest(void)
{
   volatile uint16_t value;
     
   VS1003_Reset();     
   VS1003_WriteReg(SPI_MODE,0x0820);/* ����vs1003�Ĳ���ģʽ */
   while(  MP3_DREQ ==0 );           /* �ȴ�DREQΪ�� */
   MP3_DCS(0);	       			     /* xDCS = 1��ѡ��vs1003�����ݽӿ� */
   VS1003_SPI_ReadWriteByte(0x4d);
   VS1003_SPI_ReadWriteByte(0xea);
   VS1003_SPI_ReadWriteByte(0x6d);
   VS1003_SPI_ReadWriteByte(0x54);
   VS1003_SPI_ReadWriteByte(0x00);
   VS1003_SPI_ReadWriteByte(0x00);
   VS1003_SPI_ReadWriteByte(0x00);
   VS1003_SPI_ReadWriteByte(0x00);
   delay_ms(50);  
   MP3_DCS(1);
   value = VS1003_ReadReg(SPI_HDAT0); /* ����õ���ֵΪ0x807F���������� */
}     
		 				
/*******************************************************************************
* Function Name  : VS1003_SetVol
* Description    : �趨vs1003���ŵ������͸ߵ���
* Input          : None
* Output         : None
* Return         : None
* Attention		 : None
*******************************************************************************/   
void VS1003_SetVol(void)
{
   uint8_t i;
   uint16_t bass=0;  /* �ݴ������Ĵ���ֵ */
   uint16_t volt=0;  /* �ݴ�����ֵ */
   uint8_t  vset=0;  /* �ݴ�����ֵ */ 
		 
   vset = 255 - vs1003ram[4]; /* ȡ���õ����ֵ */ 
   volt =vset;
   volt <<= 8;
   volt += vset;/* �õ��������ú��С */
   /* 0,henh.1,hfreq.2,lenh.3,lfreq */      
   for( i = 0; i < 4; i++ )
   {
       bass <<= 4;
       bass += vs1003ram[i]; 
   }     
   VS1003_WriteReg(SPI_BASS,bass);/* BASS */   
   VS1003_WriteReg(SPI_VOL,volt); /* ������ */ 
}    

/*******************************************************************************
* Function Name  : VS1003_WriteData
* Description    : VS1003д����
* Input          : None
* Output         : None
* Return         : None
* Attention		 : None
*******************************************************************************/  
void VS1003_WriteData( uint8_t * buf)
{		
   uint8_t  count = 32;

   MP3_DCS(0);   
   while( count-- )
   {
	  VS1003_SPI_ReadWriteByte( *buf++ );
   }
   MP3_DCS(1);  
   MP3_CCS(1);  
} 


/*********************************************************************************************************
      END FILE
*********************************************************************************************************/

