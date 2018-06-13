<?php

$collection1 = \Vtiful\Kernel\Collection::init(['name', 'age']);

$result1 = $collection1->combine(['George', 29]);

var_dump($result1);