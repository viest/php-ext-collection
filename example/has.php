<?php

$collection = \Vtiful\Kernel\Collection::init([
    'name' => 'viest',
    'age'  => 21
]);

$true  = $collection->has('age');
$false = $collection->has('address');

var_dump($true, $false);