/*
 * SPI  based ARINC429 driver
 This Driver provides interface for arinc429 with SPI 
 *
 * Copyright (c) 2009 ASL Advanced Systems Pvt Ltd.
 * for any clarifications please contact Ravi kulkarni <sunr2007@gmail.com>	
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License version 2 as
 *  published by the Free Software Foundation.
 */
#include <linux/hwmon.h>
#include <linux/init.h>
#include <linux/err.h>
#include <linux/delay.h>
#include <linux/input.h>
#include <linux/interrupt.h>
#include <linux/slab.h>
#include <linux/gpio.h>
#include <linux/spi/spi.h>
#include <asm/irq.h>
#include <linux/module.h>
unsigned  is_suspended:1;

static int arinc429_suspend(struct spi_device *spi,pm_message_t message)
{
	struct arinc429  *arinc=dev_get_drvdata(&spi->dev);
	spin_lock(&arinc->lock);
	arinc->is_suspended=1;
	arinc429_disable(arinc);
	spin_unlock(&arinc->lock);	

} 

static int arinc429_resume(struct spi_device *spi)
{
	struct arinc429 *arinc=dev_get_drvdata(&spi->dev);
	spin_lock(&arinc->lock);
	arinc->is_suspended=0;
	arinc429_enable(arinc);
	spin_unlock(&arinc->lock);
	
}
static int __devinit arinc429_probe(struct spi_device *spi)
{	
	struct arinc429 		 *arinc;
	struct arinc429_platform_data    *pdata=spi->dev.platform_data;
	struct spi_message		 *m;
	struct spi_transfer		 *x;

/*  I would like to  set TX wordsize 16 bits and RX wordsize to 16 bits ... except
          * that even if the hardware can do that, the SPI controller driver
          * may not.  So I  stick to very-portable 8 bit words for the time being 
	 , both RX and TX. If anybody wants to change this >8 they are most welcome to discuss*/

	spi->mode=SPI_MODE_0;
	spi->bits_per_word=8;
	err=spi_setup(spi);
	if (err<0)
	return err;
	arinc=kzalloc(sizeof(struct arinc429),GFP_KERNEL);
	dev_set_drvdata(&spi->dev,arinc);
	arinc->spi=spi;

}

static struct spi_driver arinc429_driver={
		.driver={
		.name="arinc429";
		.bus=&spi_bus_type;
		.owner=THIS_MODULE;
	},	
		.probe=arinc429_probe,
		.remove=__devexit_p(arinc429_remove),
		.suspend=arinc429_suspend,
		.resume=arinc429_resume,
		
};


static int __init arinc429_init(void)
	{
	return arincspi_register_driver(&arinc429_driver);
	}
module_init(arinc429_init);
static void __exit arinc429_exit(void)
	{
	arincspi_unregister_driver(&arinc429_driver);
	}
module_exit(arinc429_exit);
MODULE_LICENSE("GPL");
MODULE_AUTOR("Ravi Kulkarni(sunr2007@gmail.com)");
MODULE_DESCRIPTION("ARINC 429 driver using spi ");