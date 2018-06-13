<?php

$collection1 = \Vtiful\Kernel\Collection::init([
    'name' => 'viest',
    'languages' => [
        'php', 'c'
    ]
]);

$flattened = $collection1->flatten();

var_dump($flattened);

$collection2 = \Vtiful\Kernel\Collection::init([
    'Apple' => [
        ['name' => 'iPhone 6S', 'brand' => 'Apple'],
    ],
    'Samsung' => [
        ['name' => 'Galaxy S7', 'brand' => 'Samsung']
    ],
]);

$products = $collection2->flatten(2);

var_dump($products);