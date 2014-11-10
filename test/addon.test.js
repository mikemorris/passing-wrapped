'use strict';

/* jshint node:true */

var test = require('tape');
var addon = require('../addon.js');

test('addon', function(t) {
    var obj1 = addon.createObject(10);
    var obj2 = addon.createObject(20);
    var result = addon.add(obj1, obj2);

    t.equal(result, 30);
    t.end();
});
