/**
 * @file      nr_micro_shell_commands.c
 * @author    Nrush
 * @version   V0.1
 * @date      28 Oct 2019
 * *****************************************************************************
 * @attention
 * 
 * MIT License
 * 
 * Copyright (C) 2019 Nrush. or its affiliates.  All Rights Reserved.
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

/* Includes ------------------------------------------------------------------*/

#include "nr_micro_shell.h"
#include <string.h>
#include <ctype.h>

#include "NuMicro.h"
#include "project_config.h"

void custom_cmd_led_toggle(char argc, char *argv)
{
	if (argc > 1)
	{
		if (!strcmp("on", &argv[argv[1]]))
		{
			shell_printf("led toggle on\r\n");
			while(!UART_IS_TX_EMPTY(DEBUG_PORT));			
			
			set_flag(flag_console_led_on , ENABLE);
		}
		else if (!strcmp("off", &argv[argv[1]]))
		{
			shell_printf("led toggle off\r\n");
			while(!UART_IS_TX_EMPTY(DEBUG_PORT));			
			
			set_flag(flag_console_led_off , ENABLE);
		}
		else
		{
			shell_printf("led toggle cmd wrong para!\r\n");
		}
	}
	else
	{
		shell_printf("led toggle cmd invalid!\r\n");
	}
}


void custom_cmd_gpio_off(char argc, char *argv)
{
	shell_printf("gpio_off\r\n");
	while(!UART_IS_TX_EMPTY(DEBUG_PORT));

	set_flag(flag_console_gpio_off , ENABLE);
}

void custom_cmd_gpio_on(char argc, char *argv)
{
	shell_printf("gpio_on\r\n");
	while(!UART_IS_TX_EMPTY(DEBUG_PORT));

	set_flag(flag_console_gpio_on , ENABLE);
}

void custom_cmd_chip_reset(char argc, char *argv)
{
	shell_printf("chip reset\r\n");
	while(!UART_IS_TX_EMPTY(DEBUG_PORT));

	set_flag(flag_console_sys_chip_reset , ENABLE);
}

void custom_cmd_nvic_reset(char argc, char *argv)
{
	shell_printf("nvic reset\r\n");
	while(!UART_IS_TX_EMPTY(DEBUG_PORT));

	set_flag(flag_console_sys_nvic_reset , ENABLE);
}

void custom_cmd_list_qmark(char argc, char *argv)
{
	unsigned int i = 0;

	for (i = 0; nr_shell.static_cmd[i].fp != NULL; i++)
	{
		shell_printf("%s",nr_shell.static_cmd[i].cmd);
		shell_printf("\r\n");
	}
}


/**
 * @brief ls command
 */
void shell_ls_cmd(char argc, char *argv)
{
	unsigned int i = 0;
	if (argc > 1)
	{
		if (!strcmp("-l", &argv[argv[1]]))
		{

			for (i = 0; nr_shell.static_cmd[i].fp != NULL; i++)
			{
				shell_printf("%s",nr_shell.static_cmd[i].cmd);
				shell_printf("\r\n");
			}
		}
		else if (!strcmp("-v", &argv[argv[1]]))
		{
			shell_printf("ls version 1.0.\r\n");
		}
		else if (!strcmp("-h", &argv[argv[1]]))
		{
			shell_printf("useage: ls [options]\r\n");
			shell_printf("options: \r\n");
			shell_printf("\t -h \t: show help\r\n");
			shell_printf("\t -v \t: show version\r\n");
			shell_printf("\t -l \t: show all commands\r\n");
		}
	}
	else
	{
		shell_printf("ls need more arguments!\r\n");
	}
}

/**
 * @brief test command
 */
void shell_test_cmd(char argc, char *argv)
{
	unsigned int i;
	shell_printf("test command:\r\n");
	for (i = 0; i < argc; i++)
	{
		shell_printf("paras %d: %s\r\n", i, &(argv[argv[i]]));
	}
}

#ifdef NR_SHELL_USING_EXPORT_CMD
NR_SHELL_CMD_EXPORT(ls, shell_ls_cmd);
NR_SHELL_CMD_EXPORT(test, shell_test_cmd);
#else
const static_cmd_st static_cmd[] =
	{
		{"ls", shell_ls_cmd},
		{"test", shell_test_cmd},

		{"?", custom_cmd_list_qmark},		
		{"sys_nvic_reset", custom_cmd_nvic_reset},
		{"sys_chip_reset", custom_cmd_chip_reset},
		{"gpio_on", custom_cmd_gpio_on},
		{"gpio_off", custom_cmd_gpio_off},				
		{"led", custom_cmd_led_toggle},


		{"\0", NULL}};
#endif

/******************* (C) COPYRIGHT 2019 Nrush *****END OF FILE*****************/
