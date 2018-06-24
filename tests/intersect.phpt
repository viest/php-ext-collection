--TEST--
Check Collection operations
--SKIPIF--
<?php if (!extension_loaded("collection")) print "skip"; ?>
--FILE--
<?php 
$collection = \Vtiful\Kernel\Collection::init([1, 2, 3, 4, 5, 'a']);

$intersect = $collection->intersect([2, 7, 5, 9, 10, 'b']);

var_dump($intersect->toArray());
?>
--EXPECT--
array(2) {
  [0]=>
  int(2)
  [1]=>
  int(5)
}
