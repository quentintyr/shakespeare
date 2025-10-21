# FRC Robot Code for Austria Skills

### Clone the repo with submodules

```
git clone --recurse-submodules https://github.com/quentintyr/shakespeare.git 
```

## Web-ds Submodule
```
git submodule add https://github.com/quentintyr/web-ds.git src/main/deploy/web-ds

```

## Web-ds-logger Submodule
```
git submodule add https://github.com/quentintyr/web-ds-logger.git src/main/deploy/web-ds-logger
```

### Inlcude the LoggingSystem to work with Web-ds
First update paths to gradle in build.gradle

```
sources.cpp {
                source {
                    srcDirs 'src/main/cpp', 'src/main/deploy/web-ds-logger/src'
                    include '**/*.cpp', '**/*.cc'
                }
                exportedHeaders {
                    srcDirs = [
                        'src/main/include',
                        'src/main/deploy'
                    ]

                    if (includeSrcInIncludeRoot) {
                        srcDirs += 'src/main/cpp'
                    }
                }
            }
```

Then add the includes to the files
```
#include "web-ds-logger/src/LoggingSystem.h"
```
