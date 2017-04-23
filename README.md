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

## References

* [Sample http range request session](http://stackoverflow.com/a/8507991)
