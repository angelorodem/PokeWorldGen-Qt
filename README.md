# Pokemon Procedural World Generation
Procedural map generation for pokemon using C++ and Qt

Well, this actually don't generate a pokemon world yet, it procedurally spawns some colorfull squares following some "tileset rule", wich specify what kind of tile of a given tileset should be used in a specific place.

It currently generates 3 maps, a terrain height map, the temperature distribution map, and a rain distribution map.

Tileset map, generated only from height map and later it will use temperature and rain to form biomes and influence tiles types.

![Terrain tiles](https://github.com/angelorodem/PokeWorldGen-Qt/blob/master/images/terrain_tiles.png?raw=true)

These strange colors in the borders of each elevation represents a tile like "Grassy Left Corner Plato tile" (Like the next image) which will be used to generate the actual map.

![Tile example](https://github.com/angelorodem/PokeWorldGen-Qt/blob/master/images/corner.PNG?raw=true)

Terrain height map, used to generate the base map, some noises are filtered when generating the tile map.

![Height map](https://github.com/angelorodem/PokeWorldGen-Qt/blob/master/images/terrain_height.png?raw=true)

Temperature map, not used yet, but will influence biome distribution.

![TEMPERATURE](https://github.com/angelorodem/PokeWorldGen-Qt/blob/master/images/temperature.png?raw=true)

Rain map, not used yet, but will influence biome distribution.

![RAIN](https://github.com/angelorodem/PokeWorldGen-Qt/blob/master/images/rain.png?raw=true)
 



