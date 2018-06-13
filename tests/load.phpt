--TEST--
Check for collection presence
--SKIPIF--
<?php if (!extension_loaded("collection")) print "skip"; ?>
--FILE--
<?php 
echo "collection extension is available";
?>
--EXPECT--
collection extension is available
