
# Pokemon Procedural World Generation
Procedural map generation for pokemon using C++ and Qt 

Well, this actually don't generate a pokemon world yet, it creates a height map based on simplex noise using [FastNoise](https://github.com/Auburns/FastNoise) lib and filter out non valid spots using rules, then it lays textures over the resulting tiles, this texture is customizable for every avaible tile.
<p align="center">
<img src="https://github.com/angelorodem/PokeWorldGen-Qt/blob/master/images/tiles.png?raw=true" alt="Tiled map" width="400" height="400">
  </p>

The current algorithm gives good results for maps with maximum of 8 height levels, after that it gets kinda weird.

The noise map and the tiles map differs from each other, this is because when there is not a known the best tile for a certain cell, it gets flattened, and the adjacent cells are reanalyzed, this may occur a lot of times for a single adjustment. 

Logical Tileset map, generated only from height map and tile "rules".

<p align="center">
<img src="https://github.com/angelorodem/PokeWorldGen-Qt/blob/master/images/terrain_tiles.png?raw=true" alt="Logical map" width="400" height="400">
  </p>

These strange colors in the borders of each elevation represents a tile like "Grassy Left Corner tile" (Like the next image) which will be used to generate the actual map.

<p align="center">
<img src="https://github.com/angelorodem/PokeWorldGen-Qt/blob/master/images/corner.PNG?raw=true" alt="Height map" width="100" height="100">
  </p>

Terrain height map, used to generate the base map, some noises are filtered when generating the tile map.

<p align="center">
<img src="https://github.com/angelorodem/PokeWorldGen-Qt/blob/master/images/terrain_height.png?raw=true" alt="Height map" width="400" height="400">
</p>

Temperature map, not used yet, but will influence biome distribution.
<p align="center">
<img src="https://github.com/angelorodem/PokeWorldGen-Qt/blob/master/images/temperature.png?raw=true" alt="Temp map" width="400" height="400">
  </p>

Rain map, not used yet, but will influence biome distribution.
<p align="center">
<img src="https://github.com/angelorodem/PokeWorldGen-Qt/blob/master/images/rain.png?raw=true" alt="Rain map" width="400" height="400">
<p/>



