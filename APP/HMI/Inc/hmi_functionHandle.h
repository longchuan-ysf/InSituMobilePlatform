#ifndef _HMI_FUNCTIONHANDLE_H
#define _HMI_FUNCTIONHANDLE_H
#include "stdio.h"
#include "stdint.h"
#include "hmi_WidgetHandle.h"

extern void hmi_rxtask_handle(void);
extern uint8_t hmi_GetCurPagenum(uint16_t *page);
extern void hmi_refresh(void);
#endif
