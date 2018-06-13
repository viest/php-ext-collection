<?php

$collection1 = \Vtiful\Kernel\Collection::init(['name', 'age']);

$result1 = $collection1->concat(['address'])->concat([12])->concat([
    'obj' => new \stdClass()
]);

var_dump($result1);