<?php

$collection = \Vtiful\Kernel\Collection::init([
    1, 2, 3, 4, 5, 6, 7, 8, 9
]);

$chunk = $collection->forPage(2, 3);

var_dump($chunk);