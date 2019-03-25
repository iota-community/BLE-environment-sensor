/*
 * Copyright (C) 2015 IOTA Foundation
 *
 * This file is subject to the terms and conditions of the GNU Lesser
 * General Public License v2.1. See the file LICENSE in the top level
 * directory for more details.
 */

/**
 * @ingroup     examples
 * @{
 *
 * @file
 * @brief       Example application for a POSIX socket server with sensor data (Protobuf)
 *
 * @author      Philipp-Alexander Blum <philipp.blum@iota.org>
 *
 * @}
 */

#include <stdio.h>

#include "shell.h"
#include "msg.h"

/**
 * You need to use the MCU pins, described here: http://riot-os.org/api/group__boards__nrf52dk.html
 * or read the MCU specification
 */

//Todo: Find better configuration place. Remove it from driver. Board config?
//#undef DHT_PARAM_PIN
//#define DHT_PARAM_PIN               (GPIO_PIN(0, 27))

#define MAIN_QUEUE_SIZE     (8)
static msg_t _main_msg_queue[MAIN_QUEUE_SIZE];

extern int server_cmd(int argc, char **argv);

static const shell_command_t shell_commands[] = {
    { "server", "a sensor data server", server_cmd },
    { NULL, NULL, NULL }
};

int main(void)
{
    /* we need a message queue for the thread running the shell in order to
     * receive potentially fast incoming networking packets */
    msg_init_queue(_main_msg_queue, MAIN_QUEUE_SIZE);
    puts("IOTA RIOT Env sensor server");

    /* start shell */
    char line_buf[SHELL_DEFAULT_BUFSIZE];
    shell_run(shell_commands, line_buf, SHELL_DEFAULT_BUFSIZE);

    /* should be never reached */
    return 0;
}
