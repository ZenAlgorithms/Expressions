# Expressions

## Build

```shell
git clone git@github.com:ZenAlgorithms/Expressions.git
cd Expressions
cmake .
make
make install
```

## Usage

```c++
#include <expression/expression.hpp>

using namespace std;

auto it = expression::from_string("/api/servers/{server}/status");

auto result = it->query("/api/servers/production/status");

cout << result->matches() << endl;
// 1

cout << result->bindings()->at("server") << endl;
// production
```