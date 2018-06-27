--TEST--
Check Collection operations
--SKIPIF--
<?php if (!extension_loaded("collection")) print "skip"; ?>
--FILE--
<?php 
$collection1 = \Vtiful\Kernel\Collection::init([1, 6, 2, 3, 4, 5]);

$default = $collection1->max();

$collection2 = \Vtiful\Kernel\Collection::init([
    ['foo' => 10],
    ['foo' => 50],
    ['foo' => 20],
]);

$defaultKey = $collection2->max('foo');

var_dump($default, $defaultKey);
?>
--EXPECT--
int(6)
int(50)