/*
 * Copyright (c) 2016 Intel Corporation
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr.h>
#include <device.h>
#include <devicetree.h>
#include <drivers/gpio.h>


/* The devicetree node identifier for the "led0" alias. */
#define LED_NODE DT_ALIAS(led0)

#if DT_NODE_HAS_STATUS(LED_NODE, okay)
#define LED DT_GPIO_LABEL(LED_NODE, gpios)
#define PIN DT_GPIO_PIN(LED_NODE, gpios)
#define FLAGS DT_GPIO_FLAGS(LED_NODE, gpios)
#else
/* A build error here means your board isn't set up to blink an LED. */
#error "Unsupported board: led devicetree alias is not defined"
#define LED0	""
#define PIN	0
#define FLAGS	0
#endif

static const struct device *pwrled;

void pwr_led_init(void) {
	pwrled = device_get_binding(LED);
	if (pwrled == NULL) {
		return;
	}	

	gpio_pin_configure(pwrled, PIN, GPIO_OUTPUT_ACTIVE | FLAGS);
	gpio_pin_set(pwrled, PIN, (int)1);	
	}

SYS_INIT(pwr_led_init, APPLICATION, CONFIG_APPLICATION_INIT_PRIORITY);
