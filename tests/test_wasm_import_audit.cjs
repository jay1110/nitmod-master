const assert = require('assert');
const {classifyImports} = require('../tools/audit_wasm_imports.cjs');
const exportsList = [{name: 'sin', kind: 'function'}, {name: 'stdout', kind: 'global'}];
const check = (module, name, kind, source = '') =>
  classifyImports([{module, name, kind}], exportsList, source)[0].resolution;
assert.equal(check('env', 'sin', 'function'), 'engine-export-name-and-kind');
assert.equal(check('env', 'sin', 'global'), 'not-found-in-inspected-providers');
assert.equal(check('other', 'sin', 'function'), 'not-found-in-inspected-providers');
assert.equal(check('env', '__memory_base', 'global'), 'dynamic-loader-convention');
assert.equal(check('env', '__table_base', 'function'), 'not-found-in-inspected-providers');
assert.equal(check('GOT.mem', 'stdout', 'global'), 'engine-symbol-via-loader-got');
assert.equal(check('GOT.func', 'sin', 'global'), 'engine-symbol-via-loader-got');
assert.equal(check('env', '__assert_fail', 'function', 'function ___assert_fail(){}'), 'not-found-in-inspected-providers');
assert.equal(check('env', '__assert_fail', 'function', 'function ___assert_fail(){}; const a={__assert_fail:___assert_fail};'), 'javascript-binding-candidate');
console.log('WASM import classification: 9 cases passed (no instantiation)');
