<?php

$collection1 = \Vtiful\Kernel\Collection::init([
    1, [2, [3, 4]]
]);

$result1 = $collection1->collapse();

var_dump($result1);

var_dump($result1->count());
var_dump($result1->toArray());