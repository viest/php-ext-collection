<?php

$collection1 = \Vtiful\Kernel\Collection::init([
    1, 2, 3, 4, 5,
]);

$result1 = $collection1->all();

var_dump($result1);