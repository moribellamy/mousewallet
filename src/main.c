#include <stdio.h>
#include <string.h>

#include "../vendor/argparse/argparse.h"
#include "../vendor/secp256k1/examples/examples_util.h"
#include "../vendor/secp256k1/include/secp256k1.h"
#include "lib.h"

static const char *const usages[] = {
    "c90eth [options]",
    NULL,
};

int main(int argc, const char *argv[]) {
  const char *target_prefix = "";

  struct argparse_option options[] = {
      OPT_HELP(),
      OPT_GROUP("Basic options"),
      OPT_STRING('p', "prefix", &target_prefix, "prefix to seek", NULL, 0, 0),
      OPT_END(),
  };
  struct argparse argparse;
  argparse_init(&argparse, options, usages, 0);
  argparse_describe(&argparse, "\n Create Ethereum wallets.", "");
  argc = argparse_parse(&argparse, argc, argv);

  if (argc != 0) {
    argparse_help_cb(&argparse, NULL);
    return 1;
  }

  unsigned char wallet_bytes[20], private_key_bytes[32];
  size_t target_hex_len = strlen(target_prefix);

  while (1) {
    CRASH_IF(fill_random(private_key_bytes, 32) != 1,
             "Couldn't generate random key.");
    wallet_from_private_key(wallet_bytes, private_key_bytes);
    char wallet_hex[41], private_key_hex[65];
    encode_hex(wallet_hex, wallet_bytes, 20);
    if (strncmp(target_prefix, wallet_hex, target_hex_len) == 0) {
      encode_hex(private_key_hex, private_key_bytes, 32);
      printf("wallet: 0x%s\n", wallet_hex);
      printf("key:    0x%s\n", private_key_hex);
      return 0;
    }
  }
}
