# Project Series

This repository tracks an embedded system project following best practices for microcontroller development. The project serves as an educational example and case study of a microcontroller-based embedded project.

## Directory structure

The directory structure is based on the [pitchfork layout](https://github.com/vector-of-bool/pitchfork).

| Directory    | Description                                                  |
|--------------|--------------------------------------------------------------|
| build/       | Build output (object files + executable)                     |
| docs/        | Documentation (e.g., coding guidelines, images)              |
| src/         | Source files (.c/.h)                                         |
| src/app/     | Source files for the application layer (see SW architecture) |
| src/common/  | Source files for code used across the project                |
| src/drivers/ | Source files for the driver layer (see SW architecture)      |
| src/test/    | Source files related to test code                            |
| external/    | External dependencies (as git submodules if possible)        |
| tools/       | Scripts, configs, binaries                                   |

## Build

The two most common ways to build code for a microcontroller are from an IDE (often supplied by the vendor) or from the command-line through a build system (for example, make). 

In short, using an IDE is the most straightforward approach, but at the same time less flexible because it forces you into a particular environment. A build system is more complicated to set up, but it can be combined with your editor of choice, gives more control over the build process, is great for automation (see CI), and allows for a command-line based environment, which transfers better across projects. This project can be built both ways, however, _make_ is the preferred way, but the IDE is helpful when step-debugging the code.

## make (Makefile)

The code targets the MSP430G2553 and must be built with a cross-toolchain. While there are several toolchains for this microcontroller, msp430-gcc is the one used in this project, which is available on [TI's website](https://www.ti.com/tool/MSP430-GCC-OPENSOURCE).

There is a _Makefile_ to build the code with _make_ from the command-line:

```bash
TOOLS_PATH=<INSERT TOOLS PATH> make HW=<INSERT TARGET>
```

The path to the toolchain must be specified with the environment variable _TOOLS_PATH_.

The argument _HW_ specifies which hardware to target, either _NSUMO_ (Robot with 28-pin msp430g2553) or _LAUNCHPAD_ (evaluation board with 20-pin msp430g2553).

For example, if the toolchain is available at _C:/Users/User/Downloads/msp430-gcc-9.3.1.11_win64/msp430-gcc-9.3.1.11_win64_, and targeting the evaluation board:

```bash
TOOLS_PATH=C:/Users/User/Downloads/msp430-gcc-9.3.1.11_win64/msp430-gcc-9.3.1.11_win64 make HW=LAUNCHPAD
```

## IDE

The IDE provided by the vendor (TI) for the MSP430 family of microcontrollers is called Code Composer Studio (CCSTUDIO). It's an eclipse-based IDE, and is available at [TI's website](https://www.ti.com/tool/CCSTUDIO).

1. Install CCSTUDIO and MSP430-GCC, and make sure the GCC compiler can be selected from inside CCSTUDIO.
2. Create a new CCS project
   - Target: MSP430G2553
   - Compiler version: GNU v9.3.1.11
   - Empty project (no main file)
3. Drag the src/ folder into the project explorer and link to files and folders
4. Under properties
   - Add src/ directory to include paths
   - Add define symbols (see Makefile), e.g. LAUNCHPAD

## Tests

There are no unit tests, but there are test functions inside src/test/test.c, which are written to test isolated parts of the code. They run on target but are not built as part of the normal build. Only one test function can be built at a time, and it's built as follows (test_assert as an example):

```bash
make HW=LAUNCHPAD TEST=test_assert
```

## Pushing a new change

These are the typical steps taken for each change.

1. Create a local branch
2. Make the code changes
3. Build the code
4. Flash and test the code on the target
5. Static analyse the code
6. Format the code
7. Commit the code
8. Push the branch to GitHub
9. Open a pull-request
10. Merge the pull request (must pass CI first)

## Commit message

Commit messages should follow the specification laid out by [Conventional Commits](https://www.conventionalcommits.org/en/v1.0.0/).

Format: `type(scope): description`

- **Type**: `feat`, `fix`, `build`, `docs`, etc.
- **Scope**: module name (e.g., `i2c`, `uart`, `gpio`)
- **Description**: short sentence in imperative form

Example:
```
build: set the project structure and add initial files

Fill project directory with required directories to immediately 
clarify the project structure to be used throughout the project series.

Video: How I version control with git (Best Practices)
```

## Code formatter

The codebase follows certain formatting rules, which are enforced by the code formatter **clang-format**. These rules are specified in the **.clang-format** located in the root directory. There is a rule in the **Makefile** to format all source files with one command (requires clang-format to be installed).

```bash
make format
```

Sometimes it's desirable to ignore these formatting rules, and this can be achieved with special comments.

```c
// clang-format off
typedef enum {
    IO_10, IO_11, IO_12, IO_13, IO_14, IO_15, IO_16, IO_17,
    IO_20, IO_21, IO_22, IO_23, IO_24, IO_25, IO_26, IO_27,
} io_generic_e;
// clang-format on
```

## Static analysis

To catch coding mistakes early on (in addition to the ones the compiler catches), a static analyzer **cppcheck** is used. There is a rule in the **Makefile** to analyse all files with **cppcheck**.

```bash
make cppcheck
```

## Memory footprint analysis

The memory footprint on a microcontroller is very limited. The MSP430G2553 only has 16 KB (16 000 bytes) of read-only memory (ROM) or flash memory. This means one has to be conscious of how much space each code snippet takes, which is one of the challenges with microcontroller programming. For this reason, it's useful to have tools in place to analyse the space occupied. There are two such programs available in the toolchain (_readelf_ and _objdump_), and two corresponding rules in the _Makefile_.

One rule to see how much total space is occupied:
```bash
make size
```

And another rule to see how much space is occupied by individual symbols (functions + variables):
```bash
make symbols
```

which is useful to track down the worst offenders.

## License

[Add your license info here]
