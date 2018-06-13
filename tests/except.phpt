--TEST--
Check Collection operations
--SKIPIF--
<?php if (!extension_loaded("collection")) print "skip"; ?>
--FILE--
<?php 
$collection = \Vtiful\Kernel\Collection::init([
    'product_id' => 1,
    'price' => 100,
    'discount' => false
]);

$filtered = $collection->except([
    'price',
    'discount'
]);

var_dump($filtered);
?>
--EXPECT--
object(Vtiful\Kernel\Collection)#2 (1) {
  ["product_id"]=>
  int(1)
}
