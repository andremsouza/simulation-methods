build_opt_none:
	g++ -o opt_none/main opt_none/main.cpp opt_none/simulation.cpp -std=c++17 -O3 -Wall -Wextra -Wshadow -Wnon-virtual-dtor -pedantic
build_opt_none_debug:
	g++ -g -o opt_none/main opt_none/main.cpp opt_none/simulation.cpp -std=c++17 -O3 -Wall -Wextra -Wshadow -Wnon-virtual-dtor -pedantic
run_opt_none:
	./opt_none/main
build_visualization:
	g++ -o visualization/main visualization/main.cpp visualization/drawing.cpp visualization/globaldata.cpp -lGL -lGLU -lglut -Wall -Wextra -Wshadow -Wnon-virtual-dtor -pedantic
build_visualization_debug:
	g++ -g -o visualization/main visualization/main.cpp visualization/drawing.cpp visualization/globaldata.cpp -lGL -lGLU -lglut -Wall -Wextra -Wshadow -Wnon-virtual-dtor -pedantic
run_visualization:
	./visualization/main
