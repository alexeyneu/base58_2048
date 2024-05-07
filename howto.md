
compressor: words delivered from file. file name provided via command line. there're `-wif24` and `-hex32_24` options     

dcompressor: base58 encoded thing or hex string provided via command line.  there're `-wif24` and `-hex32_24` options  

msvc 2019 project with cmake build support. `open folder` in msvc  
in windows you should have `libcrypto.dll` next to `.exe` files. included to binaries here Also can be found in poco project or in compiled and linked openssl sources Any edition where it's called so will work for sure   
wif key is 27 words. 24 words or less with `-wif24` option.  
`-hex32_24` option is for tranfering private keys in hex

for `bc1q` address you can import stuff from `compressor`. Even if you'd used uncompressed wif in `decompressor`  
`P2WPKH`  
  
leading zeroes concept is kept despite that the tool can't be applied to private keys with zero bytes at start , it will deny to work in this case so you'll not see phrase at all. Yet new tool can be done from original base58 by just replace of byte range [0..255] to [0..2047] there if soomeone will lose access to this one.
