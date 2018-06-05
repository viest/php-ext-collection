<?php

$collection1 = \Vtiful\Kernel\Collection::init([
    1, 2, 3, 4, 5
]);

$result1 = $collection1->avg();

var_dump($result1);

$collection2 = \Vtiful\Kernel\Collection::init([
    ['name' => 'vikin', 'age' => 20],
    ['name' => 'viest', 'age' => 30]
]);

$result2 = $collection2->avg('age');

var_dump($result2);