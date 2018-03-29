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

The hit animation does have rotated sprites.

```cpp
sf::Sprite sprite(atlas.texture);
sprite.setTextureRect({ texture.x, texture.y, texture.w, texture.h });

if (texture.flip == true)
{
    sprite.setOrigin(texture.h, 0);
    sprite.setRotation(-90);
}

//and so on
```

The sprites are stored in an `AnimatedSprite` class which has it's own transform. When drawing the `AnimatedSprite` to the screen the transform will be combined with the backing sprite. So no one using this class would ever notice the rotation applied while loading the texture.

[1]: https://jesse-m.itch.io/skeleton-pack
[2]: https://github.com/Seng3694/TexturePacker
[3]: https://cdn.discordapp.com/attachments/425728769236664350/428706719062032386/atlas.png
[4]: http://www.1001fonts.com/arcadeclassic-font.html
[5]: https://cdn.discordapp.com/attachments/425728769236664350/428711346540904478/skeleton_animation.gif
[6]: https://github.com/nlohmann/json

## License ##

- [Textures from Jesse M.][1]
- [Font from Pizzadude][4]
- [Json library from Niels Lohmann][6]