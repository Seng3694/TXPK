# TXPK - Key Converters #

A key converter is something that converts the texture path to an identifier.

Any key converter has to import the [IKeyConverter interface][1].
This forces you to implement the following methods:

```cpp
std::string convert(const std::string& input);
void reset();
```

The `convert` method converts the path to whatever the implementation converts it to.
The `reset` method can be used to reset any state. For example the enumerator key converter increases every time `convert` is called by one. But the converter could be used by many exporters, so the counter has to be resetted.

The following converters have always the scheme **`Name (Key)`**. So you can use their key in the project file or CLI.

## File Without Extension Key Converter (FileWithoutExt) ##

The [FileWithoutExtensionConverter][2] converts a path like `path/to/texture_frame_2.png` to `texture_frame_2`.

## Regex Key Converter (...) ##

There is currently just the `NumericRegex` converter which matches only numbers `[0-9]+`. 
This converts a path like `path/to/texture_frame_2.png` to `2`.

## Enumerator Key Converter (Enumerator) ##

The [EnumeratorKeyConverter][3] counts its internal counter up by one for everytime `convert` gets called and returns the count as the key. `reset` will reset the internal counter to zero.
Assuming this is the first texture it will convert the path `path/to/texture_frame_2.png` to `0` and the next one to `1` and so on.

## Lua Key Converter (...) ##

The [LuaKeyConverter][4] works different. At load time the TXPK will load any Lua script in the `scriptDirectory` which can be configured via CLI or project file. The script search is done recursively.
Only scripts ending with `KeyConverter.lua` will be loaded as a key converter. If there is a script called for example `CustomEnumeratorKeyConverter.lua` it will be registered as `CustomEnumeratorKeyConverter`. So you could use it in your project file.  

The Lua script have to have a function defined with this signature to work properly:

```C
function convert(input)
```

Optionally you can also define a `reset` function if you have any state to reset between the exporters.

```C
function reset()
```

The `convert` function takes a string as an argument which can be converted to whatever you like it to be.
It has to return an integer or a string. If `nil` or nothing is returned, the input string will not be changed and just returned.

For a working LuaKeyConverter please check out the [example][5].


[1]:../Core/IKeyConverter.hpp
[2]:FileWithoutExtConverter.hpp
[3]:EnumeratorConverter.hpp
[4]:LuaConverter.hpp
[5]:../../../../example/README.md
