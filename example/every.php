<?php

$collection = \Vtiful\Kernel\Collection::init([
    1, 2, 3, 4
]);

$result = $collection->every(function ($value, $key) {
    return $value > 0;
});

var_dump($result);