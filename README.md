LHCOAnalysis
============

LHCOAnalysis implements a lhco file reader.

Requirements
------------
* cmake to compile
* c++11 compatible compiler (g++4.6 support of c++11 is sufficient)

Usage
-----
###Compile
* download sources
* create a build directory

    mkdir build && cd build

* use cmake to generate makefiles

    cmake ..

* use make to generate ./LHCOAnalysis in src/

    make


###Usage
* supply a file

    ./LHCOAnalysis 2 file.lhco

* read lhco events from stdin

    cat file.lhco | ./LHCOAnalysis 2
    
  This is useful to read compressed lhco files generated by MadGraph
  
    zcat file.lhco.gz | ./LHCOAnalysis 2
    
