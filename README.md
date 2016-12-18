![](https://github.com/VikinDev/v-collect/blob/master/image/cover.jpg)

## 介绍：
`vcollect` 是一个PHP c extension，提供流畅、便利的数组数据操作。

*******

## 安装：

#### 1、Clone

定位于PHP下的ext目录，执行
```bash
git clone https://github.com/VikinDev/v-collect.git
```

#### 2、编译安装

在扩展目录内，执行
```bash
phpize
./configure
make && make install
```

#### 3、修改ini

在php.ini文件中加入`extension = vcollect.so`

## 使用

#### 创建集合

```php
$test = vcollect([1, 2, 3, 4, 5, 6]);
```

#### 可用方法

******
|^_^ |^_^ |^_^ |^_^ |^_^ |^_^ |^_^ |^_^ |^_^ |^_^ |
|:--:|:--:|:--:|:--:|:--:|:--:|:--:|:--:|:--:|:--:|
|[map](#map)|[collapse](#collapse)|[avg](#avg)|[has](#has)|[mx](#mx)|[mi](#mi)|[toJson](#tojson)|[toArray](#toarray)|[take](#take)|[pluck](#pluck)|
|||||||||||

******

#### map
遍历整个集合，并将key于val数值传入至回调函数；并且可以在回调函数中return来修改值；
```php
$vcollect = vcollect([1, 2, 3, 4]);
$vcollect->map(function($key, $value) {
    return $key+$value;
    });
//[1, 3, 5, 7]
```

#### collapse
将集合转换为一维数组

```php
$vcollect = vcollect([1, 2, [3, 4]]);
$vcollect->collapse();
```
你将得到：
```php
[1, 2, 3, 4]
```

#### avg
##### 1、返回集合中所有项的平均值
```php
$vcollect = vcollect([1, 2, 3, 4, 5]);
$vcollect->avg();
```
您将得到一个整型或浮点型结果
```php
(int)3
```
##### 2、当然你也可以通过传递`键`来计算平均值
```php
$vcollect = vcollect([
        ['a'=>4],
        ['a'=>6],
        8   
    ]);
$vcollect->avg('a');
```
您将得到一个整型或浮点型结果
```php
(int)5
```

#### has
检查集合中是否含有指定的键
```php
$vcollect = vcollect(['account_id' => 1, 'product' => 'Desk']);

$vcollect->has('email');

// false
```

#### mx
返回集合中的最大值
```php
$vcollect = vcollect([1,2,3,4,5]);

$vcollect->mx();

//(int)5
```
你也可以通过传入`键值`来获取指定键的最大值
```php
$vcollect = vcollect([
        ['a'=>1.1],
        ['a'=>4],
        ['a'=>8]
    ]
);
$vcollect->mx('a');

//(int)8
```

#### mi
返回集合中的最小值
```php
$vcollect = vcollect([1,2,3,4,5]);

$vcollect->mi();

//(int)1
```
你也可以通过传入`键值`来获取指定键的最小值
```php
$vcollect = vcollect([
        ['a'=>1.1],
        ['a'=>4],
        ['a'=>8]
    ]
);
$vcollect->mi('a');

//(float)1.1
```

#### toJson
将集合进行JSON编码
```php
$vcollect = vcollect([
        'a'=>4,
        [1, 'a'=>2, 3],
        [4, [ 5, 'a'=>6 ]]
    ]);

$vcollect->toJson();

//(string)'{"a":4,"0":{"0":1,"a":2,"1":3},"1":[4,{"0":5,"a":6}]}'
```

#### toArray
将集合结果转换为数组
```php
$vcollect = vcollect([
        'a'=>4,
        [1, 'a'=>2, 3],
        [4, [ 5, 'a'=>6 ]]
    ]);

$vcollect->collapse()->toArray();

//结果：
//array (size=6)
//  0 => int 4
//  1 => int 1
//  2 => int 2
//  3 => int 3
//  4 => int 4
//  5 => 
//    array (size=2)
//     0 => int 5
//     'a' => int 6
```

#### take
获取指定数量的集合
```php
$vcollect = vcollect([1,2,3,4,5]);

$vcollect->take(1)->toArray();

//(array)[1]
```
也可以通过传入负数从集合后面获取指定数量的集合
```php
$vcollect->take(-2)->toArray();

//(array)[4, 5]
```

#### pluck
快速获取多层集合中指定「键」所有对应的值：
```php
$vcollect = vcollect([
    ['developer' => ['name' => 'Taylor'], 'id' => 2],
    ['developer' => ['name' => 'Abigail'], 'id' => 5]
]);

$vcollect->pluck('developer.name');

//['Taylor', 'Abigail']
```
你也可以指定结果集的键
```php
$vcollect->pluck('developer.name', 'id');

//[2=>'Taylor', 5=>'Abigail']
```