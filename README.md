<!-- SPDX-License-Identifier: 0BSD -->

# Search (algorithms-suggestions)

This is one of three partial implementations of the
[**algorithms-suggestions**](https://github.com/EliahKagan/algorithms-suggestions)
exercises. The others are [**Pool**](https://github.com/EliahKagan/Pool) and
[**algorithms-python**](https://github.com/EliahKagan/algorithms-python).

This was an experiment in doing some of those exercise ideas paired (in C++).

## License

[0BSD](https://spdx.org/licenses/0BSD.html). See [**`LICENSE`**](LICENSE).

## Building

Visual Studio Code, which gives a nice interface for building CMake project
against your choice of kits (and switching between kits), is suggested. Some
sample configuration, which you may or may not need to modify, is in `.vscode`.

If you'd like to build from the command line instead:

```sh
mkdir build
cd build
cmake -G Ninja ..
ninja
```

## Usage

Tests are ad-hoc. Run `./search` from the output directory after building.
