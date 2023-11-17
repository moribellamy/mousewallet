#include "../vendor/tinytest/tinytest.h"
#include "lib.h"
#include <string.h>

void test_hex2bin() {
  const char *hex = "dead40";
  const unsigned long len = 3;
  unsigned char *buf = malloc(len);

  ASSERT_EQUALS(1, decode_hex(buf, hex));
  ASSERT_EQUALS(3, len);
  ASSERT_EQUALS((unsigned char)'\xde', buf[0]);
  ASSERT_EQUALS((unsigned char)'\xad', buf[1]);
  ASSERT_EQUALS((unsigned char)'\x40', buf[2]);
}

void test_hex2bin_odd_input() {
  const char *hex = "dead4";
  const unsigned long len = 3;
  unsigned char *buf = malloc(len);
  ASSERT_EQUALS(0, decode_hex(buf, hex));
}

void test_hex2bin_wrong_bufsize() {
  const char *hex = "dead4";
  const unsigned long len = 2;
  unsigned char *buf = malloc(len);
  ASSERT_EQUALS(0, decode_hex(buf, hex));
}

void test_wallet_from_private_key() {
  // https://github.com/ethereumbook/ethereumbook/blob/develop/04keys-addresses.asciidoc
  char private_key_hex[65] =
      "f8f8a2f43c8376ccb0871305060d7b27b0554d2cc72bccf41b2705608452f315";
  unsigned char private_key_bytes[32];
  decode_hex(private_key_bytes, private_key_hex);

  unsigned char wallet_bytes[20];
  wallet_from_private_key(wallet_bytes, private_key_bytes);
  char wallet_hex[41];
  encode_hex(wallet_hex, wallet_bytes, 20);

  ASSERT_STRING_EQUALS("001d3f1ef827552ae1114027bd3ecf1f086ba0f9", wallet_hex);
}

int main() {
  RUN(test_hex2bin);
  RUN(test_hex2bin_odd_input);
  RUN(test_hex2bin_wrong_bufsize);
  RUN(test_wallet_from_private_key);
  return TEST_REPORT();
}
