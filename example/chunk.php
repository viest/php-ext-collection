<?php

$collection = \Vtiful\Kernel\Collection::init([
    1, 2, 3, 4, 5
]);

$result = $collection->chunk(4);

var_dump($result);