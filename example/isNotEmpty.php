<?php

$collection1 = \Vtiful\Kernel\Collection::init([1]);

$false = $collection1->isNotEmpty();

$collection2 = \Vtiful\Kernel\Collection::init([]);

$true = $collection2->isNotEmpty();

var_dump($false, $true);