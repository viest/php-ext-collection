--TEST--
Check Collection operations
--SKIPIF--
<?php if (!extension_loaded("collection")) print "skip"; ?>
--FILE--
<?php 
$collection = \Vtiful\Kernel\Collection::init(['name', 'age']);
$result     = $collection->concat(['address'])->concat([12])->concat([
    'obj' => new \stdClass()
]);

var_dump($result);
?>
--EXPECT--
object(Vtiful\Kernel\Collection)#4 (5) {
  [0]=>
  string(4) "name"
  [1]=>
  string(3) "age"
  [2]=>
  string(7) "address"
  [3]=>
  int(12)
  [4]=>
  object(stdClass)#2 (0) {
  }
}
