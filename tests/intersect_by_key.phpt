--TEST--
Check Collection operations
--SKIPIF--
<?php if (!extension_loaded("collection")) print "skip"; ?>
--FILE--
<?php 
$collection = \Vtiful\Kernel\Collection::init([
    'serial' => 'UX301', 'type' => 'screen', 'year' => 2009
]);

$intersect = $collection->intersectByKeys([
    'reference' => 'UX404', 'type' => 'tab', 'year' => 2011
]);

var_dump($intersect);
?>
--EXPECT--
object(Vtiful\Kernel\Collection)#2 (2) {
  ["type"]=>
  string(6) "screen"
  ["year"]=>
  int(2009)
}
