<?php

$collection1 = \Vtiful\Kernel\Collection::init([1, 6, 2, 3, 4, 5]);

$default = $collection1->max();

var_dump($default);

$collection2 = \Vtiful\Kernel\Collection::init([
    ['foo' => 10],
    ['foo' => 50],
    ['foo' => 20],
]);

$defaultKey = $collection2->max('foo');

var_dump($defaultKey);