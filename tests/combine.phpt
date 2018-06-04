--TEST--
Check Collection operations
--SKIPIF--
<?php if (!extension_loaded("collection")) print "skip"; ?>
--FILE--
<?php 
$collection = \Vtiful\Kernel\Collection::init(['name', 'age']);
$result     = $collection->combine(['George', 29]);

var_dump($result);
?>
--EXPECT--
object(Vtiful\Kernel\Collection)#2 (2) {
  ["name"]=>
  string(6) "George"
  ["age"]=>
  int(29)
}
