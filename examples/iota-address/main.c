/*
 * Copyright (C) 2018 Inria
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
 * @brief       Example demonstrating of a IOTA address generation in RIOT
 *
 * @author      Philipp-Alexander Blum <philipp-blum@jakiku.de>
 *
 * @}
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "thread.h"

#include "iota/kerl.h"
#include "iota/conversion.h"
#include "iota/addresses.h"

int main(void)
{
    puts("IOTA Wallet Application");
    puts("=====================================");

    unsigned char address[81];
    char seedChars[] = "V9OZSHTBMXMFKSXOMPJTORZ9RYTXWQWUJLBTRLSLMLLKPIAWWEZRFHFNAEJAIMH9QHBJRCLLLMSAJSDIW";
    unsigned char seedBytes[48];
    chars_to_bytes(seedChars, seedBytes, 81);
    get_public_addr(seedBytes, 0, 2, address);

    char charAddress[81];
    bytes_to_chars(address, charAddress, 48);

    puts("Generate IOTA address...");
    printf("Generated address: ");
    printf(charAddress);

    return 0;
}
