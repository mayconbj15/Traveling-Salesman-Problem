pushd src

$files = $(ls algorithms/*.cpp -name | foreach{echo algorithms\$_})

g++ -o main.exe `
    -std=c++11 `
    -I algorithms $files `
    main.cpp TSP.cpp graph.cpp
popd