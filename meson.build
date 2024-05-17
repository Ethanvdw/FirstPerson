project('FirstPerson', 'cpp',
        version : '1.0.0',
        default_options : ['warning_level=3', 'cpp_std=c++20'])

sdl2_dep = dependency('sdl2')

sources = files('src/main.cpp', 'src/Player.cpp', 'src/Raycaster.cpp', 'src/Map.cpp')

FirstPerson = executable('FirstPerson', sources, install : true,
dependencies : sdl2_dep)



test('test', FirstPerson)