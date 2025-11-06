# fgptool

<div>
  <a href="https://github.com/craftablescience/fgptool/blob/main/LICENSE" target="_blank" rel="noopener noreferrer"><img src="https://img.shields.io/github/license/craftablescience/fgptool?branch=main&label=license" alt="License" /></a>
  <a href="https://github.com/craftablescience/fgptool/actions" target="_blank" rel="noopener noreferrer"><img src="https://img.shields.io/github/actions/workflow/status/craftablescience/fgptool/build.yml?branch=main&label=builds" alt="Workflow Status" /></a>
  <a href="https://discord.gg/ASgHFkX" target="_blank" rel="noopener noreferrer"><img src="https://img.shields.io/discord/678074864346857482?label=discord&logo=Discord&logoColor=%23FFFFFF" alt="Discord" /></a>
  <a href="https://ko-fi.com/craftablescience" target="_blank" rel="noopener noreferrer"><img src="https://img.shields.io/badge/donate-006dae?label=ko-fi&logo=ko-fi" alt="Ko-Fi" /></a>
</div>

A tool to crack the filepath hashes in The Orange Box PS3 file groups.

> [!NOTE]
> This repository does not provide any content from The Orange Box. It is assumed the user
> has already extracted the contents from a legally purchased game disc.

## Credits

- [argparse](https://github.com/p-ranav/argparse)
- [sourcepp](https://github.com/craftablescience/sourcepp)

## Background

File groups (`.GRP`) store a copy of every asset the engine needs to run while a given map is
open. There are a couple other ancillary file groups that are used for streaming sounds,
particularly large files, and to initialize the selected game.

Each file group stores a collection of files, as well as an optional loading screen. Every
map file group as well as `INIT.GRP` should have a valid loading screen. Files stored in the
groups are stored with hashed 32-bit paths, and none of the original file paths are kept.
Because of the computational complexity involved with cracking a hash through brute force, it
is necessary to test the hash against a rainbow table based on file paths taken from other
releases of Orange Box games.

This program is intended to crack the file path hashes in file groups to enable better
previewing of their contents in programs like [VPKEdit](https://github.com/craftablescience/VPKEdit).

## Usage

Before running this tool, install as many copies of Orange Box games as you can. The Xbox 360
port will be very helpful, as well as copies of each release on PC. Additionally, make sure
the `.GRP` files are extracted and writable, since RPCS3 likes to mess with the file
permissions.

Cracked hashes are stored directly in the file groups, and once a hash is cracked it will
remain cracked on future runs even if given a different rainbow table.

First, use the extract operation to extract file paths from a given search path. Multiple
search paths may be entered to create a larger table. This will generate a file called
`mappings.kv` next to the `fgptool` executable.

```
$ ./fgptool -m EXTRACT "/run/media/lxlewis/Storage4/Archive/Source/X360/The Orange Box (World)/portal"

Found 235996 paths.
Hash c90578aa has multiple candidates! Using first one...
- sound/physics/metal/metal_chainlink_impact_soft3.ps3.wav.qpre
- sound/vehicles/v8/vehicle_rollover2.360.wav
Hash 77ab6f58 has multiple candidates! Using first one...
- sound/vehicles/v8/skid_normalfriction.ps3.wav.qpre
- sound/vo/episode_1/npc/female01/cit_pain06.360.wav
Created mappings.kv successfully with 235996 hashes.
```

Next, use the crack operation to attempt to crack the hashes. If a directory is given, it
will look for file groups under that directory and run the crack operation on each one.

```
$ ./fgptool -m CRACK "/home/lxlewis/Downloads/PORTAL/"

96.9665% hashes identified (96.9665% new) for BACKGROUND1.GRP
96.9895% hashes identified (96.9895% new) for BACKGROUND2.GRP
97.3069% hashes identified (97.3069% new) for ESCAPE_00.GRP
97.2945% hashes identified (97.2945% new) for ESCAPE_01.GRP
97.5813% hashes identified (97.5813% new) for ESCAPE_02.GRP
```

Repeat these two steps, alternating extract and crack operations, until satisfied with the
results. Once complete, you can either view the file groups in a program like
[VPKEdit](https://github.com/craftablescience/VPKEdit), or run the dump operation like so to
dump their contents to disk:

```
$ ./fgptool -m DUMP "/home/lxlewis/Downloads/PORTAL/TESTCHMB_A_15.GRP"

Extracted TESTCHMB_A_15.GRP to "/home/lxlewis/Downloads/PORTAL/TESTCHMB_A_15".
```

Dumping the contents of a file group and checking the contents of the `__hashed__` directory
can also be helpful in identifying unknown file path hashes manually. When attempting to
identify unknown file path hashes, the test operation can be helpful to quickly check what
hash a file path is transformed into:

```
$ ./fgptool -m TEST

$ materials/allow1024.txt
	0f403033

$ materials/allow1024_xbox.txt
	af459a7a

$ materials/allow1024.ps3.txt
	73ef4f8e

$ exit
```

Finally, the meta operation will print file group metadata, which is useful for identifying
the assigned loading screen:

```
$ ./fgptool -m META "/home/lxlewis/Downloads/PORTAL/"

BACKGROUND1.GRP
	File count: 2868
	Loading screen path: materials/vgui/appchooser/background_portal.ps3.vtf
BACKGROUND2.GRP
	File count: 2757
	Loading screen path: materials/vgui/appchooser/background_portal.ps3.vtf
ESCAPE_00.GRP
	File count: 3379
	Loading screen path: materials/vgui/appchooser/background_portal.ps3.vtf
ESCAPE_01.GRP
	File count: 3844
	Loading screen path: materials/vgui/appchooser/background_portal.ps3.vtf
ESCAPE_02.GRP
	File count: 4672
	Loading screen path: materials/vgui/appchooser/background_portal.ps3.vtf
```

## Full Help Text

```
Usage: fgptool [--help] [--mode MODE] [PATH]...

Positional arguments:
  PATH        The input path(s). [nargs: 0 or more] 

Optional arguments:
  -h, --help  shows help message and exits 
  -m, --mode  The active mode. Can be EXTRACT, CRACK, META, DUMP, or TEST. [nargs=0..1]
              [default: "CRACK"]
```
