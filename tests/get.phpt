--TEST--
Check Collection operations
--SKIPIF--
<?php if (!extension_loaded("collection")) print "skip"; ?>
--FILE--
<?php 
$collection = \Vtiful\Kernel\Collection::init([
    'name'      => 'viest',
    'extension' => 'collection',
]);

$name = $collection->get('name');
$null = $collection->get('age');
$age  = $collection->get('age', 22);

var_dump($name, $null, $age);
?>
--EXPECT--
string(5) "viest"
NULL
int(22)
