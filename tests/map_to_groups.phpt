--TEST--
Check Collection operations
--SKIPIF--
<?php if (!extension_loaded("collection")) print "skip"; ?>
--FILE--
<?php 
$collection = \Vtiful\Kernel\Collection::init([
    [
        'name' => 'John Doe',
        'department' => 'Sales',
    ],[
        'name' => 'Jane Doe',
        'department' => 'Sales',
    ],[
        'name' => 'Johnny Doe',
        'department' => 'Marketing',
    ]
]);

$grouped = $collection->mapToGroups(function ($item, $key) {
    return [$item['department'] => $item['name']];
});

var_dump($grouped);
?>
--EXPECT--
object(Vtiful\Kernel\Collection)#3 (2) {
  ["Sales"]=>
  array(2) {
    [0]=>
    string(8) "John Doe"
    [1]=>
    string(8) "Jane Doe"
  }
  ["Marketing"]=>
  array(1) {
    [0]=>
    string(10) "Johnny Doe"
  }
}
