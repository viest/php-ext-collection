<?php

$collection = \Vtiful\Kernel\Collection::init([
    1, 2, 3, 4
]);

$collbackRes = $collection->first(function ($value, $key) {
    return $value > 2;
});

$noCollback = $collection->first();

var_dump($collbackRes);
var_dump($noCollback);
