--TEST--
Check Collection operations
--SKIPIF--
<?php if (!extension_loaded("collection")) print "skip"; ?>
--FILE--
<?php
$collection1 = \Vtiful\Kernel\Collection::init([1, 2, 3, 4, 5]);
$result1     = $collection1->avg();
$collection2 = \Vtiful\Kernel\Collection::init([
    ['name' => 'vikin', 'age' => 20],
    ['name' => 'viest', 'age' => 30]
]);
$result2 = $collection2->avg('age');

var_dump($result1);
var_dump($result2);
?>
--EXPECT--
float(3)
float(25)
