<?php

$collection = \Vtiful\Kernel\Collection::init([1, 2, 3, 4, 5]);

$multiplied = $collection->map(function ($item, $key) {
    return $item * 2;
});

var_dump($multiplied);