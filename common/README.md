`option.h`提供了方便的参数解析功能，具体使用方法，参考`test-option.cpp`。


## a. 选项使用说明：
1. 选项可以没有短选项名，但是长选项名必须有。
2. 非bool类型长选项必须是`--option=value`的形式。
3. bool类型的长选项必须是`--option`。
4. bool类型短选项可以合并使用，类似于`ls -al`，合并后的最后一个短选项可以是带值的选项，后接值，中间空格隔开。
5. 非bool类型的短选项不能合并使用。


## b. 选项值限制，
非bool类型选项，可支持如下两种限制：
1. 范围限制。
比如：
```
// 长选项`tabsize`，不是必须，默认为`8`，取值必须在 4 - 16 之间
opts.Add<int>("tabsize", 't', "assume tab stops at each COLS instead of 8", false, 8, option::RangeRestrict<int>(4, 16));
```
2. 固定集合限制。
比如：
```
// 长选项`color`，没有对应的短选项，不是必须，默认为`auto`
std::set<std::string> s = {"never", "auto", "always"};
opts.Add<std::string>("color", '\0', "colorize the output; WHEN can be 'never', 'auto', or 'always' (the default); more info below", false, "auto", option::OneOfRestrict<std::string>(s));
```
