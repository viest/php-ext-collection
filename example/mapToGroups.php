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

var_dump($grouped->toArray());