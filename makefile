Game:
	
	gcc main.c -lSDL2 -lSDL2_image -lSDL2_mixer -lm -lpthread -ldl -lrt -lX11
	./a.out

Web:
	emcc -DWEB main.c -oindex.html -g -lm --bind -s USE_SDL=2 -s USE_SDL_MIXER=2 -s USE_SDL_IMAGE=2 -s MIN_WEBGL_VERSION=2 -s MAX_WEBGL_VERSION=2 -s SDL2_IMAGE_FORMATS='["png"]' --preload-file Resources/ --use-preload-plugins
	#emcc -DWEB main.c -o index.html -g -lm --bind -s USE_SDL=2  -s USE_SDL_MIXER=2 -s USE_SDL_IMAGE=2 -s SDL2_IMAGE_FORMATS='["png"]' --preload-file Resources/ --use-preload-plugins

	rm index.html
	cp shell index.html
	emrun index.html
