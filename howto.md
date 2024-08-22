
compressor: words delivered from file. file name provided via command line. there're `-secretkey`,`-wif24` and `-hex32_24` options     

dcompressor: base58 encoded thing or hex string provided via command line.  there're `-secretkey`, `-wif24` and `-hex32_24` options  

msvc 2019 project with cmake build support(option during msvc setup). `open folder` in msvc  
in windows you should have `libcrypto.dll` next to `.exe` files. included to binaries here Also can be found in poco project or in compiled and linked openssl sources Any edition where it's called so will work for sure   
wif key is 27 words. 24 words or less with `-wif24` option.  
`-hex32_24` option is for tranfering private keys in hex  
`-secretkey` is for cryptocurrencies that use edwards25519 curve. say if you wanna account on `mango markets`.  `[]` thing is supported in mfc edition but not here. too long to be an arg  

for `bc1q` address you can import stuff from `compressor`. Even if you'd used uncompressed wif in `decompressor`  
`P2WPKH`  
  
leading zeroes concept is kept despite that the tool can't be applied to private keys with zero bytes at start , it will deny to work in this case so you'll not see phrase at all. Yet new tool could be made out of original base58 by just replacing the byte value range [0..255] with [0..2047] one there. in case soomeone will lose access to this one. With some effort and programming skills key still can be decoded havin zero knowledge about how this app is coded
