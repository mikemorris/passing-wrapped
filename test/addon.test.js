'use strict';

/* jshint node:true */

var test = require('tape');
var addon = require('../addon.js');

test('addon', function(t) {
  var obj1 = new addon.MyObject();
  obj1.set(10);

  var obj2 = new addon.MyObject();
  obj2.set(20);

  addon.add(obj1, obj2, function(err, result) {
    t.ifError(err);
    t.equal(result, 30);
    t.end();
  });
});
