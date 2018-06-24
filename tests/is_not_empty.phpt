--TEST--
Check Collection operations
--SKIPIF--
<?php if (!extension_loaded("collection")) print "skip"; ?>
--FILE--
<?php 
$collection1 = \Vtiful\Kernel\Collection::init([1]);

$false = $collection1->isNotEmpty();

$collection2 = \Vtiful\Kernel\Collection::init([]);

$true = $collection2->isNotEmpty();

var_dump($false, $true);
?>
--EXPECT--
bool(false)
bool(true)