# Expressions

## Build

```shell
git clone git@github.com:ZenAlgorithms/Expressions.git
cd Expressions
mkdir build
cd build
cmake ..
make
make install
```

## Usage

```c++
#include <expressions/container.hpp>

using namespace std;

auto _container = expressions::container::from_string("/api/servers/{server}/status");

auto _result = _container->query("/api/servers/production/status");

cout << _result->matches() << endl;
// 1

cout << _result->bindings()->at("server") << endl;
// production
```

See more [examples](https://github.com/ZenAlgorithms/Expressions/blob/master/tests/implementation_test.cc) ...