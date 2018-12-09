# TXPK - Command Line Interface #

I would definetly not recommend using the CLI, but you decided to come here anyways, so let's do this.

There are a few things to know about this implementation:
- every argument starts with a minus
- every key is just one character long. e.g. `-p` or `-g`
- there are 3 different types of arguments:
  - Commands: a command will do something specific and ignoring all other options
  - Required: an option which is required if you are not using any commands
  - Option: something you can set but don't have to
- there are also positional arguments. The first one is for example the project file. So you could either write `>txpk.exe -p"projectfile.txpk"` or just `>txpk.exe "projectfile.txpk"`.

The CLI has 21 different arguments. Because the arguments are just one character long, you might have guessed that there are not much characters left. Probably should rewrite that CLI to support longer keys...

But for now here are all arguments:

| Argument 	| Short                  	| Explanation                                                   	| Type     	|
|:---------:|:-----------------------:	|---------------------------------------------------------------	|:---------:|
| -p       	| Project file           	| Path to the project file                                      	| Command  	|
| -i       	| InputDirectory         	| The directory to load the images from                         	| Required 	|
| -r       	| InputRegex             	| The regex which decides which files to take                   	| Option   	|
| -y       	| ScriptDirectory        	| The directory to load scripts from                            	| Option   	|
| -q       	| RecursiveFiles         	| If true then get all files in directory recursively           	| Option   	|
| -o       	| OutputImageDirectory   	| The directory where the output image will be written to       	| Option   	|
| -z       	| OutputDataDirectory    	| The directory where the output data will be written to        	| Option   	|
| -n       	| OutputName             	| The name all files are getting called                         	| Option   	|
| -f       	| OutputImageFormat      	| The image format of the resulting packed texture (png, jpg)   	| Option   	|
| -a       	| PackingAlgorithm       	| The [algorithm][1] to pack with                                   | Option   	|
| -d       	| DataExportAlgorithms   	| The [algorithms][2] to export data with (comma seperated)         | Option   	|
| -k       	| KeyConversionAlgorithm 	| The [algorithm][3] to convert keys with                           | Option   	|
| -s       	| AllowRotation          	| Whether the algorithm is allowed to rotate images or not      	| Option   	|
| -c       	| SizeConstraint         	| Size constraint in either Width or Height                     	| Option   	|
| -t       	| ContraintType          	| Size constraint type (None=0, Width=1, Height=2)              	| Option   	|
| -b       	| BackgroundClearColor   	| The color the image gets cleared (hexadecimal)                	| Option   	|
| -x       	| TrimImages             	| Allow to cut the image so any transparency around will be cut 	| Option   	|
| -e       	| ReplaceSameTextures    	| Allow to replace identical images                             	| Option   	|
| -h       	| Help                   	| Print help                                                    	| Command  	|
| -v       	| Version                	| Print version                                                 	| Command  	|
| -g       	| GenerateDefault        	| Generate default project file                                 	| Command  	|

As you can see not all arguments make sense. The one character limitation got me near the end of the alphabet.

Here is a python script which works as expected:
```python
from subprocess import call

call([
        "PATH/TO/txpk.exe", #executable
        "-iPATH/TO/sgb", #input dir
        "-r.+(.png)$", #regex
        "-q", #allow rotation
        "-oPATH/TO/sgb", #output dir
        "-zPATH/TO/sgb", #output dir
        "-nsgb", #output name
        "-fpng", #output image format
        "-aBlackspawn", #packing algorithm
        "-dJson,CppHeader", #export algorithms comma separated
        "-kEnumerator", #key conversion algorithm
        "-s", #allow rotation
        "-c44", #size constraint 44 pixels
        "-t1", #size constraint type 1 => width => width constrained by 44 pixels
        "-bff00ff7f", #semi transparent red clear color
        "-x", #allow cut/trim
        "-e" #allow replacing same textures
    ])
```

Because i don't want to show real paths on my computer i just wrote `PATH/TO/...`

Assuming the images used in main readme file:

![sgb_unpacked][4]

Outputs following files:

The packed image `sgb.png`:

![sgb_packed][5]

Notice how the images are trimmed and constrained by 44 pixels in width. Also the semi transparent red background color.

The json data file `sgb.json`:

```json
{
  "meta": {
    "w": 44,
    "h": 233,
    "img": "PATH/TO/sgb/sgb.png"
  },
  "bin": [
    {
      "key": 0,
      "x": 0,
      "y": 0,
      "w": 44,
      "h": 40,
      "ox": 10,
      "oy": 24,
      "sw": 64,
      "sh": 64,
      "r": false
    },
    {
      "key": 1,
      "x": 0,
      "y": 40,
      "w": 44,
      "h": 39,
      "ox": 10,
      "oy": 25,
      "sw": 64,
      "sh": 64,
      "r": false
    },
    {
      "key": 2,
      "x": 0,
      "y": 157,
      "w": 44,
      "h": 38,
      "ox": 10,
      "oy": 26,
      "sw": 64,
      "sh": 64,
      "r": false
    },
    {
      "key": 3,
      "x": 0,
      "y": 79,
      "w": 44,
      "h": 39,
      "ox": 10,
      "oy": 25,
      "sw": 64,
      "sh": 64,
      "r": false
    },
    {
      "key": 4,
      "x": 0,
      "y": 118,
      "w": 44,
      "h": 39,
      "ox": 10,
      "oy": 25,
      "sw": 64,
      "sh": 64,
      "r": false
    },
    {
      "key": 5,
      "x": 0,
      "y": 195,
      "w": 44,
      "h": 38,
      "ox": 10,
      "oy": 26,
      "sw": 64,
      "sh": 64,
      "r": false
    }
  ]
}
```

If you don't understand what all these fields mean you can just read more about the JsonExporter [here][2].

And the CppHeader file `sgb.hpp`:

```cpp
#pragma once

#define SGB_STAND_1 0
#define SGB_STAND_2 1
#define SGB_STAND_3 2
#define SGB_WALK_1 3
#define SGB_WALK_2 4
#define SGB_WALK_3 5
```

### Conclusion ###
As you can see the CLI works but is kind of cumbersome to use. All the configurations can be done in the project file too.

[1]:../core/include/TXPK/Packers/PACKERS.md
[2]:../core/include/TXPK/Exporters/EXPORTERS.md
[3]:../core/include/TXPK/KeyConverters/KEYCONVERTERS.md
[4]:../resources/sgb_unpacked.png
[5]:../resources/sgb_cli.png