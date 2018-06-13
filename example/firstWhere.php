<?php

$collection = \Vtiful\Kernel\Collection::init([
    ['name' => 'Regena', 'age' => 12],
    ['name' => 'Linda', 'age' => 14],
    ['name' => 'Diego', 'age' => 23],
    ['name' => 'Linda', 'age' => 84],
]);

$result1 = $collection->firstWhere('name', 'Linda');
$result2 = $collection->firstWhere('age', '>=', 18);

var_dump($result1);
var_dump($result2);