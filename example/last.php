<?php

$collection = \Vtiful\Kernel\Collection::init([1, 2, 3, 4]);

$callbackLast = $collection->last(function ($value, $key) {
    return $value < 3;
});

$defaultLast = $collection->last();


var_dump($callbackLast, $defaultLast);