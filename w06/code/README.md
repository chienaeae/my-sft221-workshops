## Development

### Initial

```bash
git submodule update --init --recursive

./vcpkg/bootstrap-vcpkg.sh

./vcpkg/vcpkg install
```

### Git Hooks

It is suggested to install git hook for style linting before code committing. This project is configured
with [pre-commit](https://pre-commit.com).

Installation steps:

```bash
pre-commit install --install-hooks -t commit-msg -t pre-commit
```

### clang-format

This project utilizes the tool `clang-format` to automatically format the code in a consistent and readable
manner. `clang-format` is a powerful tool that uses predefined styles or can be customized via a configuration file (
.clang-format) in the project root directory.

Install on macOS

```bash
brew install clang-format
```

Format the specified file

```bash
clang-format -i <your_file>

# or you can format the whole project with the command below
find src test include -name "*.cpp" -o -name "*.h" | xargs clang-format -i
```

### clang-tidy

`clang-tidy` is a clang-based C++ "linter" tool that provides an extensible framework for diagnosing and fixing typical
programming errors. It's an essential tool in this project that helps maintain the code quality.

Install on macOS:

```bash
brew install llvm
```

**Recommend** Use the command to heck the specified file with compile_commands.json, which is generated after
running `cmake`:

```
clang-tidy -p <build_folder_include_compile_commands.json> <your_file.cpp>
```

Also, you can use the command below to check the whole project:

```bash
python3 run-clang-tidy.py -p <build_folder_include_compile_commands.json>
```
> To see more details about `run-clang-tidy.py`, https://clang.llvm.org/extra/doxygen/run-clang-tidy_8py.html
>
> You can apply `-f` as the command below to auto fix:
> ```angular2html
> python3 run-clang-tidy.py -fix -p <build_folder_include_compile_commands.json>
> ```
**Alternative Method:** If `compile_commands.json` is not available or cannot be generated, you can still
use `clang-tidy` to check a specific file. Note that in this case, we are assuming that your `include` directory is in
your current working directory.
```
clang-tidy <your_file.cpp> -- -Iinclude
```

### Debug

```bash
cmake --preset=debug .

cmake --build debug

./debug/main
```

### Release

```bash
cmake --preset=release .

cmake --build release

./release/main
```
