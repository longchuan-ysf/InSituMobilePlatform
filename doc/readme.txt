----------------------------------------------------------------------------------------------------------------------------
ÏµÍ³Èí¼þÎÄ¼þËµÃ÷£º
×îÐÂÐÞ¸ÄÈÕÆÚ: 2019Äê11ÔÂ1ÈÕ
Ó¦ÓÃMDK V4.73¼°ÒÔÉÏ°æ±¾¿ª·¢
----------------------------------------------------------------------------------------------------------------------------	
1.  targetsÄ¿Â¼ÏÂ£º´æ·Å¸÷ÖÖ¹¤¿Ø°åµÄ¹¤³ÌÎÄ¼þ
	(1). ¸ù¾Ý¹ºÂòµÄ²»Í¬¹¤¿Ø°å»ò¿ª·¢°åÐÍºÅ´ò¿ªÏàÓ¦µÄÄ¿±êÎÄ¼þ¼Ð

    (2). ÒÔ¹¤¿Ø°åEMB8600IÎªÀý×Ó, ´ò¿ª./targets/EMB8600I£¬EMB8600IÄ¿Â¼ÏÂÓÐ2¸öÎÄ¼þ¼Ð£º
	     configÄ¿Â¼ÀïÃæÓÐ4¸öÎÄ¼þ£¬ËµÃ÷ÈçÏÂ£º
		 EMB8600I_Config.h£º        ¹¤¿Ø°åEMB8600I¹¦ÄÜ²ÎÊýÅäÖÃÎÄ¼þ
		 EMB8600I_IOConfig.h£º      ¹¤¿Ø°åEMB8600I IO¶Ë¿ÚÅäÖÃÎÄ¼þ 
		 
		 STM32F107VC_Flash.scat: 	¹¤¿ØÄ£¿éSTM32F107VC, FLASH¼°RAM·ÖÅäÎÄ¼þ	
		 STM32F107VC_FlashIAP.scat: ¹¤¿ØÄ£¿éSTM32F107VC, FLASH¼°RAM·ÖÅäÎÄ¼þ(±àÒë¿ÉÉú³ÉIAP¹¦ÄÜ¹Ì¼þ)  
		 
		 Çë°´¼ü"Alt+F7"´ò¿ªÅäÖÃ½çÃæ, ÔÚLinker½çÃæµÄ"Scatter File"ÏÂ¼ÓÔØÏàÓ¦µÄFLASH¼°RAM·ÖÅäÎÄ¼þ
		 ×¢Òâ: xxxxxxxxxxx_FlashIAP.scat, ¿É±àÒëÉú³ÉIAP¹¦ÄÜ¹Ì¼þº
		 STM32F107VC_Flash.scat: 	¹¤¿ØÄ£¿éSTM32F107VC, FLASH¼°RAM·ÖÅäÎÄ¼þ	
	
	     outputÎÄ¼þ¼Ð£ºÀïÃæÊÇ±àÒëÊä³öÎÄ¼þ£¬ÆäÖÐEMB8600I_APP.HEXÊÇ±àÒëÉú²úµÄHEXÎÄ¼þ¸ñÊ½¹Ì¼þ; 
		               ./bin/MB8600I_APP.binÊÇ±àÒëÉú³ÉbinÎÄ¼þ¸ñÊ½¹Ì¼þ;
	
	(4). µã»÷EMB8600I¹¤³ÌÎÄ¼þ, ÓÃMDK V4.73´ò¿ªÈí¼þ, ½øÐÐ±àÒëÐÞ¸Ä

	(4). ÆäËüÐÍºÅ¹¤¿Ø°å»ò¿ª·¢°å²Î¿¼EMB8600I
---------------------------------------------------------------------------------------------------------------------------		
2. configÄ¿Â¼ÏÂ: 
	(1). vars.c, vars.h: Çý¶¯¿âÄÚ²¿ÒªÓÃµ½µÄ»º´æ¼°È«¾Ö±äÁ¿, ÓÃ»§ÇÐ¼Ç²»¿É¸ü¸Ä»òÌí¼Ó; 
	
	(2). const.h: ÏµÍ³¼°Çý¶¯¿âÈí¼þ³£Á¿¶¨Òå, ÓÃ»§ÇÐ¼Ç²»¿É¸ü¸Ä»òÌí¼Ó; 
	
	(3). config.h: ÏµÍ³Èí¼þ¼°Çý¶¯¿â×ÜÅäÖÃÈí¼þ;
	     ²Ù×÷ÏµÍ³Ê¹ÄÜ¶¨Òå£º
				#define UCOS_II_EN          1	    // 1:Ê¹ÄÜUCOS-II; 0£º²»Ê¹ÓÃUCOS-II;
		 
	     ²úÆ·ÐÍºÅ¶¨Òå: ÓÐ2ÖÖ·½·¨, A. ¸ù¾ÝTarget options.../C C++/Preprocessor Symbols DefineÖÐ¶¨ÒåÑ¡Ôñ²úÆ·ÐÍºÅ
                       B. »òÕßÇë¸ù¾Ý¹ºÂòµÄ²úÆ·ÐÍºÅÑ¡Ôñ, Ö»ÄÜÑ¡ÔñÒ»¸ö, ÆäËü×¢Ïúµô  
			    ÒÔ¹ºÂòÐÍºÅ: EMB8600IÎªÀý:
				#ifdef EMB8600I_TYPE
				#define  PRODUCT_TYPE  EMB8600I	 // ÖÐÇ¶ÁèÔÆ-¹¤¿Ø°å²úÆ·
				#endif
				ÆäÖÐEMB8600I_TYPEÔÚTarget options.../C C++/Preprocessor Symbols DefineÖÐ¶¨Òå
				
				ÔÚÏÂÃæ¸ù¾Ý¹ºÂòÐÍºÅ»á×Ô¶¯Ñ¡ÔñEMB8600IµÄÅäÖÃÎÄ¼þ:
				#if (PRODUCT_TYPE == EMB8600I)      // Èç¹ûÑ¡Ôñ²úÆ·ÐÍºÅ: EMB8600I
				#define  MODULE_CLASS STM32F107XX   // ÉèÖÃ²úÆ·Ó¦ÓÃºËÐÄ¹¤¿ØÄ£¿éÀà±ð, ¶ÔÓ¦Çý¶¯¿âSTM32F107VC_xxxx_xxxxxxxx.lib
				#define  MODULE_TYPE  STM32F107VC   // ÉèÖÃ²úÆ·Ó¦ÓÃºËÐÄ¹¤¿ØÄ£¿éÐÍºÅ, ¶ÔÓ¦Çý¶¯¿âSTM32F107VC_xxxx_xxxxxxxx.lib
				#include "EMB8600I_Config.h"        // ¹¤¿Ø°åEMB8600I¹¦ÄÜ²ÎÊýÅäÖÃÎÄ¼þ
				#include "EMB8600I_IOConfig.h"      // ¹¤¿Ø°åEMB8600I IO¶Ë¿ÚÅäÖÃÎÄ¼þ 
				#endif
	
		¾ßÌåÅäÖÃÎÄ¼þ¶¨Òå, Çë´ò¿ªconfig.h×ÔÐÐ²é¿´	
---------------------------------------------------------------------------------------------------------------------------		
3.  LibrariesÄ¿Â¼ÏÂ
	
	(1). Çý¶¯¿âÎÄ¼þËµÃ÷
	    STM32F107VC_V110_xxxxxxxx.lib: STM32F107VC¹¤¿ØÄ£¿éÇý¶¯¿âÎÄ¼þ, ÊÊÓÃÓÚ¹¤¿Ø°å: EMB8600I¼°ÓÃ¸ÃÄ£¿éÉè¼ÆµÄ¹¤¿Ø°å
		STM32F107VC_NUSB_V110_xxxxxxxx.lib: STM32F107VC¹¤¿ØÄ£¿éÇý¶¯¿âÎÄ¼þ,²»º¬USB¹¦ÄÜÇý¶¯,¼õÉÙÁËÄÚ´æ¼°FLASH¿Õ¼äÕ¼ÓÃ, ÊÊÓÃÓÚ¹¤¿Ø°å: EMB8616I, EMB8600I(²»Ê¹ÓÃUSB)¼°ÓÃ¸ÃÄ£¿éÉè¼ÆµÄ¹¤¿Ø°å		
		
		STM32F103VE_V110_xxxxxxxx.lib: STM32F103VE¹¤¿ØÄ£¿éÇý¶¯¿âÎÄ¼þ, ÊÊÓÃÓÚ¹¤¿Ø°å: ÓÃ¸ÃÄ£¿éÉè¼ÆµÄ¹¤¿Ø°å		                                 
		STM32F103VE_NUSB_V110_xxxxxxxx.lib: STM32F103VE¹¤¿ØÄ£¿éÇý¶¯¿âÎÄ¼þ,²»º¬USB¹¦ÄÜÇý¶¯,¼õÉÙÁËÄÚ´æ¼°FLASH¿Õ¼äÕ¼ÓÃ, ÊÊÓÃÓÚ¹¤¿Ø°å: ÓÃ¸ÃÄ£¿éÉè¼ÆµÄ¹¤¿Ø°å
		
		STM32F103ZE_V110_xxxxxxxx.lib: STM32F103ZE¹¤¿ØÄ£¿éÇý¶¯¿âÎÄ¼þ, ÊÊÓÃÓÚ¹¤¿Ø°å: EMB8612IA¼°ÓÃ¸ÃÄ£¿éÉè¼ÆµÄ¹¤¿Ø°å
		
		STM32F407XX_V110_xxxxxxxx.lib: STM32F407VE/ZE/VG/ZG¹¤¿ØÄ£¿éÇý¶¯¿âÎÄ¼þ, ÊÊÓÃÓÚ¹¤¿Ø°å: EMB8626I, EMB8628I¼°ÓÃ¸ÃÄ£¿éÉè¼ÆµÄ¹¤¿Ø°å 
		
	(2). Çý¶¯¿âÍ·ÎÄ¼þ: 		
		sysint.h: ÏµÍ³Çý¶¯¿â³ÌÐòÍ·ÎÄ¼þ;
		gpio.h:	GPIO¶Ë¿ÚÓ²¼þÇý¶¯³ÌÐòÍ·ÎÄ¼þ;
		exit.h: Íâ²¿ÖÐ¶Ï/ÊÂ¼þ¿ØÖÆÆ÷(EXTI)Ó²¼þÇý¶¯³ÌÐòÍ·ÎÄ¼þ;
		rtc.h:	RTCÓ²¼þÇý¶¯³ÌÐòÍ·ÎÄ¼þ;
		iwdg.h:	¶ÀÁ¢¿´ÃÅ¹·(IWDG)Ó²¼þÇý¶¯³ÌÐòÍ·ÎÄ¼þ;
		uart.h:	UART´®¿ÚÓ²¼þÇý¶¯³ÌÐòÍ·ÎÄ¼þ;
		i2c.h:	I2C×ÜÏßÓ²¼þÇý¶¯³ÌÐòÍ·ÎÄ¼þ;
		spi.h:	SPI×ÜÏßÓ²¼þÇý¶¯³ÌÐòÍ·ÎÄ¼þ;
		can.h:	CANÓ²¼þÇý¶¯³ÌÐòÍ·ÎÄ¼þ;
		timer.h:TimerÓ²¼þÇý¶¯³ÌÐò(°üÀ¨PWMºÍFCLK)Í·ÎÄ¼þ;
		dac.h:	Êý×Ö/Ä£Äâ×ª»»(DAC)Ó²¼þÇý¶¯³ÌÐòÍ·ÎÄ¼þ;
		adc.h:  Ä£Äâ/Êý×Ö×ª»»(ADC)Ó²¼þÇý¶¯³ÌÐòÍ·ÎÄ¼þ;
		flash.h:FLASHÓ²¼þÇý¶¯³ÌÐòÍ·ÎÄ¼þ;
		crc.h:	CRC¼ÆËãÇý¶¯³ÌÐòÍ·ÎÄ¼þ;
		bkp:    ±¸·Ý¼Ä´æÆ÷(BKP)Ó²¼þÇý¶¯³ÌÐòÍ·ÎÄ¼þ;
		sd.h:	FATFSÎÄ¼þÏµÍ³SD¿¨½Ó¿ÚÇý¶¯³ÌÐòÍ·ÎÄ¼þ;
		AT45DBXX.h: AT45DBXXÏµÁÐFLASH¶ÁÐ´Çý¶¯º¯ÊýÍ·ÎÄ¼þ;
		W25QXX.h:	W25QXXÏµÁÐFLASH¶ÁÐ´Çý¶¯º¯ÊýÍ·ÎÄ¼þ;
		eeprom.h:	EEPROM¶ÁÐ´Çý¶¯¿â³ÌÐòÍ·ÎÄ¼þ;
		USBHost.h:  USBÖ÷»ú½Ó¿ÚÇý¶¯³ÌÐòÍ·ÎÄ¼þ(°üÀ¨FATFSÎÄ¼þÏµÍ³UÅÌ½Ó¿Ú);
		USBDevice.h:USBÉè±¸½Ó¿ÚÇý¶¯³ÌÐò;
		net.h:	ÍøÂçÇý¶¯¿â³ÌÐòÍ·ÎÄ¼þ;
		IAP.h:	IAP¸üÐÂ¹Ì¼þÇý¶¯³ÌÐòÍ·ÎÄ¼þ;
		fsmc.h: FSMC×ÜÏßÓ²¼þÇý¶¯³ÌÐòÍ·ÎÄ¼þ;
		NFlash.h: Nand Flash¶ÁÐ´Çý¶¯º¯ÊýÍ·ÎÄ¼þ;
		delay.h:  ÑÓÊ±º¯ÊýÍ·ÎÄ¼þ;
		modbus: MODBUSÐ­ÒéÍ¨ÐÅÇý¶¯³ÌÐòÍ·ÎÄ¼þ;
		subfun.h: ³£ÓÃ×Óº¯ÊýÍ·ÎÄ¼þ;
		
		×¢Òâ: ÓÃ»§ÇÐ¼Ç²»¿ÉÐÞ¸ÄÒÔÉÏÍ·ÎÄ¼þ;
        
    (3). Ó¦ÓÃ³ÌÐòÒýÓÃÇý¶¯¿âÍ·ÎÄ¼þ
		STM32Fxxx.h: ¸ÃÎÄ¼þ°üº¬(2)ÖÐËùÓÐÍ·ÎÄ¼þ, Ó¦ÓÃ³ÌÐòÖ»ÐèÒýÓÃ¸ÃÎÄ¼þ¾Í¿ÉÒÔÓ¦ÓÃÇý¶¯¿â³ÌÐò.

-----------------------------------------------------------------------------------------------------------------------------------------------	
3.  sourceÄ¿Â¼ÏÂ
	(1). UserVars.c, UserVars.h: ÓÃÓÚ¶¨ÒåÓ¦ÓÃ³ÌÐòµÄÈ«¾Ö±äÁ¿, Ç¿ÁÒ½¨ÒéÓ¦ÓÃ³ÌÐòÈ«¾Ö±äÁ¿¶¨Òåµ½ÕâÀï;
	
	(2). app_init.c: ±¾ÎÄ¼þÊÇÓ¦ÓÃ³ÌÐò¼°Çý¶¯¿âµÄ³õÊ¼»¯º¯Êý, ¸ù¾ÝConifg.hÀïµÄÅäÖÃ½øÐÐ³õÊ¼»¯; 
					 ÔÚmain.cÖ÷³ÌÐòÖÐµÚÒ»¸öµ÷ÓÃAPI_Init()½øÐÐÓ¦ÓÃ³õÊ¼»¯; Õâ¸öÎÄ¼þÖÐ³ÌÐòÓÃ»§¸ù¾ÝÐèÒª¿ÉÒÔ¸ü¸Ä;
					 
	(3). ISRHook.c:  ±¾ÎÄ¼þ¸ºÔðÕû¸öÏµÍ³ÖÐ¶Ï´¦Àíº¯Êý; ÓÃ»§ÔÚÕâ¸öÎÄ¼þ´¦ÀíÖÐ¶Ï;
	
	(4). main.c:     ±¾ÎÄ¼þ¸ºÔðÏµÍ³³õÊ¼»¯¡¢ucosÆô¶¯ÓëÈÎÎñ´´½¨¡¢¿´ÃÅ¹·´¦Àí;
	
	(5). TaskIO.c:   ±¾ÎÄ¼þ¸ºÔðIOÊäÈëÊä³öÈÎÎñ´¦Àí; ÓÃ»§ºÍIOÏà¹ØµÄ²Ù×÷ÇëÔÚÕâ¸öÎÄ¼þÖÐ±àÐ´;
	
	(6). TaskUartCan.c: ±¾ÎÄ¼þ¸ºÔð²âÊÔ´®ÐÐÍ¨ÐÅ½Ó¿ÚUART(RS232ºÍRS485)¡¢CANºÍUSBÐéÄâ´®¿ÚÍ¨ÐÅÈÎÎñ´¦Àí; 
					    ÓÃ»§µÄUART/RS232/RS485/CAN/ÐéÄâ´®¿ÚµÄÓ¦ÓÃ³ÌÐòÇëÔÚÕâ¸öÎÄ¼þÖÐ±àÐ´;
						
	(7). TaskADC_DAC.c: ±¾ÎÄ¼þ¸ºÔðADC²É¼¯ºÍDAC1/2×ª»»Êä³öÈÎÎñ´¦Àí; ÓÃ»§AD²É¼¯¼°DAC¿ØÖÆÊä³öÇëÔÚÕâ¸öÎÄ¼þÖÐ±àÐ´;
	
	(8). TaskPWMClk.c:  ±¾ÎÄ¼þ¸ºÔðTIM¶¨Ê±Æ÷, PWMÐÅºÅÊä³ö¼°FCLKÂö³åÊäÈëÈÎÎñ´¦Àí; 	
						ÓÃ»§¶¨Ê±Æ÷²Ù×÷,PWMÊä³ö¿ØÖÆ,FCLKÂö³åÐÅºÅÊäÈë´¦ÀíÇëÔÚÕâ¸öÎÄ¼þÖÐ±àÐ´
						
	(9). TaskModbus.c:  ±¾ÎÄ¼þÊÇModbusÐ­Òé, Ö÷»úÄ£Ê½ºÍ´Ó»úÄ£Ê½²âÊÔÀý³Ì;
						ÓÃ»§Ó¦ÓÃModbusÐ­Òé½øÐÐÖ÷»ú¼°´Ô»úÍ¨ÐÅ, ÇëÔÚÕâ¸öÎÄ¼þÖÐ±àÐ´;
						
	(10). TaskLWIP.c:   ±¾ÎÄ¼þ¸ºÔðÍøÂçÐ­ÒéÕ»LWIP´¦Àí; ÓÃ»§½øÐÐÍøÂçÍ¨ÐÅ¼°ÍøÂç¸üÐÂ¹Ì¼þÇëÔÚÕâ¸öÎÄ¼þÖÐ±àÐ´;
	
	(11). TaskDTU.c:    ±¾ÎÄ¼þ¸ºÔðÓë¹¤ÒµDTUÄ£¿éÍ¨ÐÅÈÎÎñ´¦Àí; ÓÃ»§Íâ½ÓÎÒ¹«Ë¾DTUÍ¨ÐÅÄ£¿é, ÇëÔÚÕâ¸öÎÄ¼þÖÐ±àÐ´;

	(12). AT.c:         ±¾ÎÄ¼þ¸ºÔðATÖ¸Áî´¦Àí;

----------------------------------------------------------------------------------------------------------------------------------------------------		
4. initÄ¿Â¼ÏÂ
    (1). inita.s:   ³ÌÐòÆô¶¯´úÂëÎÄ¼þ, »ã±àÓïÑÔ; Ð¾Æ¬¸´Î»ºó, ×î¿ªÊ¼Ö´ÐÐ¸Ã´úÂë, ×îºóÖ±½ÓÌø×ªµ½mainº¯Êý; ÓÃ»§²»¿ÉÐÞ¸Ä¸ÃÎÄ¼þ; 
	(2). vectors.s: ³ÌÐòÖÐ¶ÏÏòÁ¿±íÎÄ¼þ, »ã±àÓïÑÔ; Ð¾Æ¬ËùÓÐÖÐ¶Ï¶¼»á´ÓÕâ¸ö±í¿ªÊ¼Ö´ÐÐ, Í¨¹ýÕâ¸ö±í½«ÖÐ¶ÏÌø×ªµ½ÖÐ¶Ï´¦Àíº¯Êý; ÓÃ»§²»¿ÉÐÞ¸Ä¸ÃÎÄ¼þ; 

----------------------------------------------------------------------------------------------------------------------------------------------------
5.  fatfsÄ¿Â¼ÏÂ
	(1). ffconf.h: fatfsÎÄ¼þÏµÍ³ÅäÖÃÎÄ¼þ, ÓÃ»§¿É¸ù¾ÝÐèÇóÅäÖÃ²ÎÊý;
	(2). ff.c: fatfsÎÄ¼þÏµÍ³Ô´ÂëÎÄ¼þ, ²»ÐèÒªÐÞ¸Ä;
	(3). ff.h: fatfsÎÄ¼þÏµÍ³Ó¦ÓÃÄ£¿é¹«¹²°üº¬ÎÄ¼þ; ²»ÐèÒªÐÞ¸Ä, ÓÃ»§ÔÚ³ÌÐòÖÐÒª¼ÓÔØÕâ¸öÍ·ÎÄ¼þ²ÅÄÜÓ¦ÓÃÎÄ¼þÏµÍ³º¯Êý;
	(4). diskio.c, diskio.h: fatfsÎÄ¼þÏµÍ³ºÍÓ²¼þ´æ´¢½éÖÊ(SPI Flash,SD¿¨,UÅÌ, Nand Flash)½Ó¿ÚÇý¶¯ÎÄ¼þ¼°Ó¦ÓÃÄ£¿é¹«¹²°üº¬ÎÄ¼þ; 
							 Õâ²¿·ÖÒÑ¾­×öºÃ,ÓÃ»§²»Ðè×öÈÎºÎÐÞ¸Ä;
	
	(5). ffsystem.c: fatfsÎÄ¼þÏµÍ³Óë²Ù×÷ÏµÍ³Ïà¹Ø³ÌÐò, ÓÃ»§¿ÉÒÔÔÚÕâÀï½øÐÐÐÞ¸Ä;
    (6). ffunicode.c: fatfsÎÄ¼þÏµÍ³ÓëUNICODE×Ö¿âÏà¹Ø³ÌÐò; ÓÃ»§Ò»°ã²»ÐèÐÞ¸Ä;
    (7). integer.h: fatfsÎÄ¼þÏµÍ³Êý¾ÝÀàÐÍ¶¨Òå; ÓÃ»§Ò»°ã²»ÐèÐÞ¸Ä;
    
----------------------------------------------------------------------------------------------------------------------------------------------------
6.  lwipÄ¿Â¼ÏÂ(×¢: ÎÞUCOSÀý³ÌÔÝÊ±Î´ÊµÏÖÍøÂçÍ¨ÐÅ)
	(1). lwip.c: ÍøÂçtcpipÐ­ÒéÕ»Ô´ÂëÎÄ¼þ, ÓÃ»§²»¿ÉÐÞ¸Ä;
	(2). sys_arch.c: Óë²Ù×÷ÏµÍ³½Ó¿ÚÇý¶¯ÎÄ¼þ, ÓÃ»§²»ÐèÐÞ¸Ä;
	(3). ethernetif.c: ÓëÍøÂçÓ²¼þÇý¶¯º¯ÊýµÄ½Ó¿ÚÎÄ¼þ, ÓÃ»§Ò»°ã²»ÐèÐÞ¸Ä;
	(4). lwipopts.h: lwip³£ÓÃ²ÎÊýÅäÖÃÎÄ¼þ, ÓÃ»§¸ù¾ÝÐèÒªÐÞ¸Ä;
	(5). opt.h: lwipÈ«²¿²ÎÊýÅäÖÃÎÄ¼þ, ÓÃ»§¸ù¾ÝÐèÒªÐÞ¸Ä;

----------------------------------------------------------------------------------------------------------------------------------------------------
7.  OSConfigÄ¿Â¼ÏÂ(×¢: ÎÞUCOSÀý³ÌÎÞ¸ÃÄ¿Â¼)
	(1). OSHook.c, OSHook.h: ²Ù×÷ÏµÍ³»Øµ÷º¯ÊýÎÄ¼þ;
	(2). OSVars.c,OSVars.h: ²Ù×÷ÏµÍ³ÈÎÎñÈ«¾Ö±äÁ¿¶¨Òå, ÓÃ»§¿ÉÒÔ°ÑºÍ²Ù×÷ÏµÍ³Ïà¹ØµÄÈ«¾Ö±äÁ¿ÉèÖÃµ½ÕâÀï;
	(3). app_cfg.h: ¸ºÔð²Ù×÷ÏµÍ³¸÷¸öÈÎÎñÓÅÏÈ¼¶ºÍ¶ÑÕ»ÅäÖÃ;
	(4). os_cfg.h: ²Ù×÷ÏµÍ³ÅäÖÃÎÄ¼þ;	
---------------------------------------------------------------------------------------------------------------------------------	
8.  ucos-iiÄ¿Â¼ÏÂ(×¢: ÎÞUCOSÀý³ÌÎÞ¸ÃÄ¿Â¼)
	(1). ucos-ii.c: ²Ù×÷ÏµÍ³Ô´ÂëÎÄ¼þ;
	(2). os_cpu_a.asm, cpu_a.asm, lib_mem_a.asm: ²Ù×÷ÏµÍ³ÓëMCUÓ²¼þÏà¹ØµÄÒÆÖ²ÎÄ¼þ; ÓÃ»§²»¿ÉÐÞ¸Ä;
----------------------------------------------------------------------------------------------------
¹ØÓÚ²âÊÔ³ÌÐòÐÞ¸ÄËµÃ÷£º
----------------------------------------------------------------------------------------------------
ÈÕÆÚ: 2019.3.6
ÐÞ¸Ä: ÕýÊ½·¢²¼°æ
----------------------------------------------------------------------------------------------------
°æ±¾£ºV1.10: 
ÈÕÆÚ: 2019.6.1
ÐÞ¸Ä: (1). ¸üÐÂÇý¶¯¿â, ×îÐÂÈÕÆÚ2019.6.1
	  (2). ²âÊÔ³ÌÐò½øÐÐ²¿·ÖÐÞ¸Ä
----------------------------------------------------------------------------------------------------
°æ±¾£ºV1.10: 
ÈÕÆÚ: 2019.9.1
ÐÞ¸Ä: (1). ¸üÐÂÇý¶¯¿â, ×îÐÂÈÕÆÚ2019.9.1
	  (2). Ôö¼Ó×Ô¶¨ÒåATÖ¸Áî¿ØÖÆ, ½«ËùÓÐ´òÓ¡Êä³ö¶¼ÒÔATÖ¸ÁîÐÎÊ½Êä³ö
	  (3). ¸üÐÂ¹¤³ÌÎÄ¼þ¼°ÅäÖÃÎÄ¼þ´æ·ÅÎ»ÖÃ£º
	       Ôö¼ÓtagetsÄ¿Â¼×÷Îª¹¤³ÌÎÄ¼þ´æ·ÅÎ»ÖÃ, ²Î¿¼1ÖÐtargetsÄ¿Â¼ËµÃ÷
		   ¸ùÄ¿Â¼ÏÂconfigÄ¿Â¼Ö»´æ·Åvars.c, vars.h, const.h, config.h, ÆäËüÎÄ¼þÈ«²¿Å²µ½./targets/.../configÏÂ

----------------------------------------------------------------------------------------------------
°æ±¾£ºV1.10: 
ÈÕÆÚ: 2019.10.1
ÐÞ¸Ä: (1). ¸üÐÂÇý¶¯¿â, ×îÐÂÈÕÆÚ2019.10.1
	  (2). ÐÞ¸ÄDI_Read()º¯Êý, ½â¾ö¶à¸öDIÍ¬Ê±±ä»¯Ê±º¯ÊýÖ´ÐÐÊ±¼ä¹ý³¤ÎÊÌâ

---------------------------------------------------------------------------------------------------
°æ±¾£ºV1.10: 
ÈÕÆÚ: 2019.11.1
ÐÞ¸Ä: (1). ¸üÐÂÇý¶¯¿â, ×îÐÂÈÕÆÚ2019.11.1
      (2). ÐÞ¸ÄCAN_APPInit()º¯Êý: CANPara.IDE³õÊ¼»¯Ê¹ÓÃÅäÖÃCAN1_IDE; CANPara.RTR³õÊ¼»¯Ê¹ÓÃÅäÖÃCAN1_RTR; 
	  (3). ÐÞ¸ÄTaskUartCan.c,CAN²Ù×÷²¿·ÖÊ¹ÓÃAT_CAN_FLAG±êÖ¾

---------------------------------------------------------------------------------------------------
°æ±¾£ºV1.10: 
ÈÕÆÚ: 2020.8.24
ÐÞ¸Ä: (1). ¸üÐÂÇý¶¯¿â, ×îÐÂÈÕÆÚ2020.8.24, ¾ßÌåÐÞ¸ÄÄÚÈÝ¼ûlib_readme.txt;
      (2). ÐÞ¸ÄAPP_Init.cÎÄ¼þ²¿·Öº¯Êý£¬Ôö¼ÓDMA¹¦ÄÜÅäÖÃ; 
	  (3). ÐÞ¸ÄTaskLWIP.c, ÐÞ¸Ä²¿·Ö³ÌÐò;
	  (4). ÐÞ¸ÄTaskPWMFClk.c, Ôö¼ÓPWMµÄDMA¹¦ÄÜ¿ØÖÆÂö³åÊä³ö;
	  (5). Ôö¼ÓAT.cÎÄ¼þ, Íê³ÉATÖ¸ÁîV1.00°æ±¾¿ØÖÆ;
	  (6). ÆäËü²¿·Ö³ÌÐòÐÞ¸Ä;
	  

---------------------------------------------------------------------------------------------------