# Data storage for scene and assets

## Scene

.fwsc (Firework Scene)

### HEADER

The 24-byte header contains

| Type      | Name         |
| --------- | ------------ |
| char[4]   | magic        |
| uint32    | version      |
| uint32    | size         |
| uint32    | module_count |
| uint32[2] | reserved     |

`magic` The magic number '0x46575343' (FWSC in ascii)
`version` Version of Firework scene the file is saved at
`size` The size in bytes of the file, including the header
`module_count` The total amount of 'Modules' in the file

### Modules

| Type        | Name    |
| ----------- | ------- |
| uint32      | type    |
| uint32      | size    |
| ubyte[size] | data    |
| padding     | padding |

`type` The type of data
`size` The size of the data array
`data` The binary data of the module

#### Module types

| HEX        | ASCII | Desciption of binary data                 |
| ---------- | ----- | ----------------------------------------- |
| 0x46574142 | FWAB  | Path to an asset bundle used by the scene |
| 0x004f424a | OBJ   | The objects in the scene                  |
|            |       |                                           |

#### Asset bundle

The asset bundle location. Example:
`data/Scene1Bundle.fwab`

#### Objects

Consists of sevel paths, inside the asset bunde in the following format:

| Type           | Name         |
| -------------- | ------------ |
| uint32         | pathlen      |
| uint32         | proplen      |
| char[strlen]   | path         |
| ubyte[proplen] | object_props |

`pathlen` the length of the path inside bundle
`proplen` the length of the binay data inside the bundle
`path` a string to a asset bunde and a path inside
Example string:
`Scene1Bundle:objects/test`
`object_props` the object properties(transform etc)

## Assets

.fwab (Firework Asset Bundle)

### HEADER

The 24-byte header contains

| Type         | Name        |
| ------------ | ----------- |
| char[4]      | magic       |
| uint32       | version     |
| uint32       | size        |
| uint32       | asset_count |
| uint32       | length      |
| char[length] | name        |
| uint32[2]    | reserved    |

`magic` The magic number '0x46574142' (FWAB in ascii)
`version` Version of Firework assets the file is saved as
`size` The size in bytes of the file, including the header
`asset_count` The total amount of assets in the file
`lenght` lenght of the name
`name` the name of the bundle

### Assets

| Type           | Name     |
| -------------- | -------- |
| uint32         | type     |
| uint32         | size     |
| uint32         | name_len |
| char[name_len] | name     |
| ubyte[size]    | data     |
| padding        | padding  |

`type` The type of data
`size` The size of the data array
`data` The binary data of the asset

#### Module types

| HEX        | ASCII | Desciption of binary data    |
| ---------- | ----- | ---------------------------- |
| 0x00424c50 | BLP   | A Blueprint (Premade object) |
| 0x4d455348 | MESH  | A Mesh                       |
| 0x004d4154 | MAT   | A Material                   |
| 0x00544558 | TEX   | A Texture                    |
| 0x53435054 | SCPT  | A Script                     |
| 0x53435054 | SHDR  | A Shader                     |
|            |       |                              |

#### Blueprint

A recipe to create an object

| Type                  | Name            |
| --------------------- | --------------- |
| uint32                | component_count |
| uint32                | component_size  |
| ubyte[component_size] | components      |

##### Components

| Type                   | Name           |
| ---------------------- | -------------- |
| uint32                 | type           |
| uint32                 | size           |
| uint32                 | name_len       |
| char[name_len]         | name           |
| ubyte[size - name_len] | component_data |

#### Mesh

A mesh encoded like this

| Type                   | Name            |
| ---------------------- | --------------- |
| uint32                 | mesh_data_size  |
| uint32                 | index_data_size |
| ubyte[mesh_data_size]  | mesh_data       |
| ubyte[index_data_size] | index_data      |

The mesh data consits of an array of Vertices that contain a position, normals(normalized) and uvs as single precision float encoded values.

Example vertex:

| Position       | Normal         | uv         |
| -------------- | -------------- | ---------- |
| 1.0, 0.4, 0.33 | 1.0, -1.0, 1.0 | 0.44, 0.33 |

The index data is a 'formula' to create a mesh from the vertex data.

#### Material

#### Texture

#### Script

#### Shader
