--TEST--
Check Collection operations
--SKIPIF--
<?php if (!extension_loaded("collection")) print "skip"; ?>
--FILE--
<?php 
$collection = \Vtiful\Kernel\Collection::init([1, 2, 3, 4]);

$result = $collection->every(function ($value, $key) {
    return $value > 0;
});

var_dump($result);
?>
--EXPECT--
bool(true)
