<?php

$collection = \Vtiful\Kernel\Collection::init([
    'name'      => 'viest',
    'extension' => 'collection',
]);

$name = $collection->get('name');
$null = $collection->get('age');
$age  = $collection->get('age', 22);

var_dump($name, $null, $age);