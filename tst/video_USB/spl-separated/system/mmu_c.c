// ���ļ��ɺ���ҫ��ƣ�����ͨ��QQ��ϵ���ߣ�26750452
#include "mmu.h"

#ifndef CACHE_ALIGN
#define CACHE_ALIGN   (32)
#endif

////////////////////////////////////////////////////////////////////////////////
//|          |
//| �������� |: MMU_CleanDCacheArray
//| �������� |: ��ָ���������ڵ�cache��������洢��
//|          |:
//| �����б� |:
//|          |:
//| ��    �� |:
//|          |:
//| ��ע��Ϣ |: ���������������cachelineΪ������Ԫ��
//|          |: ����32�ֽڶ��룬��С��32�ֽڵ�������
////////////////////////////////////////////////////////////////////////////////
void MMU_CleanDCacheArray(unsigned long mva, unsigned long num)
{
  signed long size = num;
  while (size > 0) {
    MMU_CleanDCacheMVA(mva);
    mva += CACHE_ALIGN;
    size -= CACHE_ALIGN;
  }
  MMU_DrainWriteBuffer();
}

////////////////////////////////////////////////////////////////////////////////
//|          |
//| �������� |: MMU_InvalidateDCacheArray
//| �������� |: ��ָ���������ڵ�cache��Ϊ��Ч����ᵼ��cache�������
//|          |:
//| �����б� |:
//|          |:
//| ��    �� |:
//|          |:
//| ��ע��Ϣ |: ���������������cachelineΪ������Ԫ��
//|          |: ����32�ֽڶ��룬��С��32�ֽڵ�������
////////////////////////////////////////////////////////////////////////////////
void MMU_InvalidateDCacheArray(unsigned long mva, unsigned long num)
{
  signed long size = num;
  while (size > 0) {
    MMU_InvalidateDCacheMVA(mva);
    mva += CACHE_ALIGN;
    size -= CACHE_ALIGN;
  }
}

