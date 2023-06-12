# zkllvm proving of doomreplay
ZKLLVM compilation, proof generation, and verification of "user input"->"target game state" state transitions in the Doom core.




## Doomreplay run (generate video demo)
 
```
cd doomgeneric
make -f Makefile.dr
./doomgeneric -iwad ../doom1.wad -input ../input/test1.txt -nrecord 3500 -framerate 35 -render_frame -render_input -render_username -output test1.mp4
```

## Zkldoom run (super stripped version for zk proving)
 
```
cd zkldoom
make -f Makefile.zkld
./zkldoom -iwad ../doom1.wad -input ../input/test1.txt -nrecord 3500 -framerate 35 -render_frame -render_input -render_username -output test1.mp4
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

