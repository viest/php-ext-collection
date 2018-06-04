--TEST--
Check Collection operations
--SKIPIF--
<?php if (!extension_loaded("collection")) print "skip"; ?>
--FILE--
<?php 
$collection = \Vtiful\Kernel\Collection::init([
    'color' => 'orange',
    'type' => 'fruit',
    'remain' => 6
]);

$diff = $collection->diffAssoc([
    'color' => 'yellow',
    'type' => 'fruit',
    'remain' => 3,
    'used' => 6
]);

var_dump($diff);
?>
--EXPECT--
object(Vtiful\Kernel\Collection)#2 (2) {
  ["color"]=>
  string(6) "orange"
  ["remain"]=>
  int(6)
}
