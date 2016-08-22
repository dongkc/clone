# Clone
Clone is a multi-part download manager using HTTP in C++.

##What
Clone is a download manager which uses multiple threads to download single file in parts 
and merge them into single file. 

##Building

Make sure you have CMake to build the project and boost libraries for code. If not, install it by

```
sudo apt-get install cmake
sudo apt-get install libboost-all-dev
```

Follow below steps to build the project.
```
mkdir build
cd build
cmake -D CMAKE_BUILD_TYPE=Debug ../
make
```

You can find binaries in `$CLONE_ROOT_PATH/bin` directory.

##Run

You can find binaries in `$CLONE_ROOT_PATH/bin`.
Run the program as example given below
```
./Clone <URL>
```

##To Do

* Handle HTTP response status code 301 Moved Permanently
* Make download faster
* Add support to download multiple files

##Thanks To

* [johnstok](http://stackoverflow.com/users/27929/johnstok) for [this](http://stackoverflow.com/questions/8293687/sample-http-range-request-session)
