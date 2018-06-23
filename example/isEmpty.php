<?php

$collection1 = \Vtiful\Kernel\Collection::init([1]);

$true = $collection1->isEmpty();

$collection2 = \Vtiful\Kernel\Collection::init([]);

$false = $collection2->isEmpty();

var_dump($true, $false);