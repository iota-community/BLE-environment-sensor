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
 * @brief       Example demonstrating of transaction in IOTA with RIOT
 *https://github.com/embedded-iota/iota-c-light-wallet
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
#include "iota/transfers.h"

//Fixme: It is not preparing a tx bundle
int main(void)
{
    puts("IOTA Wallet Application");
    puts("=====================================");

    char seedChars[] = "INSERTASEED";
    unsigned char seedBytes[48];
    chars_to_bytes(seedChars, seedBytes, 81);


    puts("Create IOTA transactions bundle...");

    //Define the output array, where the coins must initialization makes integer from pointer without a cast go to.
    TX_OUTPUT * output_one = malloc(sizeof(TX_OUTPUT));

    strcpy(output_one->address, "XFYMCVTPGGXKJ9RONKOJQKQJXMORGHSPOFXEYJBJJYZDFSTBAYIOWESKBJVMHDFELQMDGIS9XJXNRIQMA");
    output_one->value = 1000;

    puts(output_one->address);


    TX_OUTPUT output_txs[1] = {*output_one}; //ANADDRESS => 81 ternary characters

    //Define the input array. Where the coins come from

    TX_INPUT * input_one = malloc(sizeof(TX_INPUT));
    input_one->key_index = 0;
    input_one->balance = 10000;


    TX_INPUT input_txs[1] = {*input_one};


    //Define the transaction chars array. The char trytes will saved in this array. (base-27 encoded)
    char transaction_chars[10][2673];
    //Get all raw transaction trytes. Will saved in transaction_chars
    prepare_transfers(seedChars, 2, output_txs, 1, input_txs, 1, transaction_chars);

    puts("IOTA transaction chars: ");
    for(int i = 0; i < 10; i++){
        puts(transaction_chars[i]);
    }

    return 0;
}
