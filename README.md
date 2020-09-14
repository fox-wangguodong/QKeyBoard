# QKeyBoard

# 使用说明

将Keyboard目录下的.h和.cpp添加到工程目录下，在需要支持虚拟键盘的窗口的构造函数和析构函数添加如下代码

``` 构造函数
    KeyboardInstaller::installObject(this);
```

``` 析构函数
    KeyboardInstaller::removeObject(this);
```

# 问题
若输入中文时不显示汉字，需要将py.db数据库文件放到可执行文件目录下
