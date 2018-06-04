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

$flipped = $collection->flip();

var_dump($flipped);
?>
--EXPECT--
object(Vtiful\Kernel\Collection)#2 (2) {
  ["viest"]=>
  string(4) "name"
  ["collection"]=>
  string(9) "extension"
}
