--TEST--
Check Collection operations
--SKIPIF--
<?php if (!extension_loaded("collection")) print "skip"; ?>
--FILE--
<?php 
$collection1 = \Vtiful\Kernel\Collection::init([1]);

$true = $collection1->isEmpty();

$collection2 = \Vtiful\Kernel\Collection::init([]);

$false = $collection2->isEmpty();

var_dump($true, $false);
?>
--EXPECT--
bool(true)
bool(false)
