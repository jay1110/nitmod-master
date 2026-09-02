// Static name/kind audit only. Never instantiates a module or executes engine JS.
const fs = require('fs');
const crypto = require('crypto');

function classifyImports(imports, exports, runtimeSource = '') {
  const available = new Map(exports.map(entry => [entry.name, entry.kind]));
  return imports.map(entry => {
    let resolution = 'not-found-in-inspected-providers';
    if (entry.module === 'env' && entry.kind === 'global' &&
        ['__memory_base', '__table_base'].includes(entry.name)) {
      resolution = 'dynamic-loader-convention';
    } else if (entry.module === 'env' && available.get(entry.name) === entry.kind) {
      resolution = 'engine-export-name-and-kind';
    } else if (entry.kind === 'global' &&
        ((entry.module === 'GOT.mem' && available.get(entry.name) === 'global') ||
         (entry.module === 'GOT.func' && available.get(entry.name) === 'function'))) {
      resolution = 'engine-symbol-via-loader-got';
    } else if (entry.module === 'env' && entry.kind === 'function' && entry.name === '__assert_fail' &&
        /function\s+___assert_fail\s*\(/.test(runtimeSource) &&
        /\b__assert_fail\s*:\s*___assert_fail\b/.test(runtimeSource)) {
      resolution = 'javascript-binding-candidate';
    }
    return {...entry, resolution};
  });
}

function describe(path) {
  const bytes = fs.readFileSync(path);
  return {path, sha256: crypto.createHash('sha256').update(bytes).digest('hex'), bytes};
}

function audit(enginePath, runtimePath, modulePaths) {
  const engine = describe(enginePath);
  const runtime = describe(runtimePath);
  const exports = WebAssembly.Module.exports(new WebAssembly.Module(engine.bytes));
  return {
    schema_version: 1, instantiated: false, full_abi_verified: false,
    engine: {path: engine.path, sha256: engine.sha256},
    runtime: {path: runtime.path, sha256: runtime.sha256},
    modules: modulePaths.map(path => {
      const input = describe(path);
      const imports = WebAssembly.Module.imports(new WebAssembly.Module(input.bytes));
      return {path, sha256: input.sha256, imports: classifyImports(imports, exports, runtime.bytes.toString('utf8'))};
    })
  };
}

module.exports = {classifyImports, audit};
if (require.main === module) {
  const [engine, runtime, ...modules] = process.argv.slice(2);
  if (!engine || !runtime || !modules.length) {
    console.error('usage: node audit_wasm_imports.cjs <engine.wasm> <engine.js> <side-module> [...]');
    process.exitCode = 1;
  } else {
    console.log(JSON.stringify(audit(engine, runtime, modules), null, 2));
  }
}
