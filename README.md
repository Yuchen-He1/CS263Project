# CS263Project

##step of how to compile and run C/C++ program on web assembly

running on local webassembly runtime
```shell
emcc file -o executable -s STANDALONE_WASM=1
wasm3 executable argument1 argument2 ...
```
running on browser
```shell
 emcc matrix.c -o matrix.js -sEXPORTED_FUNCTIONS="['function_name']" -sEXPORTED_RUNTIME_METHODS="['cwrap']" -sALLOW_MEMORY_GROWTH=1 -O3
```
##TODO benchmark 
matrix_multiplication -[x]
recursion -[x]
file_io (code is running on sandbox(webassembly) and wasm3 doesn't support access file system)
