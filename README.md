# Volsed

<img width="278" height="332" alt="volsed-in-fl" src="https://github.com/user-attachments/assets/d10d3886-1f2f-4115-8871-0bc2140bd95e" />


**Volsed** is a simple audio gain plugin built with the [JUCE](https://juce.com/) framework.

It lets you adjust the output volume of your audio, from -12 dB to +12 dB. It also includes a bypass button to quickly turn off gain processing and hear the original signal.

Volsed is designed to do one thing and keep it simple, with a clean interface and straightforward controls.

## Features

- Output gain adjustment from -12 dB to +12 dB.
- Smooth volume changes to avoid sudden jumps in level.
- Bypass button to turn gain processing on or off.
- Mono and stereo support.
- Available as both a VST3 plugin and a standalone application.

## Compatibility

Volsed has been tested and works in **FL Studio**. It should also work in other DAWs that support VST3 plugins.

## Requirements

To build Volsed from source, you'll need:

- **CMake** 3.22 or newer.
- A C/C++ compiler (MSVC, Clang, or GCC).
- **Ninja** (recommended).

Make sure CMake, your compiler, and Ninja are added to your system's `PATH`.

## Building from Source

### 1. Clone the Repository

Clone the repository and open the project directory in your terminal.

### 2. Configure the Project

If you're using MSVC on Windows, open a Developer Command Prompt and run:

```bash
cmake -B build -G Ninja -DCMAKE_BUILD_TYPE=Release -DCMAKE_C_COMPILER=cl -DCMAKE_CXX_COMPILER=cl
```

### 3. Build

Once CMake has finished configuring the project, run:

```bash
cmake --build build --config Release -j 8
```

## Build Output

After a successful build, you'll find the generated files in:

```text
build/Volsed_artefacts/Release/
```

The output includes:

- **VST3:** `VST3/Volsed.vst3`
- **Standalone:** `Standalone/Volsed.exe`

## Installing

To use Volsed in your DAW:

1. Find the `Volsed.vst3` folder in the build output.
2. Copy it to your system's VST3 plugin directory.
3. Restart your DAW or rescan your plugins.
4. Find Volsed in your plugin list and load it.
