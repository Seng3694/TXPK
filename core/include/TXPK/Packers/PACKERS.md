# TXPK - Packers #

The packers are kind of the heart piece of TXPK. 
A packer packs all input textures into one single texture.

Any packer has to import the [IPacker interface][1].
This forces you to implement the following methods:

```cpp
bool validate(
    RectanglePtrs& rectangles, 
    const uint32& sizeConstraint, 
    const SizeContraintType& constraintType, 
    const bool& allowRotation) const;

Bin pack(
    RectanglePtrs& rectangles, 
    const uint32& sizeConstraint, 
    const SizeContraintType& constraintType, 
    const bool& allowRotation) const;
```

The `validate` method validates whether the rectangles/parameters are valid for this implementation or not.
The `pack` method is the actual packing algorithm.

The reason why a packer receives rectangle pointers rather than normal rectangles is 
because multiple textures could point to the same rectangle after being merged together (the process of replacing two identical images).

The following packers have always the scheme **`Name (Key)`**. So you can use their key in the project file or CLI.

## Same Size Packer (SameSize) ##

The [SameSizePacker][3] only packs textures which share the same size. 
For example every texture would have 32x48. That would be valid for the SameSizePacker.

If there are different sized textures the `validate` method will return false and the packer won't run.

This packer won't rotate textures!

The `width:height` ratio from the packed image is either `1:1` or width is slighty bigger than height.
Obviously this can differ when using size constraints.

**Warning**: it is possible that you input only same sized textures but it will be invalid. 
The reason for this is mostly the texture trimming process which does run before the textures are packed. 
So be careful when using the SameSizePacker combined with texture trimming.

## Black Spawn Packer (Blackspawn) ##

The [BlackspawnPacker][2] packs every kind of texture or image. The `validate` function always returns true.
If you are interested in the details then please check out [jimscott's][4] lightmaps example or the [source code][5].

This algorithm does rotate textures if appropriate (and allowed). 
Because it could allocate more space in any direction as nessecary it could result into extra transparency at the right or bottom border.
That's why i definetly recommend enabling texture trimming when using the BlackSpawnPacker.
A full example using every option enabled and the BlackspawnPacker can be found [here][6].

[1]:../Core/IPacker.hpp
[2]:BlackspawnPacker.hpp
[3]:SameSizePacker.hpp
[4]:http://blackpawn.com/texts/lightmaps/default.html
[5]:../../../src/Packers/BlackspawnPacker.cpp
[6]:../../../../example/README.md
