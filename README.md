# Volsed

<img width="278" height="332" alt="volsed-in-fl" src="https://github.com/user-attachments/assets/d10d3886-1f2f-4115-8871-0bc2140bd95e" />


**Volsed** is an audio plugin and standalone application built using the [JUCE](https://juce.com/) framework.

## Features

- VST3 audio plugin support.
- Standalone application.
- Built with the JUCE framework.
- Compatible with FL Studio.

## Compatibility

Volsed has been tested and verified to work correctly in **FL Studio**.

## Prerequisites

Before building the project, make sure the following tools are installed on your system:

- **CMake** (version 3.22 or higher)
- **C/C++ Compiler** (MSVC is used in the default instructions; Clang and GCC are also supported)
- **Ninja** build system (recommended)

**Note:** Make sure that your compiler, CMake, and Ninja are properly added to your system's `PATH` environment variable.

## Building from Source

### 1. Clone the Repository

Clone the repository and navigate to the project root directory.

### 2. Generate Build Files

Open a terminal or, if you're using MSVC on Windows, a Developer Command Prompt.

Run the following command to configure the project using CMake and Ninja:

```bash
cmake -B build -G Ninja -DCMAKE_BUILD_TYPE=Release -DCMAKE_C_COMPILER=cl -DCMAKE_CXX_COMPILER=cl
```

### 3. Build the Project

Once the configuration is complete, compile the project using:

```bash
cmake --build build --config Release -j 8
```

## Build Artifacts

After a successful build, the generated files will be available in the following directory:

```text
build/Volsed_artefacts/Release/
```

The build output includes:

- **VST3 Plugin:** `VST3/Volsed.vst3`
- **Standalone Application:** `Standalone/Volsed.exe`

### Installing the VST3 Plugin

To use Volsed in your DAW:

1. Locate the generated `Volsed.vst3` directory.
2. Copy it to your DAW's VST3 plugin directory.
3. Open or restart your DAW.
4. Scan for new plugins if necessary.

You can now load **Volsed** in FL Studio or any other compatible VST3 host.
