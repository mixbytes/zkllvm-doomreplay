# zkllvm proving of doomreplay
ZKLLVM compilation, proof generation, and verification of "user input"->"target game state" state transitions in the Doom core.


## Compilation, linking of circuits
[TEMP] build for zkllvm is made with CMake. Now at compile/linking/assigner stages. Don't forget to read what you're going to run :)

Now ZKLLVM compiler/assigner/linkers are pointing to ${HOME}/zkllvm pre-build binaries of needed versions
(needed to debug different dev brahches of each submodule).
```
mkipr -p build
cd build
cmake .. 
make zkldoom_compile_sources
```


## Doomreplay run (generate video demo)
```
cd doomgeneric
make -f Makefile.dr && ./doomgeneric -iwad ../doom1.wad -output test1.mp4
```

## [TEMP] Zkldoom run (super stripped version for zk proving and check consistencey with original "doomreplay")
```
cd ~/zkllvm-doomreplay/zkldoom/ && make -f Makefile.zkld && ./zkldoom
```

## [TEMP] Run all compile-link-asssign-prove (run full zk-cycle)
(GENERATE MINIMAL PROOF)
```
cd ~/zkllvm-doomreplay/build/ && cmake .. && make zkldoom_run_prover
```




### Run assigner
[TEMP] - Creates empty ```z_main.inp.json``` and tries to run assinger using these inputs. Should generate ```.tbl``` file with intermediate signals
```
mkipr -p build
cd build
cmake .. 
make zkldoom_run_assigner
```

#Run prepare statement (runs compilation, assignment, preparation of statement (.json file) for proving
[TEMP] Generates ```.json``` file with proving statement
```
mkipr -p build
cd build
cmake .. 
make zkldoom_run_prepare_statement
```




## helper script to hardcode .wad files

Takes ```./doom1.wad``` file and puts its binary contents into ```unsigned char * wad_contents[] = "\x01\x02\...``` buffer in ```doom1_wad_hardcopy.h``` file

Compile
```
gcc hardcode_wad.c -o hardcode_wad
```

Run
```
./hardcode_wad ./doom1.wad doomgeneric/doom1_wad_hardcopy.h

```


## Inputs

```
,   - new frame
x   - escape
e   - enter
l   - left
r   - right
u   - up
d   - down
a   - alt
s   - shift
p   - use
f   - fire
t   - tab
y   - yes
n   - no
<   - strafe left
>   - strafe right
0-9 - weapons
```

Example inputs ([TEMP] hardcoded)
```
char USER_INPUT[] =
"u,u,u,u,u,u,u,u,u,u,u,u,u,u,u,u,u,u,u,u,u,u,u,u,u,u,u,u,u,u,u,u,u,u,u,u,u,u,u,u,"
"u,u,u,u,u,u,u,u,u,u,u,u,u,u,u,u,u,u,u,u,"
"r,r,r,r,r,r,r,r,r,r,r,r,"
"su,su,su,su,su,su,su,su,su,su,su,su,su,su,su,su"
"su,su,su,su,su,su,su,su,su,su,su,su,su,su,su,su"
"su,su,su,su,su,su,su,su,su,su,su,su,su,su,su,su"
"su,su,su,su,su,su,su,su,su,su,su,su,su,su,su,su"
"su,su,su,su,su,su,su,su,su,su,su,su,su,su,su,su"
"su,su,su,su,su,su,su,su,su,su,su,su,su,su,su,su"
"r,r,r,r,r,r,r,r,r,r,r,r,r,r,r,r,r,r,r,r,r,"
"p,"
"r,r,r,r,r,"
"su,su,su,su,su,su,su,su,su,su,su,su,su,su,su,su"
"su,su,su,su,su,su,su,su,su,su,su,su,su,su,su,su"
"l,l,l,l,l,l,l,l"
"su,su,su,su,su,su,su,su,su,su,su,su,su,su,su,su"
"su,su,su,su,su,su,su,su,su,su,su,su,su"
",,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,"
"sd,sd,sd,sd,sd"
"r,r,r,r"
"f,f,f,f,f,f,f,f,f,f,f,f,f,f,f,f,f,f,f,f,f,f,f,f"
"f,f,f,f,f,f,f,f,f,f,f,f,f,f,f,f,f,f,f,f,f,f,f,f"
"f,f,f,f,f,f,f,f,f,f,f,f,f,f,f,f,f,f,f,f,f,f,f,f"
"f,f,f,f,f,f,f,f,f,f,f,f,f,f,f,f,f,f,f,f,f,f,f,f"
"f,f,f,f,f,f,f,f,f,f,f,f,f,f,f,f,f,f,f,f,f,f,f,f"
",,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,"
",,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,"
",,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,"
"sd,sd,sd,sd,sd,sd,sd,sd,sd,sd,sd,sd,sd,sd,sd,sd"
;
```
