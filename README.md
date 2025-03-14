# CS263Project

## Requirements
```shell
sudo apt install build-essential
sudo apt install python3 python3-pip
sudo apt install nodejs npm
npm install pyodide
```

Install emsdk

```shell
git clone https://github.com/emscripten-core/emsdk.git
cd emsdk
./emsdk install latest
./emsdk activate latest
source ./emsdk_env.sh
```

## step to run wasm c benchmark

```shell
cd WASM/C_Benchmark/
chmod +x compile_and_run_wasm.sh 
./compile_and_run_wasm.sh 
```

Output file: 'wasm_results_c.csv'


## step to run wasm c++ benchmark

```shell
cd WASM/CPP_Benchmark/
chmod +x compile_and_run_wasm.sh 
./compile_and_run_wasm.sh 
```

Output file: 'wasm_results_cpp.csv'

## step to run wasm python benchmark

```shell
cd WASM/Python_Benchmark/
node run_python_wasm.mjs
```

Output file: 'python_wasm_results.csv'


## step to run wasm Java benchmark

```shell
cd WASM/Java_Benchmark/java-wasm-app/target/java-wasm-app-1.0-SNAPSHOT    
python3 -m http.server 8080
```

To see the output, open the link in the browser and then you will be able to see the output in the webpage.




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
# perf stat is a tool that counts hardware events, such as cache misses, or branches mispredicted
perf stat wasmtime executable argument1 argument2 ...
# perf record and perf report are used to monitor hotspots in the program
perf record wasmtime executable argument1 argument2 ...
perf report
# perf trace is used to trace syscall
perf trace wasmtime executable argument1 argument2 ...
# generate flamegraph
perf record -g wasmtime my_program.wasm
perf script | stackcollapse-perf.pl | flamegraph.pl > flamegraph.svg

