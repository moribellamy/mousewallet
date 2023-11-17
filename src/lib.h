#ifndef MOUSEWALLET_LIB_H
#define MOUSEWALLET_LIB_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../vendor/pcg-c/extras/entropy.h"
#include "../vendor/pcg-c/include/pcg_variants.h"

#define CRASH_IF(bool_val, message)                                            \
  do {                                                                         \
    if (bool_val) {                                                            \
      fprintf(stderr, "Error in %s at line %d: %s\n", __FILE__, __LINE__,      \
              (message));                                                      \
      exit(1);                                                                 \
    }                                                                          \
  } while (0)

/**
 * @param bin Output buffer for binary data. Always zeroed-out before
 * attempted conversion. strlen(hex) / 2 bytes will be written.
 * @param hex The hexadecimal string to convert. If invalid, population of the
 * output bin stops. Should have even length.
 * @return 1 on success, 0 otherwise.
 */
int decode_hex(unsigned char *bin, const char *hex);

/**
 * @param hex Output buffer for hex data. <size>*2+1 chars will be written. The
 * last one is '\0'.
 * @param bin Input binary to encode.
 * @param size Size of <bin>.
 * @return 1 on success, 0 otherwise.
 */
static inline int encode_hex(char *hex, const unsigned char *bin, size_t size) {
  memset(hex, 0, size * 2);
  size_t i;
  int offset = 0;
  for (i = 0; i < size; i++) {
    offset += sprintf(hex + offset, "%02x", bin[i]);
  }
  return 1;
}

/**
 * @param wallet_bytes The bytes for the generated wallet from the private key.
 * @param private_key_bytes  The private key from which to generate the wallet.
 */
void wallet_from_private_key(unsigned char *wallet_bytes,
                             unsigned const char *private_key_bytes);

#endif // MOUSEWALLET_LIB_H
