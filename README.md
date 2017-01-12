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

#### Documention

wikin:[https://github.com/VikinDev/v-collect/wiki](https://github.com/VikinDev/v-collect/wiki)

## License

MIT