# Sprite Sheet Packer #

Small project to pack textures into an atlas. Data is stored in JSON files.
Inspired by [aggsol][1]. Algorithm for packing from [blackspawn][2].

## How it works ##

Folder with 500 random generated rectangle images:

<img src="https://cdn.discordapp.com/attachments/425728769236664350/428126812619669505/images.PNG" width="500">

Dragging the folder on the TexturePacker.exe will create an `atlas.png` and an `atlas.json`:

<img src="https://cdn.discordapp.com/attachments/425728769236664350/428126828184600586/atlas.png"
width="500">

```json
{
  "path": "path/to/textures",
  "bin": [
    {
      "path": "202.png",
      "x": 0,
      "y": 0,
      "w": 97,
      "h": 97,
      "flip": 0
    },
    {
      "path": "444.png",
      "x": 0,
      "y": 97,
      "w": 92,
      "h": 100,
      "flip": 0
    },

```

The packer can be executed via command line with the following arguments:

`arg1: path/to/textures`

`arg2: allowFlip (default=0 => no flip)` (90° spin)

`arg3: fileRegex (default="" => take all)`

`arg4: atlasBackgroundColor (default="00000000" => transparent)` (RGBA)

Example:
```
>TexturePacker.exe "path/to/textures" "1" "[2]{1}[0-9]{2}(.png)$" "ff00ffff"
```

Here all images with a file name like "2`xx`.png" in the directory "path/to/images" will be packed. They will be flipped if it's appropriate and the resulting atlas will be cleared with magenta.

Result atlas:

<img src="https://cdn.discordapp.com/attachments/425728769236664350/428126843707719680/atlas_args.png" width="500">

Looking at the atlas.json, there are some images which got flipped.

```json
{
    "path": "215.png",
    "x": 456,
    "y": 0,
    "w": 82,
    "h": 90,
    "flip": 1
}
```

The dimensions of the resulting atlas will always be squared except when all the textures share the same size. The dimensions will then be precalculated. For example 12 textures with 64x64 will be packed like this:

<img src="https://cdn.discordapp.com/attachments/425728769236664350/428136997232836609/atlas.png">

## Build ##

Project uses [CMake][3] to generate platform and compiler-specific build files.

### Dependencies ###

Before building, make sure that [SFML 2.0+][4] is installed. Also note that this project uses `C++14` features such as `auto` and `lambdas`, and therefore requires a `C++14` compliant compiler in order to build successfully.

### Building on Windows (Visual Studio) ###
1. Ensure SFML is installed (if CMake fails to find SFML automatically, edit the `SFML_ROOT` variable in the [CMakeLists.txt][4])

2. Clone the repository
    ```
    git clone https://github.com/Seng3694/TexturePacker
    ```

3. Generate the build files (depending on your Visual Studio Version the `cmake` command differs. In this case `"Visual Studio 15"` will generate the Visual Studio 2017 project files)
    ```
    mkdir build
    cd build
    cmake -G "Visual Studio 15" ../TexturePacker
    ```

4. Open the `.sln` file in Visual Studio and build the `ALL_BUILD` target.

[1]:https://github.com/aggsol/sprite-sheet-packer
[2]:http://blackpawn.com/texts/lightmaps/default.html
[3]:http://www.cmake.org/
[4]:http://www.sfml-dev.org/