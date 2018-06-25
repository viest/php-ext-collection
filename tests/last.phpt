--TEST--
Check Collection operations
--SKIPIF--
<?php if (!extension_loaded("collection")) print "skip"; ?>
--FILE--
<?php 
$collection = \Vtiful\Kernel\Collection::init([1, 2, 3, 4]);

$callbackLast = $collection->last(function ($value, $key) {
    return $value < 3;
});

$defaultLast = $collection->last();

var_dump($callbackLast, $defaultLast);
?>
--EXPECT--
int(2)
int(4)
