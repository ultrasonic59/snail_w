// ���ļ��ɺ���ҫ��ƣ�����ͨ��QQ��ϵ���ߣ�26750452
////////////////////////////////////////////////////////////////////////////////
#if (defined(HDL_MAX) && (HDL_MAX > 0))

#ifdef __cplusplus
extern "C"  {
#endif

#ifndef __INLINE
#define __INLINE inline
#endif

#undef HANDLE_T

#if (HDL_MAX > 65535)
#define HANDLE_T uint32_t
#elif (HDL_MAX > 255)
#define HANDLE_T uint16_t
#else
#define HANDLE_T uint8_t
#endif

static HANDLE_T hdlpool[HDL_MAX + 1];

////////////////////////////////////////////////////////////////////////////////
//|          |
//| �������� |: __hdl_pool_init
//| �������� |: ��ʼ������ģ��ľ���ء�
//|          |:
//| �����б� |:
//|          |:
//| ��    �� |:
//|          |:
//| ��ע��Ϣ |:
//|          |:
////////////////////////////////////////////////////////////////////////////////
static __INLINE void __hdl_pool_init(void)
{
  unsigned i;

  for (i = 0; i < HDL_MAX; i++) {
    hdlpool[i] = (i + 1);
  }
  hdlpool[i] = 0;
}

////////////////////////////////////////////////////////////////////////////////
//|          |
//| �������� |: __hdl_alloc
//| �������� |: �Ӿ����ȡ��һ�����о����
//|          |:
//| �����б� |:
//|          |:
//| ��    �� |:
//|          |:
//| ��ע��Ϣ |:
//|          |:
////////////////////////////////////////////////////////////////////////////////
static __INLINE HANDLE_T __hdl_alloc(void)
{
  HANDLE_T hdl;

  hdl = hdlpool[0];
  if (hdl == 0)
    return 0;
  hdlpool[0] = hdlpool[hdl];
  return hdl;
}

////////////////////////////////////////////////////////////////////////////////
//|          |
//| �������� |: __hdl_free
//| �������� |: �ͷ�ָ�������
//|          |:
//| �����б� |:
//|          |:
//| ��    �� |:
//|          |:
//| ��ע��Ϣ |:
//|          |:
////////////////////////////////////////////////////////////////////////////////
static __INLINE void __hdl_free(HANDLE_T hdl)
{
  hdlpool[hdl] = hdlpool[0];
  hdlpool[0] = hdl;
}

#undef HANDLE_T
#undef HDL_MAX

#ifdef __cplusplus
}
#endif

#endif /* HDL_MAX */

