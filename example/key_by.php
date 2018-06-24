<?php

$collection1 = \Vtiful\Kernel\Collection::init([
    ['product_id' => 'prod-100', 'name' => 'Desk'],
    ['product_id' => 'prod-200', 'name' => 'Chair'],
]);

$keyed1 = $collection1->keyBy('product_id');

$collection2 = \Vtiful\Kernel\Collection::init([
    ['product_id' => 'prod-100', 'name' => 'Desk'],
    ['product_id' => 'prod-200', 'name' => 'Chair'],
]);

$keyed2 = $collection2->keyBy(function ($item) {
    return strtoupper($item['product_id']);
});

var_dump($keyed1, $keyed2);