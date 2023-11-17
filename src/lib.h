#ifndef C90ETH_LIBRARY_H
#define C90ETH_LIBRARY_H

#include <stdio.h>
#include <stdlib.h>

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
int encode_hex(char *hex, const unsigned char *bin, size_t size);

/**
 * @param wallet_bytes The bytes for the generated wallet from the private key.
 * @param private_key_bytes  The private key from which to generate the wallet.
 */
void wallet_from_private_key(unsigned char *wallet_bytes,
                             unsigned const char *private_key_bytes);

#endif // C90ETH_LIBRARY_H
