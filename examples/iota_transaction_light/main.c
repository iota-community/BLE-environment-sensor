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
#include <stdint.h>

#include "iota/kerl.h"
#include "iota/conversion.h"
#include "iota/addresses.h"
#include "iota/transfers.h"

typedef struct {
    iota_wallet_tx_output_t txs[1];
    uint32_t length;
} iota_txs_output_buffer_t;

typedef struct {
    iota_wallet_tx_input_t txs[1];
    uint32_t length;
} iota_txs_input_buffer_t;

iota_txs_output_buffer_t output_buffer = {};
iota_txs_input_buffer_t input_buffer = {};

char transaction_chars[2674];
char bundle_hash[81];
int tx_receiver(iota_wallet_tx_object_t * tx_object){
    puts("\n");
    puts("Address: ");
    puts(tx_object->address);
    puts("Tag: ");
    puts(tx_object->tag);
    puts("Value: ");
    printf("\n%li\n", (long int) tx_object->value);
    puts("currentIndex:");
    printf("\n%li\n", tx_object->currentIndex);
    puts("lastIndex:");
    printf("\n%li\n", tx_object->lastIndex);
    puts("Signature: ");
    puts(tx_object->signatureMessageFragment);
    puts("\n\n");
    puts("raw transaction data:\n");
    iota_wallet_construct_raw_transaction_chars(transaction_chars,bundle_hash, tx_object);
    puts(transaction_chars);

    return 1;
}

int bundle_receiver(char * hash){
    puts("HASH: ");
    puts("");
    strcpy(bundle_hash, hash);
    for(int i = 0; i < 81; i++){
        printf("%c", hash[i]);
    }
    puts("\n\n");

    return 1;
}

//Define the transaction chars array. The char trytes will saved in this array. (base-27 encoded)
//char transaction_chars[4][2673];

char seedChars[] = "J9FERMAA9BPBCJEOZUKTIRIQEOQHFWYTHTJB9PI9KGUHPTLVX9TQJACWTUNVQJKEQVDRDBIJIB9WAHTVB";

//tx_receiver_t tx_receiver_func = &tx_receiver;
//bundle_hash_receiver bundle_receiver_func = &bundle_receiver;

int run_bundle_creation(void){

    char address_from[81];
    iota_wallet_get_address(seedChars, 0, 2, address_from);

    char address_to[81];
    iota_wallet_get_address(seedChars, 1, 2, address_to);

    //Alias for txs buffer
    iota_wallet_tx_output_t * txs_output = output_buffer.txs;
    iota_wallet_tx_input_t * txs_input = input_buffer.txs;

    unsigned char seedBytes[48];
    chars_to_bytes(seedChars, seedBytes, 81);

    puts("Create IOTA transactions bundle...");

    //Define output
    iota_wallet_tx_output_t * first_output = &txs_output[0];
    strcpy(first_output->address, address_to);
    first_output->value = 10000;

    //Define the input array. Where the coins come from
    iota_wallet_tx_input_t * first_input = &txs_input[0];

    first_input->key_index = 0;
    first_input->value = 10000;
    strcpy(first_input->address, address_from);


    //Get all raw transaction trytes. Will saved in transaction_chars
    puts("Prepare transfer...");

    uint8_t security = 2;
    iota_wallet_bundle_description_t bundle_description;
    strcpy(bundle_description.seed, seedChars);
    bundle_description.security = security;
    bundle_description.output_txs = output_buffer.txs;
    bundle_description.output_txs_length = 1;
    bundle_description.input_txs = input_buffer.txs;
    bundle_description.input_txs_length = 1;
    bundle_description.timestamp = 0;

    iota_wallet_create_tx_bundle(&bundle_receiver, &tx_receiver, &bundle_description);
    puts("Prepared Transfer.");

    puts("IOTA transaction chars: ");
    /*for(int i = 0; i < 3; i++){
        printf("%s", transaction_chars[i]);
    }*/
    puts("DONE.");

    return 0;
}

//Fixme: It is not preparing a tx bundle
int main(void)
{
    puts("IOTA Wallet Application");
    puts("=====================================");

    run_bundle_creation();

    return 0;
}