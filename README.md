# CS263Project

## step of how to compile and run C/C++ program on web assembly

running on local webassembly runtime
```shell
emcc file -o executable -s STANDALONE_WASM=1
wasm3 executable argument1 argument2 ...
```
running on browser
```shell
 emcc matrix.c -o matrix.js -sEXPORTED_FUNCTIONS="['function_name']" -sEXPORTED_RUNTIME_METHODS="['cwrap']" -sALLOW_MEMORY_GROWTH=1 -O3
```
## benchmark tools
by using the following shell command 
```shell
time wasmtime executable argument1 argument2 ...
perf stat wasmtime executable argument1 argument2 ...
perf record wasmtime executable argument1 argument2 ...
perf report
perf trace wasmtime executable argument1 argument2 ...
# generate flamegraph
perf record -g wasmtime my_program.wasm
perf script | stackcollapse-perf.pl | flamegraph.pl > flamegraph.svg
```
## TODO benchmark 
matrix_multiplication -[x]
recursion -[x]
file_io (to test file io, we need to use wasmtime and compile by using clang instead of emcc)

