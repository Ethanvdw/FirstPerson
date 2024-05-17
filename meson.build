project('FirstPerson', 'cpp',
        version : '1.0.0',
        default_options : ['warning_level=3', 'cpp_std=c++20'])

sdl2_dep = dependency('sdl2')

FirstPerson = executable('FirstPerson', 'main.cpp', install : true,
dependencies : sdl2_dep)



test('test', FirstPerson)