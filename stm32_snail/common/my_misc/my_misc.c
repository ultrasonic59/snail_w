#include <stdint.h>
#include "board.h"
#include "my_misc.h"

#include "can_cmds.h"
#include "printk.h"
static uint32_t GetSector(uint32_t Address);

///=======================================================================
void uDelay (const uint32_t usec)
{
uint32_t count = 0;
const uint32_t utime = 45*usec;////(120 * usec / 7);
do
  {
   if ( ++count > utime )
    {
    return ;
    }
  }
while (1);
}
///=======================================================================

pFunction Jump_To_Application;
uint32_t jumpAddress;

void goto_booter(void)
{
__disable_irq();
NVIC_SetVectorTable(NVIC_VectTab_FLASH, BOOT_BASE_ADDRESS);
  
jumpAddress = *(__IO uint32_t*) (BOOT_BASE_ADDRESS + 4);
////Jump_To_Application = (pFunction)JumpAddress;
////printk(" Jamp addres=[%x:%x]\r\n",jumpAddress,BOOT_BASE_ADDRESS);	
   Jump_To_Application = (pFunction) jumpAddress;
/* Initialize user application's Stack Pointer */
__set_CONTROL(0) ;
__set_MSP(*(__IO uint32_t*) BOOT_BASE_ADDRESS);
Jump_To_Application();
  
}
void goto_app(void)
{
////uint32_t sp_tst=0;  
__disable_irq();
NVIC_SetVectorTable(NVIC_VectTab_FLASH, APP_BASE_ADDRESS);
jumpAddress = *(__IO uint32_t*) (APP_BASE_ADDRESS + 4);
////sp_tst= *(__IO uint32_t*) (APP_BASE_ADDRESS);
///printk(" Jamp addres=[%x:%x:%x]\r\n",jumpAddress,APP_BASE_ADDRESS,sp_tst);	
///printk(" Jamp addres=[%x:%x:%x]\r\n",jumpAddress,APP_BASE_ADDRESS,sp_tst);	
///printk(" Jamp addres=[%x:%x:%x]\r\n",jumpAddress,APP_BASE_ADDRESS,sp_tst);	
////printk(" Jamp addres=[%x:%x:%x]\r\n",jumpAddress,APP_BASE_ADDRESS,sp_tst);	
Jump_To_Application = (pFunction)jumpAddress;
/* Initialize user application's Stack Pointer */
__set_CONTROL(0) ;
__set_MSP(*(__IO uint32_t*) APP_BASE_ADDRESS);
Jump_To_Application();
  
}
////=================================================
void FLASH_If_Init(void)
{ 
FLASH_Unlock(); 

  /* Clear pending flags (if any) */  
FLASH_ClearFlag(FLASH_FLAG_EOP | FLASH_FLAG_OPERR | FLASH_FLAG_WRPERR | 
                FLASH_FLAG_PGAERR | FLASH_FLAG_PGPERR|FLASH_FLAG_PGSERR);
}

uint32_t FLASH_If_Erase(uint32_t StartSector)
{
uint32_t UserStartSector = GetSector(APP_BASE_ADDRESS);

if (FLASH_EraseSector(UserStartSector, VoltageRange_3) != FLASH_COMPLETE)
    {
    return 1;
    }
   
  return 0;
}
uint32_t FLASH_If_Write(__IO uint32_t* FlashAddress, uint32_t* Data ,uint32_t DataLength)
{
  uint32_t i = 0;

  for (i = 0; (i < DataLength) && (*FlashAddress <= (APP_END_ADDRESS-4)); i++)
  {
    /* Device voltage range supposed to be [2.7V to 3.6V], the operation will
       be done by word */ 
    if (FLASH_ProgramWord(*FlashAddress, *(uint32_t*)(Data+i)) == FLASH_COMPLETE)
    {
     /* Check the written value */
      if (*(uint32_t*)*FlashAddress != *(uint32_t*)(Data+i))
      {
        /* Flash content doesn't match SRAM content */
        return(2);
      }
      /* Increment FLASH destination address */
      *FlashAddress += 4;
    }
    else
    {
      /* Error occurred while writing data in Flash memory */
      return (1);
    }
  }

  return (0);
}

static uint32_t GetSector(uint32_t Address)
{
  uint32_t sector = 0;
  
  if((Address < ADDR_FLASH_SECTOR_1) && (Address >= ADDR_FLASH_SECTOR_0))
  {
    sector = FLASH_Sector_0;  
  }
  else if((Address < ADDR_FLASH_SECTOR_2) && (Address >= ADDR_FLASH_SECTOR_1))
  {
    sector = FLASH_Sector_1;  
  }
  else if((Address < ADDR_FLASH_SECTOR_3) && (Address >= ADDR_FLASH_SECTOR_2))
  {
    sector = FLASH_Sector_2;  
  }
  else if((Address < ADDR_FLASH_SECTOR_4) && (Address >= ADDR_FLASH_SECTOR_3))
  {
    sector = FLASH_Sector_3;  
  }
  else if(Address >= ADDR_FLASH_SECTOR_4)
  {
    sector = FLASH_Sector_4;  
  }
    return sector;
}

uint8_t erase_sectors(uint8_t *data)
{
return FLASH_If_Erase(0);  
}
uint8_t prg_dat(uint8_t *data)
{
uint8_t ii;   
FLASH_Status t_fl_stat;  
uint8_t num_bytes;
uint32_t addr_prg;
prg_flash_cmd_t *p_prg_flash_cmd=(prg_flash_cmd_t *)data;
num_bytes=p_prg_flash_cmd->num_bytes;

if((num_bytes>MAX_NUM_BYTES_PRG)||(num_bytes==0))
  return ERROR_NUM_BYTES_PRG;
////????addr_prg=p_prg_flash_cmd->b_addr + APP_BASE_ADDRESS;
////????if(addr_prg>APP_END_ADDRESS)
////????  return ERROR_ADDR_PRG;
#if 0
switch(num_bytes)  {
  case 1:
    t_fl_stat=FLASH_ProgramByte(addr_prg, p_prg_flash_cmd->data[0]); 
    break;
  case 2:
    t_fl_stat=FLASH_ProgramHalfWord(addr_prg, (uint16_t )p_prg_flash_cmd->data[0]); 
    break;
  case 3:
    for(ii=0;ii<3;ii++)
      {
      t_fl_stat=FLASH_ProgramByte(addr_prg+ii, p_prg_flash_cmd->data[ii]); 
      if( t_fl_stat!=FLASH_COMPLETE)
        break;
      }
    break;
  case 4:
    t_fl_stat=FLASH_ProgramWord(addr_prg, (uint32_t )p_prg_flash_cmd->data[0]); 
    break;
}
#endif

if(t_fl_stat==FLASH_COMPLETE ) 
  return 0;  
else
  return ERROR_FLAH_PRG;

}

////=================================================
