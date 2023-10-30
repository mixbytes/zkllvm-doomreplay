# zkllvm proving of doomreplay
ZKLLVM compilation, proof generation, and verification of "user input"->"target game state" state transitions in the Doom core.


# [TEMP] run all in debug environment

```
git clone git@github.com:mixbytes/zkllvm-doomreplay.git
cd zkllvm-doomreplay

```
Now make sure you have all ZKLLVM deps installed (CMake, Boost, Clang).
AND SET ALL BINARIES to look at really existing files locations [HERE](https://github.com/mixbytes/zkllvm-doomreplay/blob/99dc234fae714efb801fcf46d35c50e09213fce7/cmake/CircuitCompile.cmake#L80)

Now you can run multiple variants of zkldoom (I assume project resides in ```~/zkllvm-doomreplay/```):

## 1. Run ZKLLVM compile .ll only
```
cd ~/zkllvm-doomreplay/build/ && cmake .. && make zkldoom_compile_sources
```

## 2. Run assigner (compile and then assign, inputs are already pre-generated or saved in repo):
```
cd ~/zkllvm-doomreplay/build/ && cmake .. && make zkldoom_run_assigner
```

## 3. Run prover (compile, assign, prepare statement, run prover)
```
cd ~/zkllvm-doomreplay/build/ && cmake .. && make zkldoom_run_prover
```

(all targets are described in [CircuitCompile.cmake](https://github.com/mixbytes/zkllvm-doomreplay/blob/main/cmake/CircuitCompile.cmake) file



## 4. Run noZKLLVM compiled version (should output trace of player's coordinates, health, ammo):
```
cd ~/zkllvm-doomreplay/zkldoom/ && rm build/*.o && make -f Makefile.zkld && ./zkldoom
```

## 5. Doomreplay run (generate video demo)
```
cd ~/zkllvm-doomreplay/doomgeneric && make -f Makefile.dr && ./doomgeneric -iwad ../doom1.wad -output test1.mp4
```
(creates ```test1.mp4``` file with replay if everything is ok)



# Generate harcoded .wad in doom1_wad_hardcopy.h

(obsolete, now miniwad.wad is used ) - but I still use helper script to hardcode .wad files

Takes ```./doom1.wad``` file and puts its binary contents into ```unsigned char * wad_contents[] = "\x01\x02\...``` buffer in ```doom1_wad_hardcopy.h``` file

Compile
```
gcc hardcode_wad.c -o hardcode_wad
```

Run
```
./hardcode_wad ./doom1.wad doomgeneric/doom1_wad_hardcopy.h

```
