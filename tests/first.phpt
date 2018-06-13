--TEST--
Check Collection operations
--SKIPIF--
<?php if (!extension_loaded("collection")) print "skip"; ?>
--FILE--
<?php 
$collection = \Vtiful\Kernel\Collection::init([
    1, 2, 3, 4
]);

$collbackRes = $collection->first(function ($value, $key) {
    return $value > 2;
});

$noCollback = $collection->first();

var_dump($collbackRes);
var_dump($noCollback);
?>
--EXPECT--
int(3)
int(1)
