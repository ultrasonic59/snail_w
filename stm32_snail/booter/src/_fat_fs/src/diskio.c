#include "diskio.h"
#include "types.h"
#include "rook_sd.h"

////unsigned char flg_req_osc=0;

/*---------------------------------------*/
/* Prototypes for disk control functions */

///int assign_drives (int, int);
DSTATUS disk_initialize (uint8_t drv)
{
DSTATUS stat=0;
  
return stat;   
}
DSTATUS disk_status (uint8_t drv)
{
DSTATUS stat=0;
  
return stat;  
}
DRESULT disk_read (uint8_t drv, uint8_t* buff, uint32_t sector, uint32_t count)
{
if(SD_ReadSector(sector, buff, count)==TRUE)
  return RES_OK;
else
  return RES_ERROR;
  
}
DRESULT disk_write (uint8_t drv, const uint8_t* buff, uint32_t sector, uint32_t count)
{
if(SD_WriteSector(sector, buff, count)==TRUE) 
  return RES_OK;
else
  return RES_ERROR;
}
DRESULT disk_ioctl (uint8_t drv, uint8_t ctrl, void* buff)
{
return (DRESULT)0;  
}
