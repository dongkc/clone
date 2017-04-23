# Clone
Clone is a multi-part download manager using HTTP in C++.

## What
Clone is a download manager which uses multiple threads to download single file in parts 
and merge them into single file. 

## Building

Make sure you have CMake and boost libraries installed.

```
mkdir build
cd build
cmake -D CMAKE_BUILD_TYPE=Debug ../
make
```

You can find binaries in `$CLONE_ROOT_PATH/bin` directory.

## Run

After building you can find binaries in `$CLONE_ROOT_PATH/bin`.
```
./Clone <URL>
```

## To Do

* Handle HTTP response status code 301 Moved Permanently
* Make download faster
* Add support to download multiple files

## Thanks To

* [johnstok](http://stackoverflow.com/users/27929/johnstok) for [this](http://stackoverflow.com/questions/8293687/sample-http-range-request-session)
