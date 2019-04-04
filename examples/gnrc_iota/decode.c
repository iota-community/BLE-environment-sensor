#include <stdio.h>

#include "pb_decode.h"
#include "pb_encode.h"

#include "proto_compiled/test.pb.h"

bool decode_status;

int decode_transaction_message(
        IotaTransactionMessage * message_ptr, uint8_t * encoded_msg_ptr, size_t decoded_msg_size) {
    pb_istream_t stream = pb_istream_from_buffer(encoded_msg_ptr, decoded_msg_size);

    decode_status = pb_decode(&stream, TestMessage_fields, message_ptr);

    if (!decode_status)
    {
        printf("Decoding failed: %s\n", PB_GET_ERROR(&stream));
        return 1;
    }

    return 0;
}
