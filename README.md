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

## Zkldoom run (super stripped version for zk proving and check consistencey with original "doomreplay")
```
cd zkldoom
make -f Makefile.zkld && ./zkldoom
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

