--TEST--
Check Collection operations
--SKIPIF--
<?php if (!extension_loaded("collection")) print "skip"; ?>
--FILE--
<?php 
$collection = \Vtiful\Kernel\Collection::init([
    'name' => 'viest',
    'extension' => 'collection'
]);

$result = $collection->forget('name');

var_dump($result);
?>
--EXPECT--
object(Vtiful\Kernel\Collection)#1 (1) {
  ["extension"]=>
  string(10) "collection"
}



