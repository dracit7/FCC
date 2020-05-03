
## HUST PL Labs

本仓库为华中科技大学编译原理实验代码。

- `inc`: 存放了一些全局的头文件。
- `lib`: 存放的所有的库文件。
- `bin`: 存放编译好的二进制文件。
- `obj`: 存放中间文件。
- `tests`: 存放用于测试的输入文件。

### Lab 1

Lab 1的功能可以由下面的make指令来进行检查：

```bash
make test SHOW_TUPLES=1
make test SHOW_AST=1
```

前者展示所有的词法元素二元组，后者展示抽象语法树。

如果要单独测试某个输入文件，请将相应的输入文件放在`tests`文件夹下，并执行`make test-xxx SHOW_XXX=1`，其中`xxx`是输入文件的文件名去掉扩展名之后的结果，如`make test-array SHOW_TUPLES=1`。