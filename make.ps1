pushd src
g++ -o main.exe `
    -std=c++11 `
    -I algorithms algorithms/*.cpp `
    main.cpp TSP.cpp graph.cpp
popd
