# Example #

This is an example of how the packed atlas files could be used.

## Resources ##

All used resources are just for illustration purposes. 
Graphics are from [Jesse M.][1].
The font is from [Pizzadude][4].

## Get it started ##
The unpacked images:

<img src="https://cdn.discordapp.com/attachments/425728769236664350/428704832946176000/unknown.png" width="70%">

Packed atlas created by the [TexturePacker][2]:

![atlas][3]

Notice the rotated textures.

The example app loads the sprites and animates them.

![result][5]

### How rotation is handled in the TexturePacker ###

![rotation][7]

The texture gets rotated by 90° and then the origin will be moved 

```cpp
if(texture.flip == true)
{
    sprite.setRotation(90);
    sprite.setOrigin(0, texture.width); 
}
//source: https://github.com/Seng3694/TexturePacker/blob/master/engine/src/ImageRenderer.cpp
```

This step has to be reversed:

```cpp
if (texture.flip == true)
{
    sprite.setOrigin(texture.height, 0);
    sprite.setRotation(-90);
}
//source: https://github.com/Seng3694/TexturePacker/blob/master/example/src/Animation.cpp
```

### Does this litter my code with rotation hacks? ###
The sprites are stored in an `AnimatedSprite` class which has it's own transform. When drawing the `AnimatedSprite` to the screen the transform will be combined with the backing sprite. So no one using this class would ever notice the rotation applied while loading the texture.

[1]: https://jesse-m.itch.io/skeleton-pack
[2]: https://github.com/Seng3694/TexturePacker
[3]: https://cdn.discordapp.com/attachments/425728769236664350/428706719062032386/atlas.png
[4]: http://www.1001fonts.com/arcadeclassic-font.html
[5]: https://cdn.discordapp.com/attachments/425728769236664350/428711346540904478/skeleton_animation.gif
[6]: https://github.com/nlohmann/json
[7]: https://cdn.discordapp.com/attachments/425728769236664350/428547432335409153/rotation.gif

## License ##

- [Textures from Jesse M.][1]
- [Font from Pizzadude][4]
- [Json library from Niels Lohmann][6]