
compressor: words delivered from file. file name provided via command line. there're `-wif24` and `-hex32_24` options     

dcompressor: base58 encoded thing or hex string provided via command line.  there're `-wif24` and `-hex32_24` options  

msvc 2019 project with cmake build support.  
in windows you should have libcrypto.dll next to .exe files, not included  
wif key is 27 words or 24 words with `-wif24` option.  
`-hex32_24` option is for tranfering private keys in hex

for `bc1q` address you can import stuff from `compressor`. Even if you'd used uncompressed wif in `decompressor`
