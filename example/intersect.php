<?php

$collection = \Vtiful\Kernel\Collection::init([1, 2, 3, 4, 5, 'a']);

$intersect = $collection->intersect([2, 7, 5, 9, 10, 'b']);

var_dump($intersect->toArray());