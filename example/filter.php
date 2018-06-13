<?php

// 传递了回调函数
$collection1 = \Vtiful\Kernel\Collection::init([
    1, 2, 3, 4
]);

$callbackRes = $collection1->filter(function ($value, $key) {
    return $value > 2;
});

var_dump($callbackRes);


// 没有传递回调函数
$collection2 = \Vtiful\Kernel\Collection::init([
    1, 2, 3, null, false, '', 0, []
]);

$noCallback = $collection2->filter();

var_dump($noCallback);