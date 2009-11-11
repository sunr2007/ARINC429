/*
 * SPI  based ARINC429 protocol  driver
 This Driver implements arinc 429 protocol implementation 
why so serious?
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





module_init();
module_exit();
MODULE_LICENSE("GPL");
MODULE_AUTOR("Ravi Kulkarni(sunr2007@gmail.com)");
MODULE_DESCRIPTION("ARINC 429 PROTOCOL Implementation using spi ");