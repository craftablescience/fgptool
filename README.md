# fgptool

<div>
  <a href="https://github.com/craftablescience/fgptool/blob/main/LICENSE" target="_blank" rel="noopener noreferrer"><img src="https://img.shields.io/github/license/craftablescience/fgptool?branch=main&label=license" alt="License" /></a>
  <a href="https://github.com/craftablescience/fgptool/actions" target="_blank" rel="noopener noreferrer"><img src="https://img.shields.io/github/actions/workflow/status/craftablescience/fgptool/build.yml?branch=main&label=builds" alt="Workflow Status" /></a>
  <a href="https://discord.gg/ASgHFkX" target="_blank" rel="noopener noreferrer"><img src="https://img.shields.io/discord/678074864346857482?label=discord&logo=Discord&logoColor=%23FFFFFF" alt="Discord" /></a>
  <a href="https://ko-fi.com/craftablescience" target="_blank" rel="noopener noreferrer"><img src="https://img.shields.io/badge/donate-006dae?label=ko-fi&logo=ko-fi" alt="Ko-Fi" /></a>
</div>

A tool to crack the filepath hashes in The Orange Box PS3 file groups.

## Credits

- [argparse](https://github.com/p-ranav/argparse)
- [sourcepp](https://github.com/craftablescience/sourcepp)

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
