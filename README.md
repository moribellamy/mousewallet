# Mousewallet

An example implementation of generating an ethereum wallet in C99.

```
$ ./mousewallet --help
Usage: mousewallet [options]

Create Ethereum wallets.

    -h, --help            show this help message and exit

    Basic options
        -p, --prefix=<str>    prefix to seek
```

If no args are given, generate a private key (along with the resulting eth address) to STDOUT.

If the `--prefix` arg is given, we generate random wallets until we find one with the given prefix.
