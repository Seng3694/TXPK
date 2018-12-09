# TXPK - Exporters #

An exporter is something which exports data in terms of the texture packing process to any kind of format. There are just a few exporters but you can write your own with Lua or extend the C++ source code.
Any exporter has to import the [IDataExporter interface][1].
This forces you to implement this method:

```cpp
void exportData(
    TexturePtrs& textures, 
    const uint32& width, 
    const uint32& height, 
    const std::string& imagePath, 
    const std::string& outputDirectory, 
    const std::string& outputName) const;
```

The `textures` hold any kind of information about the packed textures like path and dimensions.
`width`, `height` and `imagePath` are metadata from the resulting packed image. `outputDirectory` is the directory where the exporter should save the file to. `outputName` is the name which should be used when creating a file.

The following exporters have always the scheme **`Name (Key)`**. So you can use their key in the project file or CLI.

## Json Exporter (Json) ##

The [`JsonExporter`][2] exports the given data to a json file. Here is an extract from the example json output file:

```json
{
  "meta": {
    "w": 215,
    "h": 198,
    "img": "../sheets/skeleton.png"
  },
  "bin": [
    {
      "key": 0,
      "x": 68,
      "y": 36,
      "w": 32,
      "h": 22,
      "ox": 3,
      "oy": 5,
      "sw": 43,
      "sh": 37,
      "r": true
    },
    {
      "key": 1,
      "x": 132,
      "y": 36,
      "w": 32,
      "h": 22,
      "ox": 3,
      "oy": 5,
      "sw": 43,
      "sh": 37,
      "r": true
    },
    {
      "key": 2,
      "x": 110,
      "y": 99,
      "w": 21,
      "h": 32,
      "ox": 3,
      "oy": 5,
      "sw": 43,
      "sh": 37,
      "r": false
    },
    [...]
  ]
}
```

First we can see the `meta` data from the packed texture. The width, height and the path to the texture this file relates to.
In the `bin` are the informations about every single texture which got packed.

| Name | Description                                                                  |
|------|------------------------------------------------------------------------------|
| key  | The key to uniquely identify the texture                                     |
| x    | The x value where to find the texture in the resulting packed image.         |
| y    | The y value where to find the texture in the resulting packed image.         |
| w    | The width of the (trimmed and rotated) texture.                                                    |
| h    | The height of the (trimmed and rotated) texture                                                    |
| ox   | The offset in x direction which can occur when texture trimming was enabled. |
| oy   | The offset in y direction which can occur when texture trimming was enabled. |
| sw   | The source width the texture had before trimming (if it was enabled).        |
| sh   | The source height the texture had before trimming (if it was enabled).       |
| r    | Whether the texture got rotated by 90° ccw or not.                           |

## Cpp Header Exporter (CppHeader) ##
The [CppHeaderExporter][3] transforms the path to the source images to an uppercase macro with the key the current key converter creates. 
For example using the [EnumeratorConverter][4] the result may look like this:

```cpp
#pragma once

#define SGB_STAND_1 0
#define SGB_STAND_2 1
#define SGB_STAND_3 2
#define SGB_WALK_1 3
#define SGB_WALK_2 4
#define SGB_WALK_3 5
```

The files were called like `sgb_stand_1.png` which got converted to `SGB_STAND_1` and returns the unique identifier `0`.

## Lua Exporter (...) ##
The [LuaExporter][5] works different. At load time the TXPK will load any Lua script in the `scriptDirectory` which can be configured via CLI or project file.
The Lua script search is done recursively. Only scripts ending with `Exporter.lua` will be loaded as exporter. If there is a script called for example `CustomCppHeaderExporter.lua` it will be registered as `CustomCppHeaderExporter`. So you could use it in your project file. 

The Lua scripts have to have a function defined with this signature to work properly:
```C
function export(textures, width, height, imagePath, outputDirectory, outputName)
```

`textures` is an iterable table containing multiple `texture` tables.
`texture` table has the following keys:
```C
texture = {
    path,        --string
    bounds,      --rectangle
    offsetX,     --number
    offsetY,     --number
    sourceWidth, --number
    sourceHeight --number
}
```
bounds being a `rectangle` table is defined like this:
```C
rectangle = {
    left,   --number
    top,    --number
    width,  --number
    height, --number
    rotated --boolean
}
```

Other function parameters:
- `width` (number) is the width of the packed texture.
- `height` (number) is the width of the packed texture.
- `imagePath` (string) is the path to the packed texture.
- `outputDirectory` (string) is the directory path where any output file should be saved to.
- `outputName` (string) is the name the exported output file should be saved with.

For a working LuaExporter please check out the [example][6].

[1]:../Core/IDataExporter.hpp
[2]:JsonExporter.hpp
[3]:CppHeaderExporter.hpp
[4]:../KeyConverters/KEYCONVERTERS.md
[5]:LuaExporter.hpp
[6]:../../../../example/README.md
