build:
	gcc -o main softsim/main.c softsim/globaldata.c softsim/initializer.c softsim/running.c softsim/timing.c -lm -O3 -Wall -Wextra -Wshadow -pedantic
build_debug:
	gcc -o main softsim/main.c softsim/globaldata.c softsim/initializer.c softsim/running.c softsim/timing.c -lm -O0 -g -Wall -Wextra -Wshadow -pedantic
build_visualization:
	g++ -o visualization softplot/main.cpp softplot/drawing.cpp softplot/globaldata.cpp -lm -O3 -lGL -lGLU -lglut -Wall -Wextra -Wshadow -Wnon-virtual-dtor -pedantic
build_visualization_debug:
	g++ -o visualization softplot/main.cpp softplot/drawing.cpp softplot/globaldata.cpp -lm -O3 -g -lGL -lGLU -lglut -Wall -Wextra -Wshadow -Wnon-virtual-dtor -pedantic
run:
	./main
run_visualization:
	./visualization