# palette

**palette** generates colour palettes based on the dominant colours found in an input image.

## Development

### Prerequisites

- CMake >= 3.17
- A modern-ish C compiler

### Build

- `mkdir build && cd build`
- `cmake -DCMAKE_BUILD_TYPE=<Debug|Release> ..` (choose either Debug or Release)
- `make`

### Run

- `<build_folder>/palette` executes the CLI entry point.

### Test

- `<build_folder>/tests/palette_test` executes the unit tests.
