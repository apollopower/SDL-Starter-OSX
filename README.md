#SDL2 Starter Framework - OSX

### Template with starter code for games/graphics programming using C++ & SDL, WITHOUT xcode 

This framework is composed of two (seperate) libraries of SDL, that are commonly used together:
- SDL2
- SDL2_image

All header files and lib files are properly allocated into their respective directories.

## Quick Start

Inside the repository, compile by calling the makefile:

```
make game
```

Now the ```play``` executable should be created. Run it like so:

```
./play
```

Your C++ program using SDL2 should now run!

## SDL Setup from Scratch

If needed for new projects, you can always do the setup without this framework. Make sure that you have SDL2 and SDL2_image
installed on your machine. You can use Homebrew:

```
brew install sdl2
brew install sdl2_image
```

In your new project, you will need to copy over the header and lib files from the sdl2 directories into
the ```include``` and ```lib``` folders.