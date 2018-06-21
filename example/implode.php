<?php

$collection1 = \Vtiful\Kernel\Collection::init([
    1, 'a'
]);

$result1 = $collection1->implode('-');

var_dump($result1);

$collection2 = \Vtiful\Kernel\Collection::init([
    ['name' => 'viest', 'age' => 21],
    ['name' => 'vikin', 'age' => 20],
    ['name' => 'wjx',   'age' => 22],
]);

$result2 = $collection2->implode('name', '-');

var_dump($result2);