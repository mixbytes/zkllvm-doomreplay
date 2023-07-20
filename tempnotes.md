[TEMP]
Doomgeneric state output helper
```
make -f Makefile.dr && ./doomgeneric -iwad ../doom1.wad -output test1.mp4 2>/dev/null | fgrep playerState
```
ZKLDomm state output helper
```
make -f Makefile.zkld && ./zkldoom 2>/dev/null | fgrep playerState
```
