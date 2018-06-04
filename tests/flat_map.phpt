--TEST--
Check Collection operations
--SKIPIF--
<?php if (!extension_loaded("collection")) print "skip"; ?>
--FILE--
<?php 
$collection = \Vtiful\Kernel\Collection::init([
    ['name' => 'Sally'],
    ['school' => 'Arkansas'],
    ['age' => 28]
]);

$flattened = $collection->flatMap(function ($values) {
    return array_map('strtoupper', $values);
});

var_dump($flattened);
?>
--EXPECT--
object(Vtiful\Kernel\Collection)#3 (3) {
  [0]=>
  array(1) {
    ["name"]=>
    string(5) "SALLY"
  }
  [1]=>
  array(1) {
    ["school"]=>
    string(8) "ARKANSAS"
  }
  [2]=>
  array(1) {
    ["age"]=>
    string(2) "28"
  }
}
