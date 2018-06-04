--TEST--
Check Collection operations
--SKIPIF--
<?php if (!extension_loaded("collection")) print "skip"; ?>
--FILE--
<?php 
$collection = \Vtiful\Kernel\Collection::init([1, 2, 3, 4, 5]);
$result = $collection->count();
var_dump($result);
?>
--EXPECT--
int(5)
