include (module type of Idb_IndexStoreShared);

let name: t => string;
let keyPath: t => Js.Json.t;
let indexNames: t => array(string);
let autoIncrement: t => bool;

let put: (t, ~value: 'value, ~key: 'key=?, unit) => Js.Promise.t(unit);
let add: (t, ~value: 'value, ~key: 'key=?, unit) => Js.Promise.t(unit);
let delete: (t, 'key) => Js.Promise.t(unit);
let clear: t => Js.Promise.t(unit);
let deleteIndex: (t, string) => unit;
let createIndex:
  (
    t,
    string,
    ~keyPath: [ | `String(string) | `Strings(array(string))]=?,
    ~unique: bool=?,
    ~multiEntry: bool=?,
    unit
  ) =>
  Idb_Index.t;
let index: (t, string) => Idb_Index.t;