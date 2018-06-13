--TEST--
Check Collection operations
--SKIPIF--
<?php if (!extension_loaded("collection")) print "skip"; ?>
--FILE--
<?php 
$collection = \Vtiful\Kernel\Collection::init([1, 2, 3, 4, 5]);
$result = $collection->diff([2, 4, 6, 8]);
var_dump($result);
?>
--EXPECT--
object(Vtiful\Kernel\Collection)#2 (3) {
  [0]=>
  int(1)
  [2]=>
  int(3)
  [4]=>
  int(5)
}
