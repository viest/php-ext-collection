<?php

$collection = \Vtiful\Kernel\Collection::init([
    'product_id' => 1,
    'price'      => 100,
    'discount'   => false,
]);

$filtered = $collection->except([
    'price',
    'discount',
]);

var_dump($filtered);