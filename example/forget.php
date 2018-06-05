<?php

$collection = \Vtiful\Kernel\Collection::init([
    'name' => 'viest',
    'extension' => 'collection'
]);

$result = $collection->forget('name');

var_dump($result);