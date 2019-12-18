build_perk:
	g++ -o perkolacio/main perkolacio/main.cpp -std=c++17 -O3 -Wall -Wextra -Wshadow -pedantic
build_fractal:
	g++ -o dla_fraktal/main dla_fraktal/main.cpp -std=c++17 -lm -O3 -Wall -Wextra -Wshadow -pedantic
build_visualization_fractal:
	g++ -o softplot_fractal/main softplot_fractal/main.cpp softplot_fractal/drawing.cpp softplot_fractal/globaldata.cpp -std=c++17 -lm -O3 -lGL -lGLU -lglut -Wall -Wextra -Wshadow -Wnon-virtual-dtor -pedantic
build_visualization_perk:
	g++ -o softplot_perk/main softplot_perk/main.cpp softplot_perk/drawing.cpp softplot_perk/globaldata.cpp -std=c++17 -lm -O3 -lGL -lGLU -lglut -Wall -Wextra -Wshadow -Wnon-virtual-dtor -pedantic
run_perk:
	./perkolacio/main
run_fractal:
	./dla_fraktal/main
run_visualization_perk:
	./softplot_perk/main
run_visualization_fractal:
	./softplot_fractal/main