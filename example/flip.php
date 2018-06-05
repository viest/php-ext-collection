<?php

$collection = \Vtiful\Kernel\Collection::init([
    'name' => 'taylor',
    'framework' => 'laravel'
]);

$flipped = $collection->flip();

var_dump($flipped);