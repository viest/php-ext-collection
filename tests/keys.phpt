--TEST--
Check Collection operations
--SKIPIF--
<?php if (!extension_loaded("collection")) print "skip"; ?>
--FILE--
<?php 
$collection = \Vtiful\Kernel\Collection::init([
    'prod-100' => ['product_id' => 'prod-100', 'name' => 'Desk'],
    'prod-200' => ['product_id' => 'prod-200', 'name' => 'Chair'],
]);

$keys = $collection->keys();

var_dump($keys);
?>
--EXPECT--
object(Vtiful\Kernel\Collection)#2 (2) {
  [0]=>
  string(8) "prod-100"
  [1]=>
  string(8) "prod-200"
}
