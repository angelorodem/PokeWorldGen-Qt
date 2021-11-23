
# Pokemon Procedural World Generation
Procedural map generation for pokemon using C++ and Qt 

this algorithm creates a height map based on simplex noise using [FastNoise](https://github.com/Auburns/FastNoise) and then filter out non valid spots, and finishes by laying textures over the resulting tiles using a ruleset.
<p align="center">
<img src="https://github.com/angelorodem/PokeWorldGen-Qt/blob/master/images/tiles.png?raw=true" alt="Tiled map" width="400" height="400">
  </p>

The current algorithm gives good results for maps with a maximum of 8 height levels, higher values cause bad-looking maps because the tile rules do not support multiple height edges.

The noise and the tiles maps differ because when there is not the best tile for a cell, it gets flattened, and the adjacent cells are rescanned. 

Logical Tileset map generated only from height map and tile "rules".

<p align="center">
<img src="https://github.com/angelorodem/PokeWorldGen-Qt/blob/master/images/terrain_tiles.png?raw=true" alt="Logical map" width="400" height="400">
  </p>

Colors in the borders of each elevation represent a tile like "Grassy Left Corner tile" which is used to generate the final map.

<p align="center">
<img src="https://github.com/angelorodem/PokeWorldGen-Qt/blob/master/images/corner.PNG?raw=true" alt="Height map" width="100" height="100">
  </p>

Terrain heightmap used to generate the base map, some noises are filtered when generating the tilemap.

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
