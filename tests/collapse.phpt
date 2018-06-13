--TEST--
Check Collection operations
--SKIPIF--
<?php if (!extension_loaded("collection")) print "skip"; ?>
--FILE--
<?php 
$collection = \Vtiful\Kernel\Collection::init([
    1, [2, [3, 4]]
]);

$result = $collection->collapse();

var_dump($result);
?>
--EXPECT--
object(Vtiful\Kernel\Collection)#2 (4) {
  [0]=>
  int(1)
  [1]=>
  int(2)
  [2]=>
  int(3)
  [3]=>
  int(4)
}
