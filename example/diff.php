<?php

$collection = \Vtiful\Kernel\Collection::init([
    1, 2, 3, 4, 5
]);

$result = $collection->diff([
    2, 4, 6, 8
]);

var_dump($result);