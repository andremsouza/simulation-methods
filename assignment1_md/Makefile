build_opt_none:
	g++ -o opt_none/main opt_none/main.cpp opt_none/simulation.cpp -std=c++17 -O3 -Wall -Wextra -Wshadow -Wnon-virtual-dtor -pedantic
build_opt_none_debug:
	g++ -g -o opt_none/main opt_none/main.cpp opt_none/simulation.cpp -std=c++17 -O3 -Wall -Wextra -Wshadow -Wnon-virtual-dtor -pedantic
build_opt_verlet:
	g++ -o opt_verlet/main opt_verlet/main.cpp opt_verlet/simulation.cpp -std=c++17 -O3 -Wall -Wextra -Wshadow -Wnon-virtual-dtor -pedantic
build_opt_verlet_debug:
	g++ -g -o opt_verlet/main opt_verlet/main.cpp opt_verlet/simulation.cpp -std=c++17 -O3 -Wall -Wextra -Wshadow -Wnon-virtual-dtor -pedantic
build_opt_verlet_tabulated:
	g++ -o opt_verlet_tabulated/main opt_verlet_tabulated/main.cpp opt_verlet_tabulated/simulation.cpp -std=c++17 -O3 -Wall -Wextra -Wshadow -Wnon-virtual-dtor -pedantic
build_opt_verlet_tabulated_debug:
	g++ -g -o opt_verlet_tabulated/main opt_verlet_tabulated/main.cpp opt_verlet_tabulated/simulation.cpp -std=c++17 -O3 -Wall -Wextra -Wshadow -Wnon-virtual-dtor -pedantic
run_opt_none:
	./opt_none/main $(ARGS)
run_opt_none_default:
	./opt_none/main true 800
run_opt_verlet:
	./opt_verlet/main $(ARGS)
run_opt_verlet_default:
	./opt_verlet/main true 800
run_opt_verlet_tabulated:
	./opt_verlet_tabulated/main $(ARGS)
run_opt_verlet_tabulated_default:
	./opt_verlet_tabulated/main true 800
build_visualization:
	g++ -o visualization/main visualization/main.cpp visualization/drawing.cpp visualization/globaldata.cpp -lGL -lGLU -lglut -Wall -Wextra -Wshadow -Wnon-virtual-dtor -pedantic
build_visualization_debug:
	g++ -g -o visualization/main visualization/main.cpp visualization/drawing.cpp visualization/globaldata.cpp -lGL -lGLU -lglut -Wall -Wextra -Wshadow -Wnon-virtual-dtor -pedantic
run_visualization:
	./visualization/main
