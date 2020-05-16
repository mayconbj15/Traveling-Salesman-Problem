pushd src

$files = $(Get-ChildItem algorithms/*.cpp -name | foreach {
    echo "algorithms/$_"
})

g++ -g -o main.exe `
    -std=c++14 `
    -I algorithms $files `
    main.cpp TSP.cpp graph.cpp

popd
