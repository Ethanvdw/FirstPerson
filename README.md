# Raycasting Project

This project is a simple implementation of raycasting in C++. Raycasting is a rendering technique to create a 3D perspective in a 2D map. We shoot rays from the player to every direction in player's field of view and check what walls they hit. This is used to render a 3D view of the map.

## Prerequisites

Before you begin, ensure you have met the following requirements:

- You have installed the latest version of [Meson](https://mesonbuild.com/Getting-meson.html)

## Building and Running the Project

To build and run the project, follow these steps:

1. Clone the repository:
```bash
git clone https://github.com/Ethanvdw/FirstPerson.git
cd First Person
```

2. Create and navigate to your build directory
```bash
meson setup builddir
cd builddir
```

3. Build and run the project
```bash
meson compile
meson run
```
